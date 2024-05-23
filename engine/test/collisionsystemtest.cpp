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
	cst.testAddCollisionEnergy();
	cst.testCombineWithRotation();
	cst.testCalculateCollisionVelocities();
	cst.testCalculateDirections();
	cst.testSetGameObjectsVelocityAfterCollision();
	cst.testCreateCollisionPoints();
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

void CollisionSystemTest::testCheckCollisionUsingSAT()
{
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

void CollisionSystemTest::testAddCollisionEnergy()
{
	CollisionSystem::CollisionObjectInfo oi;
	oi.obj = new GameObject(nullptr);
	oi.velocityAfterCollision = glm::vec3(0, 1, 0);
	oi.obj->setVelocityComponent(VelocityComponent(1, -1, 0));
	float energyRetention = 1.0f;
	cs->addCollisionEnergy(oi, energyRetention);
	std::cout << " linearvelocity x: " << oi.obj->getVelocityComponent().linearVelocity.x;
	std::cout << " linearvelocity y: " << oi.obj->getVelocityComponent().linearVelocity.y;
	std::cout << " linearvelocity z: " << oi.obj->getVelocityComponent().linearVelocity.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testHaveOppositeSigns()
{
	bool os = cs->haveOppositeSigns(1, -1);
	bool os2 = cs->haveOppositeSigns(1, 1);
	std::cout << " os? " << os;
	std::cout << " os2? " << os2;
	std::cout << std::endl;
}

void CollisionSystemTest::testSetVelocities()
{
}

void CollisionSystemTest::testCombineWithRotation()
{
	glm::vec3 objLinearVelocity(0, -1, 0);
	glm::vec3 objRotation(0, 0, 1);
	CollisionSystem::CollisionInfo coi;
	coi.collisionNormal = glm::vec3(0, 1, 0);
	coi.centroidB = glm::vec3(0.5f, 0.5f, 0);
	glm::vec3 collisionPoint(0, 0, 0);
	glm::vec3 combined = cs->combineWithRotation(objLinearVelocity, objRotation, coi, collisionPoint);
	std::cout << " combined velocity x: " << combined.x;
	std::cout << " combined velocity y: " << combined.y;
	std::cout << " combined velocity z: " << combined.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testCalculateCollisionVelocities()
{
	float m1 = 100.0f;
	float m2 = 100.0f;
    glm::vec3 v1 = {5.0f, 0.0f, 0.0f};
    glm::vec3 v2 = {-5.0f, 0.0f, 0.0f};
    glm::vec3 normal = {1.0f, 0.0f, 0.0f};

    CollisionSystem::SpeedsAfterCollision result = cs->calculateCollisionVelocities(m1, m2, v1, v2, normal);

	std::cout << " speed1: x: " << result.v1;
	std::cout << " speed2: y: " << result.v2;
	std::cout << std::endl;
}

void CollisionSystemTest::testCalculateDirections()
{
	CollisionSystem::CollisionInfo coi;
	coi.collisionNormal = glm::vec3(0, 1, 0);
	CollisionSystem::DirectionsAfterCollision directions = cs->calculateDirections(coi);
	std::cout << " directionAX " << directions.vecA.x;
	std::cout << " directionAY " << directions.vecA.y;
	std::cout << " directionAZ " << directions.vecA.z;
	std::cout << " directionBX " << directions.vecB.x;
	std::cout << " directionBY " << directions.vecB.y;
	std::cout << " directionBZ " << directions.vecB.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testSetForces()
{
}

void CollisionSystemTest::testTransformVertices()
{
}


void CollisionSystemTest::testSetGameObjectsVelocityAfterCollision()
{
	glm::vec3 linearVelocity(0, -1, 0);
	glm::vec3 rotation(0, 0, 0);
	glm::vec3 centroid(0.5f, 0.5f, 0);
	std::vector<CollisionSystem::CollisionPoint>collisionPoints;
	collisionPoints.push_back(CollisionSystem::CollisionPoint(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), centroid));
	//collisionPoints.push_back(CollisionSystem::CollisionPoint(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0)));
	collisionPoints.push_back(CollisionSystem::CollisionPoint(glm::vec3(1, 1, 0), glm::vec3(-0.5, 0, 0),centroid));
	
	cs->setGameObjectsVelocityAfterCollision(linearVelocity,rotation,collisionPoints,1,1,true);
	std::cout << " linearVelocity x:" <<  linearVelocity.x;
	std::cout << " linearVelocity y:" <<  linearVelocity.y;
	std::cout << " linearVelocity z:" <<  linearVelocity.z;

	std::cout << " rotation x:" <<  rotation.x;
	std::cout << " rotation y:" <<  rotation.y;
	std::cout << " rotation z:" <<  rotation.z;
	std::cout << std::endl;
}

void CollisionSystemTest::testCreateCollisionPoints()
{
	CollisionSystem::CollisionInfo coi;
	coi.centroidA = glm::vec3(0.5f, 0.5f, 0);
	coi.centroidB = glm::vec3(0.5f, -0.5f, 0);
	coi.collides = true;
	coi.collisionNormal = glm::vec3(0, 1, 0);
	coi.collisionPoints = {
		glm::vec3(0.2f,0,0)
	};
	coi.edgePoints = {
		glm::vec3(0,0,0),
		glm::vec3(1,0,0)
	};
	coi.objectA = new GameObject(nullptr);
	coi.objectA->createComponent<VelocityComponent>(0,-10,0);
	coi.objectA->createComponent<PhysicsComponent>(10, true, 1, true, 0, glm::vec3(1, 1, 1), true);
	coi.objectB = new GameObject(nullptr);
	coi.objectB->createComponent<VelocityComponent>(0, 0, 0);
	coi.objectB->createComponent<PhysicsComponent>(10, true, 1, true, 0, glm::vec3(1, 1, 1), true);

	std::unordered_map<int, std::vector<CollisionSystem::CollisionPoint>>map;
	cs->createCollisionPoints(map,coi);

	int a = 0;
}


