#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "MaxelerSvgGenerator.h"
#include "LeftDownShape.h"
#include "LeftUpShape.h"
#include "RightDownShape.h"
#include "RightUpShape.h"
#include "UpLeftShape.h"
#include "UpRightShape.h"

using namespace std;

/**
 * The program needs to draw 21 shapes on the picture
 * The order in which they are added should not matter
 */

//TODO: read the shapes from a configuration file

int main (int argc, char *argv[]) {
    int result = 0;
    MaxelerSvgGenerator* generator = new MaxelerSvgGenerator();
    Shape* shape = NULL;
    if(NULL == generator) {
        cout << "Can't create svg generator: not enough memory" << endl;
        result = 1;
    }
    if (0 == result) {
        shape = new UpRightShape(0,0,0,40,10,10);
        if(NULL == shape) {
            cout << "Can't create UpRightShape(0,0,0,40,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new UpRightShape(0,360,0,400,10,10);
        if(NULL == shape) {
            cout << "Can't create UpRightShape(0,360,0,400,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new UpLeftShape(400,0,400,40,10,10);
        if(NULL == shape) {
            cout << "Can't create UpLeftShape(400,0,400,40,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new UpLeftShape(400,360,400,400, 10, 10);
        if(NULL == shape) {
            cout << "Can't create UpLeftShape(400,360,400,400,10,10): not enough memory" << endl;
            result = 1;
        }
    }

    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(30,195,70,195,10,10);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(30,195,70,195,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(50,120,90,120,10,10);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(50,120,90,120,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(103,65,143,65,10,10);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(103,65,143,65,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(178,45,218,45,10,10);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(178,45,218,45,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(119,157,279,157,40,40);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(119,157,279,157,40,40): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(139,202,259,202,30,30);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(139,202,259,202,30,30): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(159,237,239,237,20,20);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(159,237,239,237,20,20): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(179,262,219,262,10,10);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(179,262,219,262,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightDownShape(190,277,210,277,5,5);
        if(NULL == shape) {
            cout << "Can't create RightDownShape(186,277,210,277,5,5): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new LeftDownShape(293,64,253,64,10,10);
        if(NULL == shape) {
            cout << "Can't create LeftDownShape(293,64,253,64,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new LeftDownShape(349,118,309,118,10,10);
        if(NULL == shape) {
            cout << "Can't create LeftDownShape(349,118,309,118,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new LeftDownShape(370,194,330,194,10,10);
        if(NULL == shape) {
            cout << "Can't create LeftDownShape(370,194,330,194,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new LeftUpShape(350,269,310,269,10,10);
        if(NULL == shape) {
            cout << "Can't create LeftUpShape(350,269,310,269,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new LeftUpShape(296,324,256,324,10,10);
        if(NULL == shape) {
            cout << "Can't create LeftUpShape(296,324,256,324,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightUpShape(180,344,220,344,10,10);
        if(NULL == shape) {
            cout << "Can't create RightUpShape(180,344,220,344,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightUpShape(105,325,145,325,10,10);
        if(NULL == shape) {
            cout << "Can't create RightUpShape(105,325,145,325,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        shape = new RightUpShape(50,271,90,271,10,10);
        if(NULL == shape) {
            cout << "Can't create RightUpShape(50,271,90,271,10,10): not enough memory" << endl;
            result = 1;
        }
    }
    if(0 == result) {
        generator->AddShape(shape);
        shape = NULL;
        generator->GenerateSvgCommands();
    }
    delete generator;
    return result;
}