#pragma once
#include <iostream>
#include <engine/systems/collisionsystem.h>
#include <../assets/basicShapes/plane.h>

class CollisionSystemTest {
public:
	CollisionSystemTest() {
	}
    static void setup() {

		GameObject* object1 = new GameObject(nullptr);
		Plane* plane = new Plane();
		object1->setMeshComponent(plane);
		object1->setPhysicsComponent(PhysicsComponent(100, true, 1, true, 1, glm::vec3(100, 100, 1), true));

		GameObject* object2 = new GameObject(nullptr);
		Plane* plane2 = new Plane();
		object2->setMeshComponent(plane2);
		object2->setPhysicsComponent(PhysicsComponent(100, true, 1, true, 1, glm::vec3(100, 100, 1), true));

		gameObjects.push_back(object1);
		gameObjects.push_back(object2);
		cs = new CollisionSystem(gameObjects);
	}

	static void testCalculateCentroid();
	static void testSetCollisionPoints();
	static void testFindSeparation();
	static void testCheckCollisionUsingBoundingVolumes();
	static void testCheckCollisionUsingSAT();
	static void testCalculateRotationalVelocity();
	static void testIsRotatingTowards();
	static void testAddEnergyLoss();
	static void testAddCollisionEnergy();
	static void testHaveOppositeSigns();
	static void testSetVelocities();
	static void testCombineWithRotation();
	static void testCalculateCollisionVelocities();
	static void testCalculateDirections();
	static void testSetForces();
	static void testTransformVertices();
private:

	static std::vector<GameObject*>gameObjects;
	static CollisionSystem* cs;

};
