#include <iostream>
#include "MaxelerSimpleVM.h"

MaxelerSimpleVM::MaxelerSimpleVM() :
        iDataSize(0),
        iData(NULL),
        iImageSize(0),
        iInstructionPointer(0),
        iStackPointer(0) {
}

MaxelerSimpleVM::~MaxelerSimpleVM() {
    delete[] iData;
    iData = NULL;
}

bool MaxelerSimpleVM::LoadImage(const string& aImagePath) {
    bool result = true;
    FILE * pFile;
    char imageAsciiHexaIntValue [KVmImageLineSize];
    //TODO: need to test all kinds of relative and absolute paths.
    errno_t error = fopen_s(&pFile, aImagePath.c_str(), "r");
    if (pFile == NULL || 0 != error) {
        perror ("Error opening file");
        result = false;
    } else {
        fgets (imageAsciiHexaIntValue , KVmImageLineSize , pFile);
        iDataSize = AsciiHexaToInt(imageAsciiHexaIntValue);
        if (0 < iDataSize) {
            // for debugging:
            //cout << "Found data size in image: " << iDataSize << endl;
            if(NULL != iData) {
                delete[] iData;
                iData = NULL;
            }
            iData = new int[iDataSize];
            fgets (imageAsciiHexaIntValue , KVmImageLineSize , pFile);
            iImageSize = AsciiHexaToInt(imageAsciiHexaIntValue);
            if (0 < iImageSize && iImageSize <= iDataSize) {
                int ii = 0;
                for(; ii < iImageSize && !feof(pFile) ; ++ii) {
                    fgets (imageAsciiHexaIntValue , KVmImageLineSize , pFile);
                    iData[ii] = AsciiHexaToInt(imageAsciiHexaIntValue);
                }
                // for debugging:
/*
                if(feof(pFile)) {
                    cout << "End of file at index " << ii << endl;
                } else {
                    cout << "iData[";
                    for(int jj = 0; jj < iImageSize; ++jj) {
                        cout << iData[jj];
                        if(1+jj < iImageSize) {
                            cout << ", ";
                        }
                    }
                    cout << ']' << endl;
                }
*/
            } else {
                cout << "Found bad image size " << iImageSize << " for a data size of " << iDataSize << endl;
                result = false;
            }
        } else {
            cout << "Found bad data size in image: " << iDataSize << endl;
            result = false;
        }
        fclose (pFile);
    }
    return result;
}

bool MaxelerSimpleVM::ExecuteLoadedImage() {
    bool result = true;
    if(iImageSize > iDataSize || 0 >= iDataSize || 0 >= iImageSize || NULL == iData) {
        cout << "No valid image loaded" << endl;
    } else {
        iInstructionPointer = 0;
        iStackPointer = iDataSize;
        bool keepExecutingImage = true;
        try {
            do {
                keepExecutingImage = ExecuteInstruction();
            } while (keepExecutingImage);
        } catch (VmException vmex) {
            cout << vmex.what() << endl;
            cout << "instruction pointer = " << iInstructionPointer << endl;
            cout << "stack pointer = " << iStackPointer << endl;
            cout << "image size = " << iImageSize << endl;
            cout << "data size = " << iDataSize << endl;
            result = false;
        }
    }
    return result;
}

int MaxelerSimpleVM::AsciiHexaToInt(const string& aAsciiHexaString) {
    int result = 0;
    if (KNumberOfHexaCharsInOneInt <= aAsciiHexaString.length()) {
        for(int ii = 0 ; ii < KNumberOfHexaCharsInOneInt ; ++ii) {
            char hexaChar = aAsciiHexaString[ii];
            int hexaCharValue = 0;
            if ('0' <= hexaChar && '9' >= hexaChar) {
                hexaCharValue = (int)(hexaChar - '0');
            } else if ('A' <= hexaChar && 'F' >= hexaChar) {
                hexaCharValue = 10 + (int)(hexaChar - 'A');
            } else if ('a' <= hexaChar && 'f' >= hexaChar) {
                hexaCharValue = 10 + (int)(hexaChar - 'a');
            } else {
                cout << "Found image line pretending to be in ASCII hexa: " << aAsciiHexaString << endl;
                result = -1;
                break;
            }
            result += hexaCharValue;
            if ((ii+1) < KNumberOfHexaCharsInOneInt) {
                result = result << KNumberOfBitsInOneHexaChar;
            }
        }
    } else {
        cout << "Found ASCII Hexa string too short: " << aAsciiHexaString << endl;
        result = -1;
    }
    return result;
}

void MaxelerSimpleVM::Push(int aValue) {
    if(iImageSize == iStackPointer) {
        throw new VmStackPushException; 
    }
    iData[--iStackPointer] = aValue;
}

int MaxelerSimpleVM::Pop() {
    if(iDataSize <= iStackPointer) {
        throw new VmStackPopException;
    }
    return iData[iStackPointer++];
}

