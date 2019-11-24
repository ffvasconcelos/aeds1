/*

Algoritmos e Estruturas de Dados 1

Aluno: Francisco Figueiredo Vasconcelos

Matricula: 18.1.8018

Projeto: TAD Biblioteca

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Questoes da prova*/

//Livro mais emprestado

int IndiceLivroMaisEmprestado(TModuloLivro moduloLivro, TModuloEmprestimo moduloEmprestimo)
{

    int indiceLivro;

    int qnt1;
    int qnt2 = -1;

    int i, j;

    for(i = 0; i < moduloLivro.Indice; i++)
    {

        qnt1 = 0;

        for(j = 0; j < moduloEmprestimo.Indice; j++)
        {
            if(strcmp(moduloEmprestimo.Vetor[j].ISBNLivro, moduloLivro.Vetor[i].Isbn) == 0)
            {
                qnt1++;
            }
        }

        if(qnt1 > qnt2)
        {

            qnt2 = qnt1;
            indiceLivro = i;

        }

    }

    return indiceLivro;
}

//Multas total em aberto e qnt livros

void MultasEmAbertoELivrosAssociados(TModuloEmprestimo modulo)
{

    int i;

    int multaTotal = 0;
    int qntLivros = 0;

    for(i = 0; i < modulo.Indice; i++)
    {

        if(modulo.Vetor[i].PG == 0)
        {
            multaTotal += modulo.Vetor[i].Multa;
            qntLivros++;
        }

    }

    printf("\n\nTotal de multas em aberto: R$%d,00\n", multaTotal);
    printf("Quantidade de livros relacionados: %d", qntLivros);
}

//Livros em comum

int LivrosEmComum (TUsuario user1, TUsuario user2, TModuloEmprestimo modulo)
{

    int qntLivros = 0;

    int i, j;

    for(i = 0; i < modulo.Indice; i++)
    {
        if(strcmp(user1.CPF,modulo.Vetor[i].CPFLocador) == 0)
        {
            for(j = 0; j < modulo.Indice; j++)
            {
                if(strcmp(user2.CPF,modulo.Vetor[j].CPFLocador) == 0)
                {
                    if(strcmp(modulo.Vetor[i].ISBNLivro,modulo.Vetor[j].ISBNLivro) == 0)
                    {
                        qntLivros++;
                        break;
                    }
                }
            }
        }
    }

    return qntLivros;

}

//Alterar Livro atualizada

void AlterarLivroAtualizada(TModuloLivro* moduloLivro, TModuloEmprestimo* moduloEmprestimo, TLivro livro)
{
    int indice = PesquisarLivro((*moduloLivro), livro);
    char isbnAux[6];


    if(indice != -1)
    {
        int i;
        strcpy(isbnAux, moduloLivro->Vetor[indice].Isbn);
        printf("\nFaca as alteracoes:\n");
        LerLivro(&moduloLivro->Vetor[indice]);
        for(i = 0; i < (*moduloEmprestimo).Indice; i++)
        {
            if(strcmp((*moduloEmprestimo).Vetor[i].ISBNLivro, isbnAux) == 0)
            {
                strcpy(moduloEmprestimo->Vetor[i].ISBNLivro, moduloLivro->Vetor[indice].Isbn);
            }
        }
        printf("\n>>>>>Livro alterado com sucesso<<<<<");
    }
    else
    {
        printf("\n>>>>>Livro nao encontrado<<<<<");
    }
}
