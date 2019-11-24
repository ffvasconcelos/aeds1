#include <stdio.h>
#include <stdlib.h>

int main (){

    //Declarou ponteiro, aterra e inicializa

    int numero, *p1, *p2, *p3;
    p1 = NULL;
    p2 = NULL;
    p3 = NULL;

    printf("\nDigite um numero: ");
    scanf("%d", &numero);

    p1 = &numero;

    printf("\nNumero: %d", *p1);

    p2 = (int*) malloc (sizeof(int));
    *p2 = numero;
    printf("\nNumero: %d", *p2);
    free(p2);

    p3 = (int*)malloc(sizeof(int));
    *p3 = 7;
    printf("\nNumero: %d", *p3);
    free(p3);
    p3 = NULL;

    p3 = (int*)malloc(sizeof(int));
    printf("\nNumero: %d", *p3);
    printf("\nNumero: %d", *p2);
    free(p3);
}
