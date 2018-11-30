#include "drawCorrelationFunctions.C"
#include "drawExcitationFunction.C"
#include "drawMtDependence.C"
#include "drawCentrality.C"
#include "drawRsideVsRlong.C"

void drawAllFigures()
{
    drawCorrelationFunctions();
    drawExcitationFunction();
    drawMtDependence();
    drawCentrality();
    drawRsideVsRlong();
}
