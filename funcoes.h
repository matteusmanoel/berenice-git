#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#define MAX_CHAR 25

typedef struct{
    int codigoItem;
    char nomeItem[MAX_CHAR];
    float precoItem;
    int qtdeEstoque;
    float venda[2]; // [0] qtdeVendida, [1] subTotal
}Produto;

typedef struct No{
    Produto produto;
    struct No* prox;
} No;

typedef struct Lista{
    No* inicio;
} Lista;

void mainMenu();

Lista* menuProdutos(Lista* lista);
void Vendas(Lista* lista);
void cadastroProdutos(Lista* lista);
void exibirCadastrados(Lista* lista);
void salvarCadastrados(Lista* lista);
Lista* lerSalvos();
void atualizarProdutos(Lista* lista);
void excluirProdutos(Lista* lista);
void realizaVendas(Lista* lista);
void realizaPagamento(float totalCompra, Lista* lista);
Produto* CarrinhoCompras(Lista* lista);
void VisualizarCarrinho(float, Lista* lista);
void VisualizarNotaFiscal(float, Lista* lista);
void relatorioVendas(Lista* lista);

void inicializar(Lista* lista);
void InserirInicio(Lista* lista, Produto* produto);
void Adicionar(Lista* lista, Produto* produto);
Produto* Procurar(Lista* lista, int codigoProduto);
void Remover(Lista* lista, int codigoProduto);
int ContadorItens (Lista* lista);


#endif
