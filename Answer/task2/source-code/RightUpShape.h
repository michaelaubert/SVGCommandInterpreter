#pragma once

#include "Shape.h"

/**
 * One of the shapes the program needs to draw
 * The |_| at the beginning "points" to the bottorm of the picture and the _ at the end points to the right.
 * The program needs to draw 3 such shapes.
 */

class RightUpShape : public Shape {
public:
    RightUpShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~RightUpShape();

public:
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile);
};