#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

Produto* CarrinhoCompras(Lista* lista){

    Produto* produto;
    int itemEncontrado = 0;
    int codigo = 0;

    do{
        exibirCadastrados(lista);
        printf("\n\t\t\tInforme o código do produto que deseja comprar: ");
        scanf("%d", &codigo);

        produto = Procurar(lista, codigo);

        if(produto == NULL){
            system("cls");
            printf("\t\t\t   -------------------------- Produto Não Existe! -------------------------   \n\n");
            system("pause");
        }

    }while(produto == NULL);

    return produto;
}

void realizaVendas(Lista* lista){

    No* itemLista;
    Produto* itemEscolhido = NULL; //produto escolhido
    int qtdEscolhida = 0; //quantidade vendida
    int novaCompra = 2;
    float totalCompra = 0.00;

    if(lista == NULL){
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a opção Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a opção Cadastrar (Para cadastrar novos produtos, caso não existam)\n");
        return lista;
    }

    do {

        do {

            itemEscolhido = CarrinhoCompras(lista);

            printf("\n\t\t\tItem selecionado:\n"
                   "\n\t\t----------------------------------------------------------------------------------------------\n"
                   "\n\t\t %d -> %s|| Preço[R$%.2f]  ||  Estoque: %d  ||  Quantidade: %.2f  ||  Subtotal: R$%.2f\n",
               itemEscolhido->codigoItem,
               itemEscolhido->nomeItem,
               itemEscolhido->precoItem,
               itemEscolhido->qtdeEstoque,
               itemEscolhido->venda[0],
               itemEscolhido->venda[1]);

            printf("\n\t\t----------------------------------------------------------------------------------------------\n\n");

            printf("\n\t\t\tInforme a quantidade que deseja comprar: ");
            scanf("%d", &qtdEscolhida);

            if(qtdEscolhida <= 0 || qtdEscolhida > itemEscolhido->qtdeEstoque){
                system("cls");
                printf("\n\t\t\tDigite uma quantidade válida e compativel com o estoque...");
            }

        } while (qtdEscolhida <= 0 || qtdEscolhida > itemEscolhido->qtdeEstoque);

        system("cls");

        itemEscolhido->venda[0] += qtdEscolhida; //qtdeVendida
        itemEscolhido->venda[1] += (itemEscolhido->precoItem * qtdEscolhida); //subTotal
        itemEscolhido->qtdeEstoque -= qtdEscolhida;

        itemLista = lista->inicio;
        while (itemLista != NULL){
            totalCompra += itemLista->produto.venda[1];
            itemLista = itemLista->prox;
        }

        printf("\n\t\t   ----------------------- Item adicionado ao carrinho com sucesso! -----------------------\n\n ");

        VisualizarCarrinho(totalCompra, lista);

        printf("\n\t\tDeseja adicionar um novo produto?"
               "\n\t\t1 -> Sim"
               "\n\t\t2 -> Não"
               "\n\t\tOpção: ");
        scanf("%d", &novaCompra);

    } while(novaCompra != 2);

    realizaPagamento(totalCompra, lista);


    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    getchar();
    system("cls");
}

