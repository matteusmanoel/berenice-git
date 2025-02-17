#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

Lista* menuProdutos(Lista* lista){

    setlocale(LC_ALL, "Portuguese");

    int opcSelecionada;

    do{

        system ("cls");
        int opcSelecionada = 0;

        printf("\t\t\t\t\t========== Menu Produtos ===========\n"
               "\n\t\t\t\t\t1. Cadastrar"
               "\n\t\t\t\t\t2. Exibir"
               "\n\t\t\t\t\t3. Salvar"
               "\n\t\t\t\t\t4. Ler"
               "\n\t\t\t\t\t5. Atualizar"
               "\n\t\t\t\t\t6. Excluir"
               "\n\t\t\t\t\t7. Voltar\n\n"
               "\t\t\t\t\t=====================================\n"
               "\n\t\t\t\t\t---> ");
        scanf("%d",&opcSelecionada);
        system("cls");

        if(opcSelecionada == 1){
            cadastroProdutos(lista);
        }else if(opcSelecionada == 2){
            exibirCadastrados(lista);
            system("pause");
        }else if(opcSelecionada == 3){
            salvarCadastrados(lista);
        }else if(opcSelecionada == 4){
            lista = lerSalvos();
        }else if(opcSelecionada == 5){
            atualizarProdutos(lista);
        }else if(opcSelecionada == 6){
            excluirProdutos(lista);
        }else if(opcSelecionada == 7){
            break;
        }else{
            printf("\t\t\t\t------------------ Opção Inválida! ------------------\n\n");
        }

    } while(opcSelecionada != 7);

    return lista;
}

void Vendas(Lista* lista){

    setlocale(LC_ALL, "Portuguese");

    int opcSelecionada;

    do {

        int opcSelecionada = 0;

        printf("\t\t\t\t\t========== Menu Vendas ===========\n"
               "\n\t\t\t\t\t1. Realizar Venda"
               "\n\t\t\t\t\t2. Relatório de Vendas"
               "\n\t\t\t\t\t3. Voltar\n\n"
               "\t\t\t\t\t=====================================\n"
               "\n\t\t\t\t\t---> ");
        scanf("%d",&opcSelecionada);
        system("cls");

        if(opcSelecionada == 1){
            realizaVendas(lista);
        }else if(opcSelecionada == 2){
            relatorioVendas(lista);
        }else if(opcSelecionada < 1 || opcSelecionada > 3){
            printf("\t\t\t\t------------------ Opção Inválida! ------------------\n\n");
        }else if(opcSelecionada == 3){
            break;
        }

    } while(opcSelecionada != 3);

    return lista;
}

void mainMenu(){

    setlocale(LC_ALL, "Portuguese");

    int opcSelecionada;

    Lista* lista = (Lista*) malloc(sizeof(Lista));
    inicializar(lista);

    do{

        int opcSelecionada = 0;

        printf("\t\t\t\t\t========== Menu Principal ===========\n"
               "\n\t\t\t\t\t1. Produtos"
               "\n\t\t\t\t\t2. Vendas"
               "\n\t\t\t\t\t3. Sair\n\n"
               "\t\t\t\t\t=====================================\n"
               "\n\t\t\t\t\t---> ");
        scanf("%d",&opcSelecionada);
        system("cls");

        if(opcSelecionada == 1){
           lista = menuProdutos(lista);
        } else if(opcSelecionada == 2){
            Vendas(lista);
        }else if (opcSelecionada == 3){
            printf("O sistema será encerrado!\n"
                    "Informações não salvas são perdidas!\n\n");
            system("pause");
            break;
        }else{
            printf("\t\t\t\t------------------ Opção Inválida! ------------------\n\n");
        }

    }while(opcSelecionada != 3);
}

int main(){

    setlocale(LC_ALL, "Portuguese");

    mainMenu();
    return 0;
}
