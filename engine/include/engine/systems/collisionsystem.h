#pragma once
#include "systembase.h"
#include "engine/graphics/camera.h"
#include "engine/util/transformer.h"
#include <unordered_map>

class CollisionSystem : public SystemBase {
public:
	CollisionSystem(std::vector<GameObject*>& gameObjects);
	void onUpdate(float deltaTime) override;
	friend class CollisionSystemTest;
private:
	Transformer transformer;
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

	struct CollisionObjectInfo {
		GameObject* obj;
		glm::vec3 collisionPoint;
		glm::vec3 velocityAfterCollision;
		glm::vec3 centroid;
		glm::vec3 normal;
		bool rotates;
		float friction;
	};
	struct SpeedsAfterCollision {
		float v1;
		float v2;
	};
	struct DirectionsAfterCollision {
		glm::vec3 vecA;
		glm::vec3 vecB;
	};
	struct CollisionPoint {
		glm::vec3 pos;
		glm::vec3 velocity;
		glm::vec3 centroid;
	};




	glm::vec3 calculateCentroid(std::vector<glm::vec3>& vertices);

	/*
	* vertex1 and vertex2 are vertices of an edge from object A
	* verticesB is a list of all vertices from object B
	* onEdgeScalar is negative if collisionPoint is within range of the edge
	* normalAndVertex if negative objB is facing the normal
	*/
	void setCollisionPoints(CollisionInfo& collisionInfo, glm::vec3& vertex1, glm::vec3& vertex2, std::vector<glm::vec3>& verticesB, glm::vec3& normal);

	/*
	* verticesA create the edges, and verticesB are the vertices of object B that are all compared to each edge
	*/
	CollisionInfo findSeparation(std::vector<glm::vec3>& verticesA, std::vector<glm::vec3>& verticesB, float rot);

	/*
	* check if there's collision using bounding volumes
	*/
	bool checkCollisionUsingBoundingVolumes(glm::vec3 posA, glm::vec3 boxA, glm::vec3 posB, glm::vec3 boxB);

	/*
	* checks if there's collision using the find separation method, and return a CollisionInfo object
	* with info about the collision. Calculates 2 separate CollisionInfo objects since in each CollisionInfo
	* struct there's objectA that represents the edges and objectB that represents the compared vertices.
	* CollisionInfo objects contain info about the separation value, and the collisionInfo object with greater
	* separation (that is still in collision, which means it can't be a positive value) is returned from the method
	*/
	CollisionInfo checkCollisionUsingSAT(GameObject* object1, GameObject* object2
		, std::unordered_map<int, std::vector<glm::vec3>>& transformedVertices);


	glm::vec3 calculateRotationalVelocity(glm::vec3 rotation, glm::vec3 angleVector);
	bool isRotatingTowards(glm::vec3 normal, glm::vec3 rotVec);
	void addEnergyLoss(glm::vec3& vec, const glm::vec3& normal, float retention);
	void addCollisionEnergy(CollisionObjectInfo& collisionObjectInfo, float retention);
	bool haveOppositeSigns(float x, float y);
	void setVelocities(CollisionObjectInfo& collisionObjectInfo);
	/*
	* add rotation vector to the uhh velocity thing
	*/
	glm::vec3 combineWithRotation(glm::vec3& objLinearVelocity, glm::vec3& objRotation, CollisionInfo& collisionInfo, glm::vec3 collisionPointCentroid);

	/*
	* calculates Speeds of both objects after the collision
	* v1m1 + v2m2 = u1m1 + u2m2
	* v1 + u1 = v2 + u2
	*
	* u2 = v1 + u1 - v2
	* 
	* v1m1 + v2m2 = u1m1 + (v1 + u1 - v2)m2
	* v1m1 + v2m2 = u1m1 + v1m2 + u1m2 - v2m2
	* v1m1 + v2m2 - v1m2 + v2m2 = u1m1 + u1m2
	* u1(m1 + m2) = v1m1 + v2m2 - v1m2 + v2m2
	* 
	* u1 = v1m1 + v2m2 - v1m2 + v2m2 / (m1 + m2)
	*/
	SpeedsAfterCollision calculateCollisionVelocities(float m1, float m2, glm::vec3 v1, glm::vec3 v2, glm::vec3 normal);
	/*
	* calculates directions of each object after the collision
	* used to be more complex but i realized at some point that i can just add the -normal to the original velocity
	*/
	DirectionsAfterCollision calculateDirections(CollisionInfo& collisionInfo);

	/*
	* Changes objects Velocity components based on the type of collision.
	* objA is the collisionObject which's edge collides with the B
	* objB is the collisionObject that collides with the edge of the A (if there's more than 1 collisionPoint objB technically also collides with an edge)
	*/
	void setForces(CollisionInfo& collisionInfo);

	/*
	* transform vertices of all objects with it's modelMatrix to get the true coordinates
	* returns map of object ids and object vertices
	*/
	std::unordered_map<int, std::vector<glm::vec3>> transformVertices();


	void createCollisionPoints(std::unordered_map<int, std::vector<CollisionPoint>>& cpMap, CollisionInfo& info);

	/*
	* Set GameObjects velocity after the collision using the collisionpoints
	*/
	void setGameObjectsVelocityAfterCollision(glm::vec3& linearVelocity, glm::vec3& rotation, std::vector<CollisionPoint>& collisionPoints);
};