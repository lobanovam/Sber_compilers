#include <algorithm>
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

    Token *varToken; 
    switch (token_type) {

        case TokenTypes::TYPE_ID:
            Tokens.push_back(Token(TokenTypes::TYPE_ID, TokenValues::NO_VALUE, TokenArg(lexer->YYText())));
            break;

        case TokenTypes::VARIABLE:
            Tokens.push_back(Token(TokenTypes::VARIABLE, TokenValues::NO_VALUE, TokenArg(lexer->YYText())));
            break;

        case TokenTypes::KEYWORD:
            {
                std::string origin = lexer->YYText();
                std::for_each(origin.begin(), origin.end(),  [](unsigned char c) { return std::toupper(c); });
                Tokens.push_back(Token(TokenTypes::KEYWORD, keyWord_map[origin], TokenArg(lexer->YYText())));
            }
            break;

        case TokenTypes::D_NUMBER:
            Tokens.push_back(Token(TokenTypes::D_NUMBER, TokenValues::NO_VALUE, std::stod(lexer->YYText())));
            break;
     
        case TokenTypes::I_NUMBER:
            Tokens.push_back(Token(TokenTypes::I_NUMBER, TokenValues::NO_VALUE, std::stoi(lexer->YYText())));
            break;

        case TokenTypes::STRING:
            Tokens.push_back(Token(TokenTypes::STRING, TokenValues::NO_VALUE, TokenArg(lexer->YYText())));
            break;
        
        case TokenTypes::OP:
            Tokens.push_back(Token(TokenTypes::OP, op_map[lexer->YYText()], TokenArg(lexer->YYText())));
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


void Tokenizer::printTokens() {

    size_t size = Tokens.size();
    std::cout << "Total " << size << " correct tokens:" << std::endl;
    for (size_t i = 0; i < size; i++) {
        switch (Tokens[i].t_type_) {
            case TokenTypes::TYPE_ID:
                std::cout << "TokenType: TYPE_ID,  TokenValue: " << Tokens[i].t_arg_.s_value_ << std::endl;
                break;

            case TokenTypes::KEYWORD:
                std::cout << "TokenType: Keyword,  TokenValue: " << Tokens[i].t_arg_.s_value_ << std::endl;
                break;

            case TokenTypes::I_NUMBER:
                std::cout << "TokenType: I_Number, TokenValue: " << Tokens[i].t_arg_.i_value_ << " (int)" <<std::endl; 
                break;

            case TokenTypes::D_NUMBER:
                std::cout << "TokenType: D_Number, TokenValue: " << Tokens[i].t_arg_.d_value_ << " (double)" << std::endl;
                break;
            
            case TokenTypes::STRING:
                std::cout << "TokenType: String,   TokenValue: " << Tokens[i].t_arg_.s_value_ << std::endl;
                break;
            
            case TokenTypes::VARIABLE:
                    std::cout << "TokenType: Variable, TokenValue: " << Tokens[i].t_arg_.s_value_ << std::endl;
                break;

            case TokenTypes::OP:
                    std::cout << "TokenType: OP,       TokenValue: " << Tokens[i].t_arg_.s_value_ << std::endl;
                break;
        }
    }
}

