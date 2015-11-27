#pragma once

#include "Shape.h"

/**
 * One of the shapes the program needs to draw
 * The |_| at the beginning "points" to the bottom of the picture and the _ at the end points to the left.
 * The program needs to draw 2 such shapes.
 */

class LeftUpShape : public Shape {
public:
    LeftUpShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~LeftUpShape();

public:
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile);
};