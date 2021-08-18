#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAXSENHAS 430000 // Altere para os testes iniciais. No final ordene pelo menos metade disso.

struct senha{
	char *palavra;
	int tamanho;
	int frequencia;
};

typedef struct senha Senha;

void MergeSort(Senha** senhas, int inicio, int final){
	if(inicio != final){
		int v1, v2, tamanhoAuxiliar, metade = (inicio + final) / 2;
		Senha** senha_temp;
		int i, j;

		MergeSort(senhas, inicio, metade);
		MergeSort(senhas, metade+1, final);

		v1 = inicio;
		v2 = metade+1;
		tamanhoAuxiliar = (final - inicio)+1;
		senha_temp = (Senha**) malloc (tamanhoAuxiliar * sizeof(Senha*));

		for(i=0;i<tamanhoAuxiliar;i++){
			if(v1 > metade){
				for(j=i;j<tamanhoAuxiliar;j++){
					senha_temp[j] = senhas[v2];
					v2++;
				}
				break;
			}
			
			else if(v2 > final){
				for(j=i;j<tamanhoAuxiliar;j++){
					senha_temp[j] = senhas[v1];
					v1++;
				}
				break;
			}

			else if(strcmp(senhas[v1]->palavra, senhas[v2]->palavra) < 0){
				senha_temp[i] = senhas[v1];
				v1++;
			}

			else{
				senha_temp[i] = senhas[v2];
				v2++;
			}
		}

		for(i=0;i<tamanhoAuxiliar;i++){
			senhas[inicio] = senha_temp[i];
			inicio++;
		}
		free(senha_temp);
	}
}

void LerSenhas(Senha **senhas, char *filepath){
	FILE *fp;
	int n= 0, tam, freq;
	char pass[200];

	fp= fopen(filepath, "r");

	size_t contador=0;
	while(fscanf(fp, "%d %d %[^\n]", &tam, &freq, pass) == 3){
		senhas[n]= (Senha*)malloc(sizeof(Senha));
		senhas[n]->tamanho= tam;
		senhas[n]->frequencia= freq;
		senhas[n]->palavra= (char*)malloc((tam+1) * sizeof(char));
		pass[tam]= '\0';
		strcpy(senhas[n]->palavra, pass);
		n++;
		if(++contador == MAXSENHAS){
			break;
		}
	}
	fclose(fp);
}

int main(void){
    int n;
	Senha** senhas;
	senhas= (Senha**)malloc(MAXSENHAS * sizeof(Senha*));

	LerSenhas(senhas, "senhas.txt");

	clock_t horaInicial = clock();

	printf("Serao ordenadas %d senhas em Merge Sort, por favor aguarde!\n",MAXSENHAS);

	MergeSort(senhas, 0, MAXSENHAS-1);

	clock_t horaFinal = clock();

	double tempoDecorrido = (double) (horaFinal - horaInicial)/CLOCKS_PER_SEC;

	for(n=0;n<MAXSENHAS;n++){
		printf("%s - %d - %d\n", senhas[n]->palavra, senhas[n]->tamanho, senhas[n]->frequencia);
	}

	printf("\nSera criado um arquivo de saida para armazenamento dos dados.\n");

	FILE *arquivo;
	arquivo= fopen("saida.txt", "w");

	for(n=0;n<MAXSENHAS;n++){
		fprintf(arquivo, "%s - %d - %d\n", senhas[n]->palavra, senhas[n]->tamanho, senhas[n]->frequencia);
	}

	printf("\n\nO tempo necessario para ordenar o vetor de senhas eh %f segundos.\n",tempoDecorrido);
	printf("O tempo necessario para ordenar o vetor de senhas eh %f milissegundos.\n",tempoDecorrido*1000);

	system("pause");

	for(n=0;n<MAXSENHAS;n++){
		free(senhas[n]);
	}

	free(senhas);

	return 0;
}