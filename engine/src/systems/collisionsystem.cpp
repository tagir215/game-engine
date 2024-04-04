#include "../include/engine/collisionsystem.h"
#include "../include/engine/transformer.h"
#include <cmath>
#include <unordered_map>
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <sstream>
#include <iostream>

CollisionSystem::CollisionSystem(std::vector<GameObject*>gameObjects, Camera* camera) : SystemBase(gameObjects), camera(camera) {
			
}
const float PI = 3.14159265358979323846f;

struct CollisionInfo {
	bool collides;
	float separation;
	std::vector<glm::vec3>edgePoints;
	std::vector<glm::vec3>collisionPoints;
	glm::vec3 collisionNormal;
	glm::vec3 centroidA;
	glm::vec3 centroidB;
	GameObject* objectA;
	GameObject* objectB;
};

struct ForceInfo {
	GameObject* object;
	glm::vec3 position;
	glm::vec3 force;
};

glm::vec3 calculateCentroid(std::vector<glm::vec3>& vertices) {
	glm::vec3 centroid(0,0,0);
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

/*
* vertex1 and vertex2 are vertices of an edge from object A
* verticesB is a list of all vertices from object B
* onEdgeScalar is negative if collisionPoint is within range of the edge
* normalAndVertex if negative objB is facing the normal 
*/
void setCollisionPoints(CollisionInfo& collisionInfo, glm::vec3& vertex1, glm::vec3& vertex2, std::vector<glm::vec3>& verticesB, glm::vec3& normal) {
	glm::vec3 v1ToV2 = vertex2 - vertex1;
	glm::vec3 v2ToV1 = vertex1 - vertex2;

	collisionInfo.collisionPoints = std::vector<glm::vec3>();

	for (glm::vec3 vertexB : verticesB) {
		glm::vec3 v1ToB = vertexB - vertex1;
		glm::vec3 v2ToB = vertexB - vertex2;
		float onEdgeScalar = glm::dot(v1ToB, v2ToB);
		float normalAndVertex = glm::dot(v1ToB, normal);
		if (normalAndVertex <= 0 && onEdgeScalar < 5) {
			collisionInfo.collisionPoints.push_back(vertexB);
		}
	}

	if (collisionInfo.collisionPoints.size() > 0) {
		float distToCentroid = glm::distance(collisionInfo.collisionPoints[0], collisionInfo.centroidB);
		float v1ToCentroid = glm::distance(vertex1,collisionInfo.centroidB);
		float v2ToCentroid = glm::distance(vertex2,collisionInfo.centroidB);

		if (v1ToCentroid < distToCentroid) {
			collisionInfo.collisionPoints.push_back(vertex1);
		}
		else if (v2ToCentroid < distToCentroid) {
			collisionInfo.collisionPoints.push_back(vertex2);
		}
	}

}


/*
* verticesA create the edges, and verticesB are the vertices of object B that are all compared to each edge
*/
CollisionInfo findSeparation(std::vector<glm::vec3>& verticesA, std::vector<glm::vec3>& verticesB, float rot) {
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

/*
* checks if there's collision using the find separation method, and return a CollisionInfo object
* with info about the collision. Calculates 2 separate CollisionInfo objects since in each CollisionInfo
* struct there's objectA that represents the edges and objectB that represents the compared vertices.
* CollisionInfo objects contain info about the separation value, and the collisionInfo object with greater
* separation (that is still in collision, which means it can't be a positive value) is returned from the method
*/
CollisionInfo checkCollision(GameObject* object1, GameObject* object2
	, std::unordered_map<int, std::vector<glm::vec3>>& transformedVertices) {
	std::vector<glm::vec3>vertices1 = transformedVertices[object1->getId()];
	std::vector<glm::vec3>vertices2 = transformedVertices[object2->getId()];
	float rot1 = object1->getTransform().rotation.y;
	float rot2 = object2->getTransform().rotation.y;
	CollisionInfo collisionA = findSeparation(vertices1, vertices2, rot1);
	CollisionInfo collisionB = findSeparation(vertices2, vertices1, rot2);
	if (!collisionA.collides) return collisionA;
	else if (!collisionB.collides) return collisionB;
	else {
		glm::vec3 mov1 = object1->getVelocity().velocity;
		glm::vec3 mov2 = object2->getVelocity().velocity;

		if (collisionA.collisionPoints.size() > collisionB.collisionPoints.size()) {
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

glm::vec3 calculateMirrorVec(glm::vec3 normal, glm::vec3 vec) {
	glm::vec3 projection = glm::dot(vec, normal) * normal;
	glm::vec3 mirrorVector = projection + projection - vec;

	return mirrorVector;
}

glm::vec3 calculateRotationVector(glm::vec3 rotation, glm::vec3 angleVector) {
	glm::vec3 zvector(0, 0, rotation.z);
	return glm::cross(angleVector, zvector);
}

bool isRotatingTowards(glm::vec3 normal, glm::vec3 rotVec) {
	float dot = glm::dot(normal, rotVec);
	return dot < 0;
}

struct CollisionInfo2 {
	GameObject* obj;
	glm::vec3 collisionPoint;
	glm::vec3 velocity0;
	glm::vec3 velocity1;
	glm::vec3 centroid;
	glm::vec3 normal;
	bool rotates;
	float friction;
};

void addEnergyLoss(glm::vec3& vec, const glm::vec3& normal, float retention) {
	glm::vec3 n = glm::normalize(normal) * (1 - retention);
	vec -= glm::dot(vec, n) * n;

}

void addCollisionEnergy(CollisionInfo2& collisionInfo2, float retention) {
	glm::vec3 collisionDirection = glm::normalize(collisionInfo2.velocity1);
	glm::vec3 projectionVelocity = glm::dot(collisionInfo2.velocity0, collisionDirection) * collisionDirection;
	//float lengthOfToAddVector = std::abs(glm::length(projectionVelocity) - glm::length(collisionInfo2.velocity1));
	float lengthOfToAddVector = glm::distance(projectionVelocity, collisionInfo2.velocity1);
	glm::vec3 toAddVector = collisionDirection * lengthOfToAddVector;
	addEnergyLoss(toAddVector,collisionInfo2.normal,retention);
	collisionInfo2.obj->getVelocity().velocity += toAddVector;
}

bool haveOppositeSigns(float x, float y) {
	int signX = std::signbit(x);
	int signY = std::signbit(y);
	return signX != signY;
}

void setVelocities(CollisionInfo2& collisionInfo2) {
	if (glm::length(collisionInfo2.velocity1) == 0) {
		return;
	}

	const float ENERGY_RETENTION = 0.5f;
	glm::vec3 collisionToCentroid = collisionInfo2.collisionPoint - collisionInfo2.centroid;
	float projectionLength = glm::dot(collisionToCentroid, collisionInfo2.velocity1) / glm::length(collisionInfo2.velocity1);
	glm::vec3 projection = glm::normalize(collisionInfo2.velocity1) * projectionLength;

	glm::vec3 edge = glm::cross(collisionInfo2.normal, glm::vec3(0, 0, 1));
	float dot = glm::dot(edge, collisionToCentroid);
	int offsetDirection = dot / std::abs(dot);
	float c = glm::length(collisionToCentroid);
	float a = glm::length(projection);
	float forceOffset = std::sqrt(c * c - a * a) * offsetDirection;


	if (collisionInfo2.rotates && collisionInfo2.obj->getPhysics().rotates) {
		float r = glm::length(collisionToCentroid);
		float rot = (glm::length(collisionInfo2.velocity1) / forceOffset) * ENERGY_RETENTION;
		collisionInfo2.obj->getVelocity().rotation.z = rot;
		if (haveOppositeSigns(rot,collisionInfo2.obj->getVelocity().rotation.z)) {
			addCollisionEnergy(collisionInfo2,ENERGY_RETENTION);
		}
	}
	else {
		addCollisionEnergy(collisionInfo2,ENERGY_RETENTION);
	}

}

/*
* add rotation vector to the uhh velocity thing
*/
glm::vec3 combineWithRotation(GameObject* obj, CollisionInfo& collisionInfo, glm::vec3 collisionPointCentroid) {
	glm::vec3 collisionPointAngleVector = glm::normalize(collisionInfo.centroidB - collisionPointCentroid);
	glm::vec3 rotVec = calculateRotationVector(obj->getVelocity().rotation, collisionPointAngleVector);

	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);
	glm::vec3 rotVecProjection = glm::dot(normal, rotVec) * normal;

	glm::vec3 velocityRotationAdded = rotVecProjection + obj->getVelocity().velocity;
	return velocityRotationAdded;
}

struct SpeedsAfterCollision {
	float v1;
	float v2;
};
struct DirectionsAfterCollision {
	glm::vec3 vecA;
	glm::vec3 vecB;
};

/*
* v1m1 + v2m2 = u1m1 + u2m2
* v1 + u1 = v2 + u2
* u2 = v1 + u1 - v2
* v1m1 + v2m2 = u1m1 + (v1 + u1 - v2)m2
* v1m1 + v2m2 = u1m1 + v1m2 + u1m2 - v2m2
* v1m1 + v2m2 + v2m2 + v1m2 = u1m1 + u1m2
*
* u1 = (v1m1 + 2v2m2 + v1m2) / (m1 + m2)
* u2 = v1 + u1 - v2
*/
SpeedsAfterCollision calculateCollisionVelocities(float m1, float m2, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal) {
	glm::vec3 n = glm::normalize(normal);
	glm::vec3 v1n = glm::dot(v1, n) * n;
	glm::vec3 v2n = glm::dot(v2, n) * n;

	glm::vec3 v1f = (v1n * m1 + v2n * m2 + v2n * m2 + v1n * m2) / (m1 + m2);
	glm::vec3 v2f = (v1n + v2n - v1f);

	if (glm::length(v1f) == 200 && glm::length(v2f) == 400) {
		int wtf = 0;
	}
	return SpeedsAfterCollision(glm::length(v1f), glm::length(v2f));
}

DirectionsAfterCollision calculateDirections(CollisionInfo& collisionInfo) {
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

/*
* Changes objects Velocity components based on the type of collision.
* objA is the collisionObject which's edge collides with the B
* objB is the collisionObject that collides with the edge of the A (if there's more than 1 collisionPoint
* objB technically also collides with an edge)
*/
void setForces(CollisionInfo& collisionInfo) {
	if (collisionInfo.collisionPoints.size() == 0) {
		return;
	}

	glm::vec3 edgeA = collisionInfo.edgePoints[1] - collisionInfo.edgePoints[0];

	GameObject* objA = collisionInfo.objectA;
	GameObject* objB = collisionInfo.objectB;


	//	if (glm::dot(objB->getVelocity().velocity, collisionInfo.collisionNormal) > 1) return;

	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);
	glm::vec3 collisionPointCentroid = calculateCentroid(collisionInfo.collisionPoints);

	glm::vec3 velocityRotationAddedA = combineWithRotation(objA, collisionInfo, collisionPointCentroid);
	glm::vec3 velocityRotationAddedB = combineWithRotation(objB, collisionInfo, collisionPointCentroid);


	SpeedsAfterCollision speedsAfterCollision = calculateCollisionVelocities(
		objA->getPhysics().mass,
		objB->getPhysics().mass,
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

	float totalFriction = objA->getPhysics().friction * objB->getPhysics().friction;

	bool rotates = false;
	if (collisionInfo.collisionPoints.size() < 2) {
		rotates = true;
	}

	CollisionInfo2 collisionA{
		objA,
		collisionPointCentroid,
		objA->getVelocity().velocity,
		collisionVecA,
		collisionInfo.centroidA,
		-normal,
		rotates,
		totalFriction
	};

	CollisionInfo2 collisionB{
		objB,
		collisionPointCentroid,
		objB->getVelocity().velocity,
		collisionVecB,
		collisionInfo.centroidB,
		normal,
		rotates,
		totalFriction
	};

	if (objA->getId() + objB->getId() == 3) {
		if (objA->getId() == 2 && speedsAfterCollision.v1 > 100) {
			int a = 0;
		}
		if (objB->getId() == 2 && speedsAfterCollision.v2 > 100) {
			int b = 0;
		}
	}

	setVelocities(collisionA);
	setVelocities(collisionB);

}

std::unordered_map<int, std::vector<glm::vec3>> CollisionSystem::transformVertices() {
	std::unordered_map<int, std::vector<glm::vec3>>map;
	for (GameObject* object : gameObjects) {
		if (!object->getPhysics().collidable) continue;
		map[object->getId()] = std::vector<glm::vec3>();
		glm::mat4 modelMatrix = transformer.getModelMatrix(object->getTransform());
		std::array<float, 18>vertices = object->getMesh()->getVertices();
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


void CollisionSystem::onUpdate(float deltaTime) {
	std::vector<std::vector<bool>>memo(gameObjects.size(), std::vector<bool>(gameObjects.size()));
	std::unordered_map<int, std::vector<glm::vec3>>map = transformVertices();
	for (int i = 0; i < gameObjects.size(); ++i) {
		for (int j = 0; j < gameObjects.size(); ++j) {
			if (i == j) continue;
			int smaller = i < j ? i : j;
			int bigger = i > j ? i : j;
			CollisionInfo collision = checkCollision(gameObjects[i], gameObjects[j], map);
			if (collision.collides && !memo[smaller][bigger]) {
				setForces(collision);
				memo[smaller][bigger] = true;
			}
		}
	}

}