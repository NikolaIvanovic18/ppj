%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <map>
    #include <exception>

    #include "SymbolTable.hpp"
    #include "parser.tab.hpp"
%}

%%
string  {return STRING_T;}
start   {return START_T;}
end     {return END_T;}
std_output  {return OUT_T;}
std_input   {return IN_T;}
std_error   {return ERR_T;}
print_ALL   {return PRINT_T;}
if          {return IF_T;}
else        {return ELSE_T;}
"<<"        {return SHL_T;}
">>"        {return SHR_T;}
[A-Za-z_][A-Za-z0-9_]*  {
                                yylval.s = new std::string(yytext);
                                return ID_T;
                        }
["][^""]*["]    {
                    yylval.s = new std::string(yytext);
                    return STRING_CONST_T;
                }
"=="        {return EQ_T;}
"!="        {return NEQ_T;}
[+*~()=;{}:] {return *yytext;}
"//".*      { }
[ \t\n]     { }
.           {
                std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
                exit(EXIT_FAILURE);
            }
%%