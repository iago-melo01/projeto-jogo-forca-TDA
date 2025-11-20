#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

typedef struct {
    char palavra[20];
    char dica[100];
} Palavra;

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

void jogarRodada(Palavra objeto) {
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
        int encontrou_letra = 0;
        system("cls");

        desenhaForca(quantidade_erros);
        printf("Dica: %s\n\n", objeto.dica);
        printaLetrasTentadas(letrasTentadas, quantidade_letras_tentadas);

        printf("Palavra Misteriosa:\n");
        for (int i = 0; i < tamanho; i++) {
            printf("%c ", exibicao[i]);
        }

        printf("\n\nAdvinhe uma letra da palavra!\n");
        char letra = lerLetraValida(letrasTentadas, &quantidade_letras_tentadas);

        for (int i = 0; i < tamanho; i++) {
            if (letra == objeto.palavra[i] && letra != exibicao[i]) {
                exibicao[i] = letra;
                acertos++;
                encontrou_letra = 1;
            }
        }

        if (!encontrou_letra) {
            printf("\nLetra não existe na palavra\n");
            quantidade_erros++;
            Sleep(1000);
        }
    }

    system("cls");
    desenhaForca(quantidade_erros);

    if (acertos == tamanho) {
        printf("Parabéns Você acertou a Palavra: %s", objeto.palavra);
    }
    else {
        printf("Você foi enforcado");
    }
}

int sorteio(int max) {
    return rand() % max;
}

int main() {
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));

    Palavra banco[] = {
        {"mouse",   "Dispositivo usado para mover o cursor na tela"},
        {"teclado", "Periférico cheio de teclas"},
        {"monitor", "Exibe as imagens do computador"},
        {"fone",    "Usado para ouvir áudio"}
    };

    char continuar;

    while (1) {
        int indice = sorteio(4);
        Palavra escolhida = banco[indice];

        jogarRodada(escolhida);

        printf("\n\nDeseja Continuar ? (Y/N) ");
        scanf_s(" %c", &continuar, 1);

        if (continuar == 'N' || continuar == 'n') {
            break;
        }
    }

    return 0;
}
