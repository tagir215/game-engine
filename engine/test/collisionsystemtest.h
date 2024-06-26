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
		StaticMesh* mesh = new StaticMesh();
		mesh->setVertices(std::vector<float>{
			-0.5f, -0.5f, 0.0f,        //left-bottom
				0.5f, -0.5f, 0.0f,     //right-bottom
				0.5f, 0.5f, 0.0f,      //right-top
				-0.5f, -0.5f, 0.0f,    //left-bottom
				0.5f, 0.5f, 0.0f,      //right-top
				-0.5f, 0.5f, 0.0f      //left-top
		});
		object1->setMeshComponent(mesh);
		object1->setPhysicsComponent(PhysicsComponent(100, true, 1, true, 1, glm::vec3(100, 100, 1), true));
		object1->setTransformComponent(new TransformComponent(glm::vec3(1, 0, 0)));

		GameObject* object2 = new GameObject(nullptr);
		Plane* plane2 = new Plane();
		object2->setMeshComponent(plane2);
		object2->setPhysicsComponent(PhysicsComponent(100, true, 1, true, 1, glm::vec3(100, 100, 1), true));
		object2->setTransformComponent(new TransformComponent(glm::vec3(-1, 0, 0)));

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
	static void testSetGameObjectsVelocityAfterCollision();
	static void testCreateCollisionPoints();
private:

	static std::vector<GameObject*>gameObjects;
	static CollisionSystem* cs;

};
