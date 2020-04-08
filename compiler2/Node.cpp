#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

StartNode::StartNode(ProgramNode* pn)
{
	mPn = pn;
}

void StartNode::Interpret()
{
	mPn->Interpret();
}

StartNode::~StartNode()
{
	delete mPn;
	MSG("StartNode Deleting");
}

void StartNode::Code(InstructionsClass& machineCode)
{
	mPn->Code(machineCode);
}


ProgramNode::ProgramNode(BlockNode* bn)
{
	//MSG("ProgramNode Created");
	mBn = bn;
}

void ProgramNode::Interpret()
{
	mBn->Interpret();
}

ProgramNode::~ProgramNode()
{
	delete mBn;
	MSG("ProgramNode Deleting");
}

void ProgramNode::Code(InstructionsClass& machineCode)
{
	mBn->Code(machineCode);
}

StatementNode::StatementNode()
{
	//MSG("StatementNode Created");
}

void StatementNode::Interpret()
{
}

StatementNode::~StatementNode()
{
}

void StatementNode::Code(InstructionsClass& machineCode)
{
}

BlockNode::BlockNode(StatementGroupNode* sgn)
{
	mSgn = sgn;
}

void BlockNode::Interpret()
{
	mSgn->Interpret();
}

BlockNode::~BlockNode()
{
	delete mSgn;
	MSG("BlockNode Deleting");
}

void BlockNode::Code(InstructionsClass& machineCode)
{
	mSgn->Code(machineCode);
}

void StatementGroupNode::AddStatement(StatementNode* sn)
{
	stl.push_back(sn);
}

StatementGroupNode::StatementGroupNode()
{
}

void StatementGroupNode::Interpret()
{
	for (int i = 0; i < stl.size(); i++)
	{
		stl[i]->Interpret();
	}
}

StatementGroupNode::~StatementGroupNode()
{
	for (int i = 0; i < stl.size(); i++)
	{
		delete stl[i];
	}
	MSG("StatementGroupNode deleting");
}

void StatementGroupNode::Code(InstructionsClass& machineCode)
{
	for (int i = 0; i < stl.size(); i++)
	{
		stl[i]->Code(machineCode);
	}
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en)
{
	mIn = in;
	mEn = en;
}

AssignmentStatementNode::~AssignmentStatementNode()
{
	delete mIn;
	delete mEn;
	MSG("AssignmentNode Deleting");
}

void AssignmentStatementNode::Interpret()
{
	int eval = mEn->Evaluate();
	mIn->SetValue(eval);
}

void AssignmentStatementNode::Code(InstructionsClass& machineCode)
{
	mEn->CodeEvaluate(machineCode);
	int index = mIn->GetIndex();
	machineCode.PopAndStore(index);

}

IntegerNode::IntegerNode(int n)
{
	mInteger = n;
}

int IntegerNode::Evaluate()
{
	return mInteger;
}

void IntegerNode::CodeEvaluate(InstructionsClass& machineCode)
{
	machineCode.PushValue(mInteger);
}

IdentifierNode::IdentifierNode(string label, SymbolTableClass* table)
{
	mLabel = label;
	mtable = table;
}

void IdentifierNode::DeclareVariable()
{
	mtable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v)
{
	mtable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex()
{
	int index = mtable->GetIndex(mLabel);
	return index;
}

int IdentifierNode::Evaluate()
{
	int value = mtable->GetValue(mLabel);
	return value;
}

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode)
{
	machineCode.PushVariable(GetIndex());
}

DeclarationStateNode::DeclarationStateNode(IdentifierNode* in)
{
	mIn = in;
}

DeclarationStateNode::~DeclarationStateNode()
{
	delete mIn;
	MSG("DeclarationNode Deleting");
}

void DeclarationStateNode::Interpret()
{
	mIn->DeclareVariable();
}

void DeclarationStateNode::Code(InstructionsClass& machineCode)
{
	mIn->DeclareVariable();
}

CoutStatementNode::CoutStatementNode(ExpressionNode* en)
{
	mEn = en;
}

CoutStatementNode::~CoutStatementNode()
{
	delete mEn;
	MSG("CoutNode Deleting");
}

