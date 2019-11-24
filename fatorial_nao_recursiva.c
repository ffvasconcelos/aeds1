#include <stdio.h>

long int fatorial(int n){
    int i;
    int prod = 1;

    if(i == 1 || i == 0){
        return 1;
    }

    for(i = n; i > 1; i--){
        prod *= i;
    }
    return prod;
}


int main (){

    int n;
    long int fat;

    printf("Calculo de fatorial\n\n");

    printf("Digite o numero: ");
    fflush(stdin);
    scanf("%d", &n);

    fat = fatorial(n);

    printf("\n%d%! = %d", n, fat);
}
