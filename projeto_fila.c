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

typedef struct fila
{
    TCelula* frente;
    TCelula* tras;
    int tamanho;
} TFila;

void ImprimirUsuario(TUsuario user)
{

    printf("\nNome: %s", user.Nome);
    printf("\nSobrenome: %s", user.Sobrenome);
    printf("\nCPF: %s", user.CPF);
    printf("\nRG: %s", user.RG);
    printf("\nData de nascimento: %d/%d/%d", user.DataDeNascimento.Dia, user.DataDeNascimento.Mes, user.DataDeNascimento.Ano);
    printf("\nEndereço:");
    printf("\nLogradouro: %s", user.Endereco.Logradouro);
    printf("\nBairro: %s", user.Endereco.Bairro);
    printf("\nNúmero: %d", user.Endereco.Num);
    printf("\nComplemento: %s", user.Endereco.Complemento);
    printf("\nCidade: %s", user.Endereco.Cidade);
    printf("\nCEP: %s", user.Endereco.CEP);

    if(user.Tipo == 1)
    {
        printf("\nTipo: Aluno");
        printf("\nMatrícula: %s", user.Matricula);
    }
    else
    {
        if(user.Tipo == 2)
        {
            printf("\nTipo: Funcionário");
        }
        else
        {
            printf("\nTipo: Professor");
        }

        printf("Siape: %s", user.Siape);
    }

    printf("Quantidade de livros locados: %d", user.QtdLivros);

}

void FFVazia(TFila* fila)
{
    fila->frente = (TCelula*)malloc(sizeof(TCelula));
    fila->tras = fila->frente;
    fila->tras->prox = NULL;
    fila->tamanho = 0;
}

int Vazia(TFila fila)
{
    return (fila.frente==fila.tras);
}

void Enfileirar(TFila* fila, TUsuario item)
{
    fila->tras->prox = (TCelula*)malloc(sizeof(TCelula));
    fila->tras = fila->tras->prox;
    fila->tras->prox = NULL;
    fila->tras->item = item;
    fila->tamanho++;
}

void Desenfileirar(TFila* fila, TUsuario* item)
{
    TCelula* aux;
    if(!Vazia(*fila))
    {
        aux = fila->frente->prox;
        *item = aux->item;
        //ponte
        fila->frente->prox = aux->prox;
        if(fila->frente->prox == NULL)
        {
            fila->tras = fila->frente;
        }
        free(aux);
        fila->tamanho--;
    }

}

void Pesquisar(TFila* fila, TUsuario* item)
{
    TUsuario aux;
    TFila filaaux;
    FFVazia(&filaaux);

    while(!Vazia(*fila))
    {
        Desenfileirar(fila, &aux);
        if(strcmp(aux.CPF, item->CPF) == 0)
        {
            *item = aux;
            fila->tamanho--;
        }
        else
        {
            Enfileirar(&filaaux, aux);
        }
    }

    while(!Vazia(filaaux))
    {
        Desenfileirar(&filaaux, &aux);
        Enfileirar(fila, aux);
    }

    free(filaaux.frente);

}

int PesquisarBooleana(TFila* fila, TUsuario* item)
{
    TUsuario aux;
    int flag = 0;
    TFila filaaux;
    FFVazia(&filaaux);

    while(!Vazia(*fila))
    {
        Desenfileirar(fila, &aux);
        if(strcmp(aux.CPF, item->CPF) == 0)
        {
            flag = 1;
        }
        Enfileirar(&filaaux, aux);
    }

    while(!Vazia(filaaux))
    {
        Desenfileirar(&filaaux, &aux);
        Enfileirar(fila, aux);
    }

    free(filaaux.frente);

    return flag;

}


void Imprimir(TFila fila)
{
    TUsuario aux;
    TFila filaaux;
    FFVazia(&filaaux);
    int i = 1;

    while(!Vazia(fila))
    {
        Desenfileirar(&fila, &aux);
        Enfileirar(&filaaux, aux);
        printf("\nPosicao %d:\n", i);
        ImprimirUsuario(aux);
        i++;
    }

    while(!Vazia(filaaux))
    {
        Desenfileirar(&filaaux, &aux);
        Enfileirar(&fila, aux);
    }

    free(filaaux.frente);

}

//Exercicios

//1

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

//2

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

//3

void InverterFila(TFila* fila)
{

    TUsuario aux;
    TFila filaaux1;
    FFVazia(&filaaux1);

    int i, j, n;

    n = fila->tamanho;

    for(i = 0; i < n; i++)
    {

    }

    free(filaaux1.frente);

}


int main()
{


}
