/*
Lista Algoritmos e Estruturas de Dados I
Arvores de busca binaria
Francisco Figueiredo Vasconcelos
*/

//Questao 5

void Exibir_MENU(){
    system("cls");

    printf("Operacoes da arvore: \n\n\n");
    printf("\t1) Maximo\n");
    printf("\t2) Minimo\n");
    printf("\t3) Inserir\n");
    printf("\t4) Remover\n");
    printf("\t5) Sucessor\n");
    printf("\t6) Predecessor\n");
    printf("\t7) Caminhamento Central\n");
    printf("\t8) SAIR");
}

void Exec_Menu(int num, TArvore* arvore, TCelula* no, TItem item){

    switch (num){
    case 1:
        **no = Maximo(arvore->raiz);
        printf("%d", *no->item);
        break;
    case 2:
        **no = Minimo(arvore->raiz);
        printf("%d", *no->item);
        break;
    case 3:
        Inserir(&(arvore->raiz), NULL, item);
        break;
    case 4:
        no = Pesquisar(arvore->raiz, item);
        Retirar(arvore, &no);
        break;
    case 5:
        no = Pesquisar(arvore->raiz, item);
        no = Sucessor(no);
        printf("%d", *no->item);
        break;
    case 6:
        no = Pesquisar(arvore->raiz, item);
        no = Predecessor(no);
        printf("%d", *no->item);
        break;
    case 7:
        Central(arvore->raiz);
    default:
        return;
    }
}
