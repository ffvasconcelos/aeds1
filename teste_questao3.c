#include<stdio.h>
#include<string.h>
#include<math.h>

int comprimento(char* str){
    if(*str == '\0'){
        return 0;
    } else {
        return 1 + comprimento(str + 1);
    }
}

int toInt(char *str, int cmp){
    if(cmp == 0){
        return 0;
    } else {
        return (str[cmp - 1] - '0') * pow(10, comprimento(str) - cmp) + toInt(str, cmp - 1);
    }
}

int main(void){
    char num[10];

    strcpy(num, "2000");

    printf("%d", toInt(num, comprimento(num)) + 777);
}
