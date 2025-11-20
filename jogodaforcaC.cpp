#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>// biblioteca que possibilita o sorteio de um número com base no horário do PC
#include <windows.h>// biblioteca para utilizar o sleep

//OBS:Utilizar Structs para armazenar as dicas de cada palavra

void faz_linhas(int tamanho_palavra,char * palavra) {// Função que recebe o número de char's da palavra junto com
	setlocale(LC_ALL, "");
	char exibicao[20];                              //   um ponteiro guardando o endereço do array da palavra sorteada
	for (int i = 0; i < tamanho_palavra; i++) {
		exibicao[i] = '_';
	}
	exibicao[tamanho_palavra] = '\0';

	int acertos = 0;
	int limite_erros = 0;
	char letra;
	while(limite_erros < 5 && acertos < tamanho_palavra) {
		int encontrou_letra = 0;
		system("cls");
		printf("Palavra Misteriosa \n");
		for (int i = 0; i < tamanho_palavra; i++) {
			printf("%c ", exibicao[i]);
		}

		printf("\nAdvinhe uma letra da palavra!\n");
		scanf_s(" %c", &letra);

		for (int i = 0; i < tamanho_palavra; i++) {
			if (letra == palavra[i] && letra != exibicao[i]) {
				exibicao[i] = letra;
				acertos ++;
				encontrou_letra = 1;
			}
		}
		if (encontrou_letra == 0) {
			printf("\nLetra não existe na palavra\n");
			limite_erros++;
			Sleep(1500);
		}
	}
	if (acertos == tamanho_palavra) {
		printf("Parabéns Você acertou a Palavra: %s", palavra);
	}
	else {
		printf("Você foi enforcado");
	}

}
int sorteio() {
	srand(time(NULL));// Pega um número aleatório sorteado com base no horário do PC
	int numero_sorteado = rand() % 4; // Limita esse número em apenas 0 à 3
	return numero_sorteado;
}

int main() {

	char banco[][10] = {"mouse","teclado","monitor","fone"};
	char continuar;
	while (1) {
		int palavraint = sorteio();
		int contador = 0;// quantidade de letras da palavra sorteada
		while (banco[palavraint][contador] != '\0') {
			contador += 1;
		}
		faz_linhas(contador, banco[palavraint]);// Printa as linhas da palavras
		printf("\n Deseja Continuar ? (Y/N)");
		scanf_s(" %c",&continuar);

		if (continuar == 'N') {
			break;
		}
	}
}