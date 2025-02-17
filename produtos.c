#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

void cadastroProdutos(Lista* lista){

    int qtdParaCadastrar = 0;  //limite Loop para cadastro
    int codigo = 0;             //codigo do item
    char nome[MAX_CHAR];        //nome do item
    float preco = 0;            //pre�o do item
    int quant = 0;              //quantidade do item
    int validador = 0;

    printf("\n\t\t\t\t-------------------- Cadastro de Produtos --------------------\n\n");

    do {
        printf("\n\t\t\t\tDigite a quantidade de produtos que deseja cadastrar: ");
        scanf("%d", &qtdParaCadastrar);

        if(qtdParaCadastrar <= 0){
            system("cls");
            printf("\t\t\t\tQuantidade de produtos inv�lido! (Digite um numero maior que 0!)\n\n");
        }

    } while(qtdParaCadastrar <= 0);

    Produto* produto = (Produto*) malloc(sizeof(Produto));

    if(produto == NULL){
        printf("Erro na aloca��o de mem�ria!");
        return;
    }

    for(int i = 0; i < qtdParaCadastrar; i++){

        // CODIGO DO ITEM
        do {
            system("cls");
            printf("\n\t\t\t\t-------------------- Cadastro de Produtos [%d] --------------------\n\n", qtdParaCadastrar - i);
            printf("\n\t\t\t\tDigite o c�digo do %d� produto: ", i + 1);
            scanf("%d", &codigo);
            getchar();
            validador = 0;


            if(codigo <= 0){  // condi��o de id igual a zero
                system("cls");
                printf("\t\t\t\tC�digo de produto inv�lido! (Digite um numero maior que 0!)\n\n");
                validador++;
            }

            if(Procurar(lista, codigo) != NULL){ // condi��o de id existente
                system("cls");
                printf("\t\t\t\tC�digo de item inv�lido! (ID j� existe!)\n\n");
                validador++;
            }

            if(validador > 0){
                system("pause");
            }

        } while(validador > 0);


        // NOME DO ITEM
       do {
            //fflush(stdin);

            printf("\n\t\t\t\tDigite o nome do produto: ");
            fgets(nome, MAX_CHAR, stdin);
            strtok(nome, "\n");
            validador = 0;

            if(strcmp(nome, " ") == 0) { // condi��o de nome n�o ser s� espa�os
                printf("\n\t\t\t\tInforma��o 'nome' � obrigat�ria, digite um nome v�lido!\n");
                validador++;
            }

        } while(validador > 0);


        // PRE�O DO ITEM
        do {
            printf("\n\t\t\t\tDigite o pre�o do produto: ");
            scanf("%f", &preco);
            getchar();
            validador = 0;

            if(preco < 0) {  // condi��o de pre�o ser miaor ou igual a zero
                printf("\n\t\t\t\tDigite um pre�o v�lido! (Maior ou igual a 0)\n");
                validador++;
            }

        } while(validador > 0);


        // QUANTIDADE DO ITEM
        do {
            printf("\n\t\t\t\tDigite a quantidade do produto: ");
            scanf("%d", &quant);
            getchar();
            validador = 0;

            if(quant < 0) { // condi��o de pre�o ser miaor ou igual a zero
                printf("\n\t\t\t\tDigite uma quantidade v�lida! (Maior ou igual a 0)\n");
                validador++;
            }

        } while(validador > 0);


        produto->codigoItem = codigo;
        strcpy(produto->nomeItem, nome);
        produto->precoItem = preco;
        produto->qtdeEstoque = quant;
        produto->venda[0] = 0.00; //qtdeVendida
        produto->venda[1] = 0.00; //subTotal

        Adicionar(lista, produto);

        printf("\n\t\t\t\tProduto cadastrado com sucesso!\n");
        system("pause");
    }
    system("cls");

}

void exibirCadastrados(Lista* lista){

    if(lista == NULL){
        system("cls");
        printf("\t\t\t------------------------ N�o h� produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a op��o Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a op��o Cadastrar (Para cadastrar novos produtos, caso n�o existam)\n");
        return;
    }

    printf("\t\t\t----------------------------- Produtos Atualizados (%d) ---------------------------\n\n",
           ContadorItens(lista));

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        printf("\t\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
                   itemLista->produto.codigoItem, itemLista->produto.nomeItem,
                   itemLista->produto.precoItem, itemLista->produto.qtdeEstoque);

        itemLista = itemLista->prox;
    }

}

void salvarCadastrados(Lista* lista){

    FILE *arquivo = NULL;
    arquivo = fopen("produtos.txt", "w");

    if(lista == NULL || arquivo == NULL){
        system("cls");
        printf("\t\t\t------------------------ N�o h� produtos cadastrados! ----------------------\n\n"
               "\t\t\t------------------------------------ ou ------------------------------------\n\n"
               "\t\t\t------------------------ Erro na abertura do arquivo! ----------------------\n\n");
        return;
    }

    Produto* produto = (Produto*) malloc(sizeof(Produto));

    if(produto == NULL){
        printf("Erro na aloca��o de mem�ria!");
        return;
    }

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        fprintf(arquivo, ( itemLista->prox == NULL ? "%d\n%s\n%.2f\n%d\n%.f" : "%d\n%s\n%.2f\n%d\n%.f\n"),
                itemLista->produto.codigoItem,
                itemLista->produto.nomeItem,
                itemLista->produto.precoItem,
                itemLista->produto.qtdeEstoque,
                itemLista->produto.venda[0]);

        itemLista = itemLista->prox;
    }

    printf("\t\t\t---------------------- Produtos Salvos Com Sucesso! ----------------------\n\n");
    fclose(arquivo);

    system("pause");

}

