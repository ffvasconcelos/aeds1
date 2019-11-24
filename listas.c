#include <stdlib.h>
#include <stdio.h>
#define MAX 10


typedef struct {
  int Chave;
  /* outros componentes */
} TipoItem;

typedef struct celula {
  TipoItem item;
  struct celula* prox;
} TCelula;

typedef struct {
  TCelula* primeiro;
  TCelula* ultimo;
} TLista;


void FLVazia(TLista *Lista)
{ Lista -> primeiro = (TCelula *) malloc(sizeof(TCelula));
  Lista -> ultimo = Lista -> primeiro;
  Lista -> primeiro -> prox = NULL;
}

int Vazia(TLista Lista)
{ return (Lista.primeiro == Lista.ultimo);
}

void Inserir(TipoItem x, TLista *Lista)
{ Lista -> ultimo -> prox = (TCelula *) malloc(sizeof(TCelula));
  Lista -> ultimo = Lista -> ultimo -> prox;
  Lista -> ultimo -> item = x;
  Lista -> ultimo -> prox = NULL;
}

void Retirar(TCelula* p, TLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TCelula* q;
  if (Vazia(*Lista) || p == NULL || p -> prox == NULL)
  { printf(">>>>> ERROR: Lista vazia ou posicao nao existe!!! <<<<<\n");
    return;
  }
  q = p -> prox;
  *Item = q -> item;
  p -> prox = q -> prox;
  if (p -> prox == NULL)
    Lista -> ultimo = p;
  free(q);
}

void Imprimir(TLista Lista)
{ TCelula* Aux;
  Aux = Lista.primeiro -> prox;
  while (Aux != NULL){
    printf("%d\n", Aux -> item.Chave);
    Aux = Aux -> prox;
  }
}
