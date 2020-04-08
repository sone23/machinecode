#include "Scanner.h"

TokenClass ScannerClass::GetNextToken()
{
	string lexeme;
	StateMachineClass sm;
	TokenType CTT;
	MachineState current = START_STATE;
	do {
		char c = mFin.get();
		lexeme += c;
		if (lexeme == "\n") {
			mLineNumber += 1;
		}
		current = sm.UpdateState(c, CTT);
		if (current == START_STATE || current == COMMENT_STATE 
			|| current == LINECOMMENT_STATE) {
			lexeme = "";
		}
	} while (current != CANTMOVE_STATE);
	
	if (CTT == BAD_TOKEN) {
		cout << "Bad Token" << endl;
		exit(1);
	}
	mFin.unget();
	lexeme.pop_back();
	//std::cout << lexeme << " " << lexeme.length() << std::endl;
	TokenClass TC(CTT, lexeme);
	TC.CheckReserved();
	return TC;
}

TokenClass ScannerClass::PeekNextToken()
{
	int current_line = GetLineNumber();
	char c = mFin.tellg();
	TokenClass tc = GetNextToken();
	if (!mFin) // if we triggered EOF, then seekg doesn't work,
		mFin.clear();
	mFin.seekg(c);
	mLineNumber = current_line;
	return tc;
}

int ScannerClass::GetLineNumber()
{
	return mLineNumber;
}

ScannerClass::ScannerClass(string input)
{
	MSG("Initializing ScannerClass object");
	mFin.open(input);
	mLineNumber = 1;
}
