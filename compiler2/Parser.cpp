#include "Parser.h"

ParserClass::ParserClass(ScannerClass* sc, SymbolTableClass* st)
{
	mSt = st;
	mSc = sc;
}

StartNode* ParserClass::Start()
{
	ProgramNode* pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;


}

ProgramNode* ParserClass::Program()
{
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	ProgramNode* pn = new ProgramNode(bn);
	return pn;
}

BlockNode* ParserClass::Block()
{
	Match(LCURLY_TOKEN);
	StatementGroupNode* sgn = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode* bn = new BlockNode(sgn);
	return bn;
}

StatementGroupNode* ParserClass::StatementGroup()
{

	StatementGroupNode* sgn = new StatementGroupNode();
	while (true) {
		StatementNode* sn = Statement();
		if (sn == NULL) {
			break;
		}
		sgn->AddStatement(sn);
	}
	return sgn;
}

StatementNode* ParserClass::Statement()
{
	TokenClass t = mSc->PeekNextToken();
	if (t.GetTokenType() == INT_TOKEN) {
		return DeclarationStatement();
	}
	else if (t.GetTokenType() == IDENTIFIER_TOKEN){
		return AssignmentStatement();
	}

	else if (t.GetTokenType() == COUT_TOKEN) {
		return CoutStatement();
	}
	else if (t.GetTokenType() == LCURLY_TOKEN) {
		return Block();
	}
	else if (t.GetTokenType() == IF_TOKEN) {
		return IfStatement();
	}
	else if (t.GetTokenType() == WHILE_TOKEN) {
		return WhileStatement();
	}
	return NULL;
}

DeclarationStateNode* ParserClass::DeclarationStatement()
{
	
	Match(INT_TOKEN);
	IdentifierNode* in = Identifier();
	DeclarationStateNode* dsn = new DeclarationStateNode(in);
	Match(SEMICOLON_TOKEN);
	return dsn;
}

AssignmentStatementNode* ParserClass::AssignmentStatement()
{
	IdentifierNode* in = Identifier();
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode* en =  Expression();
	Match(SEMICOLON_TOKEN);
	AssignmentStatementNode* an = new AssignmentStatementNode(in, en);
	return an;

}

CoutStatementNode* ParserClass::CoutStatement()
{
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode* en =  Expression();
	Match(SEMICOLON_TOKEN);
	CoutStatementNode* cn = new CoutStatementNode(en);
	return cn;
}

IdentifierNode* ParserClass::Identifier()
{

	TokenClass tc = Match(IDENTIFIER_TOKEN);
	string lexeme = tc.GetLexeme();
	IdentifierNode* in = new IdentifierNode(lexeme, mSt);
	return in;
}

ExpressionNode* ParserClass::Expression()
{
	ExpressionNode* en = Or();
	return en;
}

IfStatementNode* ParserClass::IfStatement()
{
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	StatementNode* sn = Statement();
	IfStatementNode* ifn = new IfStatementNode(en, sn);
	return ifn;
}

WhileStatementNode* ParserClass::WhileStatement()
{
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	StatementNode* sn = Statement();
	WhileStatementNode* whileNode = new WhileStatementNode(en, sn);
	return whileNode;
}

ExpressionNode* ParserClass::Relational()
{
	ExpressionNode* current = PlusMinus();
	TokenType tt = mSc->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN)
	{
		Match(tt);
		current = new LessNode(current, PlusMinus());
	}
	else if (tt == LESSEQUAL_TOKEN)
	{
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	}
	else if (tt == GREATER_TOKEN)
	{
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	}
	else if (tt == GREATEREQUAL_TOKEN)
	{
		Match(tt);
		 current = new GreaterEqualNode( current, PlusMinus());
	}
	else if (tt == EQUAL_TOKEN)
	{
		Match(tt);
		current = new EqualNode( current, PlusMinus());
	}
	else if (tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		current = new NotEqualNode( current, PlusMinus());
	}
	return current;
}

ExpressionNode* ParserClass::TimesDivide()
{
	ExpressionNode* current = Factor();
	while (true) {
		TokenType tt = mSc->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if (tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current, Factor());
		}
		return current;
	}
	
}

ExpressionNode* ParserClass::PlusMinus()
{
	ExpressionNode* current = TimesDivide();
	while (true)
	{
		TokenType tt = mSc->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode* ParserClass::And()
{
	ExpressionNode* current = Relational();
	while (true) {
		TokenType tt = mSc->PeekNextToken().GetTokenType();
		if (tt == AND) {
			Match(tt);
			current = new AndNode(current, Relational());
		}
		return current;
	}
}

ExpressionNode* ParserClass::Or()
{
	ExpressionNode* current = And();
	while (true) {
		TokenType tt = mSc->PeekNextToken().GetTokenType();
		if (tt == OR) {
			Match(tt);
			current = new OrNode(current, And());
		}
		return current;
	}
}

ExpressionNode* ParserClass::Factor()
{
	TokenType tt = mSc->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		return  Identifier();
	}
	else if (tt == INTEGER_TOKEN) {
		return Integer();
	}
	else if (tt == LPAREN_TOKEN) {
		Match(LPAREN_TOKEN);
		return Expression();
		Match(RPAREN_TOKEN);
	}
	else {
		return NULL;
	}
}

IntegerNode* ParserClass::Integer()
{
	TokenClass tc = Match(INTEGER_TOKEN);
	int lexeme = atoi(tc.GetLexeme().c_str());
	IntegerNode* in = new IntegerNode(lexeme);
	return in;
}



TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mSc->GetNextToken();
	if (currentToken.GetTokenType() != expectedType)
	{
		cerr << "Error in ParserClass::Match. " << endl;
		cerr << "Expected token type " <<
			TokenClass::GetTokenTypeName(expectedType) <<
			", but got type " << currentToken.GetTokenTypeName()
			<< endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " <<
		currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}
