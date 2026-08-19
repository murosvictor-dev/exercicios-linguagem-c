#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21
enum TipoVacina{BCG, TRIPLICE, FEBRE_AMARELA, HEPATITE, POLIO};
typedef struct{
	char nome[MAX];
	int numero_cartao;
	enum TipoVacina tipo;
	int idade;
	float altura;
	}crianca;
int localiza_cartao(int cartao, crianca *vetor, int tamanho);
float calcula_idade_media(crianca *vetor, int total);
float calcula_altura_media(crianca *vetor, int tamanho);
char *tipo_vacina(enum TipoVacina tipo);
int main(){
	crianca *vetor=NULL;
	enum TipoVacina tipo;
	int tamanho=0;
	int total=0;
	char opcao;
	int num_cartao;
	int categoria;
	int idade_crianca;
	float altura_crianca;
	int i;
	int j;
	float hmin=999999999;
	float hmax=-99999999;
	char aux[MAX];
	int indice;
	float soma=0.0;
	int quantidade_vacinas[5]={0,0,0,0,0};
	while(1){
	printf("C- CADASTRAR UMA CRIANCA\nB- DAR BAIXA EM UMA CRIANCA\nP- PESQUISAR UMA CRIANCA\nR- GERAR RELATORIO\n");
	printf("S- ENCERRAR PROGRAMA\n");
	scanf(" %c", &opcao);
	switch(opcao){
		case 'C':
		case 'c':
			printf("INFORME O CARTAO, O TIPO DE VACINA, A IDADE E A ALTURA\n");
			scanf("%d %d %d %f", &num_cartao, &categoria, &idade_crianca, &altura_crianca);
			if(num_cartao<1000 || num_cartao>10000){
				printf("CARTAO INVALIDO\n");
				continue;
			}
			indice=localiza_cartao(num_cartao, vetor, tamanho);
			if(indice!=-1){
				printf("CARTAO JA CADASTRADO\n");
				continue;
			}
			if(categoria<0 || categoria>4){
				printf("TIPO DE VACINA INVALIDO\n");
				continue;
			}
			if(idade_crianca<2 || idade_crianca>12){
				printf("FORA DA FAIXA ETARIA\n");
				continue;
			}

			if(altura_crianca<0.80 || altura_crianca>1.60){
				printf("ALTURA INVALIDA\n");
				continue;
			}
			printf("INFORME O NOME COMPLETO\n");
			scanf(" %20[^\n]", aux);
			tamanho++;
			vetor=(crianca*)realloc(vetor,tamanho*sizeof(crianca));
			quantidade_vacinas[categoria]++;
			if(vetor==NULL && tamanho>0){
				printf("ERRO DE MEMORIA\n");
				return 1;
				}
			vetor[tamanho-1].numero_cartao=num_cartao;
			vetor[tamanho-1].idade=idade_crianca;
			strcpy(vetor[tamanho-1].nome, aux);//o mais a esquerda recebe os dados do mais a direita
			vetor[tamanho-1].tipo=(enum TipoVacina)categoria;
			vetor[tamanho-1].altura=altura_crianca;
			if(vetor==NULL && tamanho>0){
				printf("ERRO DE MEMORIA\n");
				return 1;
				}
				break;
				case's':
				case 'S':
					return 0;
					break;
				case 'b':
				case 'B':printf("INFORME O CARTAO\n");
				scanf("%d", &num_cartao);
				indice=localiza_cartao(num_cartao, vetor, tamanho);
				if(indice==-1){
					printf("CRIANCA NAO ENCONTRADA\n");
					continue;
				}
				quantidade_vacinas[vetor[indice].tipo]--;//Remove diretamente a vacina registrada no vetor contagem;
					//vetor[indice].tipo fornecerá o tipo de vacina cadastrada (0, 1, 2, 3,..)
					//A seguir, o vetor auxiliar munido do indice fará o decremento
					tamanho--;
				for(i=0;i<tamanho-1;i++){
					vetor[i]=vetor[i+1];
				}	
				vetor=(crianca*)realloc(vetor, tamanho*sizeof(crianca));
				if(vetor==NULL && tamanho>0){
				printf("ERRO DE MEMORIA\n");
				return 1;
				}//Medida de segurança
				break;
				case 'p':
				case 'P': printf("INFORME O CARTAO\n");
				scanf("%d", &num_cartao);
				indice=localiza_cartao(num_cartao, vetor, tamanho);
				if(indice==-1){
					printf("CRIANCA NAO ENCONTRADA");
					continue;
				}
				printf("NOME: [%s]\n",vetor[indice].nome);
				printf("VACINA: %d\n", vetor[indice].tipo);
				printf("IDADE: [%d]\n", vetor[indice].idade);
				printf("ALTURA: [%.2f]\n", vetor[indice].altura);
				break;	
				case 'r':
				case 'R':
					if(tamanho==0){
						printf("NAO HOUVERAM VISITAS HOJE\n");
						FILE *arq=fopen("relatorio_posto.txt", "w");
						fprintf(arq, "NUMERO DE VACINAS BCG: 0\n");
						fprintf(arq, "NUMERO DE VACINAS TRIPLICE: 0\n");
						fprintf(arq, "NUMERO DE VACINAS FEBRE AMARELA: 0\n");
						fprintf(arq, "NUMERO DE VACINAS HEPATITE: 0\n");
						fprintf(arq, "NUMERO DE VACINAS POLIO: 0\n");
						fprintf(arq, "IDADE MEDIA: 0.0 ANOS\n");
						fprintf(arq, "ALTURA MEDIA: 0.00 m\n");
						fprintf(arq, "ALTURA MINIMA: 0.00 m\n");
						fprintf(arq, "ALTURA MAXIMA: 0.00 m\n");
						fclose(arq);
						continue;
					}
					FILE *arq=fopen("relatorio_posto.txt", "w");
					fprintf(arq, "NUMERO DE VACINAS BCG: %d\n", quantidade_vacinas[0]);
						fprintf(arq, "NUMERO DE VACINAS TRIPLICE: %d\n", quantidade_vacinas[1]);
						fprintf(arq, "NUMERO DE VACINAS FEBRE AMARELA: %d\n", quantidade_vacinas[2]);
						fprintf(arq, "NUMERO DE VACINAS HEPATITE: %d\n", quantidade_vacinas[3]);
						fprintf(arq, "NUMERO DE VACINAS POLIO: %d\n", quantidade_vacinas[4]);
						for(i=0;i<tamanho;i++){
							if(vetor[i].altura>hmax){
								hmax=vetor[i].altura;
							}
							if(vetor[i].altura<hmin){
								hmin=vetor[i].altura;
							}
							float soma=0.0;
							}
						fprintf(arq, "IDADE MEDIA: %.2f ANOS\n", calcula_idade_media(vetor, tamanho));
						fprintf(arq, "ALTURA MEDIA: %.2f M\n", calcula_altura_media(vetor, tamanho));
						fprintf(arq, "ALTURA MINIMA: %.2f M\n", hmin);
						fprintf(arq, "ALTURA MAXIMA: %.2f M\n", hmax);
						fprintf(arq, "CRIANCAS CADASTRADAS\n");
						int trocou = 1;
     int temp;
     float temp2;
     int temp3;
     int temp4;
    char aux[1000];
    
    
	for (i = 0; i < tamanho && trocou; i++){
        trocou = 0;
        for ( j = 1; j < tamanho; j++){
            if (strcmp(vetor[j-1].nome, vetor[j].nome) == 1){
                strcpy(aux, vetor[j].nome);
                strcpy(vetor[j].nome, vetor[j-1].nome);
                strcpy(vetor[j-1].nome, aux);
                trocou = 1;
                
                
				temp=vetor[j].numero_cartao;
                vetor[j].numero_cartao=vetor[j-1].numero_cartao;
                vetor[j-1].numero_cartao=temp;
                
                temp2=vetor[j].altura;
                vetor[j].altura=vetor[j-1].altura;
                vetor[j-1].altura=temp2;
                
                temp3=vetor[j].idade;
                vetor[j].idade=vetor[j-1].idade;
                vetor[j-1].idade=temp3;
                
                temp4=vetor[j].tipo;
                vetor[j].tipo=vetor[j-1].tipo;
                vetor[j-1].tipo=temp4;
                
            }
        }
    }
						fprintf(arq,"%-20s %-6s %-5s %-7s %-13s\n", "NOME", "CARTAO", "IDADE", "ALTURA", "VACINA");
						for(i=0;i<tamanho;i++){
							fprintf(arq, "[%-20s] %-6d %-5d %-7.2f %-13s\n", vetor[i].nome, vetor[i].numero_cartao, vetor[i].idade, vetor[i].altura, tipo_vacina(vetor[i].tipo));
						}
						fclose(arq);//sem medidas de segurança
						break;
						default: printf("COMANDO INVALIDO\n");
						break;
					
				
	}
}
	
	
}
int localiza_cartao(int num_cartao, crianca *vetor, int tamanho){
	int i;
	if(vetor==NULL || tamanho==0){
		return -1;
	}
	for(i=0;i<tamanho;i++){
		if( vetor[i].numero_cartao==num_cartao){
			return i;
		}
		}
		return -1;
		}
		char *tipo_vacina(enum TipoVacina tipo){//função retorna um ponteiro
	switch(tipo){
		case BCG: return "[BCG]";
		case TRIPLICE: return "[TRIPLICE]";
		case FEBRE_AMARELA: return "[FEBRE AMARELA]";
		case HEPATITE: return "[HEPATITE]";
		case POLIO: return "[POLIO]";
		default: return "TIPO INVALIDO";
		
	}
}
float calcula_idade_media(crianca *vetor, int tamanho){
	int i;
	int soma=0;
	float media=0.0;
	for(i=0;i<tamanho;i++){
		soma+=vetor[i].idade;
	}
	media=(float)soma/tamanho;
	return media;
}
float calcula_altura_media(crianca *vetor, int tamanho){
	int i;
	float soma=0.0;
	float media=0.0;
	for(i=0;i<tamanho;i++){
		soma+=vetor[i].altura;
	}
	media=(float)soma/tamanho;
	return media;
}


