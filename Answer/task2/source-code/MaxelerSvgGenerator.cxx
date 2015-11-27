#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "MaxelerSvgGenerator.h"

MaxelerSvgGenerator::MaxelerSvgGenerator() :
        iCurrentShape(NULL),
        iIsUseCurrentShapeBeginVertex(true),
        iCurrentVertex(0,0),
        iShapeLinkedList(NULL),
        iLastShapeListElement(NULL) {
}

MaxelerSvgGenerator::~MaxelerSvgGenerator() {
    CleanShapeLinkedList();
}

void MaxelerSvgGenerator::CleanShapeLinkedList() {
    iLastShapeListElement = NULL;
    delete iCurrentShape;
    iCurrentShape = NULL;
    ShapeLinkedListElement* shapeListElement = NULL;
    iCurrentVertex = Vertex(0,0);//TODO: implement Vertex::SetX(int) and Vertex::SetY(int)
    while (NULL != (shapeListElement = iShapeLinkedList)) {
        delete shapeListElement->iShape;
        shapeListElement->iShape = NULL;
        iShapeLinkedList = shapeListElement->iNext;
        delete shapeListElement;
        shapeListElement = NULL;
    }
}

void MaxelerSvgGenerator::AddShape(Shape* aShape) {
    if(NULL == iLastShapeListElement) {
        CleanShapeLinkedList();// just in case
        iShapeLinkedList = new ShapeLinkedListElement;
        if(NULL == iShapeLinkedList) {
            cout << "Can't initialize shape linked list: not enough memory" << endl;
            delete aShape;
        } else {
            iShapeLinkedList->iShape = aShape;
            iShapeLinkedList->iNext = NULL;
            iLastShapeListElement = iShapeLinkedList;
        }
    } else {
        iLastShapeListElement->iNext = new ShapeLinkedListElement;
        if(NULL == iLastShapeListElement->iNext) {
            cout << "Can't add a shape to the linked list: not enough memory" << endl;
            delete aShape;
        } else {
            iLastShapeListElement = iLastShapeListElement->iNext;
            iLastShapeListElement->iNext = NULL;
            iLastShapeListElement->iShape = aShape;
        }
    }
}

void MaxelerSvgGenerator::GenerateSvgCommands() {
    FILE* pFile;
    //TODO: make file path configurable (command line argument, maybe) and test all kinds of relative and absolute paths.
    errno_t error = fopen_s(&pFile, "result.txt", "w");
    if (pFile == NULL || 0 != error) {
        perror ("Error opening file");
    } else {
        while(NULL != iShapeLinkedList) {
            FindAndExtractNearestShape();
            if(NULL != iCurrentShape) {
                iCurrentShape->GenerateCommandsToMoveFrom(iCurrentVertex, iIsUseCurrentShapeBeginVertex, pFile);
                iCurrentShape->GenerateCommandsToDraw(iIsUseCurrentShapeBeginVertex, pFile);
                if(iIsUseCurrentShapeBeginVertex) {
                    iCurrentVertex = iCurrentShape->GetVertexEnd();
                } else {
                    iCurrentVertex = iCurrentShape->GetVertexBegin();
                }
                delete iCurrentShape;
                iCurrentShape = NULL;
            }
        }
        if (0 > fputc('X', pFile)) {
            cout << "X command write failed" << endl;
        }
        fclose (pFile);
    }
}

void MaxelerSvgGenerator::FindAndExtractNearestShape() {
    iCurrentShape = NULL;
    ShapeLinkedListElement* current = iShapeLinkedList;
    ShapeLinkedListElement* previousOfCurrent = NULL;
    ShapeLinkedListElement* nearest = NULL;
    ShapeLinkedListElement* previousOfNearest = NULL;
    int shortestSquaredDistance = KSquaredDiagonal;
    // find the shape nearest shape to iCurrentVertex by comparing the square of the length of a straight point-to-point line
    // (without moving the SVG "cursor", obviously)
    while (0 < shortestSquaredDistance && NULL != current) {
        if(NULL != current->iShape) {
            int currentSquaredDistance = current->iShape->GetVertexEnd().SquaredDistanceFrom(iCurrentVertex);
            if(shortestSquaredDistance > currentSquaredDistance) {
                shortestSquaredDistance = currentSquaredDistance;
                iIsUseCurrentShapeBeginVertex = false;
                previousOfNearest = previousOfCurrent;
                nearest = current;
            }
            currentSquaredDistance = current->iShape->GetVertexBegin().SquaredDistanceFrom(iCurrentVertex);
            if(shortestSquaredDistance > currentSquaredDistance) {
                shortestSquaredDistance = currentSquaredDistance;
                iIsUseCurrentShapeBeginVertex = true;
                previousOfNearest = previousOfCurrent;
                nearest = current;
            }
        }
        previousOfCurrent = current;
        current = current->iNext;
    }
    if (NULL!=nearest) {
        iCurrentShape = nearest->iShape;
        // remove shape from the linked list
        nearest->iShape = NULL;
        if(NULL != previousOfNearest) {
            previousOfNearest->iNext = nearest->iNext;
        } else {
            iShapeLinkedList = iShapeLinkedList->iNext;
        }
        nearest->iNext = NULL;
        delete nearest;
    }
}