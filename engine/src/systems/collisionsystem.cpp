#include "engine/systems/collisionsystem.h"
#include "engine/util/transformer.h"
#include <cmath>
#include <unordered_map>
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <sstream>
#include <iostream>

CollisionSystem::CollisionSystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects) {
}


glm::vec3 CollisionSystem::calculateCentroid(std::vector<glm::vec3>& vertices) {
	glm::vec3 centroid(0, 0, 0);
	for (glm::vec3 vertex : vertices) {
		centroid.x += vertex.x;
		centroid.y += vertex.y;
		centroid.z += vertex.z;
	}
	centroid.x /= vertices.size();
	centroid.y /= vertices.size();
	centroid.z /= vertices.size();
	return centroid;
}


CollisionSystem::CollisionInfo CollisionSystem::findSeparation(
	std::vector<glm::vec3>& verticesA, std::vector<glm::vec3>& verticesB, float rot)
{
	CollisionInfo collisionInfo(true);
	collisionInfo.centroidA = calculateCentroid(verticesA);
	collisionInfo.centroidB = calculateCentroid(verticesB);

	float mostAlignedNormal = -std::numeric_limits<float>::max();

	int j = verticesA.size() - 1;
	for (int i = 0; i < verticesA.size(); ++i) {
		glm::vec3 vertex1 = verticesA[i];
		glm::vec3 vertex2 = verticesA[j];
		glm::vec3 edge = vertex2 - vertex1;
		float z = -1;
		if (rot != 0) z = 1;
		glm::vec3 zvec(0, 0, z);
		glm::vec3 normal = glm::cross(edge, zvec);
		glm::vec3 vecToCentroid = collisionInfo.centroidB - vertex1;

		float dotVecToCentroidAndNormal = glm::dot(normal, vecToCentroid);
		float smallestDp = std::numeric_limits<float>::max();

		for (int j = 0; j < verticesB.size(); ++j) {
			glm::vec3 vertexB = verticesB[j];
			glm::vec3 vecToB = vertexB - vertex1;
			float dp = glm::dot(vecToB, normal);
			if (dp < smallestDp) {
				smallestDp = dp;
			}

			if (dp <= 0 && dotVecToCentroidAndNormal > mostAlignedNormal) {
				mostAlignedNormal = dotVecToCentroidAndNormal;
				collisionInfo.collisionNormal = normal;
				collisionInfo.separation = smallestDp;
				collisionInfo.edgePoints = std::vector<glm::vec3>();
				collisionInfo.edgePoints.push_back(vertex1);
				collisionInfo.edgePoints.push_back(vertex2);
				setCollisionPoints(collisionInfo, vertex1, vertex2, verticesB, normal);
			}

		}
		if (smallestDp > 0) {
			collisionInfo.collides = false;
			break;
		}
		j = i;
	}
	return collisionInfo;
}

bool CollisionSystem::checkCollisionUsingBoundingVolumes(glm::vec3 posA, glm::vec3 boxA, glm::vec3 posB, glm::vec3 boxB) {
	float distX = glm::abs(posA.x - posB.x);
	float distY = glm::abs(posA.y - posB.y);
	float xx = boxA.x / 2 + boxB.x / 2;
	float yy = boxA.y / 2 + boxB.y / 2;
	if (distX < xx && distY < yy) {
		return true;
	}
	//return false;
	return true;
}

CollisionSystem::CollisionInfo CollisionSystem::checkCollisionUsingSAT(GameObject* object1, GameObject* object2
	, std::unordered_map<int, std::vector<glm::vec3>>& transformedVertices) {
	std::vector<glm::vec3>vertices1 = transformedVertices[object1->getId()];
	std::vector<glm::vec3>vertices2 = transformedVertices[object2->getId()];
	float rot1 = object1->getTransformComponent()->rotation.y;
	float rot2 = object2->getTransformComponent()->rotation.y;
	CollisionInfo collisionA = findSeparation(vertices1, vertices2, rot1);
	CollisionInfo collisionB = findSeparation(vertices2, vertices1, rot2);
	if (!collisionA.collides) return collisionA;
	else if (!collisionB.collides) return collisionB;
	else {
		glm::vec3 mov1 = object1->getVelocityComponent().linearVelocity;
		glm::vec3 mov2 = object2->getVelocityComponent().linearVelocity;

		if (glm::distance(collisionA.edgePoints[0],collisionA.edgePoints[1])
			> glm::distance(collisionB.edgePoints[0],collisionB.edgePoints[1] )) {
			collisionA.objectA = object1;
			collisionA.objectB = object2;
			return collisionA;
		}
		else {
			collisionB.objectA = object2;
			collisionB.objectB = object1;
			return collisionB;
		}
	}
}

