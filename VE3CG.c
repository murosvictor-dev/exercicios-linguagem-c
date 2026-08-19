#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum TipoDrone{RECONHECIMENTO, MAPEAMENTO, ATAQUE, TRANSPORTE};
typedef struct{
	int id;
    enum TipoDrone tipo;
	float autonomia;
}cadastro_drone;
int localiza_drone(int id, cadastro_drone *vetor, int tamanho);
char *tipo_drone(enum TipoDrone tipo);
int main(){
	cadastro_drone *drone=NULL;
	enum TipoDrone tipo;
	int tamanho=0;
	char opcao;
	int idt_drone;
	int categoria=0;
	float range;
	int indice;
	int i;
		float media;
	int quantidade_tipo[4]={0,0,0,0};
	while(1){
		printf("C - CADASTRAR UM NOVO DRONE\n");
		printf("B - BAIXAR UM DRONE DO CADASTRO\n");
		printf("P - PESQUISAR UM DRONE CADASTRADO\n");
		printf("R - GERAR UM RELATORIO\n");
		printf("S - ENCERRAR O PROGRAMA\n");
		scanf(" %c", &opcao);
		switch(opcao){
			case 'C': 
			case 'c': printf("INFORME ID, TIPO DO DRONE E AUTONOMIA\n");
			scanf("%d %d %f", &idt_drone, &categoria, &range);
			if(idt_drone<10000 || idt_drone>100000){
				printf("IDENTIFICACAO INVALIDA\n");
				continue;
			}
			indice=localiza_drone(idt_drone, drone, tamanho);
			if(indice!=-1){
				printf("DRONE JA CADASTRADO\n");
				continue;
			}
			if(categoria<0 || categoria>3){
				printf("TIPO DE DRONE INVALIDO\n");
				continue;
			}
			if(range<=0){
				printf("AUNTONOMIA INVALIDA\n");
				continue;
			}
			tamanho++;
			quantidade_tipo[categoria]++;
			drone=(cadastro_drone*)realloc(drone, tamanho*sizeof(cadastro_drone));
			if(drone==NULL){
				printf("[ERRO]: Alocacao de memoria incorreta!\n");
				return 1;
			}
			drone[tamanho-1].id=idt_drone;
			drone[tamanho-1].tipo=(enum TipoDrone)categoria;
			drone[tamanho-1].autonomia=range;
			break;
			case 'P':
			case 'p': printf("INFORME O ID DO DRONE\n");
			scanf("%d", &idt_drone);
			indice=localiza_drone(idt_drone, drone, tamanho);
			if(indice==-1){
				printf("DRONE NAO ENCONTRADO\n");
				continue;
			}
			printf("TIPO: %s\n", tipo_drone(drone[indice].tipo));
			printf("AUTONOMIA: [%.2f]\n", drone[indice].autonomia);
			break;
			case 'B':
			case 'b': printf("INFORME O ID DO DRONE\n");
			scanf("%d", &idt_drone);
			indice=localiza_drone(idt_drone, drone, tamanho);
			if(indice==-1){
				printf("DRONE NAO ENCONTRADO\n");
				continue;
			}
	quantidade_tipo[drone[indice].tipo]--;
int j=indice;
for(j=indice;j<tamanho-1;j++){
	drone[j]=drone[j+1];
}
tamanho--;
drone=(cadastro_drone*)realloc(drone, tamanho*sizeof(cadastro_drone));
if(drone==NULL && tamanho>0){
	printf("[ERRO]: Alocacao de memoria incorreta!\n");
	return 1;
	}
	break;
	case 's':
	case 'S': return 0;
	break;
	case 'R':
	case 'r':{
	FILE *arq=fopen("relatorio_drones.txt", "w");
	if(arq==NULL){
		printf("FALHA AO CRIAR O ARQUIVO\n");
		return 1;
	}
	float soma=0.0;
	fprintf(arq, "NUMERO DE DRONES DE RECONHECIMENTO: %d\n", quantidade_tipo[0]);
	fprintf(arq, "NUMERO DE DRONES DE MAPEAMENTO: %d\n", quantidade_tipo[1]);
	fprintf(arq, "NUMEROD DE DRONES DE ATAQUE: %d\n", quantidade_tipo[2]);
	fprintf(arq, "NUMERO DE DRONES DE TRANSPORTE: %d\n", quantidade_tipo[3]);
	for(i=0;i<tamanho;i++){
		
		soma+=drone[i].autonomia;
		}
		if(tamanho==0){
			media=0.0;
		}
		media=(float)soma/tamanho;
		fprintf(arq, "AUTONOMIA MEDIA: %.2f minutos\n", media);
		fprintf(arq,"DRONES CADASTRADOS:\n");
		fprintf(arq," %-7s %-15s %-5s\n", "ID", "TIPO", "AUTONOMIA");
		for(i=0;i<tamanho;i++){
			fprintf(arq, "%-7d %-17s %-9.2f\n", drone[i].id, tipo_drone(drone[i].tipo), drone[i].autonomia);
		}
		fclose(arq);
		break;
	}
		default: printf("COMANDO INVALIDO\n");
		break;
		
	}
	}
	if(drone!=NULL){
		free(drone);
	}
	return 0;
}
int localiza_drone(int idt_drone, cadastro_drone*drone, int tamanho){
	int i;
	if(drone==NULL || tamanho==0){
		return -1;
	}
	for(i=0;i<tamanho;i++){
		if( drone[i].id==idt_drone){
			return i;
		}
		}
		return -1;
		}
char *tipo_drone(enum TipoDrone tipo){//função retorna um ponteiro
	switch(tipo){
		case RECONHECIMENTO: return "[RECONHECIMENTO]";
		case MAPEAMENTO: return "[MAPEAMENTO]";
		case TRANSPORTE: return "[TRANSPORTE]";
		case ATAQUE: return "[ATAQUE]";
		default: return "TIPO DE DRONE INVALIDO";
		
	}
}

