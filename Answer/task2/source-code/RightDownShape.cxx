#include "RightDownShape.h"

RightDownShape::RightDownShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
    Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
RightDownShape::~RightDownShape() {
}

void RightDownShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
    } else {
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
    }
}