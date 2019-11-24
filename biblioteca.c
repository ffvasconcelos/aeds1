/*

Algoritmos e Estruturas de Dados 1

Aluno: Francisco Figueiredo Vasconcelos

Matricula: 18.1.8018

Projeto: TAD Biblioteca

*/


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

/*Livro*/

typedef struct TLivro
{
    char Isbn [6];
    char Titulo [30];
    char PrimeiroNomeAutor [30];
    char SegundoNomeAutor [30];
    char Editora [30];
    TData DataDePublicacao;
    char LocalPublicacao [40];
    int Edicao;
    int QntExistente;
    int QntLocados;
} TLivro;

/*Usuarios*/

typedef struct TUsuario
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

/*Emprestimo*/

typedef struct TEmprestimo
{
    char CPFLocador [11];
    char ISBNLivro [6];
    TData DataEmprestimo;
    TData DataEntrega;
    TData DataDevolucao;
    int Multa;
    int PG;
} TEmprestimo;

/*Modulos*/

typedef struct tmoduloUsuario
{

    TUsuario Vetor[100];
    int Indice;

} TModuloUsuario;

typedef struct tmoduloLivro
{

    TLivro Vetor[100];
    int Indice;

} TModuloLivro;

typedef struct tmoduloEmprestimo
{

    TEmprestimo Vetor[100];
    int Indice;

} TModuloEmprestimo;

/*Operacoes Auxiliares*/

// Verificar condicoes do emprestimo

int VerificarCondicoesEmprestimo(TUsuario user, TModuloEmprestimo modulo)
{

    int i;
    int multaTotal;

    for(i = 0; i < modulo.Indice; i++)
    {
        if(strcmp(user.CPF,modulo.Vetor[i].CPFLocador) == 0)
        {
            if(modulo.Vetor[i].PG != 1)
            {
                return 0;
            }



            if(user.Tipo == 1 || user.Tipo == 2)
            {
                if(user.QtdLivros < 3)
                {
                    return 1;
                }
            }
            else
            {
                if(user.QtdLivros < 5)
                {
                    return 1;
                }
            }
        }
    }

    return 2;
}

//Datas
TData CalcularDataEntrega(TData Data_Emprestimo)
{


    TData Data_Entrega = Data_Emprestimo;

    Data_Entrega.Dia += 14;

    if(Data_Entrega.Mes == 1 || Data_Entrega.Mes == 3 || Data_Entrega.Mes == 5 || Data_Entrega.Mes == 7 || Data_Entrega.Mes == 8 || Data_Entrega.Mes == 10)
    {

        if(Data_Entrega.Dia > 31)
        {

            Data_Entrega.Dia = Data_Entrega.Dia - 31;
            Data_Entrega.Mes++;

        }

    }
    else
    {

        if(Data_Emprestimo.Mes == 12)
        {

            if(Data_Entrega.Dia > 31)
            {

                Data_Entrega.Dia = Data_Entrega.Dia - 31;
                Data_Entrega.Ano++;
                Data_Entrega.Mes = 1;

            }

        }
        else
        {

            if(Data_Entrega.Dia > 30)
            {
                Data_Entrega.Dia = Data_Entrega.Dia - 30;
                Data_Entrega.Mes++;
            }

        }


    }

    return Data_Entrega;

}

