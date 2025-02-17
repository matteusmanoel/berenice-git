#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

void cadastroProdutos(Lista* lista){

    int qtdParaCadastrar = 0;  //limite Loop para cadastro
    int codigo = 0;             //codigo do item
    char nome[MAX_CHAR];        //nome do item
    float preco = 0;            //preço do item
    int quant = 0;              //quantidade do item
    int validador = 0;

    printf("\n\t\t\t\t-------------------- Cadastro de Produtos --------------------\n\n");

    do {
        printf("\n\t\t\t\tDigite a quantidade de produtos que deseja cadastrar: ");
        scanf("%d", &qtdParaCadastrar);

        if(qtdParaCadastrar <= 0){
            system("cls");
            printf("\t\t\t\tQuantidade de produtos inválido! (Digite um numero maior que 0!)\n\n");
        }

    } while(qtdParaCadastrar <= 0);

    Produto* produto = (Produto*) malloc(sizeof(Produto));

    if(produto == NULL){
        printf("Erro na alocação de memória!");
        return;
    }

    for(int i = 0; i < qtdParaCadastrar; i++){

        // CODIGO DO ITEM
        do {
            system("cls");
            printf("\n\t\t\t\t-------------------- Cadastro de Produtos [%d] --------------------\n\n", qtdParaCadastrar - i);
            printf("\n\t\t\t\tDigite o código do %dº produto: ", i + 1);
            scanf("%d", &codigo);
            getchar();
            validador = 0;


            if(codigo <= 0){  // condição de id igual a zero
                system("cls");
                printf("\t\t\t\tCódigo de produto inválido! (Digite um numero maior que 0!)\n\n");
                validador++;
            }

            if(Procurar(lista, codigo) != NULL){ // condição de id existente
                system("cls");
                printf("\t\t\t\tCódigo de item inválido! (ID já existe!)\n\n");
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

            if(strcmp(nome, " ") == 0) { // condição de nome não ser só espaços
                printf("\n\t\t\t\tInformação 'nome' é obrigatória, digite um nome válido!\n");
                validador++;
            }

        } while(validador > 0);


        // PREÇO DO ITEM
        do {
            printf("\n\t\t\t\tDigite o preço do produto: ");
            scanf("%f", &preco);
            getchar();
            validador = 0;

            if(preco < 0) {  // condição de preço ser miaor ou igual a zero
                printf("\n\t\t\t\tDigite um preço válido! (Maior ou igual a 0)\n");
                validador++;
            }

        } while(validador > 0);


        // QUANTIDADE DO ITEM
        do {
            printf("\n\t\t\t\tDigite a quantidade do produto: ");
            scanf("%d", &quant);
            getchar();
            validador = 0;

            if(quant < 0) { // condição de preço ser miaor ou igual a zero
                printf("\n\t\t\t\tDigite uma quantidade válida! (Maior ou igual a 0)\n");
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
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a opção Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a opção Cadastrar (Para cadastrar novos produtos, caso não existam)\n");
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
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n"
               "\t\t\t------------------------------------ ou ------------------------------------\n\n"
               "\t\t\t------------------------ Erro na abertura do arquivo! ----------------------\n\n");
        return;
    }

    Produto* produto = (Produto*) malloc(sizeof(Produto));

    if(produto == NULL){
        printf("Erro na alocação de memória!");
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
        printf("\t\t\t 1. Utilize a opção Cadastrar (Para registrar novos produtos)\n");
        printf("\t\t\t 2. Utilize a opção Salvar (Para arquivar os novos produtos)\n");
        return NULL;
    }


    Lista* lista = (Lista*) malloc(sizeof(Lista));
    inicializar(lista);

    if(lista == NULL){
        printf("Erro na alocação de memória!");
        return lista;
    }

    while (!feof(arq)){

        Produto* produto = (Produto*) malloc(sizeof(Produto));
        if(produto == NULL){
            printf("Erro na alocação de memória!");
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
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a opção Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a opção Cadastrar (Para cadastrar novos produtos, caso não existam)\n");
        return;
    }

    No* itemLista = lista->inicio;

     while (itemLista != NULL){
        printf("\t\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               itemLista->produto.codigoItem, itemLista->produto.nomeItem,
               itemLista->produto.precoItem, itemLista->produto.qtdeEstoque);

        itemLista = itemLista->prox;
    }

    printf("\n\t\t\tInforme o código do produto que deseja atualizar: ");
    scanf("%d", &codigo);

    Produto* produto = Procurar(lista, codigo);

    if(produto == NULL){
        printf("Erro na alocação de memória!");
        return;
    }

    if(produto == NULL){
        system("cls");
        printf("\t\t\t-------------------------- Produto Não Existe! -------------------------\n\n");
        return;
    }

    do {
        printf("\n\t\t\t\tDigite o preço do produto: ");
        scanf("%f", &preco);
        getchar();
        validador = 0;

        if(preco < 0) {  // condição de preço ser miaor ou igual a zero
            system("cls");
            printf("\n\t\t\t\tDigite um preço válido! (Maior ou igual a 0)\n");
            validador++;
        }

    } while(validador > 0);

    do {
        printf("\n\t\t\t\tDigite a quantidade do produto: ");
        scanf("%d", &quant);
        getchar();
        validador = 0;

        if(quant < 0) { // condição de preço ser miaor ou igual a zero
            system("cls");
            printf("\n\t\t\t\tDigite uma quantidade válida! (Maior ou igual a 0)\n");
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
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a opção Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a opção Cadastrar (Para cadastrar novos produtos, caso não existam)\n");
        return;
    }

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        printf("\t\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               itemLista->produto.codigoItem, itemLista->produto.nomeItem,
               itemLista->produto.precoItem, itemLista->produto.qtdeEstoque);

        itemLista = itemLista->prox;
    }

    printf("\n\t\t\tInforme o código do produto que deseja excluir: ");
    scanf("%d", &itemParaExcluir);

    Produto* produto = Procurar(lista, itemParaExcluir);

    if (produto == NULL){
        printf("\t\t\t   -------------------------- Produto Não Existe! -------------------------   \n\n");
        return;
    }

    do{
        printf("\n\t\t\tDeseja realmente excluir o produto?"
               "\n\n\t\t\t [%d] -> [%s] --------- [R$%.2f]  ---------- [%d]\n",
               produto->codigoItem, produto->nomeItem, produto->precoItem, produto->qtdeEstoque);

        printf("\n\t\t\t1.Sim"
               "\n\t\t\t2.Não"
               "\n\t\t\tOpção: ");
        scanf("%d", &confirmacao);
        getchar();

        switch (confirmacao){

        case 1:
            Remover(lista, itemParaExcluir);

            system("cls");
            printf("\t\t\t\t------------------ Produto Excluído Com Sucesso! ------------------   \n\n");
            break;

        case 2:
            system("cls");
            printf("\t\t\t\t-------------------------- Produto Mantido! -------------------------   \n\n");
            break;

        default:
            system("cls");
            printf("\n\t\t\t\tDigite uma opção válida! \n");
        }

    } while(confirmacao != 1 && confirmacao != 2);


    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    system("cls");

}
