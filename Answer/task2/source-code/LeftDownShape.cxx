#include "LeftDownShape.h"

LeftDownShape::LeftDownShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
        Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
LeftDownShape::~LeftDownShape() {
}

void LeftDownShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
    } else {
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
    }
}