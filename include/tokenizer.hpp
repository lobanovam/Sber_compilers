#include "tokens.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <FlexLexer.h>

struct TokenArg {
        int          i_value_;
        double       d_value_;
        std::string  s_value_;

        TokenArg(int i_value)         : i_value_(i_value) {};
        TokenArg(double d_value)      : d_value_(d_value) {};
        TokenArg(std::string s_value) : s_value_(s_value) {};
}; 

struct Token 
{
    TokenTypes  t_type_;
    TokenValues t_value_;
    TokenArg    t_arg_;

    Token(TokenTypes t_type, TokenValues t_value, TokenArg t_arg) : t_type_(t_type), t_value_(t_value), t_arg_(t_arg) {}; 
    Token();
};

class Tokenizer {

    std::vector<Token> Tokens;

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