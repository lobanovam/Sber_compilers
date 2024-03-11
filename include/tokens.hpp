#include <type_traits>

enum class TokenValues 
{
    NO_VALUE,

    //keywords
    IF,
    ELSE,
    LOOP,
    THEN,
    WHILE,
    NOT,
    TRUE,
    FALSE,
    PRINT,
    PRINTLN,

    //ops
    ADD, 
    SUB,
    MUL,
    DIV,
    ASSIGN,
    OPEN_BR,
    CLOSE_BR
};

enum class TokenTypes 
{
    UNKNOWN_TOKEN = -1,
    EOF_TYPE,
    TYPE_ID,
    VARIABLE,
    OP,
    KEYWORD,
    D_NUMBER,
    I_NUMBER,
    STRING,

    UNCLOSED_STRING,
    UNCLOSED_COMMENT,
};
