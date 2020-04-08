#pragma once
#include "Scanner.h"
#include "Node.h"
#include "Token.h"
#include "Debug.h"

class ParserClass {
public:
	ParserClass(ScannerClass* sc, SymbolTableClass* st);
	StartNode* Start();
	ProgramNode* Program();
	BlockNode* Block();
	StatementGroupNode* StatementGroup();
	StatementNode* Statement();
	DeclarationStateNode* DeclarationStatement();
	IdentifierNode* Identifier();
	ExpressionNode* Expression();
	ExpressionNode* Relational();
	ExpressionNode* TimesDivide();
	ExpressionNode* PlusMinus();
	ExpressionNode* And();
	ExpressionNode* Or();
	ExpressionNode* Factor();
	IntegerNode* Integer();
	IfStatementNode* IfStatement();
	WhileStatementNode* WhileStatement();
	AssignmentStatementNode* AssignmentStatement();
	CoutStatementNode* CoutStatement();
	TokenClass Match(TokenType expectedType);
private:
	ScannerClass* mSc;
	SymbolTableClass* mSt;
};