Lista* lerSalvos(){

    FILE *arq = NULL; //abre arquivo e faz leitura armazenando no ponteiro de retorno

    arq = fopen("produtos.txt", "r");

    if(arq == NULL){
        printf("\t\t\t------------------------ Erro na abertura do arquivo! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a op��o Cadastrar (Para registrar novos produtos)\n");
        printf("\t\t\t 2. Utilize a op��o Salvar (Para arquivar os novos produtos)\n");
        return NULL;
    }


    Lista* lista = (Lista*) malloc(sizeof(Lista));
    inicializar(lista);

    if(lista == NULL){
        printf("Erro na aloca��o de mem�ria!");
        return lista;
    }

    while (!feof(arq)){

        Produto* produto = (Produto*) malloc(sizeof(Produto));
        if(produto == NULL){
            printf("Erro na aloca��o de mem�ria!");
            return lista;
        }

        fscanf(arq, "%d", &produto->codigoItem);
        fgetc(arq);
        fgets(produto->nomeItem, MAX_CHAR, arq);
        strtok(produto->nomeItem, "\n");
        fscanf(arq, "%f", &produto->precoItem);
        fgetc(arq);
        fscanf(arq, "%d", &produto->qtdeEstoque);
        fgetc(arq);
        fscanf(arq, "%d", &produto->venda[0]);
        fgetc(arq);

        Adicionar (lista, produto);
    }

    printf("\t\t\t---------------------- Produtos Lidos Com Sucesso! ----------------------\n\n");
    fclose(arq);

    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    getchar();
    system("cls");

    return lista;

}

void atualizarProdutos(Lista* lista){

    int validador = 0;
    int codigo = 0;
    int itemEncontrado = -1;
    float preco = 0;
    int quant = 0;

    if(lista == NULL){
        printf("\t\t\t------------------------ N�o h� produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a op��o Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a op��o Cadastrar (Para cadastrar novos produtos, caso n�o existam)\n");
        return;
    }

    No* itemLista = lista->inicio;

     while (itemLista != NULL){
        printf("\t\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               itemLista->produto.codigoItem, itemLista->produto.nomeItem,
               itemLista->produto.precoItem, itemLista->produto.qtdeEstoque);

        itemLista = itemLista->prox;
    }

    printf("\n\t\t\tInforme o c�digo do produto que deseja atualizar: ");
    scanf("%d", &codigo);

    Produto* produto = Procurar(lista, codigo);

    if(produto == NULL){
        printf("Erro na aloca��o de mem�ria!");
        return;
    }

    if(produto == NULL){
        system("cls");
        printf("\t\t\t-------------------------- Produto N�o Existe! -------------------------\n\n");
        return;
    }

    do {
        printf("\n\t\t\t\tDigite o pre�o do produto: ");
        scanf("%f", &preco);
        getchar();
        validador = 0;

        if(preco < 0) {  // condi��o de pre�o ser miaor ou igual a zero
            system("cls");
            printf("\n\t\t\t\tDigite um pre�o v�lido! (Maior ou igual a 0)\n");
            validador++;
        }

    } while(validador > 0);

    do {
        printf("\n\t\t\t\tDigite a quantidade do produto: ");
        scanf("%d", &quant);
        getchar();
        validador = 0;

        if(quant < 0) { // condi��o de pre�o ser miaor ou igual a zero
            system("cls");
            printf("\n\t\t\t\tDigite uma quantidade v�lida! (Maior ou igual a 0)\n");
            validador++;
        }

    } while(validador > 0);

    produto->precoItem = preco;
    produto->qtdeEstoque = quant;

    system("cls");
    printf("\t\t\t---------------------- Produtos Atualizados Com Sucesso! ----------------------\n");
    printf("\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
            produto->codigoItem, produto->nomeItem, produto->precoItem, produto->qtdeEstoque);


    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    getchar();
    system("cls");
}

void excluirProdutos(Lista* lista){

    int itemParaExcluir = 0;
    int confirmacao  = 0;
    int itemEncontrado = -1;

    if(lista == NULL){
        printf("\t\t\t------------------------ N�o h� produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a op��o Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a op��o Cadastrar (Para cadastrar novos produtos, caso n�o existam)\n");
        return;
    }

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        printf("\t\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               itemLista->produto.codigoItem, itemLista->produto.nomeItem,
               itemLista->produto.precoItem, itemLista->produto.qtdeEstoque);

        itemLista = itemLista->prox;
    }

    printf("\n\t\t\tInforme o c�digo do produto que deseja excluir: ");
    scanf("%d", &itemParaExcluir);

    Produto* produto = Procurar(lista, itemParaExcluir);

    if (produto == NULL){
        printf("\t\t\t   -------------------------- Produto N�o Existe! -------------------------   \n\n");
        return;
    }

    do{
        printf("\n\t\t\tDeseja realmente excluir o produto?"
               "\n\n\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               produto->codigoItem, produto->nomeItem, produto->precoItem, produto->qtdeEstoque);

        printf("\n\t\t\t1.Sim"
               "\n\t\t\t2.N�o"
               "\n\t\t\tOp��o: ");
        scanf("%d", &confirmacao);
        getchar();

        switch (confirmacao){

        case 1:
            Remover(lista, itemParaExcluir);

            system("cls");
            printf("\t\t\t\t------------------ Produto Exclu�do Com Sucesso! ------------------   \n\n");
            break;

        case 2:
            system("cls");
            printf("\t\t\t\t-------------------------- Produto Mantido! -------------------------   \n\n");
            break;

        default:
            system("cls");
            printf("\n\t\t\t\tDigite uma op��o v�lida! \n");
        }

    } while(confirmacao != 1 && confirmacao != 2);


    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    system("cls");

}