void CollisionSystem::setCollisionPoints(CollisionInfo& collisionInfo, glm::vec3& vertex1, glm::vec3& vertex2, std::vector<glm::vec3>& verticesB, glm::vec3& normal) {

	collisionInfo.collisionPoints = std::vector<glm::vec3>();

	for (glm::vec3 vertexB : verticesB) {
		glm::vec3 v1ToB = vertexB - vertex1;
		float normalAndVertex = glm::dot(v1ToB, normal);
		if (normalAndVertex <= 0) {
			glm::vec3 v2ToB = vertexB - vertex2;
			glm::vec3 BToV1 = vertex1 - vertexB;
			glm::vec3 BToV2 = vertex2 - vertexB;
			glm::vec3 v2ToV1 = vertex1 - vertex2;
			glm::vec3 v1ToV2 = vertex2 - vertex1;
			float onEdgeScalarB = glm::dot(v1ToB, v2ToB);
			float onEdgeScalarV1 = glm::dot(v2ToV1, BToV1);
			float onEdgeScalarV2 = glm::dot(v1ToV2, BToV2);
			if (onEdgeScalarB <= 0)
				collisionInfo.collisionPoints.push_back(vertexB);
			else if (onEdgeScalarV1 < 0)
				collisionInfo.collisionPoints.push_back(vertex1);
			else if (onEdgeScalarV2 < 0)
				collisionInfo.collisionPoints.push_back(vertex2);
		}
	}

	// old logic tht i don't think mkes any snse
	//if (collisionInfo.collisionPoints.size() > 0) {
	//	float distToCentroid = glm::distance(collisionInfo.collisionPoints[0], collisionInfo.centroidB);
	//	float v1ToCentroid = glm::distance(vertex1, collisionInfo.centroidB);
	//	float v2ToCentroid = glm::distance(vertex2, collisionInfo.centroidB);

	//	if (v1ToCentroid < distToCentroid) {
	//		collisionInfo.collisionPoints.push_back(vertex1);
	//	}
	//	else if (v2ToCentroid < distToCentroid) {
	//		collisionInfo.collisionPoints.push_back(vertex2);
	//	}
	//}

}

glm::vec3 CollisionSystem::calculateRotationalVelocity(glm::vec3 rotation, glm::vec3 angleVector) {
	glm::vec3 zvector(0, 0, rotation.z);
	return glm::cross(angleVector, zvector);
}

bool CollisionSystem::isRotatingTowards(glm::vec3 normal, glm::vec3 rotVec) {
	float dot = glm::dot(normal, rotVec);
	return dot < 0;
}


void CollisionSystem::addEnergyLoss(glm::vec3& vec, const glm::vec3& normal, float retention) {
	glm::vec3 n = glm::normalize(normal) * (1 - retention);
	vec -= glm::dot(vec, n) * n;
}

void CollisionSystem::addCollisionEnergy(CollisionObjectInfo& collisionObjectInfo, float retention) {
	glm::vec3 collisionDirection = glm::normalize(collisionObjectInfo.velocityAfterCollision);
	glm::vec3 projectionVelocity = glm::dot(collisionObjectInfo.obj->getVelocityComponent().linearVelocity, collisionDirection) * collisionDirection;
	//float lengthOfToAddVector = std::abs(glm::length(projectionVelocity) - glm::length(collisionInfo2.velocity1));
	float lengthOfToAddVector = glm::distance(projectionVelocity, collisionObjectInfo.velocityAfterCollision);
	glm::vec3 toAddVector = collisionDirection * lengthOfToAddVector;
	addEnergyLoss(toAddVector, collisionObjectInfo.normal, retention);
	collisionObjectInfo.obj->getVelocityComponent().linearVelocity += toAddVector;
}

bool CollisionSystem::haveOppositeSigns(float x, float y) {
	int signX = std::signbit(x);
	int signY = std::signbit(y);
	return signX != signY;
}

