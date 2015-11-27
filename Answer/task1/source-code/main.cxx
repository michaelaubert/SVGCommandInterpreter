#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "MaxelerSimpleVM.h"

using namespace std;

//TODO: better return codes.

int main (int argc, char *argv[]) {
    int result = 0;
    if (argc < 2) {
        cout << "Usage: " << argv[0] << "imagePath" << endl;
        result = 1;
    } else {
        MaxelerSimpleVM* simpleVm = new MaxelerSimpleVM();
        if(NULL == simpleVm) {
            cout << "Can't create virtual machine: not enough memory" << endl;
            result = 1;
        } else {
            if (simpleVm->LoadImage(argv[1])) {
                if (!simpleVm->ExecuteLoadedImage()) {
                    cout << "Image execution failed: bad VM or corrupt image" << endl;
                    result = 1;
                }
            } else {
                cout << "Can't load executable image: not enough memory, file not found or corrupt file" << endl;
                result = 1;
            }
            delete simpleVm;
        }
    }
    return result;
}