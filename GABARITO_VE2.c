#include <stdio.h>
#include <string.h>
#define VERDADE 1
#define FALSIDADE 0
#define MAX 100
#define STOP -1
#define MIN 5
#define NOME 21
int localiza_cartao(int visitas[], int registros, int nr);
float calcula_idade_media(int idades[], int registros);

int main(){
	int doses=0;
	int idade;
	int nr;
	int registros=0;
	int visitas[MAX];
	char nomes[MAX][NOME];
	int idades[MAX];
	int i, j;
	float IM=0.0;
    printf("*****************************\n");
	printf("POSTO DE SAUDE PRAIA VERMELHA\n");
	printf("*****************************\n");
	
	printf("Digite o total de doses do dia (min. 5): ");
	scanf("%d", &doses);
	
	while(doses<5){
		printf("O total de doses deve ser >=5\n");
		printf("Digite o total de doses do dia (min.5): ");
		scanf("%d", &doses);
		

	}
	while (registros<doses){
		printf("Insira o nr do cartao e a idade da crianca: ");
		scanf("%d %d", &nr, &idade);
	
	//Antes de registrarmos a entrada, deve-se verificar se todas as restrições foram atendidas
		if(nr==STOP){
		break;
	}
	if( nr<1000 || nr>9999){
		printf("CARTAO INVALIDO\n");
		continue;
	}

		//verificação se o cartao já consta no banco de dados
	if(localiza_cartao(visitas, registros, nr)!=-1){
		printf("CARTAO JAH INSERIDO\n");
		continue;
	}

	
	if(idade>12 || idade<2){
		printf("FORA DA FAIXA ETARIA!\n");
		continue;
	}
	    		visitas[registros]=nr;
		idades[registros]=idade;
		printf("Insira o nome e sobrenome:  \n");
scanf(" %[^\n]", nomes[registros]);
while(getchar() !='\n');
        registros++;
    }
     int trocou = 1;
     int temp;
     int temp2;
    char aux[1000];
    
	for (i = 0; i < registros && trocou; i++){
        trocou = 0;
        for ( j = 1; j < registros; j++){
            if (strcmp(nomes[j-1], nomes[j]) == 1){
                strcpy(aux, nomes[j]);
                strcpy(nomes[j], nomes[j-1]);
                strcpy(nomes[j-1], aux);
                trocou = 1;
                
                
				temp=idades[j];
                idades[j]=idades[j-1];
                idades[j-1]=temp;
                
                temp2=visitas[j];
                visitas[j]=visitas[j-1];
                visitas[j-1]=temp2;
                
            }
        }
    }
 printf("\n");
if(registros==0){
	printf("Nao houve visitas este dia\n");
	return 0;
}

IM = calcula_idade_media(idades, registros);

printf("**************** \n");
printf("RELATORIO DIARIO\n");
printf("****************\n");
printf("Media das idades: %.1f anos.", IM);
    printf("\nNOME.                     CARTAO        IDADE\n");
    for (i = 0; i < registros; i++) {
        printf("%-20s       %-5d         %d\n", nomes[i], visitas[i], idades[i]);
    }

    return 0;
	
}
int localiza_cartao(int visitas[], int registros, int nr){
	int i;
	for(i=0;i<registros;i++){
			if(visitas[i]==nr){
			
			return i;
		}
	}
return -1;// caso nao encontre nada
	}
float calcula_idade_media(int idades[], int registros){
		int i;
		int soma=0;
		float media= 0.0;
		for(i=0;i<registros;i++){
			soma+=idades[i];
		
			}
				media=(float)soma/registros;
			return media;
	}