//TODO: 2 big switch statements are not so good for maintaining the instruction set.
// split into methods, then into classes.

bool MaxelerSimpleVM::ExecuteInstruction() {
    bool result = true;
    int instruction = iData[iInstructionPointer++];
    //cout << instruction << endl;
    int optionalData = instruction & 0x00ffffff;
    int operand1;
    int operand2;
    char inputChar;
    if (0x80000000 & instruction) { //binop instructions
        instruction = (instruction & 0x7f000000) >> 24;
        if(EAdd <= instruction && EIsLessThan >= instruction) {
            operand2 = Pop();
            operand1 = Pop();
            switch(instruction) {
                case EAdd:
                    //cout << "push("<< operand1 << '+' << operand2 << ')' << endl;
                    Push(operand1 + operand2);
                    break;
                case ESubstract:
                    //cout << "push("<< operand1 << '-' << operand2 << ')' << endl;
                    Push(operand1 - operand2);
                    break;
                case EMultiply:
                    //cout << "push("<< operand1 << '*' << operand2 << ')' << endl;
                    Push(operand1 * operand2);
                    break;
                case EDivide:
                    //cout << "push("<< operand1 << '/' << operand2 << ')' << endl;
                    Push(operand1 / operand2);
                    break;
                case EAnd:
                    //cout << "push("<< operand1 << '&' << operand2 << ')' << endl;
                    Push(operand1 & operand2);
                    break;
                case EOr:
                    //cout << "push("<< operand1 << '|' << operand2 << ')' << endl;
                    Push(operand1 | operand2);
                    break;
                case EXor:
                    //cout << "push("<< operand1 << '^' << operand2 << ')' << endl;
                    Push(operand1 ^ operand2);
                    break;
                case EEquals:
                    if(operand1 == operand2) {
                        //cout <<"push(1)" <<endl;
                        Push(1);
                    } else {
                        //cout <<"push(0)" << endl;
                        Push(0);
                    }
                    break;
                case EIsLessThan:
                    if(operand1 < operand2) {
                        //cout <<"push(1)" <<endl;
                        Push(1);
                    } else {
                        //cout <<"push(0)" << endl;
                        Push(0);
                    }
                    break;
                default:
                    throw new VmInstructionException;
            }
        } else {
            throw new VmInstructionException;
        }
    } else { // monop instructions
        instruction = (instruction & 0x7f000000) >> 24;
        switch(instruction) {
            case EPop:
                //cout << "pop()" << endl;
                operand1 = Pop();
                break;
            case EPush:
                //cout << "push("<< optionalData << ')' << endl;
                Push(optionalData);
                break;
            case EPushIp:
                //cout << "puship("<< iInstructionPointer << ')' << endl;
                Push(iInstructionPointer);
                break;
            case EPushSp:
                //cout << "pushsp("<< iStackPointer << ')' << endl;
                Push(iStackPointer);
                break;
            case ELoad:
                //cout << "eloadpop()" << endl;
                operand1 = Pop();
                if(0 <= operand1 && iDataSize > operand1) {
                    //cout << "push(" << iData[operand1] << ") from location " << operand1 << endl;
                    Push(iData[operand1]);
                } else {
                    throw new VmStackOutOfBoundException;
                }
                break;
            case EStore:
                //cout << "estorepop()" << endl;
                operand2 = Pop();
                //cout << "estorepop()" << endl;
                operand1 = Pop();
                if(0 <= operand1 && iDataSize > operand1) {
                    //cout << " set location " << operand1 << " to " << operand2 << endl;
                    iData[operand1] = operand2;
                } else {
                    throw new VmStackOutOfBoundException;
                }
                break;
            case EJump:
                //cout << "ejumppop()" << endl;
                operand2 = Pop();
                //cout << "ejumppop()" << endl;
                operand1 = Pop();
                if(0 != operand2) {
                    if(0 <= operand1 && iDataSize > operand1) {
                        //TODO: currently enabling execution of data. Should it?
                        //cout << "set ip to " << operand1 << "because 0!=" << operand2 << endl;
                        iInstructionPointer = operand1;
                    } else {
                        throw new VmStackOutOfBoundException;
                    }
                }
                break;
            case ENot:
                //cout << "enotpop()" << endl;
                if (0 == Pop()) {
                    //cout << "push(1)" << endl;
                    Push(1);
                } else {
                    //cout << "Push(0)" << endl;
                    Push(0);
                }
                break;
            case EPutc:
                //cout << "eputcpop()" << endl;
                operand1 = Pop() & 0x000000ff;
                if(0x0000000a == operand1) {
                    cout << endl;
                } else {
                    cout << (char)operand1;
                }
                break;
            case EGetc:
                inputChar = getchar();
                operand1 = inputChar;
                operand1 &= 0x000000ff;
                Push(operand1);
                break;
            case EHalt:
                result = false;
                break;
            default:
                throw new VmInstructionException;
        }
    }
    return result;
}