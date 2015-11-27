#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Vertex.h"

using namespace std;

#define KDefaultStep 10

/**
 * Shape is responsible for writing to the output file the correct commands to draw each one of the 21 shapes.
 * Shape is not responsible for deciding in which order the shapes are drawn
 * @see MaxelerSvgGenerator
 * All shapes begin with a |_| and end with a _
 * Shapes can be drawn from beginning to end or from end to beginning
 * Shape also writes to the output file the correct commands to move the SVG "cursor" (without drawing)
 * between drawings.
 */

class Shape {

private:
    /*
     * CommandIndex must match KMoveCommandArray in Shape.cxx
     * @see KMoveCommandArray
     */
    //TODO: move to Shape.cxx
    enum CommandIndex {
        EDownRight=0,
        EUpRight,
        EUpLeft,
        EDownLeft,
        ERight,
        EUp,
        ELeft,
        EDown,
        EParenthesis,
        EShortenHorizontalStep,
        EEnlargeHorizontalStep,
        EShortenVerticalStep,
        EEnlargeVerticalStep
    };

public:
    /**
     * @param aBeginX X coordinate for the first dot a the beginning of the shape
     * @param aBeginY Y coordinate for the first dot a the beginning of the shape
     * @param aEndX X coordinate for the last dot a the end of the shape
     * @param aEndY Y coordinate for the last dot a the end of the shape
     * @param aWidthStep length of each of the horizontal lines in the shape
     * @param aHeightStep length of each of the vertical lines in the shape
     * Shape can generate commands even when aWidthStep and aHeightStep are not 10
     */
    //TODO: default constructors with both steps at 10, for this and all subclasses
    Shape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep);
    virtual ~Shape();

public:
    /**
     * Outputs commands to move (without drawing, using 'P') from aOrigin to the beginning or end of this shape
     * Needs to be called before GenerateCommandsToDraw.
     * @param aOrigin last position of the SVG "cursor"
     * @param aIsUseBeginVertex true if the SVG "cursor" destination should be the beginning of this shape
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     * It is valid for GenerateCommandsToMoveFrom to output no command if this shape ends or begin at aOrigin. 
     */
    void GenerateCommandsToMoveFrom(const Vertex& aOrigin, bool aIsUseBeginVertex, FILE* apFile);

    /**
     * Outputs commands to draw this shape at the current SVG "cursor"
     * @param aIsUseBeginVertex true if this shape should be drawn from beginning to end.
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     * Subclasses must define GenerateCommandsToDraw by deciding in which order to call
     * DrawUp, DrawDown, DrawRight and DrawLeft below
     */
    virtual void GenerateCommandsToDraw(bool aIsUseBeginVertex, FILE* apFile)=0;

    /**
     * @returns a const reference to the Vertex at the end of this shape.
     * Used to update the current SVG "cursor" after drawing this shape from beginning to end
     */
    const Vertex& GetVertexEnd() const;

    /**
     * @returns a const reference to the Vertex at the beginning of this shape.
     * Used to update the current SVG "cursor" after drawing this shape from end to beginning
     */
    const Vertex& GetVertexBegin() const;

protected:

    /**
     * Outputs the commands to draw a vertical line pointing toward the bottom of the picture
     * The aHeightStep parameter in the Shape constructor indicates the length of the line
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     */
    void DrawUp(FILE* apFile);

    /**
     * Outputs the commands to draw a vertical line pointing toward the top of the picture
     * The aHeightStep parameter in the Shape constructor indicates the length of the line
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     */
    void DrawDown(FILE* apFile);

    /**
     * Outputs the commands to draw a horizontal line pointing to the right
     * The aWidthStep parameter in the Shape constructor indicates the length of the line
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     */
    void DrawRight(FILE* apFile);

    /**
     * Outputs the commands to draw a horizontal line pointing to the left
     * The aHeightWidth parameter in the Shape constructor indicates the length of the line
     * @param apFile a stdlib stream open for writing text. where the commands will be written.
     */
    void DrawLeft(FILE* apFile);

private:
    Vertex iBeginVertex;
    Vertex iEndVertex;
    int iWidthStep;
    int iHeightStep;
};