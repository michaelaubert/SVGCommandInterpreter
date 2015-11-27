#include "RightUpShape.h"

RightUpShape::RightUpShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
    Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
RightUpShape::~RightUpShape() {
}

void RightUpShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
    } else {
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
    }
}