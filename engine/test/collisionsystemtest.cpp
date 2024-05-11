#include "collisionsystemtest.h"

int main() {
	CollisionSystemTest cst;
	cst.testCalculateCentroid();
	cst.testFindSeparation();
	cst.testSetCollisionPoints();
	cst.testCheckCollisionUsingBoundingVolumes();
	cst.testHaveOppositeSigns();
	cst.testCalculateRotationalVelocity();
	cst.testIsRotatingTowards();
	cst.testAddEnergyLoss();
	return 0;
}

CollisionSystem* CollisionSystemTest::cs = nullptr;
std::vector<GameObject*> CollisionSystemTest::gameObjects;

void CollisionSystemTest::testCalculateCentroid()
{
	std::vector<glm::vec3>vecs;
	vecs.push_back(glm::vec3(0, 0, 0));
	vecs.push_back(glm::vec3(1, 0, 0));
	vecs.push_back(glm::vec3(1, 1, 0));
	vecs.push_back(glm::vec3(0, 1, 0));
	glm::vec3 c = cs->calculateCentroid(vecs);
	std::cout << " x: " << c.x;
	std::cout << " y: " << c.y;
	std::cout << " z: " << c.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testSetCollisionPoints()
{
	std::vector<glm::vec3>verticesB;
	verticesB.push_back(glm::vec3(0, 0, 0));
	verticesB.push_back(glm::vec3(1, 0, 0));
	verticesB.push_back(glm::vec3(1, 1, 0));
	verticesB.push_back(glm::vec3(0, 1, 0));

	glm::vec3 vertex1(0, 0, 0);
	glm::vec3 vertex2(0, 0.5f, 0);
	glm::vec3 normal(1, 0, 0);

	CollisionSystem::CollisionInfo coi;
	cs->setCollisionPoints(coi, vertex1, vertex2, verticesB,  normal);
	for (glm::vec3& collisionPoint : coi.collisionPoints) {
		std::cout << " x: " << collisionPoint.x;
		std::cout << " y: " << collisionPoint.y;
		std::cout << " z: " << collisionPoint.z;
		std::cout << ",";
	}
	std::cout << std::endl;
}

void CollisionSystemTest::testFindSeparation()
{
	std::vector<glm::vec3>verticesA;
	std::vector<glm::vec3>verticesB;
	std::vector<glm::vec3>verticesC;

	verticesA.push_back(glm::vec3(2, 0, 0));
	verticesA.push_back(glm::vec3(2, 2, 0));
	verticesA.push_back(glm::vec3(3, 0, 0));

	verticesB.push_back(glm::vec3(0, 0, 0));
	verticesB.push_back(glm::vec3(1, 1, 0));
	verticesB.push_back(glm::vec3(1, 0, 0));

	verticesC.push_back(glm::vec3(0, 0, 0));
	verticesC.push_back(glm::vec3(3, 0.5f, 0));
	verticesC.push_back(glm::vec3(0, 2, 0));

	CollisionSystem::CollisionInfo coi = cs->findSeparation(verticesA, verticesB, 0);
	std::cout << " collidesAB " << coi.collides;
	CollisionSystem::CollisionInfo coi2 = cs->findSeparation(verticesA, verticesC, 0);
	std::cout << " collidesAC " << coi2.collides;
	std::cout << std::endl;
}

void CollisionSystemTest::testCheckCollisionUsingBoundingVolumes()
{
	glm::vec3 posA(0, 0, 0);
	glm::vec3 boxA(1.1f, 1.1f, 0);
	glm::vec3 posB(1, 0, 0);
	glm::vec3 boxB(1, 1, 0);
	bool collides = cs->checkCollisionUsingBoundingVolumes(posA, boxA, posB, boxB);

	glm::vec3 posA2(0, 0, 0);
	glm::vec3 boxA2(1.1f, 1.1f, 0);
	glm::vec3 posB2(1, 0, 0);
	glm::vec3 boxB2(0.5f, 0.5f, 0);
	bool collides2 = cs->checkCollisionUsingBoundingVolumes(posA2, boxA2, posB2, boxB2);

	std::cout << "collides: " << collides << " collides2: " << collides2 << std::endl;
}

void CollisionSystemTest::testCalculateRotationalVelocity()
{
	glm::vec3 angleVector(1, 0, 0);
	glm::vec3 rot(0, 0, 2);
	glm::vec3 rotationVector = cs->calculateRotationalVelocity(rot, angleVector);
	std::cout << " rotationVecX: " << rotationVector.x;
	std::cout << " rotationVecY: " << rotationVector.y;
	std::cout << " rotationVecZ: " << rotationVector.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testIsRotatingTowards()
{
	glm::vec3 normal(0, 1, 0);
	glm::vec3 rotVec(0, -1, 0);
	std::cout << "isRotatingTowards: " << cs->isRotatingTowards(normal, rotVec) << std::endl;
}

void CollisionSystemTest::testAddEnergyLoss()
{
	float energyRetention = 0.5f;
	glm::vec3 vec(1, 1, 0);
	glm::vec3 normal(0, 1, 0);
	cs->addEnergyLoss(vec, normal, energyRetention);
	std::cout << " velocity x: " << vec.x;
	std::cout << " velocity y: " << vec.y;
	std::cout << " velocity z: " << vec.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testHaveOppositeSigns()
{
	bool os = cs->haveOppositeSigns(1, -1);
	bool os2 = cs->haveOppositeSigns(1, 1);
	std::cout << " os? " << os;
	std::cout << " os2? " << os2;

}
