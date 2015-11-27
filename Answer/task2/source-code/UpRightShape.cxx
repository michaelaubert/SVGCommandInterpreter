#include "UpRightShape.h"

UpRightShape::UpRightShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
    Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
UpRightShape::~UpRightShape() {
}

void UpRightShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawRight(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
    } else {
        DrawDown(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
    }
}