#include <cctype>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <FlexLexer.h>
#include <math.h>
#include <ostream>
#include <string>
#include <unordered_map>
#include <valarray>
#include "../include/tokenizer.hpp"


int Tokenizer::GetToken(TokenTypes token_type) {

    switch (token_type) {

        case TokenTypes::TYPE_ID:
            Tokens.push_back(*Tokenizer::getType());
            break;

        case TokenTypes::VARIABLE:
            Tokens.push_back(*Tokenizer::getVar());
            break;

        case TokenTypes::KEYWORD:
            Tokens.push_back(*Tokenizer::getKeyWord());
            break;

        case TokenTypes::D_NUMBER:
            Tokens.push_back(*Tokenizer::getDoubleNumber());
            break;
     
        case TokenTypes::I_NUMBER:
            Tokens.push_back(*Tokenizer::getIntNumber());
            break;

        case TokenTypes::STRING:
            Tokens.push_back(*Tokenizer::getString());
            break;
        
        case TokenTypes::OP:
            Tokens.push_back(*Tokenizer::getOp());
            break;

        case TokenTypes::UNCLOSED_STRING:
            std::cout << "SYNTAX ERROR on line (" << Tokenizer::lexer->lineno()<<"): unclosed string"<< std::endl;
            Tokens.pop_back();
            return 1;

        case TokenTypes::UNCLOSED_COMMENT:
            std::cout << "SYNTAX ERROR on line (" << Tokenizer::lexer->lineno()<<"): unclosed comment"<< std::endl;
            return 1;
        
        case TokenTypes::UNKNOWN_TOKEN:
            std::cout << "SYNTAX ERROR on line (" << Tokenizer::lexer->lineno()<<"): symbol \"" << Tokenizer::lexer->YYText() << "\" is unexpected" << std::endl;
            return 1;
    }

    return 0;
}

Token *Tokenizer::getVar() {

    Token *varToken = new Token{};
    varToken->t_type = TokenTypes::VARIABLE;
    varToken->t_arg.s_value = lexer->YYText(); 

    return varToken;
}

Token *Tokenizer::getIntNumber() {

    Token *numToken = new Token{};
    numToken->t_type = TokenTypes::I_NUMBER;
    
    int value = std::stoi(lexer->YYText());
    numToken->t_value       = TokenValues::NO_VALUE;
    numToken->t_arg.i_value = value;

    return numToken;
}

Token *Tokenizer::getDoubleNumber() {

    Token *numToken = new Token{};
    numToken->t_type = TokenTypes::D_NUMBER;
    
    double value = std::stod(lexer->YYText());
    numToken->t_value = TokenValues::NO_VALUE;
    numToken->t_arg.d_value = value;

    return numToken;
}

Token *Tokenizer::getString() {

    Token *stringToken = new Token{};
    stringToken->t_type = TokenTypes::STRING;
    stringToken->t_value = TokenValues::NO_VALUE;
    stringToken->t_arg.s_value = lexer->YYText();

    return stringToken;
}

Token *Tokenizer::getType() {

    Token *typeToken = new Token{};
    typeToken->t_type = TokenTypes::TYPE_ID;

    typeToken->t_value = TokenValues::NO_VALUE;
    typeToken->t_arg.s_value = lexer->YYText(); 

    return typeToken;
}

Token *Tokenizer::getKeyWord() {

    Token *keyWordToken = new Token{};
    keyWordToken->t_type = TokenTypes::KEYWORD;

    std::string origin = lexer->YYText();
    std::string upperCase{};
    std::transform(origin.begin(), origin.end(), upperCase.begin(),  [](unsigned char c) { return std::toupper(c); });

    keyWordToken->t_value = keyWord_map[upperCase]; 
    keyWordToken->t_arg.s_value = lexer->YYText(); 

    return keyWordToken;
}

Token *Tokenizer::getOp() {

    Token *opToken = new Token{};
    opToken->t_type = TokenTypes::OP;
    opToken->t_value = op_map[lexer->YYText()];
    opToken->t_arg.s_value = lexer->YYText();

    return opToken;
}

void Tokenizer::printTokens() {

    size_t size = Tokens.size();
    std::cout << "Total " << size << " correct tokens:" << std::endl;
    for (size_t i = 0; i < size; i++) {
        switch (Tokens[i].t_type) {
            case TokenTypes::TYPE_ID:
                std::cout << "TokenType: TYPE_ID,  TokenValue: " << Tokens[i].t_arg.s_value << std::endl;
                break;

            case TokenTypes::KEYWORD:
                std::cout << "TokenType: Keyword,  TokenValue: " << Tokens[i].t_arg.s_value << std::endl;
                break;

            case TokenTypes::I_NUMBER:
                std::cout << "TokenType: I_Number, TokenValue: " << Tokens[i].t_arg.i_value << " (int)" <<std::endl; 
                break;

            case TokenTypes::D_NUMBER:
                std::cout << "TokenType: D_Number, TokenValue: " << Tokens[i].t_arg.d_value << " (double)" << std::endl;
                break;
            
            case TokenTypes::STRING:
                std::cout << "TokenType: String,   TokenValue: " << Tokens[i].t_arg.s_value << std::endl;
                break;
            
            case TokenTypes::VARIABLE:
                    std::cout << "TokenType: Variable, TokenValue: " << Tokens[i].t_arg.s_value << std::endl;
                break;

            case TokenTypes::OP:
                    std::cout << "TokenType: OP,       TokenValue: " << Tokens[i].t_arg.s_value << std::endl;
                break;
        }
    }
}

