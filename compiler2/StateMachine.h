#pragma once
#ifndef STATEMACHINE
#define STATEMACHINE
#include "Token.h"

enum MachineState {
    START_STATE, IDENTIFIER_STATE, INTEGER_STATE, 
    CANTMOVE_STATE, LESSTHAN_STATE, INSERTION_STATE,
    LPAREN_STATE,RPAREN_STATE, PLUS_STATE,SEMICOLON_STATE,
    ASSIGNMENT_STATE,LCURLY_STATE,RCURLY_STATE,DIVIDE_STATE,
    TIMES_STATE, COMMENT_STATE, LINECOMMENT_STATE, LESSEQUAL_STATE,
    GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOTEQUAL_STATE,PLUS_EQUAL_STATE, MINUS_EQUAL_STATE,
    MINUS_STATE, ENDFILE_STATE, EXCLAMATION_STATE, HALF_AND_STATE, AND_STATE, OR_STATE, HALF_OR_STATE,
    LAST_STATE
};

enum CharacterType {
    LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR,
    BAD_CHAR,LPAREN, RPAREN, LCURLY_CHAR, RCURLY_CHAR,
    SEMICOLON_CHAR, ASSIGNMENT_CHAR, LESSTHAN_CHAR, 
    ENDFILE_CHAR, DIVIDE_CHAR, TIMES_CHAR,NEWLINE_CHAR, 
    LESSEQUAL_CHAR, GREATER_CHAR, GREATEREQUAL_CHAR, 
    EQUAL_CHAR, MINUS_CHAR, EXCLAMATION_CHAR, AND_CHAR, OR_CHAR,
    LAST_CHAR
};


class StateMachineClass
{
    public:
        StateMachineClass();
        MachineState UpdateState(char currentCharacter, 
            TokenType& correspondingTokenType);
    private:
        MachineState mCurrentState;
        MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
        TokenType mCorrespondingTokenTypes[LAST_STATE];
};

#endif