void CoutStatementNode::Interpret()
{
	int eval = mEn->Evaluate();
	cout << eval << "\r" << endl;
}

void CoutStatementNode::Code(InstructionsClass& machineCode)
{
	mEn->CodeEvaluate(machineCode);
	machineCode.PopAndWrite();
}

ExpressionNode::ExpressionNode()
{
}

ExpressionNode::~ExpressionNode()
{
	MSG("ExpressionNode Deleting");
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* lhs, ExpressionNode* rhs)
{
	mLhs = lhs;
	mRhs = rhs;
}

BinaryOperatorNode::~BinaryOperatorNode()
{
	delete mLhs;
	delete mRhs;
	MSG("BinaryOperatorNode Deleting");
}

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int PlusNode::Evaluate()
{
	return mLhs->Evaluate() + mRhs->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int MinusNode::Evaluate()
{
	return mLhs->Evaluate() + mRhs->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int TimesNode::Evaluate()
{
	return mLhs->Evaluate() * mRhs->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int DivideNode::Evaluate()
{
	return mLhs->Evaluate() / mRhs->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int LessNode::Evaluate()
{
	if (mLhs->Evaluate() < mRhs->Evaluate())
		return 1;
	else {
		return 0;
	}
}

void LessNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int LessEqualNode::Evaluate()
{
	if (mLhs->Evaluate() <= mRhs->Evaluate())
		return 1;
	else {
		return 0;
	}
}

void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int GreaterNode::Evaluate()
{
	if (mLhs->Evaluate() > mRhs->Evaluate())
		return 1;
	return 0;
}

void GreaterNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int GreaterEqualNode::Evaluate()
{
	if (mLhs->Evaluate() >= mRhs->Evaluate())
		return 1;
	return 0;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right){
}

int EqualNode::Evaluate()
{
	if (mLhs->Evaluate() == mRhs->Evaluate())
		return 1;
	return 0;
}

void EqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int NotEqualNode::Evaluate()
{
	if (mLhs->Evaluate() != mRhs->Evaluate())
		return 1;
	return 0;
}

void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}

IfStatementNode::IfStatementNode(ExpressionNode* en, StatementNode* sn)
{
	mExpression = en;
	mStatement = sn;
}

IfStatementNode::~IfStatementNode()
{
	delete mExpression;
	delete mStatement;
}

void IfStatementNode::Interpret()
{
	if (mExpression->Evaluate()) {
		mStatement->Interpret();
	}
}

void IfStatementNode::Code(InstructionsClass& machineCode)
{
	mExpression->CodeEvaluate(machineCode);
	unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char* address1 = machineCode.GetAddress();
	mStatement->Code(machineCode);
	unsigned char* address2 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
}

WhileStatementNode::WhileStatementNode(ExpressionNode* en, StatementNode* sn)
{
	mExpression = en;
	mStatement = sn;
}

WhileStatementNode::~WhileStatementNode()
{
	delete mExpression;
	delete mStatement;
}

void WhileStatementNode::Interpret()
{
	while (mExpression->Evaluate()) {
		mStatement->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass& machineCode)
{
	unsigned char* address1 = machineCode.GetAddress();
	mExpression->CodeEvaluate(machineCode);
	unsigned char* InsertAddressToSkip = machineCode.SkipIfZeroStack();
	unsigned char* address2 = machineCode.GetAddress();
	mStatement->Code(machineCode);
	unsigned char* InsertAddressToJump = machineCode.Jump();
	unsigned char* address3 = machineCode.GetAddress();
	InsertAddressToSkip = (unsigned char*) (address3 - address2);
	InsertAddressToJump = (unsigned char*) (address1 - address3);



}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right) 
	: BinaryOperatorNode(left, right) {
}

int AndNode::Evaluate()
{
	if (mLhs->Evaluate() && mRhs->Evaluate())
		return 1;
	return 0;
}

void AndNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int OrNode::Evaluate()
{
	if (mLhs->Evaluate() || mRhs->Evaluate())
		return 1;
	return 0;
}

void OrNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
}
