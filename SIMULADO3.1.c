#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum MaterialCarga{CADEIRA, MESA, COMPUTADOR, MONITOR, NOTEBOOK};
typedef struct{
	int nr_patrimonio;
	enum MaterialCarga tipo;
	float valor_item;
}material_carga;
char *categoria_patrimonio(enum MaterialCarga tipo);
	int localiza_item(int nr_patrimonio, material_carga *itens, int tamanho);
int main(){
material_carga *itens=NULL;
	int tamanho=0;
	int num_patrimonio;
	enum MaterialCarga tipo;
	float valor;
	char opcao;
	int tipo_material;
	int indice;
	int i;
	int cadeira=0;
	int mesa=0;
	int computador=0;
	int monitor=0;
	int notebook=0;
	int quantidade_tipo[5]={0,0,0,0,0};
	while(1){
	
printf("I- INCLUIR UM NOVO ITEM NO MATERIAL CARGA\nD- DELETAR UM ITEM NO MATERIAL CARGA\nR- GERAR UM RELATORIO\nS- ENCERRAR O PROGRAMA\n");
scanf(" %c", &opcao);
if(opcao=='S' || opcao=='s'){
return 0;
}
else if(opcao=='I' || opcao=='i'){
printf("INFORME O NR PATR, TIPO MATERIAL CARGA E VALOR\n");
scanf("%d %d %f", &num_patrimonio, &tipo_material, &valor);
if(num_patrimonio<1000 || num_patrimonio>9999){
printf("NUMERO DE PATRIMONIO INVALIDO\n");
continue;
}
indice=localiza_item(num_patrimonio, itens, tamanho);
if(indice!=-1){
printf("ITEM JA CADASTRADO\n");
continue;
}
if(tipo_material<0 || tipo_material>4){
printf("TIPO DE MATERIAL INVALIDO\n");
continue;
}
quantidade_tipo[tipo_material]++;
tamanho++;
itens=(material_carga*)realloc(itens, tamanho*sizeof(material_carga));
if(itens==NULL){
printf("[ERRO]: Alocacao de memoria incorreta!\n");
return 1;
}
itens[tamanho-1].nr_patrimonio=num_patrimonio;
itens[tamanho-1].valor_item=valor;
itens[tamanho-1].tipo=(enum MaterialCarga)tipo_material;
}
else if(opcao=='D' || opcao=='d'){

printf("INFORME O NR PATRI\n");
scanf("%d", &num_patrimonio);
indice=localiza_item(num_patrimonio, itens, tamanho);
if(indice==-1){
printf("MATERIAL NAO ENCONTRADO\n");
continue;
}
quantidade_tipo[itens[indice].tipo]--;
int j=indice;
for(j=indice;j<tamanho-1;j++){
	// Este loop faz o "shift" (arrasto): puxa cada elemento após o índice deletado uma posição para trás.
// Ao fazer isso, o item que queríamos deletar é "esmagado" (sobrescrito) pelo item da frente.
// Ao final do loop, o último elemento do vetor fica duplicado, mas ele é eliminado logo em seguida pelo realloc.
	itens[j]=itens[j+1];
}

tamanho--;
itens=(material_carga*)realloc(itens, tamanho*sizeof(material_carga));
//o realloc, assim, deleta a posição em que estava o item posterior duplicado
if(itens==NULL && tamanho>0){
	printf("[ERRO]: Alocacao de memoria incorreta!\n");
	return 1;
	}
}

else if(opcao=='R' || opcao=='r'){
		float soma =0.00;
FILE *arq=fopen("relatorio.txt", "w");
if(arq==NULL){
printf("Falha ao criar o arquivo\n");
return 1;
}
fprintf(arq,"NUMERO DE CADEIRAS: %d", quantidade_tipo[0]);
fprintf(arq,"\nNUMERO DE MESAS: %d", quantidade_tipo[1]);
fprintf(arq,"\nNUMERO DE COMPUTADORES: %d", quantidade_tipo[2]);
fprintf(arq, "\nNUMERO DE MONITORES: %d", quantidade_tipo[3]);
fprintf(arq, "\nNUMERO DE NOTEBOOKS: %d", quantidade_tipo[4]);
for(i=0;i<tamanho;i++){
soma+=itens[i].valor_item;
}
fprintf(arq,"\n");
fprintf(arq,"VALOR TOTAL DO MATERIAl CARGA: %.2f", soma);
fclose(arq);
}

 else{
 	printf("OPERADOR INVALIDO\n");
 	continue;
 }
}



if(itens!=NULL){
free(itens);//a memoria só deve ser liberada quando se tiver certeza de que essa não ser mais necessária
}
return 0;
}

char *categoria_patrimonio(enum MaterialCarga tipo){
	switch(tipo){
		case CADEIRA: return "Cadeira";
		case MESA: return "Mesa";
		case COMPUTADOR: return "Computador";
		case MONITOR: return "Monitor";
		case NOTEBOOK: return "Notebook";
		default: return "Tipo nao encontrado";
		
	}
}

	int localiza_item(int nr_patrimonio, material_carga *itens, int tamanho){
		int i;
		if(itens==NULL || tamanho==0){
		return -1;
	}
		for(i=0;i<tamanho;i++){
			if(itens[i].nr_patrimonio==nr_patrimonio){
				return i;
			}
			}
		return -1;
			}
		
