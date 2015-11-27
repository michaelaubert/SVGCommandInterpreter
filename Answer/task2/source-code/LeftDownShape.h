#pragma once

#include "Shape.h"

/**
 * One of the shapes the program needs to draw
 * The |_| at the beginning "points" to the top of the picture and the _ at the end points to the left.
 * The program needs to draw 3 such shapes.
 */

class LeftDownShape : public Shape {
public:
    LeftDownShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~LeftDownShape();

public:
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile);
};