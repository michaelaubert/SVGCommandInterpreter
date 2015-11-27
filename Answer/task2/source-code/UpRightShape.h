#pragma once

#include "Shape.h"

/**
 * One of the shapes the program needs to draw
 * The |_| at the beginning "points" to the right and the _ at the end points to the bottom of the picture.
 * The program needs to draw 2 such shapes.
 */

class UpRightShape : public Shape {
public:
    UpRightShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~UpRightShape();

public:
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile);
};