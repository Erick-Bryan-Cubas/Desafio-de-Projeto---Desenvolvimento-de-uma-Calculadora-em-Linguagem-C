#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <windows.h>

float adicao(float a, float b) {
    return a + b;
}

float subtracao(float a, float b) {
    return a - b;
}

float multiplicacao(float a, float b) {
    return a * b;
}

float divisao(float a, float b) {
    if (b == 0) {
        printf("Erro: Divis�o por zero.\n");
        exit(1);
    }
    return a / b;
}

void converter_base(long num, int base) {
    if (base < 2 || base > 16) {
        printf("Erro: Base inv�lida.\n");
        exit(1);
    }

    char buffer[64];
    _itoa(num, buffer, base);
    printf("Resultado: %s\n", buffer);
}

int main() {
    
    setlocale(LC_ALL, "");
    SetConsoleTitle("Calculadora de Programador");

    int opcao;
    float a, b;
    long num;
    int base;

    printf("Calculadora\n");
    printf("1. Adi��o\n");
    printf("2. Subtra��o\n");
    printf("3. Multiplica��o\n");
    printf("4. Divis�o\n");
    printf("5. Converter para base\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
        case 2:
        case 3:
        case 4:
            printf("Digite dois n�meros: ");
            scanf("%f %f", &a, &b);
            break;
        case 5:
            printf("Digite um n�mero inteiro: ");
            scanf("%ld", &num);
            printf("Digite a base de destino (2-16): ");
            scanf("%d", &base);
            break;
        default:
            printf("Op��o inv�lida.\n");
            exit(1);
    }

    switch (opcao) {
        case 1:
            printf("Resultado: %.2f\n", adicao(a, b));
            break;
        case 2:
            printf("Resultado: %.2f\n", subtracao(a, b));
            break;
        case 3:
            printf("Resultado: %.2f\n", multiplicacao(a, b));
            break;
        case 4:
            printf("Resultado: %.2f\n", divisao(a, b));
            break;
        case 5:
            converter_base(num, base);
            break;
    }

    return 0;
}
