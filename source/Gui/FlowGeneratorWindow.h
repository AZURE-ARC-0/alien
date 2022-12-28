#pragma once

#include "EngineInterface/Definitions.h"
#include "EngineInterface/FlowCenter.h"
#include "Definitions.h"
#include "AlienWindow.h"

class _FlowGeneratorWindow : public _AlienWindow
{
public:
    _FlowGeneratorWindow(SimulationController const& simController);

private:
    void processIntern() override;

    FlowCenter createFlowCenter() const;

    SimulationController _simController;
};