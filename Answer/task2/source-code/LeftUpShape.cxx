#include "LeftUpShape.h"

LeftUpShape::LeftUpShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
    Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
LeftUpShape::~LeftUpShape() {
}

void LeftUpShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
    } else {
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
    }
}