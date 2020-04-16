#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <string>
#include <string>
#include "Symbol.h"
#include "instructions.h"
#include "Debug.h"

class Node {
public:
	Node(); 
	virtual void Interpret() = 0;
	virtual void Code(InstructionsClass& machineCode) = 0;
	virtual ~Node();
};

class StatementNode :Node {
public:
	StatementNode();
	void Interpret();
	~StatementNode();
	void Code(InstructionsClass& machineCode);

};

class StatementGroupNode :public Node {
public:
	void AddStatement(StatementNode* sn);
	StatementGroupNode();
	void Interpret();
	~StatementGroupNode();
	std::vector<StatementNode*> stl;
	void Code(InstructionsClass& machineCode);
};



class BlockNode :public StatementNode {
public:
	BlockNode(StatementGroupNode* sgn);
	void Interpret();
	~BlockNode();
	StatementGroupNode* mSgn;
	void Code(InstructionsClass& machineCode);

};

class ProgramNode :Node {
public:
	ProgramNode(BlockNode* bn);
	void Interpret();
	~ProgramNode();
	BlockNode* mBn;
	void Code(InstructionsClass& machineCode);
};

class StartNode:Node {
public:
	StartNode(ProgramNode* pn);
	void Interpret();
	~StartNode();
	ProgramNode* mPn;
	void Code(InstructionsClass& machineCode);

};

class ExpressionNode {
public:
	virtual int Evaluate() = 0;
	ExpressionNode();
	virtual ~ExpressionNode();
	virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;

};

class IdentifierNode :public ExpressionNode {
public:
	string mLabel;
	SymbolTableClass* mtable;
	IdentifierNode(string label, SymbolTableClass* table);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};



class DeclarationStateNode :public StatementNode {
public:
	DeclarationStateNode(IdentifierNode* in);
	~DeclarationStateNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	IdentifierNode* mIn;
};

class AssignmentStatementNode:public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
	~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	IdentifierNode* mIn;
	ExpressionNode* mEn;
};

class CoutStatementNode :public StatementNode {
public:
	CoutStatementNode(ExpressionNode* en);
	~CoutStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	ExpressionNode* mEn;
};



class IntegerNode:public ExpressionNode {
public:
	IntegerNode(int n);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
private:
	int mInteger;
};

class  BinaryOperatorNode:public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode* mLhs, ExpressionNode* mRhs);
	~BinaryOperatorNode();
protected:
	ExpressionNode* mLhs;
	ExpressionNode* mRhs;

};

class PlusNode:public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class MinusNode :public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class TimesNode :public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class DivideNode :public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class OrNode : public BinaryOperatorNode {
public:
	OrNode (ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};
class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode* en, StatementNode* sn);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	ExpressionNode* mExpression;
	StatementNode* mStatement;
};

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode* en, StatementNode* sn);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	ExpressionNode* mExpression;
	StatementNode* mStatement;
};

#endif

