#include "tokens.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <FlexLexer.h>

struct TokenArg {
        int          i_value;
        double       d_value;
        std::string  s_value;
}; 

struct Token 
{
    TokenTypes  t_type;
    TokenValues t_value;
    TokenArg    t_arg;
};

class Tokenizer {

    std::vector<Token> Tokens;

    Token *getIntNumber();
    Token *getDoubleNumber();
    Token *getString();
    Token *getKeyWord();
    Token *getOp();
    Token *getType();
    Token *getVar();

    std::unordered_map<std::string, TokenValues> keyWord_map = {{"IF",   TokenValues::IF},
                                                                {"ELSE" ,   TokenValues::ELSE},
                                                                {"PRINT",   TokenValues::PRINT},
                                                                {"PRINTLN", TokenValues::PRINTLN},
                                                                {"LOOP",    TokenValues::LOOP},
                                                                {"THEN",    TokenValues::THEN},
                                                                {"WHILE",   TokenValues::WHILE},
                                                                {"NOT",     TokenValues::NOT},
                                                                {"TRUE",    TokenValues::TRUE},
                                                                {"FALSE",   TokenValues::FALSE}};

    std::unordered_map<std::string, TokenValues> op_map      = {{"+", TokenValues::ADD},
                                                                {"-", TokenValues::SUB},
                                                                {"*", TokenValues::MUL},
                                                                {"/", TokenValues::DIV},
                                                                {"=", TokenValues::ASSIGN},
                                                                {"(",TokenValues::OPEN_BR},
                                                                {")",TokenValues::CLOSE_BR}};

public:

    int GetToken(TokenTypes token_type);
    FlexLexer* lexer;
    void printTokens();

    Tokenizer(Tokenizer &other) = delete;
    Tokenizer() {
        lexer = new yyFlexLexer;
    }
    ~Tokenizer() {
        delete lexer;
    }
};