void realizaPagamento(float totalCompra, Lista* lista){

    int opcPagamento = -1;
    int parcelas = -1;
    int pagarParcela = -1;
    int porcentDesc = -1;

    float desconto = -1;
    float acrescimo = -1;
    float totalVista = -1;
    float totalPrazo = -1;
    float valorRecebido = -1;
    float valorParcela = -1;

    system("cls");

    do {
        VisualizarCarrinho(totalCompra, lista);
        printf("\n\t\t\tDigite a opção de pagamento...\n"
               "\t\t\t1 - A vista\n"
               "\t\t\t2 - A prazo\n"
               "\t\t\tOpção: ");
        scanf("%d", &opcPagamento);

        if (opcPagamento < 1 || opcPagamento > 2) {
            system("cls");
            printf("\n\t\t\tDigite uma opção de pagamento válida! 1 ou 2 apenas...\n");
        }

    } while(opcPagamento < 1 || opcPagamento > 2);

    if(opcPagamento == 1) {   // A vista.
        system("cls");
        printf("\n\t\t\t-------------------------------- Você selecionou ----------------------------------------\n\n"
               "\n\t\t\t 2. Pagamento à vista.\n\n");

        if(totalCompra <= 50.99) {
            desconto = totalCompra * 0.05;
            porcentDesc = 5;
        } else if(totalCompra >= 51.00 && totalCompra <= 99.00) {
            desconto = totalCompra * 0.10;
            porcentDesc = 10;
        } else {
            desconto = totalCompra * 0.18;
            porcentDesc = 18;
        }

        totalVista = totalCompra - desconto;

        printf("\n\t\t\tTotal da compra: R$%.2f"
               "\n\t\t\tDesconto de %d%%: R$%.2f"
               "\n\t\t\tTotal com desconto: R$%.2f", totalCompra, porcentDesc, desconto, totalVista);

        do {

            printf("\n\t\t\tValor recebido: R$ ");
            scanf("%f", &valorRecebido);

            if(valorRecebido <= 0 || valorRecebido < totalVista) {
                printf("\n\t\t\tValor R$%.2f inválido! Informe um valor maior ou igual a R$%.2f\n", valorRecebido, totalVista);
            }

        } while(valorRecebido <= 0 || valorRecebido < totalVista); // Fim A vista

        system("cls");
        printf("\n\t\t\tValor Recebido: R$%.2f"
               "\n\t\t\tTroco: R$%.2f\n"
               "\n\t\t\t\t----------------------- Venda concluída! -----------------------\n\n", valorRecebido, valorRecebido-totalVista);
    }

    if(opcPagamento == 2) { //pagamento a prazo
        system("cls");
        printf("\n\t\t\t-------------------------------- Você selecionou ----------------------------------------\n\n"
               "\n\t\t\t1. Pagamento à prazo.\n");

        do {
            printf("\n\t\t\tDigite em quantas vezes deseja parcelar R$ %.2f: ", totalCompra);
            scanf("%d", &parcelas);

            if (parcelas <=0 && parcelas > 10) {
                printf("\n\t\t\tOpção %d Inválida! Informe uma quantidade de parcelas de 1 a 10!\n\n", parcelas);
            }

        } while(parcelas <= 0 || parcelas > 10);

        if(parcelas >=1 && parcelas <=3){    //parcela entre 1 e 3 tem 5% de juros
            acrescimo = 1.05;
            totalPrazo = totalCompra*acrescimo;
        }else if(parcelas >=4 && parcelas <=10){     //parcela entre 4 e 10 tem 8% de juros
            acrescimo = 1.08;
            totalPrazo = totalCompra*acrescimo;
        }

        valorParcela = totalPrazo/parcelas;

        printf("\n\t\t\tTotal a prazo em %.dx com %.2f%% de acrescimo: R$ %.2f", parcelas, acrescimo, totalPrazo);
        printf("\n\t\t\tParcelas(%d) de: R$ %.2f\n\n",parcelas, totalPrazo/parcelas);

        do {
            printf("\n\t\t\tDeseja pagar a primeira parcela?"
                   "\n\t\t\t1. Sim"
                   "\n\t\t\t2. Não"
                   "\n\t\t\tOpção: ");
            scanf("%d", &pagarParcela);

            if(pagarParcela <= 0 || pagarParcela > 2){
                system("cls");
                printf("\n\t\t\tOpção %d Inválida! Informe se"
                       "deseja ou não pagar a primeira parcela agora.\n", pagarParcela);
            }

        } while(pagarParcela <= 0 || pagarParcela > 2);

        if (pagarParcela == 1){

            do{
                printf("\n\t\t\tValor recebido para a primeira parcela: R$ ");
                scanf("%f", &valorRecebido);    //dinheiro entregue pelo cliente

                if(valorRecebido <= 0){   //caso seja um valor negativo ou 0
                    system("cls");
                    printf("\n\t\t\tValor R$%.2f Inválido! Digite um valor maior ou igual a R$%.2f.", valorRecebido, valorParcela);
                    printf("\n\t\t\tTotal a Prazo em %.dx (%.2f de acrescimo): R$ %.2f", parcelas, acrescimo, totalPrazo);
                    printf("\n\t\t\t%d parcelas de: R$ %.2f\n\n",parcelas, totalPrazo/parcelas);
                }else if(valorRecebido < valorParcela){
                    system("cls");
                    printf("\n\t\t\tValor R$%.2f inferior ao valor da parcela! Informe um valor maior ou igual a R$%.2f", valorRecebido, valorParcela);
                    printf("\n\t\t\tTotal a Prazo em %.dx (%.2f de acrescimo): R$ %.2f", parcelas, acrescimo, totalPrazo);
                    printf("\n\t\t\t%d parcelas de: R$ %.2f\n\n",parcelas, totalPrazo/parcelas);
                }else if (valorRecebido > totalPrazo){
                    printf("\n\t\t\tValor R$%.2f superior ao total da compra! (R$%.2f)"
                           "\n\t\t\tVenda concluída!"), valorRecebido, totalPrazo;
                    printf("\n\t\t\tTroco: R$%.2f\n", valorRecebido-totalPrazo);
                }else{
                    system("cls");
                    printf("\n\t\t\tTroco: R$ %.2f"
                           "\n\t\t\tO valor restante será parcelado conforme selecionado.\n"
                           "\n\t\t\tVenda concluída!\n", valorRecebido-valorParcela);
                    break;
                }

            } while(valorRecebido <= 0 || valorRecebido < totalPrazo);

        }

        if(pagarParcela == 2){
            system("cls");
            printf("\n\t\t\t\t----------------------- Venda concluída! -----------------------\n\n");
            printf("\t\t\t\tParcelamento de R$%.2f em %dx confirmado. Aguarde o boleto.\n\n", totalPrazo, parcelas);
        }
    }

    VisualizarNotaFiscal((opcPagamento == 0 ? totalPrazo : totalVista), lista);
}

