%option noyywrap
%option nounput

%{
    #include <iostream>
    #include "Sintaksno.cpp"
    #include "parser.tab.hpp"

    void greska(){
        std::cerr<<"lexer\n";
        exit(EXIT_FAILURE);
    }
%}

%%

":="                {return DODELA_T;}
"True"              {return TRUE_T;}
"False"             {return FALSE_T;}
[a-z]               {yylval.c=*yytext; return ID_T;}
"/\\"               {return KON_T;}
"\\/"               {return DIS_T;}
"<=>"               {return EKV_T;}
"=>"                {return IMP_T;}
[!()\n]             {return *yytext;}
[ \t]               {}
.                   {greska();}

%%