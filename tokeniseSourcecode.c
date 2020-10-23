#include "tokenDef.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<stdbool.h>

char* tmap[] = 
{     
    "DECLARE",
    "COLON",
    "SEMICOLON",
    "LIST",
    "OF",
    "VARIABLES",
    "ID",
    "ARRAY",
    "SQO",
    "DOT",
    "SQC",
    "NUM",
    "INT",
    "BOOL",
    "REAL",
    "JAGGED",
    "R1",
    "VALUE",
    "SIZE",
    "CBO",
    "CBC",
    "EQU",
    "ADD",
    "MUL",
    "DIV",
    "OR",
    "AND"
} ;

bool digits_only(const char *s)
{
    while (*s) 
    {
        if (isdigit(*s++) == 0) return false;
    }

    return true;
}

token* new_Token( tokenType tp, char lex[10], int vtype, int line_num)
{
    token *t = (token*)malloc(sizeof(token));
    //printf("looooooo!!!\n");
    t->line_no = line_num;
    t->type = tp;
    t->valueType = vtype;
    //printf("loooooo\n");
    strcpy(t->lexeme, lex);
    //printf("loooooo\n");
    //strcpy(t->stat_type, stype);
    t->next = NULL;
    return t;
}

token* tokeniseSourcecode( char *srcCode, token*h)
{
    FILE *fptr = fopen(srcCode, "r");
    char temp[20];
    token*s = NULL;
    h->next = NULL;
    //s = h;
    int line_num = 1;
    while(fscanf(fptr,"%s",temp) != -1)
    {
        
        if(strcmp(temp,"declare") == 0)
        {
            //printf("yoooooo\n");
            h->next = new_Token(DECLARE, temp, -1, line_num);
            //printf("yoooooo\n");
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
            
        }

        else if(strcmp(temp,"list") == 0)
        {
            h->next = new_Token(LIST, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }
        
        else if(strcmp(temp,"of") == 0)
        {
            h->next = new_Token(OF, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"variables") == 0)
        {
            h->next = new_Token(VARIABLES, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"integer") == 0)
        {
            h->next = new_Token(INT, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,";") == 0)
        {
            h->next = new_Token(SEMICOLON, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"jagged") == 0)
        {
            h->next = new_Token(JAGGED, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"size") == 0)
        {
            h->next = new_Token(SIZE, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }


        else if(strcmp(temp,"R1") == 0)
        {
            h->next = new_Token(R1, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"[") == 0)
        {
            h->next = new_Token(SQO, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
           printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"]") == 0)
        {
            h->next= new_Token(SQC, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"..") == 0)
        {
            h ->next= new_Token(DOT, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,":") == 0)
        {
            h->next = new_Token(COLON, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"{") == 0)
        {
            h->next = new_Token(CBO, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"}") == 0)
        {
            h->next= new_Token(CBC, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"values") == 0)
        {
            h->next = new_Token(VALUE, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }


        else if(strcmp(temp,"array") == 0)
        {
            h->next = new_Token(ARRAY, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
           printf("%s\n",h->next->lexeme);
            h = h->next;
        }


        else if(strcmp(temp,"boolean") == 0)
        {
            h->next = new_Token(BOOL, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"real") == 0)
        {
            h ->next= new_Token(REAL, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"+") == 0)
        {
            h->next = new_Token(ADD, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }


        else if(strcmp(temp,"*") == 0)
        {
            h->next = new_Token(MUL, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"/") == 0)
        {
            h ->next= new_Token(DIV, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"&&&") == 0)
        {
            h->next = new_Token(AND, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"|||") == 0)
        {
            h->next = new_Token(OR, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"=") == 0)
        {
            h->next = new_Token(EQU, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,"(") == 0)
        {
            h ->next= new_Token(RBO, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(strcmp(temp,")") == 0)
        {
            h ->next= new_Token(RBC, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
           printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else if(digits_only(temp))
        {
            h ->next= new_Token(NUM, temp, 0, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }

        else 
        {
            h->next= new_Token(ID, temp, -1, line_num);
            if(s == NULL)
                s = h->next;
            printf("%s\n",h->next->lexeme);
            h = h->next;
        }


        /*else if(strcmp(temp,'declare') == 0)
        {
            h = new_Token(DECLARE, temp, -1, line_num);
            h = h->next;
        }*/



        FILE *tptr = fptr;
        
        //fseek(tptr, -1, SEEK_CUR);

        char nl;
        nl = getc(tptr);
        printf("%c",nl);
        if(nl != ' ')
            line_num++;
        
    }

    return s;

}

void printTokenstream(token* t)
{
    token* h = t;
    while(h!=NULL)
    {
        printf("lex : %s  token: %s  lin_num: %d\n", h->lexeme, tmap[h->type], h->line_no);
        h = h->next;
    }
}

void main()
{
    token* t = (token*)malloc(sizeof(token));
    t->next = NULL;
    t = tokeniseSourcecode("trial.txt", t);
    printTokenstream(t);
}