void CollisionSystem::setVelocities(CollisionObjectInfo& collisionObjectInfo) {
	if (glm::length(collisionObjectInfo.velocityAfterCollision) == 0) {
		return;
	}

	const float ENERGY_RETENTION = collisionObjectInfo.obj->getPhysicsComponent().elasticity;
	glm::vec3 collisionToCentroid = collisionObjectInfo.collisionPoint - collisionObjectInfo.centroid;
	float projectionLength = glm::dot(collisionToCentroid, collisionObjectInfo.velocityAfterCollision) / glm::length(collisionObjectInfo.velocityAfterCollision);
	glm::vec3 projection = glm::normalize(collisionObjectInfo.velocityAfterCollision) * projectionLength;

	glm::vec3 edge = glm::cross(collisionObjectInfo.normal, glm::vec3(0, 0, 1));
	float dot = glm::dot(edge, collisionToCentroid);
	int offsetDirection = dot / std::abs(dot);
	float c = glm::length(collisionToCentroid);
	float a = glm::length(projection);
	float forceOffset = std::sqrt(c * c - a * a) * offsetDirection;

	if (collisionObjectInfo.rotates && collisionObjectInfo.obj->getPhysicsComponent().rotates) {
		float r = glm::length(collisionToCentroid);
		float rot = (glm::length(collisionObjectInfo.velocityAfterCollision) / forceOffset) * ENERGY_RETENTION;
		collisionObjectInfo.obj->getVelocityComponent().rotation.z = rot;
		if (haveOppositeSigns(rot, collisionObjectInfo.obj->getVelocityComponent().rotation.z)) {
			addCollisionEnergy(collisionObjectInfo, ENERGY_RETENTION);
		}
	}
	else {
		addCollisionEnergy(collisionObjectInfo, ENERGY_RETENTION);
	}

}

glm::vec3 CollisionSystem::combineWithRotation(glm::vec3& objLinearVelocity, glm::vec3& objRotation, CollisionInfo& collisionInfo, glm::vec3 centroid) {
	glm::vec3 collisionPointAngleVector = glm::normalize(collisionInfo.centroidB - centroid);
	glm::vec3 rotVec = calculateRotationalVelocity(objRotation, collisionPointAngleVector);

	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);
	glm::vec3 rotVecProjection = glm::dot(normal, rotVec) * normal;

	glm::vec3 velocityRotationAdded = rotVecProjection + objLinearVelocity;
	return velocityRotationAdded;
}


CollisionSystem::SpeedsAfterCollision CollisionSystem::calculateCollisionVelocities(
	float m1, float m2, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal)
{
	glm::vec3 n = glm::normalize(normal);
	glm::vec3 v1n = glm::dot(v1, n) * n;
	glm::vec3 v2n = glm::dot(v2, n) * n;

	//u1 = v1m1 + v2m2 - v1m2 + v2m2 / (m1 + m2)
	glm::vec3 v1f = (v1n*m1 + v2n*m2 - v1n*m2 + v2*m2) / (m1 + m2);
	//u2 = v1 + u1 - v2
	glm::vec3 v2f = v1n + v1f - v2n;

	return SpeedsAfterCollision(glm::length(v1f), glm::length(v2f));
}


CollisionSystem::DirectionsAfterCollision CollisionSystem::calculateDirections(CollisionInfo& collisionInfo) {
	//glm::vec3 vA = collisionInfo.objectA->getVelocity().velocity;
	//glm::vec3 vB = collisionInfo.objectB->getVelocity().velocity;
	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);

	//	glm::vec3 mirrorVectorB = calculateMirrorVec(normal, -vB);
	//	glm::vec3 mirrorVectorA = calculateMirrorVec(normal, -vA);
	//
	//	if (glm::length(mirrorVectorA) <= 0) {
	//		mirrorVectorA = -normal;
	//	}
	//	if (glm::length(mirrorVectorB) <= 0) {
	//		mirrorVectorB = normal;
	//	}

	glm::vec3 mirrorVectorA = -normal;
	glm::vec3 mirrorVectorB = normal;

	return DirectionsAfterCollision(mirrorVectorA, mirrorVectorB);
}

