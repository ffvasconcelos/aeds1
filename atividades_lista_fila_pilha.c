/*

ATIVIDADES EXTRA: LISTA, FILA E PILHA
FRANCISCO FIGUEIREDO VASCONCELOS
18.1.8018

*/

#include <stdio.h>
#include <stdlib.h>

//Lista

//Exercicio 1

int CompararListas(TLista lista1, TLista lista2)
{

    TCelula* aux1;
    TCelula* aux2;

    if(lista1.tamanho == lista2.tamanho)
    {

        aux1 = lista1.primeiro->prox;
        aux2 = lista2.primeiro->prox;

        while (aux1 != NULL)
        {

            if(strcmp(aux1->item.CPF, aux2->item.CPF) == 0)
            {
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
            else
            {
                return 0;
            }

        }

        return 1;

    }

    return 0;

}

int CompararListasConjunto(TLista lista1, TLista lista2)
{

    TCelula* aux1;
    TCelula* aux2;

    if(lista1.tamanho == lista2.tamanho)
    {

        aux1 = lista1.primeiro->prox;
        aux2 = lista2.primeiro->prox;

        while (aux1 != NULL)
        {

            if(Pesquisar(lista2,aux1->item)!=NULL)
            {
                aux1 = aux1->prox;
            }
            else
            {
                return 0;
            }
        }

        return 1;

    }

    return 0;

}

//Exercicio 2

void ConcatenarListas(TLista* lista1, TLista lista2)
{

    TCelula* aux;

    aux = lista2.primeiro->prox;

    while(aux != NULL)
    {
        Inserir(lista1, aux->item);
        aux = aux->prox;
    }

}

//Exercicio 3

TLista IntercalarListas(TLista lista1, TLista lista2)
{

    TCelula* aux1;
    TCelula* aux2;

    TLista lista3;

    FLVazia(&lista3);

    aux1 = lista1.primeiro->prox;
    aux2 = lista2.primeiro->prox;

    while((aux1 != NULL) || (aux2 != NULL))
    {
        if(aux1 != NULL)
        {
            Inserir(&lista3, aux1->item);
            aux1 = aux1->prox;
        }
        if(aux2 != NULL)
        {
            Inserir(&lista3, aux2->item);
            aux2 = aux2->prox;
        }
    }

    return lista3;

}

//Fila

//Exercicio 1

int FilasIguais(TFila fila1, TFila fila2)
{

    TUsuario aux1, aux2;
    TFila filaaux1, filaaux2;
    FFVazia(&filaaux1);
    FFVazia(&filaaux2);

    while(!Vazia(fila1) && !Vazia(fila2))
    {

        Desenfileirar(&fila1, &aux1);
        Desenfileirar(&fila2, &aux2);

        Enfileirar(&filaaux1, aux1);
        Enfileirar(&filaaux2, aux2);

        if(strcmp(aux1.CPF, aux2.CPF) != 0)
        {
            while(!Vazia(fila1))
            {
                Desenfileirar(&fila1, &aux1);
                Enfileirar(&filaaux1, aux1);
            }

            while(!Vazia(filaaux1))
            {
                Desenfileirar(&filaaux1, &aux1);
                Enfileirar(&fila1, aux1);
            }

            while(!Vazia(fila2))
            {
                Desenfileirar(&fila2, &aux2);
                Enfileirar(&filaaux2, aux2);
            }

            while(!Vazia(filaaux2))
            {
                Desenfileirar(&filaaux2, &aux2);
                Enfileirar(&fila2, aux2);
            }
            free(filaaux1.frente);
            free(filaaux2.frente);

            return 0;
        }

    }

    if(Vazia(fila1) && Vazia(fila2))
    {
        free(filaaux1.frente);
        free(filaaux2.frente);

        return 1;
    }
    else
    {
        if(Vazia(fila1))
        {
            while(!Vazia(filaaux1))
            {
                Desenfileirar(&filaaux1, &aux1);
                Enfileirar(&fila1, aux1);
            }

            while(!Vazia(fila2))
            {
                Desenfileirar(&fila2, &aux2);
                Enfileirar(&filaaux2, aux2);
            }

            while(!Vazia(filaaux2))
            {
                Desenfileirar(&filaaux2, &aux2);
                Enfileirar(&fila2, aux2);
            }
            free(filaaux1.frente);
            free(filaaux2.frente);

            return 0;
        }
        else
        {
            while(!Vazia(filaaux2))
            {
                Desenfileirar(&filaaux2, &aux2);
                Enfileirar(&fila2, aux2);
            }
            while(!Vazia(fila1))
            {
                Desenfileirar(&fila1, &aux1);
                Enfileirar(&filaaux1, aux1);
            }

            while(!Vazia(filaaux1))
            {
                Desenfileirar(&filaaux1, &aux1);
                Enfileirar(&fila1, aux1);
            }
            free(filaaux1.frente);
            free(filaaux2.frente);

            return 0;
        }
    }
}

//Exercicio 2

TFila IntercalarFila(TFila fila1, TFila fila2)
{

    TFila filaaux1, filaaux2;
    TUsuario aux;
    TFila fila3;
    FFVazia(&fila3);
    FFVazia(&filaaux1);
    FFVazia(&filaaux2);

    while(!Vazia(fila1))
    {
        Desenfileirar(&fila1, &aux);
        Enfileirar(&filaaux1, aux);
    }

    while(!Vazia(fila2))
    {
        Desenfileirar(&fila2, &aux);
        Enfileirar(&filaaux2, aux);
    }

    while(!Vazia(filaaux1) || !Vazia(filaaux2))
    {
        if(!Vazia(filaaux1))
        {
            Desenfileirar(&filaaux1, &aux);
            Enfileirar(&fila1, aux);
            Enfileirar(&fila3, aux);
        }

        if(!Vazia(filaaux2))
        {
            Desenfileirar(&filaaux2, &aux);
            Enfileirar(&fila2, aux);
            Enfileirar(&fila3, aux);
        }
    }

    free(filaaux1.frente);
    free(filaaux2.frente);

    return fila3;

}

//Exercicio 3

void InverteFila(TFila *fila)
{
    TUsuario aux;
    TFila filaaux;
    FFVazia(&filaaux);
    int j = 0;
    int tam = fila->tamanho;
    while(j<tam)
    {

        for(i = 0; i < fila->tamanho-1; i++)
        {
            Desenfileirar(fila, &aux);
            Enfileirar(fila, aux);
        }
        Desenfileirar(fila, &aux);
        Enfileirar(&faux, aux);
        j++;

    }

    for(int h=0; h<tam; h++)
    {
        Desenfileirar(&filaaux, &aux);
        Enfileirar(fila, aux);
    }

    free(filaaux.frente);
}

//Pilha

//1(a)

void InvertePilhaComFila(TPilha* pilha)
{

    TFila filaaux;
    TUsuario aux;

    FFVazia(&filaaux);

    while(!VaziaPilha(*pilha))
    {
        Desempilha(pilha, &aux);
        Enfileirar(&filaaux, aux);
    }

    while(!VaziaFila(filaaux))
    {
        Desenfileirar(&filaaux, &aux);
        Empilha(pilha, aux);
    }

    free(filaaux.frente);
}

//2(b)

void InvertePilhaComPilha(TPilha* pilha)
{

    TPilha pilhaaux;
    TUsuario aux, y;
    int n = pilha->tamanho;
    int i, j;

    FPVazia(&pilhaaux);

    for(i = 0; i < n; i++)
    {

        for(j = 0; j < n - i; j++)
        {
            Desempilha(pilha, &aux);
            Empilha(&pilhaaux, aux);
            if(j == 0)
                y = aux;
        }

        Empilha(pilha, y);

        for(j = 0; j < n - i; j++)
        {
            Desempilha(&pilhaaux, &aux);
            Empilha(pilha, aux);
        }

    }

    free(pilhaaux.topo);

}

//3(c)

void InvertePilhaComPilhas(TPilha* pilha)
{

    TPilha pilhaaux1, pilhaaux2;
    TUsuario aux;

    FPVazia(&pilhaaux1);
    FPVazia(&pilhaaux2);

    while(!VaziaPilha(*pilha))
    {
        Desempilha(pilha, &aux);
        Empilha(&pilhaaux1, aux);
    }

    while(!VaziaPilha(pilhaaux1))
    {
        Desempilha(&pilhaaux1, &aux);
        Empilha(&pilhaaux2, aux);
    }

    while(!VaziaPilha(pilhaaux2))
    {
        Desempilha(&pilhaaux2, &aux);
        Empilha(pilha, aux);
    }

    free(pilhaaux1.topo);
    free(pilhaaux2.topo);
}
