#pragma once
#include "StateMachine.h"
#include <fstream>

class ScannerClass {
public:
	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int GetLineNumber();
	ScannerClass(string input);
private:
	ifstream mFin;
	int mLineNumber;
};
