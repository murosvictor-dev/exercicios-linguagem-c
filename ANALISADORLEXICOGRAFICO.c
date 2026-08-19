#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIM 200
void interativa(char frase[], int tam){
    
    int vogal=0, espaco=0, consoante=0, sinal=0;
    float p_vogal=0, p_consoante=0, p_sinal=0, p_espaco=0;
    int i; 
    tam=strlen(frase);

    for(i = 0; i < tam; i++) {
        if(frase[i]=='A' || frase[i]=='a' || frase[i]=='e' || frase[i]=='E' || frase[i]=='I' || frase[i]=='i' || frase[i]=='O' || frase[i]=='o' || frase[i]=='U' || frase[i]=='u') {
            vogal++;
        }
        else if(frase[i] == ' ') {
            espaco++;
        }
        else if(frase[i]==',' || frase[i]=='!' || frase[i]=='?') { 
            sinal++;
        }
        else {
            consoante++;
        }
    }

if(tam > 0) {
        p_vogal = ((float)vogal/tam)*100;
        p_espaco = ((float)espaco/tam)*100;
        p_sinal = ((float)sinal/tam)*100;
        p_consoante = ((float)consoante/tam)*100;

        printf("Vogais: %.2f%%\n", p_vogal);
        printf("Espacos: %.2f%%\n", p_espaco);
        printf("Sinais: %.2f%%\n", p_sinal);
        printf("Consoantes: %.2f%%\n", p_consoante);
    }
}
int main(){
	int num;
	int frases=1;
	int i;
	int opcao;
	int indice;
	int opcao2;
	int tam;
printf("****************************\n");
printf("ANALISADOR LEXICO DO CHAT DCT\n");
printf("****************************\n");
printf("Digite a quantidade de frases a inserir\n");
scanf("%d", &num);
	char frase[num][DIM];
		char texto[num*DIM];


for(i=0;i<num;i++){
	
	printf("Digite a frase %d\n", frases++);
scanf(" %[^\n]", frase[i]);//caso fosse %s[^\n], a string seria lida até o primeiro espaço. DAR O ESPAÇO É FUNDAMENTAL 
while(getchar() !='\n');


}
	  printf("Voce deseja analisar:\n");
	   printf("1-Uma frase expecifica;\n");
	   printf("2-O texto total delas\n");
	   scanf("%d", &opcao);
	   switch(opcao){
	   	case 1: printf("Digite o indice da frase a analisar:  ");
	   	scanf("%d", &indice);
	interativa( frase[indice-1], 0);
	   	break;
	   	
	   	case 2:
	   		texto[0]='\0';
	   	for(i=0;i<num;i++){
		   strcat(texto,frase[i]);
		 	if(i<num-1){//logica do balde grande -> Strings convertidas em textos
		 		strcat(texto," ");
			 }
	   	}
	   
	   	interativa(texto, 0);
	   		 	break;
	   		 	
	   	
	   	
		   default: printf("Indice invalido\n");
		   
	   	break;
	   }
	   return 0;
	   
	  

}


