#pragma once

#include "Base/Definitions.h"
#include "EngineInterface/Definitions.h"

#include "Definitions.h"

class _Viewport
{
public:
    _Viewport(SimulationController const& simController);

    float getZoomFactor() const;
    void setZoomFactor(float zoomFactor);

    RealVector2D getCenterInWorldPos() const;
    void setCenterInWorldPos(RealVector2D const& worldCenter);

    IntVector2D getViewSize() const;
    void setViewSize(IntVector2D const& viewSize);

    void zoom(IntVector2D const& viewPos, float factor);
    float getZoomSensitivity() const;
    void setZoomSensitivity(float value);

    void centerTo(RealVector2D const& worldPosition, IntVector2D const& viewPos);
    RealVector2D mapViewToWorldPosition(RealVector2D const& viewPos) const;
    RealVector2D mapWorldToViewPosition(RealVector2D worldPos, bool borderlessRendering = true) const;
    RealRect getVisibleWorldRect() const;
    bool isVisible(RealVector2D const& viewPos) const;

private:
    SimulationController _simController;

    float _zoomFactor = 1.0f;
    float _zoomSensitivity = 1.03f;
    RealVector2D _worldCenter;
    IntVector2D _viewSize;
};
