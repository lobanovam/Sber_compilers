#include <iostream>
#include <FlexLexer.h>
#include <iterator>
#include <ostream>
#include "../include/tokenizer.hpp"

int main() {

    Tokenizer tokenizer;

    TokenTypes token_type = (TokenTypes) tokenizer.lexer->yylex();
    while (token_type != TokenTypes::EOF_TYPE)
    {
       if (tokenizer.GetToken(token_type))
            break;

       token_type = (TokenTypes)tokenizer.lexer->yylex(); 
    }

    tokenizer.printTokens();

    return 0;

}