#ifndef CALCULATE_CORE
#define CALCULATE_CORE

#include <string.h>

double calculate(char kind,double num1,double num2){
    double result;
    if (kind=='*'){
        result=num1*num2;
    }
    else if(kind=='+'){
        result=num1+num2;
    }
    else if(kind=='-'){
        result=num1-num2;
    }
    else if(kind=='/'){
        result=num1/num2;
    }
    return result;
}


double get_calculate(char *input_str)
{
    char input[17] = {0};
    strcpy(input, input_str);
    
    double number [10]={0};
    char symbol [10]={'0'};
    int num_store=0;
    int sym_store=0;
    double result=1;
    int i=0;

    for (i=0;i<strlen(input);i++){
        //input:0~9
        if (48<=input[i] && input[i]<=57){
            number[num_store]=input[i]-48+number[num_store]*10;
        }
        //input:+-*/
        else if(input[i]==43 || input[i]==42 || input[i]==45 || input[i]==47 || input[i]==61){
            symbol[sym_store]=input[i];
            num_store+=1;
            sym_store+=1;

        }
        else{

        }

    }

    i=0;
    //y-x --> y+(-x)
    while(symbol[i]!= '='){
        if (symbol[i]==45){
            number[i+1]*=-1;
            symbol[i]='+';
        }
        i+=1;
    }

    i=0;
    //3*4*5 --> 0+12*5 -->0+0+60
    while(symbol[i]!= '='){
        if (symbol[i]=='*' || symbol[i]=='/'){
            number[i+1]=calculate(symbol[i],number[i],number[i+1]);
            number[i]=0;
            symbol[i]='+';
        }
        i+=1;
    }
    
    i=0;
    //1+2+3 --> 0+3+3 -->0+0+6
    while(symbol[i]!= '='){
        if (symbol[i]==43){
            number[i+1]=calculate(symbol[i],number[i],number[i+1]);
            number[i]=0;
        }
        i+=1;
    }
    result=number[i];

    return result;
}



#endif