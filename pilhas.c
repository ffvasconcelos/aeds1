#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


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

typedef struct
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
    char item;
    struct celula* prox;
} TCelula;

typedef struct pilha
{
    TCelula *fundo;
    TCelula *topo;
    int tamanho;
} TPilha;

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

int VaziaFila(TFila fila)
{
    return (fila.frente==fila.tras);
}

void Enfileirar(TFila* fila, char item)
{
    fila->tras->prox = (TCelula*)malloc(sizeof(TCelula));
    fila->tras = fila->tras->prox;
    fila->tras->prox = NULL;
    fila->tras->item = item;
    fila->tamanho++;
}

void Desenfileirar(TFila* fila, char* item)
{
    TCelula* aux;
    if(!VaziaFila(*fila))
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

void FPVazia(TPilha *Pilha)
{
    Pilha->topo = (TCelula*) malloc(sizeof(TCelula));
    Pilha->fundo = Pilha->topo;
    Pilha->topo->prox = NULL;
    Pilha->tamanho = 0;
}

int VaziaPilha(TPilha Pilha)
{
    return (Pilha.topo == Pilha.fundo);
}

void Empilha(TPilha *Pilha, char x)
{
    TCelula* Aux;
    Aux = (TCelula*) malloc(sizeof(TCelula));
    Pilha->topo->item = x;
    Aux->prox = Pilha->topo;
    Pilha->topo = Aux;
    Pilha->tamanho++;
}

void Desempilha(TPilha *Pilha, char *Item)
{
    TCelula* q;
    if (VaziaPilha(*Pilha))
    {
        printf("Erro: lista vazia\n");
        return;
    }
    q = Pilha->topo;
    Pilha->topo = q->prox;
    *Item = q->prox->item;
    free(q);
    Pilha->tamanho--;
}

int Tamanho(TPilha Pilha)
{
    return (Pilha.tamanho);
}

void Imprimir(TPilha pilha)
{

    char aux;
    TPilha pilhaaux;
    FPVazia(&pilhaaux);

    while(!VaziaPilha(pilha)){
        Desempilha(&pilha, &aux);
        Empilha(&pilhaaux, aux);
    }

    while(!VaziaPilha(pilhaaux)){
        Desempilha(&pilha, &aux);
        ImprimirUsuario(aux);
        printf("\n\n");
        Empilha(&pilhaaux, aux);
    }

    free(pilhaaux.topo);

}

int Pesquisar(TPilha* pilha, TUsuario* x){

    TUsuario aux;
    TPilha pilhaaux;
    int flag = 0;
    strcpy(aux.CPF, "a");

    FPVazia(&pilhaaux);

    while(!VaziaPilha(*pilha) && (strcmp(x->CPF, aux.CPF) != 0)){
            Desempilha(pilha, &aux);
            if(strcmp(x->CPF, aux.CPF) == 0){
                flag = 1;
            }
            Empilha(&pilhaaux, aux);
    }

    while(!VaziaPilha(pilhaaux)){
        Desempilha(&pilhaaux, &aux);
        Empilha(pilha, aux);
    }

    free(pilhaaux.topo);
    return flag;

}

//Exercicios Pilha

//1(a)

void InvertePilhaComFila(TPilha* pilha){

    TFila filaaux;
    TUsuario aux;

    FFVazia(&filaaux);

    while(!VaziaPilha(*pilha)){
        Desempilha(pilha, &aux);
        Enfileirar(&filaaux, aux);
    }

    while(!VaziaFila(filaaux)){
        Desenfileirar(&filaaux, &aux);
        Empilha(pilha, aux);
    }

    free(filaaux.frente);
}

//2(b)

void InvertePilhaComPilha(TPilha* pilha){

    TPilha pilhaaux;
    TUsuario aux, y;
    int n = pilha->tamanho;
    int i, j;

    FPVazia(&pilhaaux);

    for(i = 0; i < n; i++){

        for(j = 0; j < n - i; j++){
            Desempilha(pilha, &aux);
            Empilha(&pilhaaux, aux);
            if(j == 0)
                y = aux;
        }

        Empilha(pilha, y);

        for(j = 0; j < n - i; j++){
            Desempilha(&pilhaaux, &aux);
            Empilha(pilha, aux);
        }

    }

    free(pilhaaux.topo);

}

//3(c)

void InvertePilhaComPilhas(TPilha* pilha){

    TPilha pilhaaux1, pilhaaux2;
    TUsuario aux;

    FPVazia(&pilhaaux1);
    FPVazia(&pilhaaux2);

    while(!VaziaPilha(*pilha)){
        Desempilha(pilha, &aux);
        Empilha(&pilhaaux1, aux);
    }

    while(!VaziaPilha(pilhaaux1)){
        Desempilha(&pilhaaux1, &aux);
        Empilha(&pilhaaux2, aux);
    }

    while(!VaziaPilha(pilhaaux2)){
        Desempilha(&pilhaaux2, &aux);
        Empilha(pilha, aux);
    }

    free(pilhaaux1.topo);
    free(pilhaaux2.topo);
}


//Monitoria

int VerificaExpressao(char* expressao, TPilha* pilha){

    char aux;

    while(*expressao != '\0'){
        if(*expressao == '(' || *expressao == '[' || *expressao == '{'){
            Empilha(pilha, *expressao);
        }
        else if(*expressao == ')' || *expressao == ']' || *expressao == '}'){
            Desempilha(pilha, &aux);
            if((aux == '(' && *expressao != ')')||(aux == '[' && *expressao != ']')||(aux == '{' && *expressao != '}')){

                while(!VaziaPilha(pilha)){
                    Desempilha(pilha, &aux);
                }

                return 0;
            }
        }

        if(VaziaPilha(pilha))
            return 1;
        else{
            while(!VaziaPilha(pilha)){
                Desempilha(pilha, &aux);
            }

            return 0;
        }

    }



}

