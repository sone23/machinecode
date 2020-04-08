#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include <iostream>
#include "Parser.h"

void CodeAndExecute(string inputFile)
{
	// Create scanner, symbol table, and parser objects.
	ScannerClass scanner(inputFile);
	SymbolTableClass symbolTable;
	ParserClass parser(&scanner, &symbolTable);
	// Do the parsing, which results in a parse tree.
	StartNode* root = parser.Start();
	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	machineCode.PrintAllMachineCodes();
	// Execute the machine code instructions previously created
	machineCode.Execute();
	// cleanup recursively
	delete root;
}
int main() {
	CodeAndExecute("data.txt");
	/*InstructionsClass code;
	
	cout << "Success!";

	code.Finish();
	code.Execute();*/

	return 0;
}

