#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include "banco.h"

void desenhaForca(int erros) {
    printf(" _______\n");
    printf("|       |\n");
    printf("|       %c\n", (erros >= 1 ? 'O' : ' '));
    printf("|      %c%c%c\n",
        (erros >= 3 ? '/' : ' '),
        (erros >= 2 ? '|' : ' '),
        (erros >= 4 ? '\\' : ' '));
    printf("|      %c %c\n",
        (erros >= 5 ? '/' : ' '),
        (erros >= 6 ? '\\' : ' '));
    printf("|\n");
    printf("=========\n\n");
}

void printaLetrasTentadas(char* arrayLetrasTentadas, int quantidade_letras_tentadas) {
    printf("Letras tentadas: ");
    if (quantidade_letras_tentadas == 0) {
        printf("Nenhuma");
    }
    else {
        for (int i = 0; i < quantidade_letras_tentadas; i++) {
            printf("%c, ", arrayLetrasTentadas[i]);
        }
    }
    printf("\n");
}

char lerLetraValida(char* arrayLetrasTentadas, int* quantidade_letras_tentadas) {
    char letra;
    while (1) {
        scanf_s(" %c", &letra, 1);
        letra = tolower(letra);

        if (letra == '0') {
            return '0';
        }

        int ja_tentou = 0;
        for (int i = 0; i < *quantidade_letras_tentadas; i++) {
            if (arrayLetrasTentadas[i] == letra) {
                ja_tentou = 1;
                break;
            }
        }

        if (ja_tentou) {
            printf("Essa letra já foi tentada, tente outra: ");
        }
        else {
            arrayLetrasTentadas[*quantidade_letras_tentadas] = letra;
            (*quantidade_letras_tentadas)++;
            return letra;
        }
    }
}

int tamanhoPalavra(Palavra objeto) {
    int contador = 0;
    while (objeto.palavra[contador] != '\0') {
        contador++;
    }
    return contador;
}

int jogarRodada(Palavra objeto) {
    int tamanho = tamanhoPalavra(objeto);
    char exibicao[20];

    for (int i = 0; i < tamanho; i++) {
        exibicao[i] = '_';
    }
    exibicao[tamanho] = '\0';

    char letrasTentadas[26] = { 0 };
    int quantidade_letras_tentadas = 0;
    int acertos = 0;
    int quantidade_erros = 0;

    while (quantidade_erros < 6 && acertos < tamanho) {
        system("cls");

        desenhaForca(quantidade_erros);
        printf("Dica: %s\n\n", objeto.dica);
        printaLetrasTentadas(letrasTentadas, quantidade_letras_tentadas);

        printf("Palavra Misteriosa:\n");
        for (int i = 0; i < tamanho; i++) {
            printf("%c ", exibicao[i]);
        }

        printf("\n\nAdvinhe uma letra da palavra ou aperte '0' para sair!\n");
        char letra = lerLetraValida(letrasTentadas, &quantidade_letras_tentadas);

        if (letra == '0') {
            return 1; // voltar ao menu
        }

        int encontrou = 0;

        for (int i = 0; i < tamanho; i++) {
            if (letra == objeto.palavra[i] && letra != exibicao[i]) {
                exibicao[i] = letra;
                acertos++;
                encontrou = 1;
            }
        }

        if (!encontrou) {
            printf("\nLetra não existe na palavra\n");
            quantidade_erros++;
            Sleep(1000);
        }
    }

    system("cls");
    desenhaForca(quantidade_erros);

    if (acertos == tamanho) {
        printf("Parabéns! Você acertou a Palavra: %s\n", objeto.palavra);
    }
    else {
        printf("Você foi enforcado!\n");
    }

    return 0; // rodada terminou normalmente
}

int sorteio(int max) {
    return rand() % max;
}

void menu() {
    printf("----- MENU ------\n");
    printf("1 - Criar palavra e dica\n");
    printf("2 - Jogar\n");
    printf("3 - Ver ranking\n");
    printf("4 - Sair\n");
    printf("-----------------\n");
}

int main() {
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));

    int acao_menu;
    char continuar;
    char palavra_digitada[20];
    char dica_digitada[100];

    while (1) {
        system("cls");
        menu();
        scanf_s(" %d", &acao_menu);

        switch (acao_menu) {

        case 1:
            printf("Digite uma palavra (sem espaços):\n");
            scanf_s("%19s", palavra_digitada, (unsigned)_countof(palavra_digitada));

            printf("Digite uma dica (pode ter espaços):\n");
            getchar();
            fgets(dica_digitada, 100, stdin);

            Palavra criada;

            strcpy_s(criada.palavra, sizeof(criada.palavra), palavra_digitada);
            strcpy_s(criada.dica, sizeof(criada.dica), dica_digitada);

            jogarRodada(criada);
            break;

        case 2:
            while (1) {
                
                int indice = sorteio(banco_tamanho);
                Palavra escolhida = banco[indice];

                int saiu = jogarRodada(escolhida);
                if (saiu == 1) break;

                printf("\nDeseja continuar jogando? (Y/N): ");
                scanf_s(" %c", &continuar, 1);

                if (continuar == 'N' || continuar == 'n') {
                    break;
                }
            }
            break;

        case 3:
            printf("Ranking ainda não implementado.\n");
            break;

        case 4:
            printf("Saindo...\n");
            return 0;

        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}
