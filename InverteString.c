#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inverter uma string utilizando ponteiros
void inverterString(char *str) {
    int ini = 0;
    int fim = strlen(str) - 1;
    char temp;

    // Realiza a troca de cada caractere pelo seu inverso no vetor, ou seja, o primeiro com o último, segundo com o penúltimo... até chegar no centro
    while (ini < fim) {
        temp = str[ini];
        str[ini] = str[fim];
        str[fim] = temp;
        
        ini++;
        fim--;
    }
}


void main(void) {
    char *str;
    size_t tamanho = 0;

    // Solicita ao usuário para digitar uma string
    printf("Digite o texto que deseja inverter ");

    // getline é utilizado para ler todo o texto digitado e já alocar a memória dinamicamente
    getline(&str, &tamanho, stdin);

    // Remove o caractere de nova linha no final, se existir (\n)
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // Inverte a string
    inverterString(str);

    // Exibe a string invertida
    printf("String invertida: %s\n", str);

    // Libera a memória alocada
    free(str);

}