void VisualizarCarrinho(float totalCompra, Lista* lista){

    printf("\t\t---------------------------------- Carrinho de Compras [%d] ---------------------------------------\n\n",
           ContadorItens (lista));

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        printf("\t\t%d -> %s || Preço[R$%.2f]  ||  Estoque: %d  ||  Quantidade: %.2f  ||  Subtotal: R$%.2f\n\n",
                   itemLista->produto.codigoItem, itemLista->produto.nomeItem, itemLista->produto.precoItem,
                   itemLista->produto.qtdeEstoque, itemLista->produto.venda[0], itemLista->produto.venda[1]);

        itemLista = itemLista->prox;
    }

    if(totalCompra > 0){
        printf("\t\t------------------------------ Total de compra: R$ %.2f --------------------------------------\n\n", totalCompra);
    }else{
        printf("\t\t-----------------------------------------------------------------------------------------------------\n\n");
    }

}

void VisualizarNotaFiscal(float totalCompra, Lista* lista){

    No* itemLista = lista->inicio;

    printf("\t\t\t------------------------------ Nota Fiscal -------------------------------------\n\n");

    while (itemLista != NULL){
        printf("\t\t%d -> %s || Preço[R$%.2f]  ||  Quantidade: %.2f  ||  Subtotal: R$%.2f\n\n",
                   itemLista->produto.codigoItem, itemLista->produto.nomeItem, itemLista->produto.precoItem,
                   itemLista->produto.venda[0], itemLista->produto.venda[1]);

        itemLista = itemLista->prox;
    }

    printf("\t\t\t--------------------------- Total de compra: R$ %.2f ---------------------------\n\n", totalCompra);
}

void relatorioVendas(Lista* lista){

     if(lista == NULL){
        printf("\t\t\t------------------------ Não há produtos cadastrados! ----------------------\n\n");
        printf("\t\t\t 1. Utilize a opção Ler (Para carregar os produtos cadastrados anteriormente)\n");
        printf("\t\t\t 2. Utilize a opção Cadastrar (Para cadastrar novos produtos, caso não existam)\n");
    }else{

        No* itemLista = lista->inicio;

        printf("\t\t------------------------------ Relatório de Vendas ------------------------------\n\n");

        while (itemLista != NULL){
            printf("\t\t%d -> %s || Preço[R$%.2f]  ||  Estoque: %d  ||  Quantidade: %.2f  ||  Subtotal: R$%.2f\n\n",
                       itemLista->produto.codigoItem, itemLista->produto.nomeItem, itemLista->produto.precoItem,
                       itemLista->produto.qtdeEstoque, itemLista->produto.venda[0], itemLista->produto.venda[1]);

            itemLista = itemLista->prox;
        }
        printf("\t\t----------------------------------------------------------------------------------\n\n");
    }

    printf("\n\t\t\tPressione qualquer tecla para voltar ao Menu Principal...");
    getchar();
    getchar();
    system("cls");
}
