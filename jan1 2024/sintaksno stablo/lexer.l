%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>

    using namespace std;

    #include "sintaksno.cpp"

    #include "parser.tab.hpp"

    void yyerror(string s);
%}

%%

def                             {return DEF;}
print                           {return PRINT;}
[dbh]                           {
                                    yylval.opt = yytext[0];
                                    return OPT;
                                }
[a-zA-Z][a-zA-Z0-9_]*           {
                                    yylval.ime = new string(yytext);
                                    return ID;
                                }
[1-9][0-9]*                     {
                                    yylval.x = atoi(yytext);    
                                    return BROJ;
                                }
"<<"                            {return SHL;}
">>"                            {return SHR;}
"=="                            {return EQ;}
"!="                            {return NEQ;}
"<="                            {return LEQ;}
">="                            {return GEQ;}
[+*/%&|^~=\(\);\"\<\>,-]        {return *yytext;}
[ \t\n]                         { }
.                               {
                                    cerr << "Leksicka greska" << endl;
                                    exit(EXIT_FAILURE);
                                }

%%