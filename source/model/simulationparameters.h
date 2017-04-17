#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#include "definitions.h"

struct SimulationParameters
{
	qreal cellMutationProb = 0.0;
	qreal cellMinDistance = 0.0;
	qreal cellMaxDistance = 0.0;
	qreal cellMass_Reciprocal = 0.0; //related to 1/mass
	qreal callMaxForce = 0.0;
	qreal cellMaxForceDecayProb = 0.0;
	int cellMaxBonds = 0;
	int cellMaxToken = 0;
	int cellMaxTokenBranchNumber = 0;
	qreal cellCreationEnergy = 0.0;
	int NEW_CELL_MAX_CONNECTION = 0;	//TODO: add to editor
	int NEW_CELL_TOKEN_ACCESS_NUMBER = 0; //TODO: add to editor
	qreal cellMinEnergy = 0.0;
	qreal cellTransformationProb = 0.0;
	qreal cellFusionVelocity = 0.0;

	int cellFunctionComputerMaxInstructions = 0;
	int cellFunctionComputerCellMemorySize = 0;
	int cellFunctionComputerTokenMemorySize = 0;
	qreal cellFunctionWeaponStrength = 0.0;
	qreal cellFunctionConstructorOffspringDistance = 0.0;
	qreal cellFunctionSensorRange = 0.0;
	qreal cellFunctionCommunicatorRange = 0.0;

	qreal tokenCreationEnergy = 0.0;
	qreal tokenMinEnergy = 0.0;

	qreal radiationExponent = 0.0;
	qreal radiationFactor = 0.0;
	qreal radiationProb = 0.0;

	qreal radiationVelocityMultiplier = 0.0;
	qreal radiationVelocityPerturbation = 0.0;

	void setParameters(SimulationParameters* other);

	void serializePrimitives(QDataStream& stream);
	void deserializePrimitives(QDataStream& stream);
};

#endif // SIMULATIONPARAMETERS_H
