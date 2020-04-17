#include "StateMachine.h"

StateMachineClass::StateMachineClass()
{
	for (int i = 0; i < LAST_STATE; i++) {
		for (int j = 0; j < LAST_CHAR; j++)
		{
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}
	mCurrentState = START_STATE;
	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][LPAREN] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN] = RPAREN_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	mLegalMoves[START_STATE][LESSTHAN_CHAR] = LESSTHAN_STATE;
	mLegalMoves[START_STATE][LESSEQUAL_CHAR] = LESSEQUAL_STATE;
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
	mLegalMoves[START_STATE][GREATEREQUAL_CHAR] = GREATEREQUAL_STATE;
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[START_STATE][EXCLAMATION_CHAR] = EXCLAMATION_STATE;
	mLegalMoves[START_STATE][AND_CHAR] = HALF_AND_STATE;
	mLegalMoves[START_STATE][OR_CHAR] = HALF_OR_STATE;

	mLegalMoves[COMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	mLegalMoves[COMMENT_STATE][PLUS_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LCURLY_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][RCURLY_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][SEMICOLON_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][ASSIGNMENT_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LETTER_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][DIGIT_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][WHITESPACE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][NEWLINE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LPAREN] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][RPAREN] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][SEMICOLON_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LESSTHAN_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][GREATER_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[COMMENT_STATE][DIVIDE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][EXCLAMATION_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][AND_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][OR_CHAR] = COMMENT_STATE;


	mLegalMoves[LESSTHAN_STATE][LESSTHAN_CHAR] = INSERTION_STATE;

	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[LESSTHAN_STATE][LESSTHAN_CHAR] = INSERTION_STATE;

	mLegalMoves[LINECOMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	mLegalMoves[LINECOMMENT_STATE][PLUS_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LCURLY_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][RCURLY_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][SEMICOLON_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][ASSIGNMENT_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LETTER_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][DIGIT_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][WHITESPACE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;
	mLegalMoves[LINECOMMENT_STATE][LPAREN] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][RPAREN] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][SEMICOLON_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LESSTHAN_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][GREATER_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][TIMES_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][EXCLAMATION_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][AND_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][OR_CHAR] = LINECOMMENT_STATE;

	mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;
	mLegalMoves[LESSTHAN_STATE][ASSIGNMENT_CHAR] = LESSEQUAL_STATE;
	mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR] = GREATEREQUAL_STATE;
	mLegalMoves[EXCLAMATION_STATE][ASSIGNMENT_CHAR] = NOTEQUAL_STATE;
	mLegalMoves[HALF_AND_STATE][AND_CHAR] = AND_STATE;
	mLegalMoves[HALF_OR_STATE][OR_CHAR] = OR_STATE;

	mLegalMoves[PLUS_STATE][ASSIGNMENT_CHAR] = PLUS_EQUAL_STATE;
	mLegalMoves[MINUS_STATE][ASSIGNMENT_CHAR] = MINUS_EQUAL_STATE;


	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = COMMENT_STATE;

	mLegalMoves[TIMES_STATE][DIVIDE_CHAR] = START_STATE;

	for (int i = 0; i < LAST_STATE; i++)
	{
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}
	mCorrespondingTokenTypes[LESSTHAN_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] = AND;
	mCorrespondingTokenTypes[OR_STATE] = OR;
	mCorrespondingTokenTypes[PLUS_EQUAL_STATE] = PLUS_EQUAL_TOKEN;
	mCorrespondingTokenTypes[MINUS_EQUAL_STATE] = MINUS_EQUAL_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType& correspondingTokenType)
{
	CharacterType charType = BAD_CHAR;
	if (isdigit(currentCharacter))
		charType = DIGIT_CHAR;
	else if (isalpha(currentCharacter))
		charType = LETTER_CHAR;
	else if (currentCharacter == '/')
		charType = DIVIDE_CHAR;
	else if (currentCharacter == '*')
		charType = TIMES_CHAR;
	else if (currentCharacter == '+')
		charType = PLUS_CHAR;
	else if (currentCharacter == '-')
		charType = MINUS_CHAR;
	else if (currentCharacter == '(')
		charType = LPAREN;
	else if (currentCharacter == ')')
		charType = RPAREN;
	else if (currentCharacter == '{')
		charType = LCURLY_CHAR;
	else if (currentCharacter == '}')
		charType = RCURLY_CHAR;
	else if (currentCharacter == '=')
		charType = ASSIGNMENT_CHAR;
	else if (currentCharacter == ';')
		charType = SEMICOLON_CHAR;
	else if (currentCharacter == '<')
		charType = LESSTHAN_CHAR;
	else if (currentCharacter == '>')
		charType = GREATER_CHAR;
	else if (currentCharacter == '!')
		charType = EXCLAMATION_CHAR;
	else if (currentCharacter == '&')
		charType = AND_CHAR;
	else if (currentCharacter == '|')
		charType = OR_CHAR;
	if (isspace(currentCharacter))
		charType = WHITESPACE_CHAR;
	if (currentCharacter == '\n')
		charType = NEWLINE_CHAR;
	else if (currentCharacter == EOF)
		charType = ENDFILE_CHAR;
	

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];

	mCurrentState = mLegalMoves[mCurrentState][charType];

	return mCurrentState;
}