int CalcularMulta(TData Data_Entrega, TData Data_Devolucao)
{

    int qntDias = 0;
    int multa;
    int vetorQntDias[12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

    if(Data_Devolucao.Ano - Data_Entrega.Ano != 0)
    {

        qntDias = qntDias + 365 * (Data_Devolucao.Ano - Data_Entrega.Ano);

    }

    if(Data_Devolucao.Mes - Data_Entrega.Mes > 0)
    {

        qntDias = qntDias + vetorQntDias[Data_Devolucao.Mes - 1] - vetorQntDias[Data_Entrega.Mes - 1];

    }
    else if(Data_Devolucao.Mes - Data_Entrega.Mes < 0)
    {

        qntDias = qntDias - 365 + vetorQntDias[Data_Entrega.Mes - 1] + vetorQntDias[11] - vetorQntDias[Data_Devolucao.Mes - 1];

    }

    if(Data_Devolucao.Dia - Data_Entrega.Dia > 0)
    {

        qntDias = qntDias + Data_Devolucao.Dia - Data_Entrega.Dia;

    }
    else if(Data_Devolucao.Dia - Data_Entrega.Dia < 0)
    {

        qntDias = qntDias - (vetorQntDias[Data_Devolucao.Mes - 1] - vetorQntDias[Data_Devolucao.Mes - 2]) + (vetorQntDias[Data_Entrega.Mes - 1] - vetorQntDias[Data_Entrega.Mes - 2] - Data_Entrega.Dia) + Data_Devolucao.Dia;

    }

    multa = qntDias * 2;

    return multa;

}

//Iniciar
void IniciarModuloUsuario(TModuloUsuario* modulo)
{

    modulo->Indice = 0;

}

void IniciarModuloLivro(TModuloLivro* modulo)
{

    modulo->Indice = 0;

}

void IniciarModuloEmprestimo(TModuloEmprestimo* modulo)
{

    modulo->Indice = 0;

}

//Ler
void LerUsuario(TUsuario* user)
{

    printf("\nNome: ");
    fflush(stdin);
    fgets(user->Nome,50,stdin);

    printf("\nSobrenome: ");
    fflush(stdin);
    fgets(user->Sobrenome,50,stdin);

    printf("\nCPF: ");
    fflush(stdin);
    fgets(user->CPF,14,stdin);

    printf("\nRG: ");
    fflush(stdin);
    fgets(user->RG,11,stdin);

    printf("\nLogradouro: ");
    fflush(stdin);
    fgets(user->Endereco.Logradouro,50,stdin);

    printf("\nBairro: ");
    fflush(stdin);
    fgets(user->Endereco.Bairro,50,stdin);

    printf("\nNumero: ");
    fflush(stdin);
    scanf("%d",&user->Endereco.Num);

    printf("\nComplemento: ");
    fflush(stdin);
    fgets(user->Endereco.Complemento,10,stdin);

    printf("\nCidade: ");
    fflush(stdin);
    fgets(user->Endereco.Cidade,50,stdin);

    printf("\nCEP: ");
    fflush(stdin);
    fgets(user->Endereco.CEP,11,stdin);

    printf("\nData de nascimento: ");
    printf("\nDia: ");
    fflush(stdin);
    scanf("%d", &user->DataDeNascimento.Dia);

    printf("\nMes: ");
    fflush(stdin);
    scanf("%d", &user->DataDeNascimento.Mes);

    printf("\nAno: ");
    fflush(stdin);
    scanf("%d", &user->DataDeNascimento.Ano);

    printf("\nDigite:\n1 se voce e aluno \n2 se voce e funcionario \n3 se voce e professor\n=>");
    fflush(stdin);
    scanf("%d", &user->Tipo);

    if(user->Tipo == 1)
    {

        printf("\nMatricula: ");
        fflush(stdin);
        fgets(user->Matricula,11,stdin);

        printf("\nNome do curso: ");
        fflush(stdin);
        fgets(user->NomeDoCurso, 50, stdin);

    }
    else if(user->Tipo == 2 || user->Tipo == 3)
    {

        printf("\nSiape: ");
        fflush(stdin);
        fgets(user->Siape,12,stdin);

        printf("\nDepartamento: ");
        fflush(stdin);
        fgets(user->Departamento,10,stdin);

    }

}

void LerLivro(TLivro* livro)
{
    printf("\nTitulo: ");
    fflush(stdin);
    fgets(livro->Titulo,30,stdin);

    printf("\nPrimeiro nome do autor: ");
    fflush(stdin);
    fgets(livro->PrimeiroNomeAutor,30,stdin);

    printf("\nSegundo nome do autor: ");
    fflush(stdin);
    fgets(livro->SegundoNomeAutor,30,stdin);

    printf("\nISBN: ");
    fflush(stdin);
    fgets(livro->Isbn,6,stdin);

    printf("\nEditora: ");
    fflush(stdin);
    fgets(livro->Editora,30,stdin);

    printf("\nData de publicacao: ");
    printf("\nDia: ");
    fflush(stdin);
    scanf("%d", &livro->DataDePublicacao.Dia);
    printf("\nMes: ");
    fflush(stdin);
    scanf("%d", &livro->DataDePublicacao.Mes);
    printf("\nAno: ");
    fflush(stdin);
    scanf("%d", &livro->DataDePublicacao.Ano);

    printf("\nLocal de publicacao: ");
    fflush(stdin);
    fgets(livro->LocalPublicacao,30,stdin);

    printf("\nEdicao: ");
    fflush(stdin);
    scanf("%d", &livro->Edicao);

    printf("\nQuantidade de livros: ");
    fflush(stdin);
    scanf("%d", &livro->QntExistente);

}

void LerEmprestimo(TEmprestimo* emprestimo)
{

    printf("\nCPF do locador: ");
    fflush(stdin);
    fgets(emprestimo->CPFLocador,14,stdin);

    printf("\nISBN do livro: ");
    fflush(stdin);
    fgets(emprestimo->ISBNLivro,6,stdin);

    printf("\nData de empréstimo: ");
    printf("\nDia: ");
    fflush(stdin);
    scanf("%d", &emprestimo->DataEmprestimo.Dia);

    printf("\nMês: ");
    fflush(stdin);
    scanf("%d", &emprestimo->DataEmprestimo.Mes);

    printf("\nAno: ");
    fflush(stdin);
    scanf("%d", &emprestimo->DataEmprestimo.Ano);


}

//Imprimir

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

void ImprimirLivro(TLivro livro)
{

    printf("\nTítulo: %s", livro.Titulo);
    printf("\nAutor: %s %s", livro.PrimeiroNomeAutor, livro.SegundoNomeAutor);
    printf("\nISBN: %s", livro.Isbn);
    printf("\nEditora: %s", livro.Editora);
    printf("\nEdição: %d", livro.Edicao);
    printf("\nData de publicação: %d/%d/%d", livro.DataDePublicacao.Dia, livro.DataDePublicacao.Mes, livro.DataDePublicacao.Ano);
    printf("\nLocal de publicação: %s", livro.LocalPublicacao);
    printf("\nQuantidade de cópias existentes: %d", livro.QntExistente);
    printf("\nQuantidade de cópias locadas: %d\n", livro.QntLocados);

}

void ImprimirEmprestimo(TEmprestimo emprestimo)
{

    printf("CPF do locador: %s", emprestimo.CPFLocador);
    printf("ISBN do livro locado: %s", emprestimo.ISBNLivro);
    printf("Data de realização: %d/%d/%d", emprestimo.DataEmprestimo.Dia, emprestimo.DataEmprestimo.Mes, emprestimo.DataEmprestimo.Ano);

}

//Imprimir geral

void ImprimirGeralUsuario(TModuloUsuario modulo)
{

    int count;

    for(count = 0; count < modulo.Indice; count++)
    {
        printf("\nUsuario %d:\n\n", count + 1);
        ImprimirUsuario(modulo.Vetor[count]);
    }

}

void ImprimirGeralLivro(TModuloLivro modulo)
{

    int count;

    for(count = 0; count < modulo.Indice; count++)
    {
        printf("\nLivro %d:\n\n", count + 1);
        ImprimirLivro(modulo.Vetor[count]);
    }

}

void ImprimirGeralEmprestimo(TModuloEmprestimo modulo)
{

    int count;

    for(count = 0; count < modulo.Indice; count++)
    {
        printf("\nUsuario %d:\n\n", count + 1);
        ImprimirEmprestimo(modulo.Vetor[count]);
    }

}

/*Operacoes Basicas*/

//Pesquisar
int PesquisarUsuario (TModuloUsuario modulo, TUsuario user)
{

    int i;

    for(i = 0; i < modulo.Indice; i++)
    {
        if(strcmp(modulo.Vetor[i].CPF, user.CPF) == 0)
        {
            return i;
        }
    }

}

int PesquisarLivro (TModuloLivro modulo, TLivro livro)
{

    int i = 0;

    for(i = 0; i < modulo.Indice; i++)
    {
        if(strcmp(modulo.Vetor[i].Isbn, livro.Isbn) == 0)
        {
            return i;
        }
    }
}

int PesquisarEmprestimo (TModuloEmprestimo modulo, TUsuario usuario, TLivro livro, TData data)
{

    int i;

    for(i = 0; i < modulo.Indice; i++)
    {
        if(i < modulo.Indice && ((strcmp(modulo.Vetor[i].CPFLocador,usuario.CPF) == 0) && strcmp(modulo.Vetor[i].ISBNLivro,livro.Isbn) == 0))
        {
            if((modulo.Vetor[i].DataEmprestimo.Dia == data.Dia) && (modulo.Vetor[i].DataEmprestimo.Mes == data.Mes) && (modulo.Vetor[i].DataEmprestimo.Ano == data.Ano))
            {
                return i;
            }
        }
    }
    return -1;
}


//Inserir
void InserirUsuario(TModuloUsuario* moduloUsuario, TUsuario usuario)
{

    moduloUsuario->Vetor[moduloUsuario->Indice] = usuario;
    moduloUsuario->Vetor[moduloUsuario->Indice].QtdLivros = 0;
    moduloUsuario->Indice++;

}

void InserirLivro(TModuloLivro* moduloLivro, TLivro livro)
{

    moduloLivro->Vetor[moduloLivro->Indice] = livro;
    moduloLivro->Vetor[moduloLivro->Indice].QntLocados = 0;
    moduloLivro->Indice++;

}

void InserirEmprestimo(TModuloEmprestimo* moduloEmprestimo, TModuloLivro* moduloLivro, TModuloUsuario* moduloUsuario, TEmprestimo emprestimo, TLivro livro, TUsuario user)
{

    int indiceLivro;
    int indiceUsuario;

    indiceLivro = PesquisarLivro((*moduloLivro), livro);
    indiceUsuario = PesquisarUsuario((*moduloUsuario), user);

    if(VerificarCondicoesEmprestimo((*moduloUsuario).Vetor[indiceUsuario], (*moduloEmprestimo)) == 1)
    {
        if(indiceLivro != -1)
        {
            if(indiceUsuario != -1)
            {
                if((*moduloLivro).Vetor[indiceLivro].QntExistente - (*moduloLivro).Vetor[indiceLivro].QntLocados > (float)(*moduloLivro).Vetor[indiceLivro].QntExistente * 0.1)
                {
                    moduloLivro->Vetor[indiceLivro].QntLocados++;
                    emprestimo.DataEntrega = CalcularDataEntrega(emprestimo.DataEmprestimo);
                    moduloEmprestimo->Vetor[moduloEmprestimo->Indice] = emprestimo;
                    moduloUsuario->Vetor[indiceUsuario].QtdLivros++;
                    moduloEmprestimo->Vetor[moduloEmprestimo->Indice].PG = 1;
                    moduloEmprestimo->Indice++;
                }
                else
                {
                    printf("\n>>>>>O emprestimo nao pode ser realizado, todos os livros disponiveis ja foram locados<<<<<");
                }
            }
            else
            {
                printf("\n>>>>>O emprestimo nao pode ser realizado, o usuario nao esta registrado<<<<<");
            }
        }
        else
        {
            printf("\n>>>>>O emprestimo nao pode ser realizado, o livro nao pode ser encontrado<<<<<");
        }
    }
    else if(VerificarCondicoesEmprestimo((*moduloUsuario).Vetor[indiceUsuario], (*moduloEmprestimo)) == 0)
    {
        printf("\n>>>>>O emprestimo nao pode ser realizado, o usuario tem multa pendente<<<<<");
    }
    else if(VerificarCondicoesEmprestimo((*moduloUsuario).Vetor[indiceUsuario], (*moduloEmprestimo)) == 2)
    {
        printf("\n>>>>>O emprestimo nao pode ser realizado, o usuario alcancou a quantidade maxima de livros que podem ser locados<<<<<");
    }
}

//Alterar
void AlterarUsuario(TModuloUsuario* modulo, TUsuario user)
{
    int indice = PesquisarUsuario((*modulo), user);

    if(indice != -1)
    {
        printf("\nFaca as alteracoes:\n");
        LerUsuario(&modulo->Vetor[indice]);
        printf("\n>>>>>Usuario alterado com sucesso<<<<<\n");
    }
    else
    {
        printf("\n>>>>>Usuario nao encontrado<<<<<");
    }
}

void AlterarLivro(TModuloLivro* modulo, TLivro livro)
{
    int indice = PesquisarLivro((*modulo), livro);

    if(indice != -1)
    {
        printf("\nFaca as alteracoes:\n");
        LerLivro(&modulo->Vetor[indice]);
        printf("\n>>>>>Livro alterado com sucesso<<<<<");
    }
    else
    {
        printf("\n>>>>>Livro nao encontrado<<<<<");
    }
}

void AlterarEmprestimo(TModuloEmprestimo* modulo, TUsuario user, TLivro livro, TData data)
{
    int indice = PesquisarEmprestimo((*modulo), user, livro, data);

    if(indice != -1)
    {
        printf("\nFaca as alteracoes:\n");
        LerEmprestimo(&modulo->Vetor[indice]);
        printf("\n>>>>>Emprestimo alterado com sucesso!<<<<<");
    }
    else
    {
        printf("\n>>>>>Emprestimo nao encontrado<<<<<");
    }
}

//Excluir
void ExcluirUsuario(TModuloUsuario* modulo, TUsuario user)
{

    int indice = PesquisarUsuario((*modulo), user);
    int i;

    if(indice != -1)
    {
        modulo->Indice--;
        for(i = indice; i < modulo->Indice; i++)
        {
            modulo->Vetor[i] = modulo->Vetor[i + 1];
        }
        printf("\nO usuario foi excluido\n");
    }
    else
    {
        printf("\nO usuario nao existe\n");
    }
}

void ExcluirLivro(TModuloLivro* modulo, TLivro livro)
{

    int indice = PesquisarLivro((*modulo), livro);
    int i;

    if(indice != -1)
    {
        modulo->Indice--;
        for(i = indice; i < modulo->Indice; i++)
        {
            modulo->Vetor[i] = modulo->Vetor[i + 1];
        }
        printf("\n>>>>>O livro foi excluido<<<<<\n");
    }
    else
    {
        printf("\n>>>>>O livro nao existe<<<<<<\n");
    }
}

void ExcluirEmprestimo(TModuloEmprestimo* modulo, TUsuario user, TLivro livro, TData data)
{

    int indice = PesquisarEmprestimo((*modulo), user, livro, data);
    int i;

    if(indice != -1)
    {
        modulo->Indice--;
        for(i = indice; i < modulo->Indice; i++)
        {
            modulo->Vetor[i] = modulo->Vetor[i + 1];
        }
        printf("\nO emprestimo foi excluido\n");
    }
    else
    {
        printf("\nO emprestimo nao existe\n");
    }
}

//Pagamento da multa

void EfetuarPagamento(TModuloEmprestimo* modulo, TEmprestimo emprestimo)
{

    int indiceEmprestimo;
    int resposta;

    TLivro livro;
    TUsuario user;

    strcpy(user.CPF, emprestimo.CPFLocador);
    strcpy(livro.Isbn, emprestimo.ISBNLivro);

    indiceEmprestimo = PesquisarEmprestimo((*modulo), user, livro, emprestimo.DataEmprestimo);

    do
    {

        printf("\nDeseja quitar a multa agora?\n");
        printf("Valor: R$%d.00", modulo->Vetor[indiceEmprestimo].Multa);
        printf("\nDigite 1 caso deseje e 0 caso nao queira: ");

        fflush(stdin);
        scanf("%d", &resposta);

        switch (resposta)
        {
        case 0:
            printf(">>>>>Sua divida foi armazenada<<<<<");
            resposta = 2;
            break;
        case 1:
            system("PAUSE");
            modulo->Vetor[indiceEmprestimo].PG = 1;
            printf("\n\n>>>>>Sua multa foi quitada com sucesso<<<<<");
            resposta = 2;
            break;
        default:
            printf("A opcao selecionada nao existe, tente novamente");
            system("PAUSE");
        }
    }
    while(resposta != 2);

}

//Baixa no emprestimo
void BaixaEmprestimo(TModuloEmprestimo* moduloEmprestimo, TEmprestimo emprestimo)
{

    int indiceEmprestimo;
    TUsuario user;
    TLivro livro;

    strcpy(user.CPF, emprestimo.CPFLocador);
    strcpy(livro.Isbn, emprestimo.ISBNLivro);

    printf("\nInforme a data de devolucao: ");
    printf("\n\tDia: ");
    fflush(stdin);
    scanf("%d", &emprestimo.DataDevolucao.Dia);

    printf("\n\tMes: ");
    fflush(stdin);
    scanf("%d", &emprestimo.DataDevolucao.Mes);

    printf("\n\tAno: ");
    fflush(stdin);
    scanf("%d", &emprestimo.DataDevolucao.Ano);


    indiceEmprestimo = PesquisarEmprestimo((*moduloEmprestimo), user, livro, emprestimo.DataEmprestimo);


    if(indiceEmprestimo != -1)
    {

        moduloEmprestimo->Vetor[indiceEmprestimo].DataDevolucao = emprestimo.DataDevolucao;



        moduloEmprestimo->Vetor[indiceEmprestimo].Multa = CalcularMulta(emprestimo.DataEmprestimo, emprestimo.DataDevolucao);

        if(moduloEmprestimo->Vetor[indiceEmprestimo].Multa < 0)
        {
            moduloEmprestimo->Vetor[indiceEmprestimo].Multa = 0;
            moduloEmprestimo->Vetor[indiceEmprestimo].PG = 1;
        }


        if(moduloEmprestimo->Vetor[indiceEmprestimo].Multa != 0)
        {
            moduloEmprestimo->Vetor[indiceEmprestimo].PG = 0;
            EfetuarPagamento(moduloEmprestimo, emprestimo);
        }

    }
    else
    {

        printf("\n>>>>>Esse emprestimo nao existe<<<<<\n");

    }
}

/*Modulos de Menu*/

//Mensagens

void MSG_MENU()
{
    printf("\t\t>>>>>>>>>>>>>Menu Principal<<<<<<<<<<<<<");
    printf("\n");
    printf("\n\t1) Modulo 1 - Modulo Livro");
    printf("\n\t2) Modulo 2 - Modulo Usuario");
    printf("\n\t3) Modulo 3 - Modulo Emprestimo");
    printf("\n\t4) SAIR");

    printf("\n\n\t- Digite uma opcao: ");
}

void MSG_SUBMENU(int numero_modulo)
{
    printf("\t\t>>>>>>>>>>>>>Modulo %d<<<<<<<<<<<<<", numero_modulo);
    printf("\n");
    printf("\n\t1) Inserir");
    printf("\n\t2) Alterar");
    printf("\n\t3) Pesquisar");
    printf("\n\t4) Excluir");
    printf("\n\t5) Imprimir geral");

    if(numero_modulo == 3)
    {
        printf("\n\t6) Baixa no emprestimo");
        printf("\n\t7) Efetuar pagamento da multa");
        printf("\n\t8) Sair");
    }
    else
    {
        printf("\n\t6) SAIR");
    }

    printf("\n\n\t- Digite uma opcao: ");
}

//SubMenus

void SubmenuModulo1(TModuloLivro* modulo, TLivro livro)
{
    int opcao;
    int indice;

    do
    {
        MSG_SUBMENU(1);
        fflush(stdin);
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            printf("\nInsira os dados do livro: ");
            LerLivro(&livro);
            InserirLivro(modulo,livro);
            printf("\n\n>>>>>Livro cadastrado com sucesso!<<<<<\n\n");

            system("PAUSE");

            break;
        case 2:
            printf("\nInforme o ISBN do livro desejado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);
            indice = PesquisarLivro((*modulo),livro);
            if(indice == -1)
            {
                printf("\n\n>>>>>O livro nao foi encontrado<<<<<\n\n");
            }
            else
            {
                printf("\nAltere os dados do livro:\n");
                LerLivro(&modulo->Vetor[indice]);
                printf("\n\n>>>>>Dados do livro atualizados com sucesso<<<<<\n\n");
            }

            system("PAUSE");

            break;
        case 3:
            printf("\nInforme o ISBN do livro desejado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);
            indice = PesquisarLivro((*modulo),livro);
            if(indice == -1)
            {
                printf("\n\n>>>>>O livro nao foi encontrado<<<<<\n\n");
            }
            else
            {
                ImprimirLivro(modulo->Vetor[indice]);
            }

            system("PAUSE");

            break;
        case 4:
            printf("\nInforme o ISBN do livro desejado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);
            ExcluirLivro(modulo,livro);

            system("PAUSE");

            break;
        case 5:
            printf("\nSeguem os dados dos livros cadastrados:\n\n");
            ImprimirGeralLivro((*modulo));

            system("PAUSE");

            break;
        case 6:
            printf("\n\n>>>>>Fechando o modulo<<<<<\n\n");

            system("PAUSE");

            break;
        default:
            printf("\n\n>>>>>A opcao solicitada nao existe<<<<<\n\n");
            system("PAUSE");
        }

    }
    while(opcao != 6);

}

void SubMenuModulo2(TModuloUsuario* modulo, TUsuario user)
{
    int opcao;
    int indice;

    do
    {
        MSG_SUBMENU(2);
        fflush(stdin);
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            printf("\nInsira os dados do usuario: ");
            LerUsuario(&user);
            InserirUsuario(modulo,user);
            printf("\n\n>>>>>Usuario cadastrado com sucesso!<<<<<\n\n");

            system("PAUSE");

            break;
        case 2:
            printf("\nInforme o CPF do usuario desejado: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);
            indice = PesquisarUsuario((*modulo),user);
            if(indice == -1)
            {
                printf("\n\n>>>>>O usuario nao foi encontrado<<<<<\n\n");
            }
            else
            {
                printf("\nAltere os dados do usuario:\n");
                LerUsuario(&modulo->Vetor[indice]);
                printf("\n\n>>>>>Dados do usuario atualizados<<<<<\n\n");
            }

            system("PAUSE");

            break;
        case 3:
            printf("\nInforme o CPF do usuario desejado: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);
            indice = PesquisarUsuario((*modulo),user);
            if(indice == -1)
            {
                printf("\n\n>>>>>O usuario nao foi encontrado<<<<<\n\n");
            }
            else
            {
                ImprimirUsuario(modulo->Vetor[indice]);
            }

            system("PAUSE");

            break;
        case 4:
            printf("\nInforme o CPF do usuarios desejado: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);
            ExcluirUsuario(modulo,user);
            break;

            system("PAUSE");

        case 5:
            printf("\nSeguem os dados dos usuarios cadastrados:\n\n");
            ImprimirGeralUsuario((*modulo));
            system("PAUSE");
            break;
        case 6:
            printf("\n\n>>>>>Fechando o modulo<<<<<\n\n");
            system("PAUSE");
            break;
        default:
            printf("\n\n>>>>>A opcao solicitada nao existe<<<<<\n\n");
            system("PAUSE");
        }

    }
    while(opcao != 6);

}

void SubMenuModulo3(TModuloEmprestimo* moduloEmprestimo, TEmprestimo emprestimo, TUsuario user, TLivro livro, TModuloLivro* moduloLivro, TModuloUsuario* moduloUsuario)
{
    int opcao;
    int indice;
    TData data;

    do
    {
        MSG_SUBMENU(3);
        fflush(stdin);
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            printf("\nInsira os dados do emprestimo: ");
            LerEmprestimo(&emprestimo);
            strcpy(livro.Isbn, emprestimo.ISBNLivro);
            strcpy(user.CPF, emprestimo.CPFLocador);
            InserirEmprestimo(moduloEmprestimo,moduloLivro,moduloUsuario,emprestimo,livro,user);
            printf("\n\n>>>>>Emprestimo realizado com sucesso!<<<<<\n\n");

            system("PAUSE");

            break;
        case 2:
            printf("\nInforme o CPF do usuario: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);

            printf("\nDigite o ISBN do livro locado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);

            printf("\nDigite a data que o emprestimo foi realizado: ");
            printf("\nDia: ");
            fflush(stdin);
            scanf("%d", &data.Dia);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%d", &data.Mes);
            printf("\nAno: ");
            fflush(stdin);
            scanf("%d", &data.Ano);

            indice = PesquisarEmprestimo((*moduloEmprestimo), user, livro, data);
            if(indice == -1)
            {
                printf("\n\n>>>>>O emprestimo nao foi encontrado<<<<<\n\n");
            }
            else
            {
                printf("Altere os dados do emprestimo:\n");
                LerEmprestimo(&moduloEmprestimo->Vetor[indice]);
                printf("\n\n>>>>>Dados do emprestimo atualizados<<<<<\n\n");
            }

            system("PAUSE");

            break;
        case 3:
            printf("\nInforme o CPF do usuario: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);

            printf("\nDigite o ISBN do livro locado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);

            printf("\nDigite a data que o emprestimo foi realizado: ");
            printf("\nDia: ");
            fflush(stdin);
            scanf("%d", &data.Dia);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%d", &data.Mes);
            printf("\nAno: ");
            fflush(stdin);
            scanf("%d", &data.Ano);

            indice = PesquisarEmprestimo((*moduloEmprestimo),user,livro,data);
            if(indice == -1)
            {
                printf("\n\n>>>>>O emprestimo nao foi encontrado<<<<<\n\n");
            }
            else
            {
                ImprimirEmprestimo(moduloEmprestimo->Vetor[indice]);
            }

            system("PAUSE");

            break;
        case 4:
            printf("\nInforme o CPF do usuario: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);

            printf("\nDigite o ISBN do livro locado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);

            printf("\nDigite a data que o emprestimo foi realizado: ");
            printf("\nDia: ");
            fflush(stdin);
            scanf("%d", &data.Dia);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%d", &data.Mes);
            printf("\nAno: ");
            fflush(stdin);
            scanf("%d", &data.Ano);

            ExcluirEmprestimo(moduloEmprestimo,user,livro,data);

            system("PAUSE");

            break;
        case 5:
            printf("\nSeguem os dados dos emprestimos cadastrados:\n\n");
            ImprimirGeralEmprestimo((*moduloEmprestimo));

            system("PAUSE");
            break;
        case 6:
            printf("\nInforme o CPF do usuario: ");
            fflush(stdin);
            fgets(emprestimo.CPFLocador,14,stdin);

            printf("\nDigite o ISBN do livro locado: ");
            fflush(stdin);
            fgets(emprestimo.ISBNLivro,6,stdin);

            printf("\nDigite a data que o emprestimo foi realizado: ");
            printf("\nDia: ");
            fflush(stdin);
            scanf("%d", &emprestimo.DataEmprestimo.Dia);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%d", &emprestimo.DataEmprestimo.Mes);
            printf("\nAno: ");
            fflush(stdin);
            scanf("%d", &emprestimo.DataEmprestimo.Ano);

            BaixaEmprestimo(moduloEmprestimo, emprestimo);

            system("PAUSE");

            break;
        case 7:
            printf("\nInforme o CPF do usuario: ");
            fflush(stdin);
            fgets(user.CPF,14,stdin);

            printf("\nDigite o ISBN do livro locado: ");
            fflush(stdin);
            fgets(livro.Isbn,6,stdin);

            printf("\nDigite a data que o emprestimo foi realizado: ");
            printf("\nDia: ");
            fflush(stdin);
            scanf("%d", &data.Dia);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%d", &data.Mes);
            printf("\nAno: ");
            fflush(stdin);
            scanf("%d", &data.Ano);

            indice = PesquisarEmprestimo((*moduloEmprestimo), user, livro, data);

            if(moduloEmprestimo->Vetor[indice].Multa != 0)
            {
                EfetuarPagamento(moduloEmprestimo, (*moduloEmprestimo).Vetor[indice]);
            }
            else
            {
                printf(">>>>>Nao ha multa a ser quitada<<<<<");
            }

            system("PAUSE");
            break;
        case 8:
            printf("\n\n>>>>>Fechando o modulo<<<<<\n\n");
            system("PAUSE");
            break;
        default:
            printf("\n\n>>>>>A opcao solicitada nao existe<<<<<\n\n");
            system("PAUSE");
        }

    }
    while(opcao != 8);

}

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

/*Funcao Main*/

int main ()
{

    //Variaveis auxiliares
    TUsuario usuario;
    TLivro livro;
    TEmprestimo emprestimo;
    int opcao;


    //Modulos
    TModuloUsuario moduloUsuario;
    TModuloLivro moduloLivro;
    TModuloEmprestimo moduloEmprestimo;

    IniciarModuloUsuario(&moduloUsuario);
    IniciarModuloLivro(&moduloLivro);
    IniciarModuloEmprestimo(&moduloEmprestimo);

    do
    {
        system("cls");
        MSG_MENU();
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            SubmenuModulo1(&moduloLivro, livro);
            break;
        case 2:
            SubMenuModulo2(&moduloUsuario, usuario);
            break;
        case 3:
            SubMenuModulo3(&moduloEmprestimo, emprestimo, usuario, livro, &moduloLivro, &moduloUsuario);
            break;
        case 4:
            printf("\n>>>>>>>>Saindo do programa<<<<<<<<");
            system("PAUSE");
            break;
        default:
            printf("\n>>>>>>>>>Essa opcao nao existe!<<<<<<<<<");
        }

    }
    while (opcao != 4);



}
