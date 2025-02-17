#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"

void inicializar(Lista* lista){
    lista->inicio = NULL;
}

void InserirInicio(Lista* lista, Produto* produto){

    No* novo = (No*) malloc(sizeof(No));

    novo->prox = lista->inicio;
    novo->produto = *produto;
    lista->inicio = novo;
}

void Adicionar(Lista* lista, Produto* produto){

     if(lista->inicio == NULL || produto->codigoItem < lista->inicio->produto.codigoItem){
        InserirInicio(lista, produto);
    }else{
        No* ponteiro = lista->inicio;
        No* novo = (No*) malloc(sizeof(No));
        novo->produto = *produto;

        while(ponteiro->prox != NULL && produto->codigoItem > ponteiro->prox->produto.codigoItem){
            ponteiro = ponteiro->prox;
        }

        novo->prox = ponteiro->prox;
        ponteiro->prox = novo;
    }
}

Produto* Procurar(Lista* lista, int codigoProduto){

    No* itemLista = lista->inicio;

    while (itemLista != NULL){
        if (itemLista->produto.codigoItem == codigoProduto){
            Produto* produto = (Produto*) malloc(sizeof(Produto));
            produto = &itemLista->produto;
            return produto;
        }

        itemLista = itemLista->prox;
    }

    return NULL;
}

void Remover(Lista* lista, int codigoProduto){

    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL){

        if (atual->produto.codigoItem == codigoProduto){

            if(anterior == NULL){
                lista->inicio = atual->prox;
            }else{
                anterior->prox = atual->prox;
            }
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

int ContadorItens (Lista* lista){

    No* itemLista = lista->inicio;
    int contador = 0;

    while (itemLista != NULL){
        contador = contador + 1;
        itemLista = itemLista->prox;
    }

    return contador;

}