void CollisionSystem::setForces(CollisionInfo& collisionInfo) {
	if (collisionInfo.collisionPoints.size() == 0) {
		return;
	}

	glm::vec3 edgeA = collisionInfo.edgePoints[1] - collisionInfo.edgePoints[0];

	GameObject* objA = collisionInfo.objectA;
	GameObject* objB = collisionInfo.objectB;

	//	if (glm::dot(objB->getVelocity().velocity, collisionInfo.collisionNormal) > 1) return;

	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);
	glm::vec3 collisionPointCentroid = calculateCentroid(collisionInfo.collisionPoints);

	glm::vec3 velocityRotationAddedA = combineWithRotation(
		objA->getVelocityComponent().linearVelocity, 
		objA->getVelocityComponent().rotation, 
		collisionInfo, 
		collisionPointCentroid
	);
	glm::vec3 velocityRotationAddedB = combineWithRotation(
		objB->getVelocityComponent().linearVelocity, 
		objB->getVelocityComponent().rotation, 
		collisionInfo, 
		collisionPointCentroid
	);

	SpeedsAfterCollision speedsAfterCollision = calculateCollisionVelocities(
		objA->getPhysicsComponent().mass,
		objB->getPhysicsComponent().mass,
		velocityRotationAddedA,
		velocityRotationAddedB,
		collisionInfo.collisionNormal
	);

	DirectionsAfterCollision directionsAfterCollision = calculateDirections(collisionInfo);


	glm::vec3 collisionVecA(0, 0, 0);
	if (glm::length(directionsAfterCollision.vecA) > 0)
		collisionVecA = glm::normalize(directionsAfterCollision.vecA) * speedsAfterCollision.v1;
	glm::vec3 collisionVecB(0, 0, 0);
	if (glm::length(directionsAfterCollision.vecB) > 0)
		collisionVecB = glm::normalize(directionsAfterCollision.vecB) * speedsAfterCollision.v2;

	float totalFriction = objA->getPhysicsComponent().friction * objB->getPhysicsComponent().friction;

	bool rotates = false;
	if (collisionInfo.collisionPoints.size() < 2) {
		rotates = true;
	}

	CollisionObjectInfo collisionA{
		objA,
		collisionPointCentroid,
		collisionVecA,
		collisionInfo.centroidA,
		-normal,
		rotates,
		totalFriction
	};


	CollisionObjectInfo collisionB{
		objB,
		collisionPointCentroid,
		collisionVecB,
		collisionInfo.centroidB,
		normal,
		rotates,
		totalFriction
	};

	setVelocities(collisionA);
	setVelocities(collisionB);

}

std::unordered_map<int, std::vector<glm::vec3>> CollisionSystem::transformVertices() {
	std::unordered_map<int, std::vector<glm::vec3>>map;
	for (GameObject* object : gameObjects) {
		if (!object->getPhysicsComponent().collidable) continue;
		map[object->getId()] = std::vector<glm::vec3>();
		glm::mat4 modelMatrix = transformer.getModelMatrix(object->getTransformComponent());
		std::vector<float>vertices = object->getMeshComponent()->getVertices();
		std::unordered_map<std::string, bool>memo;

		for (int i = 0; i < vertices.size(); i += 3) {
			glm::vec4 vertex(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);
			std::ostringstream oss;
			oss << vertex.x << vertex.y << vertex.z;
			if (memo.find(oss.str()) == memo.end()) {
				memo[oss.str()] = true;
			}
			else {
				continue;
			}
			map[object->getId()].push_back(modelMatrix * vertex);
		}
	}
	return map;
}

void CollisionSystem::createCollisionPoints(std::unordered_map<int, std::vector<CollisionPoint>>& collisionMap, CollisionInfo& info)
{
	for (const auto& cp : info.collisionPoints) {

		glm::vec3 velocityRotationAddedA = combineWithRotation(
			info.objectA->getVelocityComponent().linearVelocity,
			info.objectA->getVelocityComponent().rotation,
			info,
			cp
		);
		glm::vec3 velocityRotationAddedB = combineWithRotation(
			info.objectB->getVelocityComponent().linearVelocity,
			info.objectB->getVelocityComponent().rotation,
			info,
			cp
		);

		SpeedsAfterCollision speedsAfterCollision = calculateCollisionVelocities(
			info.objectA->getPhysicsComponent().mass,
			info.objectB->getPhysicsComponent().mass,
			velocityRotationAddedA,
			velocityRotationAddedB,
			info.collisionNormal
		);

		const glm::vec3 normal = glm::normalize(info.collisionNormal);

		const CollisionPoint collisionPointA(
			cp,
			-normal * speedsAfterCollision.v1,
			info.centroidA
		);
		const CollisionPoint collisionPointB(
			cp,
			normal * speedsAfterCollision.v2,
			info.centroidB
		);

		collisionMap[info.objectA->getId()].push_back(collisionPointA);
		collisionMap[info.objectB->getId()].push_back(collisionPointB);
	}

}


