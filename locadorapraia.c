#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum TipoVeiculo{SEDAN=1, HATCH, SUV, PICKUP};
typedef struct{
	int id;
	enum TipoVeiculo categoria;
	int valor;
	int estoque;
}Veiculo;
char *categoria_para_string(enum TipoVeiculo categoria);
	int buscar_veiculo(Veiculo *frota, int total, int id_busca);
int main(){
	Veiculo *frota=NULL;
	enum TipoVeiculo categoria;
	int id_busca;
	int total=0;
	char opcao;
	int indice;
	int tipo;
	int valor;
	int soma=0;
	int i;
	printf("====LOCADORA DE CARROS PRAIA VERMELHA===\n");
	while(1){
		printf("[R]-Registrar veiculo\n[D]-Remover Veiculo\n[F]-Finalizar e Salvar Relatorio\n");
		printf("Selecione uma opcao no terminal:\n");
		scanf(" %c", &opcao);
		
		if(opcao=='F' || opcao=='f'){
			printf("Encerrando expediente\n");
			break;
			}
			if (opcao=='R'|| opcao=='r'){
				printf("Digite o codigo de quatro digitos do veiculo\n");
				scanf("%d", &id_busca);
				while(id_busca<1000 || id_busca>9999){
					printf("CODIGO INVALIDO!\n");
					printf("Digite o codigo de quatro digitos do veiculo\n");
					scanf("%d", &id_busca);
				}
				
				indice=buscar_veiculo(frota, total, id_busca);
				if(indice==-1){
					printf("Selecione o tipo do veiculo a ser cadastrado\n");
					printf("1-SEDAN\n2-HATCH\n3-SUV\n4-PICKUP\n");
					scanf("%d", &tipo);
					while(tipo<1 || tipo>4){
						printf("CATEGORIA INVALIDA\n");
						printf("Selecione o tipo de veiculo a ser cadastrado:\n");
						scanf("%d", &tipo);
					}
					printf("Digite o valor do carro: ");
					scanf("%f", &valor);
					if(valor>100000 || valor<10000){
						printf("Valores invalidos!\n");
						continue;
					}
					total++;
						frota=(Veiculo*)realloc(frota,total*sizeof(Veiculo));
						if(frota==NULL){
							printf("[ERRO]: Alocacao de memoria incorreta!\n");
							return 1;
						}
						frota[total-1].id=id_busca;
						frota[total-1].categoria=(enum TipoVeiculo)tipo;
						frota[total-1].valor=valor;
						frota[total-1].estoque=0;
						frota[total-1].estoque++;
				}
					else{
						printf("Veiculo jah cadastrado!\n");
						continue;
						}
					}
					if(opcao=='D'|| opcao=='d'){
						printf("Digite o codigo do veiculo a ser despachado\n");
						scanf("%d", &id_busca);
						indice=buscar_veiculo(frota, total, id_busca);
						if(indice==-1){
							printf("Codigo nao encontrado!\n");
							}
							else{
							if(frota[indice].estoque==0){
											printf("Estoque insuficiente!\n");
										}
										else{
										frota[indice].estoque--;
										printf("Estoque atualizado com sucesso!\n");
									}
									
									}
							}
					}
					if(total==0){
						printf("EXPEDIENTE ADMNISTRATIVO: SEM ALTERACOES\n");
						return 0;
					}
					FILE *arq = fopen("locadora_inventario.txt", "w");
					if(arq==NULL){
						printf("Falha ao criar o arquivo\n");
						if(frota!=NULL)free(frota);
						return 1;
					}
					fprintf(arq, "================\n");
					fprintf(arq,"RELATORIO DIARIO\n");
					fprintf(arq, "================\n");
					fprintf(arq, "%-15s | %-12s | %-4s\n","CATEGORIA", "VALOR", "ESTOQUE");
					fprintf(arq,"-------------------------------------------\n");
					for(i=0;i<total;i++){
						fprintf(arq, "%-15s | %-12d | %-4d\n",categoria_para_string(frota[i].categoria), frota[i].valor, frota[i].estoque);
						soma+=(frota[i].valor*frota[i].estoque);
					}
					printf("\n");
					fprintf(arq,"Valor total do estoque: R$ %d\n", soma);
					fprintf(arq, "-------------------------------------------\n");
					fclose(arq);
					if(frota!=NULL){
					free(frota);
				}
				printf("Relatorio em texto gerado com sucesso!\n");
				return 0;
			}
char *categoria_para_string(enum TipoVeiculo categoria){
	switch(categoria){
		case SEDAN: return "Sedan";
		case HATCH: return "Hatch";
		case SUV: return "Suv";
		case PICKUP: return "Pickup";
		default: return "Tipo nao encontrado";
		
	}
}

	int buscar_veiculo(Veiculo *frota, int total, int id_busca){
		int i;
		if(frota==NULL || total==0){
		return -1;
	}
		for(i=0;i<total;i++){
			if(frota[i].id==id_busca){
				return i;
			}
			}
		return -1;
			}
		
