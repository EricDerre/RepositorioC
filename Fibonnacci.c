#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

// Função para verificar se um número pertence à sequência de Fibonacci
bool pertenceFibonacci(int num) {
    int a = 0, b = 1, aux;

    if (num == 0 || num == 1) {
        return true;
    }

    // Escreve a sequência de Fibonacci gerando números da sequência até que o número gerado seja maior ou igual ao número informado.
    while (b < num) {
        aux = a;
        a = b;
        b = aux + b;
    }
    // Retorna True para caso b = num. Retorna False caso não seja
    return (b == num);
}

void main(void) {
    setlocale(LC_ALL,"Portuguese");
    int numero;

    // Solicita ao usuário para informar um número
    printf("Informe um numero que deseja verificar se pertence a sequencia de Fibonacci: ");
    scanf("%d", &numero);

    // Chama a função pertenceFibonacci e caso o retorno seja True, escreve que pertence à sequência
    if (pertenceFibonacci(numero)) {
        printf("%d pertence a sequencia de Fibonacci.\n", numero);
    } 
    
    // Caso a função retorne False, ele entrará na condição "else" e escreverá que não pertence à sequência
    else {
        printf("%d nao pertence a sequancia de Fibonacci.\n", numero);
    }

}