void CollisionSystem::setGameObjectsVelocityAfterCollision(glm::vec3& linearVelocity, glm::vec3& rotation, std::vector<CollisionPoint>& collisionPoints)
{
	glm::vec3 rotationalVecToAdd(0, 0, 0);

	for (int i = 0; i < collisionPoints.size(); ++i) {

		CollisionPoint& cpA = collisionPoints[i];
		glm::vec3 aToCentroid = cpA.centroid - cpA.pos;
		glm::vec3 crossVec = glm::normalize(glm::cross(cpA.velocity, glm::vec3(0, 0, 1)));

		glm::vec3 projectedCentroid = glm::dot(crossVec, aToCentroid) * crossVec;
		float radius = glm::length(projectedCentroid);
		bool aCausesClockwiseRotation = glm::dot(aToCentroid, crossVec) < 0;

		if (aCausesClockwiseRotation) {
			rotationalVecToAdd += glm::vec3(0, 0, glm::length(cpA.velocity)/radius);
		}
		else {
			rotationalVecToAdd -= glm::vec3(0, 0, glm::length(cpA.velocity)/radius);
		}

	}
	rotation.z = rotationalVecToAdd.z;

	for (int i = 0; i < collisionPoints.size(); ++i) {

		const CollisionPoint& cpA = collisionPoints[i];
		glm::vec3 aToCentroid = cpA.centroid - cpA.pos;
		glm::vec3 crossVec = glm::normalize(glm::cross(cpA.velocity, glm::vec3(0, 0, 1)));
		bool aCausesClockwiseRotation = glm::dot(aToCentroid, crossVec) < 0;

		glm::vec3 velANormalized(0, 0, 0);
		if(glm::length(cpA.velocity) > 0)
			velANormalized = glm::normalize(cpA.velocity);
		glm::vec3 linearVelProjected = glm::dot(linearVelocity, velANormalized) * velANormalized;

		glm::vec3 cpAVel(0, 0, 0);
		if ((aCausesClockwiseRotation && rotationalVecToAdd.z < 0)
			|| (!aCausesClockwiseRotation && rotationalVecToAdd.z > 0))
		{
			cpAVel = cpA.velocity;
			glm::vec3 velToAdd = cpAVel - linearVelProjected;
			if (glm::length(velToAdd) > 0) {
				int a = 0;
			}
			linearVelocity += velToAdd;
		}
		else {
			float lengthToReduce = std::abs(rotationalVecToAdd.z);
			if (lengthToReduce < glm::length(cpA.velocity)) {
				cpAVel = cpA.velocity - velANormalized * lengthToReduce;
			}
			else {
				cpAVel = glm::vec3(0, 0, 0);
			}
		}

	}
}

/*
* creates memo to avoid duplicate comparisons
* creates map to get the true coordinates of each objects vertices after matrix calculations
* first checks collision using bounding volumes, then if bounding volumes collide checks it again using SAT
* checkCollisionUsingSAT returns a CollisionInfo object that contains information about the collision
* if collides sets Forces to the game objects
* broadcasts the collision to listeners
*/
void CollisionSystem::onUpdate(float deltaTime) {
	std::vector<std::vector<bool>>memo(gameObjects.size(), std::vector<bool>(gameObjects.size()));
	std::unordered_map<int, std::vector<glm::vec3>>verticesMap = transformVertices();
	std::unordered_map<int, std::vector<CollisionPoint>>collisionPointMap;

	for (int i = 0; i < gameObjects.size(); ++i) {
		if (!gameObjects[i]->getPhysicsComponent().collidable) continue;

		for (int j = 0; j < gameObjects.size(); ++j) {
			if (!gameObjects[j]->getPhysicsComponent().collidable) continue;
			if (i == j) continue;
			if (glm::length(gameObjects[i]->getVelocityComponent().linearVelocity) == 0
				&& glm::length(gameObjects[j]->getVelocityComponent().linearVelocity) == 0) continue;

			int smaller = i < j ? i : j;
			int bigger = i > j ? i : j;

			if (memo[smaller][bigger]) continue;

			if (!checkCollisionUsingBoundingVolumes(
				gameObjects[i]->getTransformComponent()->absolutePosition(),
				gameObjects[i]->getPhysicsComponent().boundingVolume,
				gameObjects[j]->getTransformComponent()->absolutePosition(),
				gameObjects[j]->getPhysicsComponent().boundingVolume)
				) {
				continue;
			}

			CollisionInfo collision = checkCollisionUsingSAT(gameObjects[i], gameObjects[j], verticesMap);
			if (collision.collides) {

				//setForces(collision);
				createCollisionPoints(collisionPointMap, collision);

				memo[smaller][bigger] = true;
				if (gameObjects.size() > i)
					gameObjects[i]->getPhysicsComponent().onHitEvent.broadcast(gameObjects[i], gameObjects[j]);
				if (gameObjects.size() > j)
					gameObjects[j]->getPhysicsComponent().onHitEvent.broadcast(gameObjects[j], gameObjects[i]);
			}

		}
	}

	for (GameObject* obj : gameObjects) {
		if (collisionPointMap.find(obj->getId()) == collisionPointMap.end()) continue;

		setGameObjectsVelocityAfterCollision(
			obj->getVelocityComponent().linearVelocity,
			obj->getVelocityComponent().rotation,
			collisionPointMap[obj->getId()]
		);
	}
}