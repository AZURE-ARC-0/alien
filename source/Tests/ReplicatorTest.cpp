#include <QDir>
#include <QFile>
#include <gtest/gtest.h>

#include "Model/Local/Cluster.h"
#include "Model/Api/SimulationController.h"
#include "Model/Local/UnitContext.h"
#include "Model/Api/Settings.h"
#include "tests/TestSettings.h"


class ReplicatorTest : public ::testing::Test
{
public:
	ReplicatorTest();
	~ReplicatorTest();

protected:
	SimulationController* _simulationController = nullptr;
};


ReplicatorTest::ReplicatorTest()
{
/*
	_simulationController = new SimulationController();
*/
}

ReplicatorTest::~ReplicatorTest()
{
	delete _simulationController;
}

/*
TEST_F (IntegrationTestReplicator, testRunSimulation)
{
    QFile file(INTEGRATIONTEST_REPLICATOR_INIT);
	ASSERT_TRUE(file.open(QIODevice::ReadOnly));
    QDataStream in(&file);
    _simulationController->loadUniverse(in);
    file.close();

    UnitContext* context = _simulationController->getSimulationContext();
    ASSERT_TRUE(!context->getClustersRef().empty());
    int replicatorSize = context->getClustersRef().at(0)->getCellsRef().size();
    for (int time = 0; time < INTEGRATIONTEST_REPLICATOR_TIMESTEPS; ++time) {
        _simulationController->requestNextTimestep();
    }

    int replicators = 0;
    foreach (CellCluster* cluster, context->getClustersRef()) {
        if (cluster->getCellsRef().size() >= replicatorSize)
            ++replicators;
    }
    ASSERT_TRUE(replicators >= 5);
}

*/