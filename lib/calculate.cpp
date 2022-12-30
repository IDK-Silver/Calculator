#include <iostream>
#include <string.h>
using namespace std;
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
    char input[1][17] = {0};
    strcpy(&input_str[0], input_str);
    double number [10]={0};
    char symbol [10]={'0'};
    int num_store=0;
    int sym_store=0;
    double result=1;
    int i=0;
    for (i=0;i<strlen(input[0]);i++){
        if (48<=input[0][i] && input[0][i]<=57){
            number[num_store]=input[0][i]-48+number[num_store]*10;
        }
        else if(input[0][i]==43 || input[0][i]==42 || input[0][i]==45 || input[0][i]==47 || input[0][i]==61){
            symbol[sym_store]=input[0][i];
            num_store+=1;
            sym_store+=1;

        }
        else{
            printf("error");
        }

    }

    i=0;
    while(symbol[i]!= '='){
        if (symbol[i]==45){
            number[i+1]*=-1;
            symbol[i]='+';
        }
        i+=1;
    }

    i=0;
    while(symbol[i]!= '='){
        if (symbol[i]=='*' || symbol[i]=='/'){
            number[i+1]=calculate(symbol[i],number[i],number[i+1]);
            number[i]=0;
            symbol[i]='+';
        }
        i+=1;
    }
    
    i=0;
    while(symbol[i]!= '='){
        if (symbol[i]==43){
            number[i+1]=calculate(symbol[i],number[i],number[i+1]);
            number[i]=0;
        }
        i+=1;
    }
    result=number[i];

    printf("%f",result);
}


int main (){
    char input_str[] = "42+2=";
    get_calculate(input_str);
    return 0;
}