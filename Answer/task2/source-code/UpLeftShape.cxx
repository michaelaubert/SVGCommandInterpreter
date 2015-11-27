#include "UpLeftShape.h"

UpLeftShape::UpLeftShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
    Shape(aBeginX, aBeginY, aEndX, aEndY, aWidthStep, aHeightStep) {
}
 
UpLeftShape::~UpLeftShape() {
}

void UpLeftShape::GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile) {
    if (aIsUseBeginVertex) {
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
        DrawLeft(apFile);
        DrawUp(apFile);
        DrawRight(apFile);
        DrawUp(apFile);
    } else {
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
        DrawDown(apFile);
        DrawLeft(apFile);
        DrawDown(apFile);
        DrawRight(apFile);
    }
}