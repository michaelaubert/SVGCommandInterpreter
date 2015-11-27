#pragma once
#pragma warning( disable : 4290 )

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//default buffer size for an ascii int in hexa and new line.
#define KVmImageLineSize 10

#define KNumberOfHexaCharsInOneInt 8
#define KNumberOfBitsInOneHexaChar 4

class VmException: public exception {
};

class VmInstructionException: public VmException {
  virtual const char* what() const throw()
  {
    return "Instruction not supported";
  }
};

class VmStackException: public VmException {
};

class VmStackPopException: public VmStackException {
  virtual const char* what() const throw()
  {
    return "Popping from an empty stack";
  }
};

class VmStackPushException: public VmStackException {
  virtual const char* what() const throw()
  {
    return "Pushing to a full stack";
  }
};

class VmStackOutOfBoundException: public VmStackException {
  virtual const char* what() const throw()
  {
    return "Attempting to access invalid address";
  }
};

class MaxelerSimpleVM {
private:
    enum MonopInstructionSet {
        EPop=0,
        EPush,
        EPushIp,
        EPushSp,
        ELoad,
        EStore,
        EJump,
        ENot,
        EPutc,
        EGetc,
        EHalt
    };
    enum BinopInstructionSet {
        EAdd=0,
        ESubstract,
        EMultiply,
        EDivide,
        EAnd,
        EOr,
        EXor,
        EEquals,
        EIsLessThan
    };

public:
    MaxelerSimpleVM();
    ~MaxelerSimpleVM();

public:
    /**
     * @see Image format specification
     * @param aImagePath path to image file
     * @returns true if image file was successfully loaded
     */
    bool LoadImage(const string& aImagePath);

    /**
     * Main VM loop
     * @returns true if image file was successfully loaded
     */
    bool ExecuteLoadedImage();

private:
    /**
     * @param aAsciiHexaString an ascii string beginning with 8 hexa characters
     * @returns the integer represented by the ascii param
     */
    static int AsciiHexaToInt(const string& aAsciiHexaString);

    /**
     * @param aValue to be pushed to the stack at the end of the data array
     */
    void Push(int aValue) throw(VmStackPushException);

    /**
     * @return the last value pushed to the stack at the end of the data array
     */
    int Pop() throw(VmStackPopException);

    /**
     * decodes and process the next instruction in the data array
     * @see Instruction set specification
     * @returns true if the instruction wasn not Halt (natural end of program)
     */
    bool ExecuteInstruction() throw(VmException);

private:
    int iDataSize;
    int* iData;
    int iImageSize;
    int iInstructionPointer;
    int iStackPointer;

};
