#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tdata
{
    int Dia;
    int Mes;
    int Ano;
} TData;

typedef struct tendereco
{
    char Logradouro [50];
    int Num;
    char Complemento [10];
    char Bairro [50];
    char Cidade [50];
    char CEP [11];
} TEndereco;


typedef struct usuario
{
    char Nome [50];
    char Sobrenome [50];
    char CPF [14];
    char RG [11];
    TEndereco Endereco;
    TData DataDeNascimento;
    int Tipo; // 1 ALUNO, 2 USUARIO, 3 PROFESSOR
    int QtdLivros;
    char NomeDoCurso [50];
    char Matricula [11];
    char Departamento [10];
    char Siape [12];
} TUsuario;

typedef struct celula
{
    TUsuario item;
    struct celula* prox;
} TCelula;

typedef struct lista
{
    TCelula* primeiro;
    TCelula* ultimo;
    int tamanho;

} TLista;

void FLVazia(TLista* lista)
{
    lista->primeiro = (TCelula*) malloc(sizeof(TCelula));
    lista->ultimo = lista -> primeiro;
    lista->primeiro->prox = NULL;
    lista->tamanho = 0;
}

void Inserir(TLista* lista, TUsuario item)
{
    lista->ultimo->prox = (TCelula*)malloc(sizeof(TCelula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->item = item;
    lista->tamanho++;
}

int Vazia(TLista lista)
{
    return (lista.primeiro == lista.ultimo);
}

TCelula* Pesquisar(TLista lista, TUsuario user)
{
    TCelula* aux = lista.primeiro;

    while (aux->prox != NULL)
    {
        if(strcmp(aux->prox->item.CPF, user.CPF) == 0)
        {
            return aux;
        }
        else
        {
            aux = aux->prox;
        }
    }

    return NULL;
}

void Excluir(TLista* lista, TUsuario user)
{
    TCelula* endereco = Pesquisar(*(lista), user);

    if(endereco != NULL)
    {
        TCelula* aux;

        aux = endereco->prox->prox;
        free(endereco->prox);
        endereco->prox = aux;
        lista->tamanho--;

        if(endereco->prox == NULL)
        {
            lista->ultimo = endereco;
        }
    }
}

void Liberar(TLista* lista)
{
    TCelula* auxProx = lista-> primeiro-> prox;
    TCelula* auxFree = lista-> primeiro;

    while(auxFree != NULL)
    {
        free(auxFree);
        auxFree = auxProx;
        auxProx = auxProx->prox;
    }
}


//Exercicios de implementacao

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

int main ()
{

    TLista lista1;
    TLista lista2;
    TLista lista3;

    TUsuario item;

    FLVazia(&lista1);
    FLVazia(&lista2);

    char str[50];

    int i;

    for(i = 0; i < 3; i++)
    {
        printf("\nLista1: ");
        printf("\nElemento %d: ", i+1);
        fflush(stdin);
        fgets(str,14,stdin);
        strcpy(item.CPF,str);
        Inserir(&lista1,item);
    }

    for(i = 0; i < 3; i++)
    {
        printf("\nLista2: ");
        printf("\nElemento %d: ", i+1);
        fflush(stdin);
        fgets(str,14,stdin);
        strcpy(item.CPF,str);
        Inserir(&lista2,item);
    }

    printf("\n\nRetorno Listas Iguais: %d", CompararListas(lista1, lista2));
    printf("\n\nRetorno Conjuntos Iguais: %d", CompararListasConjunto(lista1, lista2));

    lista3 = IntercalarListas(lista1, lista2);

    printf("\n\nListas intercaladas:\n");

    TCelula* aux;

    aux = lista3.primeiro->prox;

    while (aux != NULL)
    {
        printf("%s ", aux->item.CPF);
        aux = aux->prox;
    }

    printf("\n\n");

    ConcatenarListas(&lista1, lista2);

    printf("Listas concatenadas:\n");

    aux = lista1.primeiro->prox;

    while (aux != NULL)
    {
        printf("%s ", aux->item.CPF);
        aux = aux->prox;
    }

    printf("\n\n");

}

