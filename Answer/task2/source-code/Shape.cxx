#include "Shape.h"

/**
 * CAREFUL: experimentation with task2.bin seems to indicate that
 * 'J', 'K', 'M' and 'N' remain in effect (increasing or decreasing the default step of 10)
 * until cancelled by the opposite command.
 *
 * KMoveCommandArray must match Shape::CommandIndex
 */
//TODO: run more testing on task2.bin to confirm assumption above.
// should influence a command optimizer one way or another

static const char KMoveCommandArray[] = {'E', 'A', 'C', 'B', 'R', 'U', 'L', 'D', 'P','J', 'K', 'M', 'N'};

//TODO: use K and N better when they shorten command strings. (half of last moves, long total moves, reuse between move and draw)
// nevermind. this program generates code. what's really missing is a code optimizer to shorten the output.

Shape::Shape(int aBeginX, int aBeginY, int aEndX, int aEndY, int aWidthStep, int aHeightStep) :
        iBeginVertex(aBeginX, aBeginY),
        iEndVertex(aEndX, aEndY),
        iWidthStep(aWidthStep),
        iHeightStep(aHeightStep) {
}

Shape::~Shape() {
}


const Vertex& Shape::GetVertexEnd() const {
    return iEndVertex;
}

const Vertex& Shape::GetVertexBegin() const {
    return iBeginVertex;
}

void Shape::GenerateCommandsToMoveFrom(const Vertex& aOrigin, bool aIsUseBeginVertex, FILE* apFile) {
    Vertex& destination = aIsUseBeginVertex?iBeginVertex:iEndVertex;
    int distanceRight = destination.GetX() - aOrigin.GetX();
    int distanceLeft = aOrigin.GetX() - destination.GetX();
    int distanceUp = destination.GetY() - aOrigin.GetY();
    int distanceDown = aOrigin.GetY() - destination.GetY();
    string commandString;
    // first move the SVG "cursor" to inside the surrounding 20x20 pixels
    // priority to diagonal commands to shorten output
    if(distanceRight >= KDefaultStep || distanceUp >= KDefaultStep || distanceLeft >= KDefaultStep || distanceDown >= KDefaultStep) {
        commandString += KMoveCommandArray[EParenthesis];
        while (distanceRight >= KDefaultStep && distanceUp >= KDefaultStep) {
            distanceRight -= KDefaultStep;
            distanceUp -= KDefaultStep;
            commandString += KMoveCommandArray[EUpRight];
        }
        while (distanceRight >= KDefaultStep && distanceDown >= KDefaultStep) {
            distanceRight -= KDefaultStep;
            distanceDown -= KDefaultStep;
            commandString += KMoveCommandArray[EDownRight];
        }
        while (distanceLeft >= KDefaultStep && distanceUp >= KDefaultStep) {
            distanceLeft -= KDefaultStep;
            distanceUp -= KDefaultStep;
            commandString += KMoveCommandArray[EUpLeft];
        }
        while (distanceLeft >= KDefaultStep && distanceDown >= KDefaultStep) {
            distanceLeft -= KDefaultStep;
            distanceDown -= KDefaultStep;
            commandString += KMoveCommandArray[EDownLeft];
        }
        while (distanceRight >= KDefaultStep) {
            distanceRight -= KDefaultStep;
            commandString += KMoveCommandArray[ERight];
        }
        while (distanceDown >= KDefaultStep) {
            distanceDown -= KDefaultStep;
            commandString += KMoveCommandArray[EDown];
        }
        while (distanceUp >= KDefaultStep) {
            distanceUp -= KDefaultStep;
            commandString += KMoveCommandArray[EUp];
        }
        while (distanceLeft >= KDefaultStep) {
            distanceLeft -= KDefaultStep;
            commandString += KMoveCommandArray[ELeft];
        }
        commandString += KMoveCommandArray[EParenthesis];
    }
    // then prepare to bridge the last gap with a shortened step (using 'J' and 'M' modifiers) command
    string undoStepShorteningCommandString;
    if(0 < distanceRight) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceRight) ; ++ii) {
            commandString += KMoveCommandArray[EShortenHorizontalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeHorizontalStep];
        }
    } else if (0 < distanceLeft) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceLeft) ; ++ii) {
            commandString += KMoveCommandArray[EShortenHorizontalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeHorizontalStep];
        }
    }
    if(0 < distanceUp) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceUp) ; ++ii) {
            commandString += KMoveCommandArray[EShortenVerticalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeVerticalStep];
        }
    } else if (0 < distanceDown) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceDown) ; ++ii) {
            commandString += KMoveCommandArray[EShortenVerticalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeVerticalStep];
        }
    }
    // brige last gap
    if(distanceRight > 0 || distanceUp > 0 || distanceLeft > 0 || distanceDown > 0) {
        commandString += KMoveCommandArray[EParenthesis];
        if(distanceRight > 0 && distanceUp > 0) {
            commandString += KMoveCommandArray[EUpRight];
        } else if (distanceRight > 0 && distanceDown > 0) {
            commandString += KMoveCommandArray[EDownRight];
        } else if (distanceLeft > 0 && distanceDown > 0) {
            commandString += KMoveCommandArray[EDownLeft];
        } else if (distanceLeft > 0 && distanceUp > 0) {
            commandString += KMoveCommandArray[EUpLeft];
        } else if (distanceRight > 0) {
            commandString += KMoveCommandArray[ERight];
        } else if (distanceUp > 0) {
            commandString += KMoveCommandArray[EUp];
        } else if (distanceDown > 0) {
            commandString += KMoveCommandArray[EDown];
        } else {
            commandString += KMoveCommandArray[ELeft];
        }
        commandString += KMoveCommandArray[EParenthesis];
    }
    // undo step shortening (with 'K' and 'N')
    commandString += undoStepShorteningCommandString;
    if (0 < commandString.length()) {
        if (0 > fputs(commandString.c_str(), apFile)) {
            cout << "Move commands write failed" << endl;
        }
    }
}

