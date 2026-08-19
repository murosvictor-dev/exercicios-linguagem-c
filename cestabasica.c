#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Enum para as categorias fixas
enum CategoriaItem { ARROZ, MACARRAO, HIGIENE, PROTEINA };

// 2. A Struct material/produto
typedef struct {
    int codigo;
    char descricao[30];
    enum CategoriaItem categoria;
    int estoque_atual;
} ProdutoCesta;

// Protótipos das funções (Exigência comum de prova)
char* obter_nome_categoria(enum CategoriaItem cat);
int buscar_item_estoque(ProdutoCesta *estoque, int tamanho, int codigo_busca);

int main() {
    // ALOCAÇÃO DINÂMICA: Começamos com o ponteiro nulo (Vazio) e tamanho 0
    ProdutoCesta *inventario = NULL; 
    int total_itens = 0;// Controla o tamanho atual do vetor dinâmico
    int i;

    char comando;
    int cod_digitado, qtd_digitada, operacao, categoria_digitada, indice;

    printf("=== CONTROLE DE ESTOQUE DINAMICO: CESTAS BASICAS ===\n");
    printf("Comandos: [I] Alterar Estoque | [R] Salvar Inventario e Sair\n");

    while (1) {
        printf("\nDigite o comando (I ou R): ");
        scanf(" %c", &comando);

        if (comando == 'R' || comando == 'r') {
            break; 
        }

        if (comando == 'I' || comando == 'i') {
            printf("Digite o codigo do produto: ");
            scanf("%d", &cod_digitado);

            // A função faz o trabalho de buscar no vetor dinâmico
            indice = buscar_item_estoque(inventario, total_itens, cod_digitado);

            printf("Escolha: (1 - Adicionar/Cadastrar | 2 - Remover): ");
            scanf("%d", &operacao);

            if (operacao != 1 && operacao != 2) {
                printf("[ERRO] Operacao invalida!\n");
                continue;
            }

            printf("Digite a quantidade: ");
            scanf("%d", &qtd_digitada);

            // ===============================================================
            // OPERAÇÃO 1: ADICIONAR / CADASTRAR NOVO CÓDIGO
            // ===============================================================
            if (operacao == 1) {
                // Caso A: O produto já existe, apenas atualiza a quantidade
                if (indice != -1) {
                    inventario[indice].estoque_atual += qtd_digitada;
                    printf("[OK] Estoque atualizado! Novo saldo: %d\n", inventario[indice].estoque_atual);
                } 
                // Caso B: CÓDIGO NOVO! Vamos alocar espaço dinamicamente
                else {
                    printf("Produto novo detectado! Digite a descricao (Sem espacos): ");
                    char desc_nova[30];
                    scanf("%s", desc_nova);

                    printf("Digite a categoria (0-Arroz, 1-Macarrao, 2-Higiene, 3-Proteina): ");
                    scanf("%d", &categoria_digitada);

                    if (categoria_digitada < 0 || categoria_digitada > 3) {
                        printf("[ERRO] Categoria invalida! Cadastro cancelado.\n");
                        continue;
                    }

                    // AQUI ACONTECE A ALOCAÇÃO DINÂMICA
                    total_itens++;
                    inventario = (ProdutoCesta*) realloc(inventario, total_itens * sizeof(ProdutoCesta));
                    if (inventario == NULL) {
                        printf("[ERRO] Falha critica de memoria.\n");
                        return 1;
                    }

                    // Grava os dados na última posição que acabou de ser criada pelo realloc
                    int nova_pos = total_itens - 1;
                    inventario[nova_pos].codigo = cod_digitado;
                    strcpy(inventario[nova_pos].descricao, desc_nova);
                    inventario[nova_pos].categoria = (enum CategoriaItem) categoria_digitada;
                    inventario[nova_pos].estoque_atual = qtd_digitada;

                    printf("[OK] Novo produto cadastrado e alocado com sucesso!\n");
                }
            } 
            // ===============================================================
            // OPERAÇÃO 2: REMOVER
            // ===============================================================
            else if (operacao == 2) {
                if (indice == -1) {
                    printf("[ERRO] Produto nao cadastrado no inventario!\n");
                } else {
                    if (qtd_digitada > inventario[indice].estoque_atual) {
                        printf("[ERRO] Nao e possivel remover mais do que o estoque atual!\n");
                    } else {
                        inventario[indice].estoque_atual -= qtd_digitada;
                        printf("[OK] Estoque atualizado! Novo saldo: %d\n", inventario[indice].estoque_atual);
                    }
                }
            }
        }
    }

    // ===================================================================
    // ESCRITA DO INVENTÁRIO NO ARQUIVO TEXTO
    // ===================================================================
    FILE *arq = fopen("inventario_cestas.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo.\n");
        if (inventario != NULL) free(inventario);
        return 1;
    }

    fprintf(arq, "=========================================================\n");
    fprintf(arq, "             SITUACAO ATUAL DO INVENTARIO                \n");
    fprintf(arq, "=========================================================\n\n");
    fprintf(arq, "%-6s %-22s %-12s %-10s\n", "Cod", "Descricao", "Categoria", "Qtd Saldo");
    fprintf(arq, "---------------------------------------------------------\n");

    for ( i = 0; i < total_itens; i++) {
        fprintf(arq, "%03d    %-22s %-12s %-10d\n", 
                inventario[i].codigo, 
                inventario[i].descricao, 
                obter_nome_categoria(inventario[i].categoria), 
                inventario[i].estoque_atual);
    }

    fprintf(arq, "---------------------------------------------------------\n");
    fclose(arq);

    // LIBERAÇÃO OBRIGATÓRIA DA MEMÓRIA DINÂMICA
    if (inventario != NULL) {
        free(inventario);
    }

    printf("\n[FIM] Arquivo 'inventario_cestas.txt' gerado!\n");
    return 0;
}

// Implementação das funções auxiliares
char* obter_nome_categoria(enum CategoriaItem cat) {
    switch(cat) {
        case ARROZ:    return "Arroz";
        case MACARRAO: return "Macarrao";
        case HIGIENE:  return "Higiene";
        case PROTEINA: return "Proteina";
        default:       return "Outros";
    }
}

int buscar_item_estoque(ProdutoCesta *estoque, int tamanho, int codigo_busca) {
	int i;
    for ( i = 0; i < tamanho; i++) {
        if (estoque[i].codigo == codigo_busca) {
            return i; 
        }
    }
    return -1; 
}
