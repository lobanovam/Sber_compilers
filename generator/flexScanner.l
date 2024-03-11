%option c++ 
%option noyywrap
%option yylineno   


%{
using std::cout;
using std::endl;

#include "../include/tokens.hpp"
%}
                           /* definition section */
WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
TYPE_ID [A-Z][_A-Za-z1-9]+
VAR [a-z][_A-Za-z1-9]+
OP     [\+\-\=\*\\()]
DOUBLE {DIGIT}+.{DIGIT}+
INT {DIGIT1}{DIGIT}* 
KEYWORDS (else|if|loop|then|while|not|println|print)

%x COMMENT
%x SSTRING

%%                         /* rules section */

{WS}            /* skip spaces */

(t(?i:rue))|(f(?i:alse)) { return (int) TokenTypes::KEYWORD;}
(?i:{KEYWORDS})          { return (int) TokenTypes::KEYWORD;} 
{OP}                     { return (int) TokenTypes::OP;} 
{INT}                    { return (int) TokenTypes::I_NUMBER;}
{DOUBLE}                 { return (int) TokenTypes::D_NUMBER;}
{TYPE_ID}                { return (int) TokenTypes::TYPE_ID;}
{VAR}                    { return (int) TokenTypes::VARIABLE;}

\"--\"[^\n]*[\n]         { std::cout << "got small comment: " << yytext << endl;}

\"                       BEGIN(SSTRING);
<SSTRING>[^\"\0<<EOF>>]* { return (int) TokenTypes::STRING;}
<SSTRING><<EOF>>         { return (int) TokenTypes::UNCLOSED_STRING; }
<SSTRING>\"|\0           BEGIN(INITIAL);

"(...)"                       BEGIN(COMMENT);
<COMMENT>[^\(...\)<<EOF>>]*   { std::cout << "got large comment: " << yytext << endl;} 
<COMMENT><<EOF>>              { return (int) TokenTypes::UNCLOSED_COMMENT; }
<COMMENT>"(...)"              BEGIN(INITIAL);

.                        { return (int) TokenTypes::UNKNOWN_TOKEN;}

%%                         /* user code section */

//nothing