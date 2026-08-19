#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CONST 4
#define MAX 10
#define STOP 0
#define DIM 50
enum TipoAeronave{PASSAGEIRO=1, CARGUEIRO, EXECUTIVO};
char* nome_tipo(enum TipoAeronave tipo){
	switch(tipo){
	case PASSAGEIRO: return "Passageiro";
		case CARGUEIRO: return "Cargueiro";
		case EXECUTIVO: return "Executivo";
		default: return "Tipo nao enquadrado\n";
	}
	}
typedef struct{
	int codigo_voo;
	enum TipoAeronave tipo;
	int passageiros_a_bordo;
	float altitude;
}Voo;
	int localiza_voo(Voo *voo, int cont, int temp2){
	int i;
	if(voo==NULL || cont ==0){
		return 0;
	}
	for(i=0;i<cont;i++){
		if((voo+i)->codigo_voo==temp2){
			return 1;
		}
	}
	return 0;
}
int main(){
	enum TipoAeronave tipo;
	Voo *voo=NULL;
	int qtd_pass=0;
	int qtd_carg=0;
	int qtd_exec=0;
	int soma_altitude;
	int temp1;
	int temp2;
	int temp3;
	int code;
	int num;
	int tipo1=0;
	int tipo2=0;
	int tipo3=0;
	int cont=0;
	char nome[50];
	int temp4;
	int soma=0;
	float media;
	int i;
printf("==================================================\n");
	printf("CONTROLE DE TRAFEGO AEREO AEROPORTO SANTOS DUMONT\n");
	printf("==================================================\n");
	printf("Entre com o codigo do controlador de voo: ");
	scanf("%d", &code);
	while(code<1000 || code >9999){
		printf("CODIGO INVALIDO!\n");
		printf("Reinsira o codigo do operador\n");
		scanf("%d", &code);
	}
	printf("Insira o numero de aeronaves em contanto com a torre: ");
		scanf("%d", &num);
		while(num>10){
			printf("Numero nao suportado!\n");
			printf("Insira o numero de aeronaves em contato com a torre: ");
			scanf("%d", &num);
		}
	printf("Cadastre o nome do operador: ");
	scanf(" %50[^\n]", nome);
	while(cont<num){
		printf("1- PASSAGEIROS\n");
		printf("2- CARGUEIRO\n");
		printf("3- EXECUTIVO\n");
		printf("Escolha o tipo da aeronave: ");
		scanf("%d", &temp1);
		while(temp1<1 || temp1>3){
			printf("Tipo nao enquadrado\n");
				printf("1- PASSAGEIROS\n");
		printf("2- CARGUEIRO\n");
		printf("3- EXECUTIVO\n");
			printf("Escolha o tipo da aeronave\n");
			scanf("%d", &temp1);
		}
		tipo = (enum TipoAeronave )temp1;
		printf("Entre com o numero de matricula da aeronave: ");
		scanf("%d", &temp2);
		
		if(temp2==STOP){
			printf("CONTROLE ENCERRADO\n");
			break;
		}
		if (localiza_voo(voo, cont, temp2)==1){
			printf("Voo cadastrado anteriormente\n");
			continue;
		}
		printf("Entre com a altitude de operacao: ");
		scanf("%d", &temp3);
		while(temp3<30000 || temp3>42000){
			printf("Fora da faixa de monitoramento\n");
			printf("Entre com a altura de uma aeronave dentro da regiao de monitoramento: ");
			scanf("%d", &temp3);
			}
			printf("Entre com o numero de passageiros a bordo, se houverem: ");
			scanf("%d", &temp4);
			cont++;
			voo=(Voo*)realloc(voo, cont*sizeof(Voo));
			if(voo==NULL){
				printf("Erro operacional: Falha na alocacao de memoria!\n");
				return 1;
			}
			voo[cont-1].codigo_voo=temp2;
			voo[cont-1].tipo=tipo;
			voo[cont-1].altitude=(float)temp3;
			voo[cont-1].passageiros_a_bordo=temp4;
		}
			if(cont==0){
			
				printf("Sem registros\n");
				if(voo!=NULL)free(voo);
				return 0;
				}
					for(i=0;i<cont;i++){
				soma+=voo[i].altitude;
				if(voo[i].tipo==1){
					tipo1++;
					
				}
				if(voo[i].tipo==2){
					tipo2++;
				}
				if(voo[i].tipo==3){
					tipo3++;
				}
			}
	media=(float)soma/cont;
	
	FILE*arq=fopen("espaco_aereo.txt", "w");
	if(arq!=NULL){
		fprintf(arq,"=====MONITORAMENTO DE TRAFEGO=====\n");
		fprintf(arq,"Controlador: %s\n", nome);
		fprintf(arq,"Codigo: %d\n", code);
		fprintf(arq,"----------------------------------\n");
		fprintf(arq,"TOTAL DE AERONAVES DE PASSAGEIROS: %d\n ", tipo1);
		fprintf(arq,"TOTAL DE AERONAVES CARGUEIRAS: %d\n", tipo2);
		fprintf(arq,"TOTAL DE AERONAVES EXECUTIVAS: %d\n", tipo3);
			fprintf(arq,"----------------------------------\n");
			media=(float)soma/cont;
			fprintf(arq, "MEDIA DE ALTITUDE GERAL: %.2f  PES\n", media);
			fprintf(arq,"====================================\n");
			fclose(arq);
			printf("Relatorio gerado com sucesso!\n");
		}
		free(voo);
		voo=NULL;
		return 0;
		
		
	}
	