void Shape::DrawUp(FILE* apFile) {
    int distanceY = iHeightStep;
    string commandString;
    string undoStepShorteningCommandString;
    while(distanceY >= KDefaultStep) {
        commandString += KMoveCommandArray[EUp];
        distanceY -= KDefaultStep;
    }
    // Last step in the line may be shorter than the default 10 so we use 'M'
    if (distanceY > 0) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceY) ; ++ii) {
            commandString += KMoveCommandArray[EShortenVerticalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeVerticalStep];
        }
        commandString += KMoveCommandArray[EUp];
        // undo eventual step shortening with 'N'
        commandString += undoStepShorteningCommandString;
    }
    if (0 > fputs(commandString.c_str(), apFile)) {
        cout << "Draw Up commands write failed" << endl;
    }
}

void Shape::DrawDown(FILE* apFile) {
    int distanceY = iHeightStep;
    string commandString;
    string undoStepShorteningCommandString;
    while(distanceY >= KDefaultStep) {
        commandString += KMoveCommandArray[EDown];
        distanceY -= KDefaultStep;
    }
    // Last step in the line may be shorter than the default 10 so we use 'M'
    if (distanceY > 0) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceY) ; ++ii) {
            commandString += KMoveCommandArray[EShortenVerticalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeVerticalStep];
        }
        commandString += KMoveCommandArray[EDown];
        // undo eventual step shortening with 'N'
        commandString += undoStepShorteningCommandString;
    }
    if (0 > fputs(commandString.c_str(), apFile)) {
        cout << "Draw Down commands write failed" << endl;
    }
}

void Shape::DrawLeft(FILE* apFile) {
    int distanceX = iWidthStep;
    string commandString;
    string undoStepShorteningCommandString;
    while(distanceX >= KDefaultStep) {
        commandString += KMoveCommandArray[ELeft];
        distanceX -= KDefaultStep;
    }
    // Last step in the line may be shorter than the default 10 so we use 'J'
    if (distanceX > 0) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceX) ; ++ii) {
            commandString += KMoveCommandArray[EShortenHorizontalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeHorizontalStep];
        }
        commandString += KMoveCommandArray[ELeft];
        // undo eventual step shortening with 'K'
        commandString += undoStepShorteningCommandString;
    }
    if (0 > fputs(commandString.c_str(), apFile)) {
        cout << "Draw Left commands write failed" << endl;
    }
}

void Shape::DrawRight(FILE* apFile) {
    int distanceX = iWidthStep;
    string commandString;
    string undoStepShorteningCommandString;
    while(distanceX >= KDefaultStep) {
        commandString += KMoveCommandArray[ERight];
        distanceX -= KDefaultStep;
    }
    // Last step in the line may be shorter than the default 10 so we use 'J'
    if (distanceX > 0) {
        for(int ii = 0 ; ii < (KDefaultStep - distanceX) ; ++ii) {
            commandString += KMoveCommandArray[EShortenHorizontalStep];
            undoStepShorteningCommandString += KMoveCommandArray[EEnlargeHorizontalStep];
        }
        commandString += KMoveCommandArray[ERight];
        // undo eventual step shortening with 'K'
        commandString += undoStepShorteningCommandString;
    }
    if (0 > fputs(commandString.c_str(), apFile)) {
        cout << "Draw Right commands write failed" << endl;
    }
}
