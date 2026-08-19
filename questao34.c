#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STOP 0
#define DIM 51
 enum TipoProduto { ALIMENTO = 1, BEBIDA, LIMPEZA };

typedef struct {
    int codigo;
    float valor;
    int quantidade;
    enum TipoProduto tipo;
} Produtos;

char* tipo_produto(enum TipoProduto tipo) {
    switch (tipo) {
        case BEBIDA:   return "Bebida";
        case ALIMENTO: return "Alimento";
        case LIMPEZA:  return "Limpeza";
        default:       return "Nao cadastrado";
    }
}
int buscar_produto(Produtos *produtos, int cont, int temp1){
	int i;
	if(produtos==NULL || cont ==0){
		return 0;
	}
	for(i=0;i<cont;i++){
		if((produtos+i)->codigo==temp1){
			return 1;
		}
	}
	return 0;
}

float calcula_preco(Produtos *p) { 
    float valor_final = 0.00;
    valor_final = (p->quantidade) * (p->valor);
    if (p->quantidade >= 1000) {
        valor_final = 0.80 * valor_final;
    }
    else if (p->quantidade >= 10) { 
        if (p->quantidade >= 100) {
            valor_final = 0.90 * valor_final;
        } else {
            valor_final = 0.95 * valor_final;
        }
    }
    
    if (p->quantidade >= 1000) {
        valor_final = 0.80 * (p->quantidade * p->valor);
    } else if (p->quantidade >= 100) {
        valor_final = 0.90 * (p->quantidade * p->valor);
    } else if (p->quantidade >= 10) {
        valor_final = 0.95 * (p->quantidade * p->valor);
    }
    return valor_final;
}

int main() {
    Produtos *produtos = NULL;
    char nome[DIM];
    int cont = 0;
    int codigo_cliente;
    int i;
    int temp1;
    float temp2;
    int temp3;
    float soma = 0.0;
    int temp_tipo;
    enum TipoProduto tipo;
    float total_item;
    
    printf("******************************************************\n");
    printf("MERCADO PAO DE ACUCAR DA PRAIA VERMELHA\n");
    printf("******************************************************\n");
    printf("\n");
    printf("****************************************\n");
    printf("CAIXA 15 VOLUMES\n");
    printf("****************************************\n");
    printf("Entre com o codigo de 4 digitos do cliente: ");
    scanf("%d", &codigo_cliente);
    while(codigo_cliente<1000 || codigo_cliente>9999){
    	printf("CODIGO INVALIDO!\n");
    	printf("Entre com o codigo de 4 digitos do cliente: ");
    	scanf("%d", &codigo_cliente);
    	}
    printf("Digite o nome do cliente: ");
    scanf(" %50[^\n]", nome); 

    while (cont < 15) {
        printf("Codigo do produto: ");
        scanf("%d", &temp1);
        if (temp1 == 0) {
            break;
        }
        if(buscar_produto(produtos, cont, temp1)==1){
        	printf("Codigo ja cadastrado anteriormente\n");
        	continue;
		}
        printf("Tipo do produto:\n");
        printf("1-Alimento\n");
        printf("2-Bebida\n");
        printf("3-Limpeza\n");
        scanf("%d", &temp_tipo);
        while(temp_tipo<1 || temp_tipo>3){
        	printf("Produto nao cadastrado!\n");
        	printf("Escolha uma opcao valida\n");
        	 printf("Tipo do produto:\n");
        printf("1-Alimento\n");
        printf("2-Bebida\n");
        printf("3-Limpeza\n");
        scanf("%d", &temp_tipo);
    }
        
		
        tipo = (enum TipoProduto)temp_tipo;
        
        printf("Valor unitario: ");
        scanf("%f", &temp2);
        printf("Quantidade: ");
        scanf("%d", &temp3);
        
        cont++;
        produtos = (Produtos*)realloc(produtos, cont * sizeof(Produtos));
        if (produtos == NULL) {
            printf("Erro de alocacao de memoria\n");
            return 1;    
        }
        
        produtos[cont-1].codigo = temp1;
        produtos[cont-1].quantidade = temp3;
        produtos[cont-1].valor = temp2;
        produtos[cont-1].tipo = tipo; // CORRIGIDO: Atribuindo a variavel do tipo enum correta
        
        printf("\n");
    }
    
    FILE*arq=fopen("cupom.txt", "w");
    if(arq!=NULL){
	
    	fprintf(arq, "=====NOTA FISCAl=====\n");
    	

    fprintf(arq,"\n============================================================\n");
    fprintf(arq,"Codigo do cliente: %d\n", codigo_cliente);
    fprintf(arq,"Nome do Cliente: %s\n", nome);
    fprintf(arq,"============================================================\n");
    
    fprintf(arq,"%-8s %-16s %-12s %-15s %s\n", "Codigo", "Tipo do Produto", "Quantidade", "Val. Unitario", "Valor Total");
    fprintf(arq,"------------------------------------------------------------\n");
    
    for (i = 0; i < cont; i++) {
    	 total_item = calcula_preco(&produtos[i]);
        soma += total_item;
    
        fprintf(arq,"%04d   %-16s %-12d R$ %-12.2f R$ %.2f\n", produtos[i].codigo, tipo_produto(produtos[i].tipo), produtos[i].quantidade, produtos[i].valor, total_item);
    }  
     fprintf(arq,"------------------------------------------------------------\n");
    fprintf(arq,"Valor final: R$ %.2f\n", soma);
    fprintf(arq,"------------------------------------------------------------\n");
fclose(arq);
printf("Nota fiscal gerada com sucesso!\n");
}
    free(produtos);
    produtos = NULL;
    return 0;
}
