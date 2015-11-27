#pragma once

#include "Shape.h"

// 400 pixels squared + 400 pixel squared.
// no need to calculate square root as it is only used
// for distance comparisons and squaring conserves order
#define KSquaredDiagonal 320000


/**
 * MaxelerSvgGenerator contains all the Shape objects that need drawing
 * and is responsible for writting all the commands that task2.bin requires
 * to the result.txt file.
 * MaxelerSvgGenerator decides in which order to draw the shapes so that the
 * the output file remains small enough.
 * The current algorithm is:
 * - SVG "cursor" is at coordinates (0,0)
 * - while(there are still more shapes to draw) do:
 * - {
 * - - find the shape whose beginning or end is nearest to the SVG "cursor"
 * - - move SVG "cursor" to beginning or end of chosen shape
 * - - draw chosen shape
 * - - realize that the SVG "cursor" is now either at the beginning or the end of the shape that you just drew
 * - }
 * - Blame the author having implemented the Prim algorithm at school if the output file ends up being too big.
 */

class MaxelerSvgGenerator {
private:
    // use a linked list to store shapes because no need for random access
    // to find minimal distance from SVG "cursor"
    // and easy add/remove of shapes is useful
    struct ShapeLinkedListElement {
        Shape* iShape;
        ShapeLinkedListElement* iNext;
    };
public:
    MaxelerSvgGenerator();
    ~MaxelerSvgGenerator();

public:
    /**
     * Should be called 21 times (number of different shapes to draw) before GenerateSvgCommands
     * @param aShape a shape to the list of shapes to draw. MaxelerSvgGenerator keeps ownership of the object aShape points to
     */
    void AddShape(Shape* aShape);

    /**
     * Entry point and main loop of the algorithm to write the task2.bin commands to the result.txt output file.
     */
    void GenerateSvgCommands();

private:
    /**
     * resets the generator so it can be reused
     */
    //TODO: "result.txt" output should be configurable
    void CleanShapeLinkedList();

    /**
     * Populates iCurrentShape and iIsUseCurrentShapeBeginVertex below
     * to reflect the nearest shape to iCurrentVertex that still needs drawing
     */
    void FindAndExtractNearestShape();

private:
    Shape* iCurrentShape;
    bool iIsUseCurrentShapeBeginVertex;
    Vertex iCurrentVertex;
    ShapeLinkedListElement* iShapeLinkedList;
    ShapeLinkedListElement* iLastShapeListElement;
};
