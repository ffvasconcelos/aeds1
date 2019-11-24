#include <stdio.h>

long int fibonacci(int n){

    int i;
    if(i == 0 || i == 1){
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

    int main (){

    int n;
    long int fib;

    printf("Calculo de fibonacci\n\n");

    printf("Digite o numero: ");
    fflush(stdin);
    scanf("%d", &n);

    fib = fibonacci(n);

    printf("\n%d = %d", n, fib);
}


