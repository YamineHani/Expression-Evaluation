#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



#define VERBOSE 0
#define TYPE char *


typedef struct {
    int top;
    TYPE *items;
    int capacity;
} Stack;


Stack* initialize(int capacity) {Stack *s=malloc(sizeof(Stack));s->top=0;
    s->items=(TYPE*) malloc(capacity*sizeof(TYPE));
    s->capacity=capacity;
    return s;}
void destruct(Stack *s) {free(s->items);free(s);};

void push(Stack *s,TYPE value) {s->items[s->top++]=value;}
TYPE peek(Stack *s) {return s->items[s->top-1];}
void pop(Stack *s) {s->top--;}
TYPE peekPop(Stack *s) {TYPE x=peek(s); pop(s);return x;}
void freePopped(Stack *s) {free(s->items[s->top]);}
int isfull(Stack *s) {return s->top<s->capacity?0:1 ;}
int isempty(Stack *s) {return s->top==0?1:0;}
int size(Stack *s) {return s->top;}
void dispStack(Stack *s){
    char sep[3]={186,186,0};
    int i;printf(sep);
    for (i=0;i<s->top;i++) printf("%s",s->items[i]);
    printf(sep);
}
void dispStack2(Stack *s){
    int i;printf("[");
    for (i=0;i<s->top;i++) printf("%s ",s->items[i]);
    printf("]");
}


//////////////////////////////
char * preProcess(char *st){
    char str[100];int index=0;
    int status=1;// start with digit status 1 , status=0 means op
    char ch;
    while ((ch=*st++)) {
        if (ch=='(' || ch==')')  { str[index++]=' ';str[index++]=ch; status=-1;}
        else {
            int stat=isalnum(ch)?1:0;
            if (stat==status) str[index++]=ch;
            else {status=stat;str[index++]=' ';str[index++]=ch;}
        }
    }
    str[index++]=0;
    char *ret=malloc(strlen(str)+1);strcpy(ret,str);
    return ret;
}

int preced(char *st){
    //char c=*st;
    switch (*st) {
        case '#' : return 0;
        case '(' : return 1;
        case '+' : case '-' : return 2;
        case '*' : case '/' : return 3;
        default  : printf("ERRR");return -1;
    }
}
#define OPERAND 0
#define OPERATOR 1
#define OP_PAR 2
#define CL_PAR 3
int tokType(char *str) {
    char ch=*str;
    if  (isalnum(ch)) return OPERAND;
    if  (ch=='(') return OP_PAR;
    if  (ch==')') return CL_PAR;
    return OPERATOR;
}

void cat(char *st1,char * st2) {strcat(st1,st2); strcat (st1," ");}
void error(int i){
    switch (i) {
        case 1: printf("Imbalanced parenthesis\n");break;
        case 2: printf("Invalid Postfix Expression\n");break;
        case 3: printf("Operator Not Supported\n");break;
    }
    exit(0);
}

char * infPost(char * st){
    Stack *stk=initialize(100);char *cop[100];int index=0;
    char ret[1024];strcpy(ret,"");
    char *tok=strtok(st," ");
    while (tok) {
        if (VERBOSE) cop[index++]=tok;
        int typ=tokType(tok),pr;
        switch (typ) {
            case  OPERAND: cat (ret,tok);break;
            case OP_PAR: push (stk,tok);break;
            case CL_PAR:
                while (!isempty(stk) && strcmp(peek(stk),"("))
                    cat(ret,peekPop(stk));
                if (isempty(stk) || strcmp(peek(stk),"(")) error(1);
                pop(stk);break;
            case  OPERATOR:
                pr=preced(tok);
                while(!isempty (stk) &&  pr<preced(peek(stk)) )
                    cat(ret,peekPop(stk));
                push(stk,tok); break;
        }
        tok=strtok(NULL," ");
        if (VERBOSE) {
            int i;
            for (i=0;i<index;i++) printf(cop[i]);
            dispStack(stk);
            printf("%s\n",ret);

        }
    }
    while(!isempty (stk)) if (tokType(peek(stk))==OPERATOR) cat(ret,peekPop(stk));
        else error(1);
    char *s=malloc(strlen(ret)+1);strcpy(s,ret);
    return s;
}
char *intToStr(int val){
    char buf[10];
    itoa(val,buf,10);
    char *ret=malloc(strlen(buf)+1);strcpy(ret,buf);
    return ret;
}
int myPop(Stack *s) {
    if (isempty(s)) error(2);
    int x=atoi(peekPop(s));freePopped(s);return x;
}

int eval(char *str){
    Stack *data=initialize(1000);
    int res;
    char *tok=strtok(str," ");
    while (tok) {
        if (tokType(tok)==OPERAND) push(data,intToStr(atoi(tok)));
        else {int x1=myPop(data),x2=myPop(data);
            switch(tok[0]){
                case '+': res= x1+x2 ;break; case '-': res= x2-x1;break;
                case '*': res=x1*x2;break;    case '/': res=x2/x1;break;
                default: error(3);
            }
            push(data,intToStr(res));
        }
        tok=strtok(NULL," ");if (VERBOSE) dispStack2(data);
    }
    if (VERBOSE) printf("\n");
    if (size(data)!=1) error(2);
    return myPop(data);
}

int main()
{

    //for (int i=128;i<255;i++) printf("(%d %c)",i,i);
    //char *st="1+((22+11  *3 +4)*5)";
    //char *st="1 33+((22+11  *3 +4)*5";
    char *st="(3) +4+13/  3";
    printf("Expression:\t%s\n",st);
    st=preProcess(st);printf("Pre-Processed:\t%s\n",st);
    st=infPost(st);
    printf("Rev-Polish:\t%s\n",st);
    printf("Eval=%d\n",eval(st));
    return 0;
}
