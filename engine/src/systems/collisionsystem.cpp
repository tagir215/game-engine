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

void setCollisionPoints(CollisionInfo& collisionInfo, glm::vec3 vertex1, glm::vec3 vertex2, 
	std::vector<glm::vec3>verticesB, glm::vec3 normal) {
	glm::vec3 v1ToV2 = vertex2 - vertex1;
	glm::vec3 v2ToV1 = vertex1 - vertex2;

	collisionInfo.collisionPoints = std::vector<glm::vec3>();
	for (glm::vec3 vertexB : verticesB) {
		glm::vec3 v1ToB = vertexB - vertex1;
		glm::vec3 v2ToB = vertexB - vertex2;
		float normalAndVertex = glm::dot(v1ToB, normal);
		float onEdgeScalar = glm::dot(v1ToB, v2ToB);
		if (normalAndVertex <= 0 && onEdgeScalar < 0) {
			collisionInfo.collisionPoints.push_back(vertexB);
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
	glm::vec3 AtoB = collisionInfo.centroidB - collisionInfo.centroidA;

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

		if (collisionA.collisionPoints.size()>collisionB.collisionPoints.size()) {
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


/*
* Changes objects Velocity components based on the type of collision.
* objA is the collisionObject which's edge collides with the B
* objB is the collisionObject that collides with the edge of the A (if there's more than 1 collisionPoint
* objB technically also collides with an edge)
*/
void setForces(CollisionInfo& collisionInfo) {
	glm::vec3 edgeA = collisionInfo.edgePoints[1] - collisionInfo.edgePoints[0];

	GameObject* objA = collisionInfo.objectA;
	GameObject* objB = collisionInfo.objectB;

	glm::vec3 movDir = objB->getVelocity().velocity;
	if (glm::dot(movDir, collisionInfo.collisionNormal) > 1) return;

	const float ENERGY_RETENTION = 0.6f;

	glm::vec3 normal = glm::normalize(collisionInfo.collisionNormal);
	glm::vec3 projection = -glm::dot(objB->getVelocity().velocity, normal) * normal;
	glm::vec3 mirrorVector = projection + projection -  (-objB->getVelocity().velocity);

	glm::vec3 collisionPointCentroid = calculateCentroid(collisionInfo.collisionPoints);
	float radius =  glm::distance(collisionInfo.centroidB,collisionPointCentroid);

	glm::vec3 velA = objA->getVelocity().velocity;

	glm::vec3 centroidToCollision = collisionInfo.centroidB - collisionPointCentroid;
	glm::vec3 zvector(0, 0, objB->getVelocity().rotation.z);
	glm::vec3 rotVec = glm::cross(centroidToCollision,zvector);
	float dotRotMirror = glm::dot(rotVec, normal);
	float collisionSpeed = std::abs(objB->getVelocity().velocity.y + rotVec.y);
	
	glm::vec3 velB = glm::normalize(objB->getVelocity().velocity) * collisionSpeed;

	glm::vec3 collisionVec = (objA->getPhysics().mass * velA + objB->getPhysics().mass * velB)
			/ (objA->getPhysics().mass + objB->getPhysics().mass);

	float collisionRot = collisionSpeed / radius;
	glm::vec3 pToCentroid = collisionInfo.centroidB - collisionPointCentroid;
	float idk = rotVec.x * rotVec.y;

	glm::vec3 dvA = collisionVec - velA;
	glm::vec3 dvB = collisionVec - velB + mirrorVector;
	float drotB = objB->getVelocity().rotation.z - collisionRot;

	objA->getVelocity().velocity += dvA * ENERGY_RETENTION;
	objB->getVelocity().velocity += dvB * ENERGY_RETENTION;
	if (dotRotMirror<0)
		objB->getVelocity().rotation.z *= -1 * ENERGY_RETENTION;
	else 
		objB->getVelocity().rotation.z += drotB * ENERGY_RETENTION;

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