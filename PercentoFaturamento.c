#include <stdio.h>

void main(void) {

    // Define o valor de faturamente de cada estado 
    double sp = 67836.43;
    double rj = 36678.66;
    double mg = 29229.88;
    double es = 27165.48;
    double outros = 19849.53;

    // Soma todos os valores para encontrar o total
    double total = sp + rj + mg + es + outros;


    // no próprio printf, ele mostrará o cálculo do percentual de cada estado, sem a necessidade de armazenar cada percentual em uma variável
    printf("Percentual de representacao de cada estado:\n");

    // o trecho "%.2f" especificará para o printf que ele deve mostrar número com apenas 2 casas decimais, limitando-o caso tenha mais
    // já o trecho "%%" fará com que o sinal de % seja escrito após o número
    printf("SP: %.2f%%\n", (sp / total) * 100);
    printf("RJ: %.2f%%\n", (rj / total) * 100);
    printf("MG: %.2f%%\n", (mg / total) * 100);
    printf("ES: %.2f%%\n", (es / total) * 100);
    printf("Outros: %.2f%%\n", (outros / total) * 100);

    /* Caso o programador ache melhor ou necessário armazenar cada valor em uma variável, o código ficará assim:

    double percent_sp = (sp / total) * 100;
    double percent_rj = (rj / total) * 100;
    double percent_mg = (mg / total) * 100;
    double percent_es = (es / total) * 100;
    double percent_outros = (outros / total) * 100;

    printf("Percentual de representacao de cada estado:\n");
    printf("SP: %.2f%%\n", percent_sp);
    printf("RJ: %.2f%%\n", percent_rj);
    printf("MG: %.2f%%\n", percent_mg);
    printf("ES: %.2f%%\n", percent_es);
    printf("Outros: %.2f%%\n", percent_outros)

    */

}
