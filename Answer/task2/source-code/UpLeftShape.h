#pragma once

#include "Shape.h"

/**
 * One of the shapes the program needs to draw
 * The |_| at the beginning "points" to the left and the _ at the end points to the bottom of the picture.
 * The program needs to draw 2 such shapes.
 */

class UpLeftShape : public Shape {
public:
    UpLeftShape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~UpLeftShape();

public:
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile);
};