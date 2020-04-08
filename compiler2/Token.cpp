#include "Token.h"
#include <algorithm>
#include <iostream>

int case_insensitive_match(string s1, string s2) {
	//convert s1 and s2 into lower case strings
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return 1; //The strings are same
	return 0; //not matched
}

TokenClass::TokenClass()
{
}

TokenClass::TokenClass(TokenType type, const string& lexeme){
	mType = type;
	mLexeme = lexeme;
}



void TokenClass::CheckReserved()
{

	for (int i = 0; i <= ENDFILE_TOKEN; i++) {
		if (case_insensitive_match(mLexeme, gTokenTypeNames[i])) {
			mType = static_cast<TokenType>(i);
		}
	}
}

TokenType TokenClass::GetTokenType() const
{
	return mType;
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc)
{
	string lexeme = tc.GetLexeme();
	TokenType type = tc.GetTokenType();
	string name = tc.GetTokenTypeName(type);
	out << type << " " << lexeme << " "<< name;
	return out;
}

