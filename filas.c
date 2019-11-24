#include <stdlib.h>
#include <stdio.h>


typedef struct TipoItem{
    char CPF[15];
    /* outros campos */
} TUsuario;

typedef struct celula{
    TipoItem item;
    struct celula* prox;
} TipoCelula;

typedef struct TipoFila{
    TipoCelula* frente;
    TipoCelula* tras;
    int tamanho;
} TipoFila;

void FFVazia(TipoFila *Fila){
    Fila->frente = (TipoCelula*) malloc(sizeof(TipoCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
    Fila->tamanho = 0;
}

int Vazia(TipoFila Fila){
    return (Fila.frente == Fila.tras);
}

void Enfileirar(TipoItem x, TipoFila *Fila){
    Fila->tras->prox = (TipoCelula*) malloc(sizeof(TipoCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
    Fila->tamanho++;
}

void Desenfileirar(TipoFila *Fila, TipoItem *Item){
    TipoCelula* aux;
    if (!Vazia(*Fila)){
    	aux = Fila->frente->prox;
    	Fila->frente->prox = aux->prox;
    	*Item = Fila->frente->item;
    	free(q);
	if (Fila->frente->prox == NULL)
	    Fila->tras = Fila->frente;
        Fila->tamanho--;
    }
}


