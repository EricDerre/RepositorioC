#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

// Estrutura de um prato, tendo um nome alocado dinamicamente e um ponteiro que aponta para o próximo prato
typedef struct Prato {
    char* nome;
    struct Prato* proximo;
} Prato;


// Função para criar um novo prato
Prato* criarPrato(char* nome) {

     //Alocação de memória para cada prato
    Prato* novoPrato = (Prato*)malloc(sizeof(Prato)); 


    //Mensagem de erro caso não consiga alocar a memória
    if (novoPrato == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    //Alocação de memória para o nome de cada prato
    novoPrato->nome = (char*)malloc(strlen(nome) + 1); 


    //Mensagem de erro caso não consiga alocar a memória
    if (novoPrato->nome == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(novoPrato);
        exit(1);
    }

    //Copia o nome do prato recebido pela função no endereço de memória que foi alocado à cima
    strcpy(novoPrato->nome, nome); 
    printf ("\nPrato: %s adicionado com sucesso!\n", nome);

    //Inicialmente, o 1° prato deve apontar para ele mesmo como seu próximo, para manter a circularidade
    novoPrato->proximo = novoPrato;  
    return novoPrato;
}



// Função para adicionar um novo prato ao menu
Prato* adicionarPrato(Prato* menuPratos, char* nome) {

    //Aloca a memória para o novo prato
    Prato* novoPrato = criarPrato(nome);

    //Se o menu estiver vazio, o novo prato se torna o primeiro e único prato
    if (menuPratos == NULL) {
        return novoPrato; 
    }

    //Se a lista não estiver vazia, insere o prato no final e mantém a circularidade
    //"verificaMenu" recebe a lista de pratos
    Prato* verificaMenu = menuPratos;

    //"verificaMenu" percorre toda a lista até encontrar o último prato (aquele cujo próximo é igual ao primeiro)
    while (verificaMenu->proximo != menuPratos) {
        verificaMenu = verificaMenu->proximo;
    }

    //após encontrar o último prato, o novo prato a ser inserido é adicionado no final de fila
    verificaMenu->proximo = novoPrato;

    //o novo prato, então, recebe o seu "próximo prato" como o 1° prato da lista, mantendo a circularidade
    novoPrato->proximo = menuPratos;
    return menuPratos;
}



// Função para buscar um prato pelo nome
Prato* buscarPrato(Prato* menuPratos, char* nome) {

    //verifica se o menu está vazio, se sim, retorna null, pois é impossível localizar um prato em um menu vazio
    if (menuPratos == NULL) {
        return NULL;
    }

    //"verificaNome" recebe o menu de pratos
    Prato* verificaNome = menuPratos;

    do 
    {
        //utiliza a função "strcmp" para comparar se o nome atual do ponteiro "verificaNome" é o mesmo recebido pela função
        if (strcmp(verificaNome->nome, nome) == 0) {
            //se sim, retorna positivo e encerra o loop
            printf ("\nPrato %s encontrado!\n", nome);
            return verificaNome; 
        }
        //caso não encontre, ele passará para o próximo prato do menu e verificará novamente
        verificaNome = verificaNome->proximo;
    } 

    //a verificação ocorrerá enquanto o 1° elemento de "verificaNome" não seja igual ao 1° de "menuPratos", ou até encontrar
    //por isso deve-se utilizar o "do while", pois a repetição deve ser feita pelo menos 1 vez, para conseguir realizar o ciclo
    while (verificaNome != menuPratos);

    //retorna NULL caso não encontre
    printf ("\nPrato %s nao encontrado encontrado :(\n", nome);
    return NULL; 
}



// Função para contar a quantidade de pratos no menu
int contarPratos(Prato* menuPratos) {

    //verifica e retorna se o menu estiver vazio
    if (menuPratos == NULL) {
        return 0; 
    }

    int contador = 0;

    //"verificaTamanho" recebe o menu de pratos
    Prato* verificaTamanho = menuPratos;

    //utilizando a mesma lógia do "do while" da função "buscarPrato", a função atual percorre toda a lista equanto incrementa um contador
    do {
        contador++;
        verificaTamanho = verificaTamanho->proximo;
    } 
    while (verificaTamanho != menuPratos);

    //retorna o valor de "contador", onde terá o tamanho da lista
    printf ("\nQuantidade de pratos: %d\n", contador);
    return contador;
}



// Função para remover um prato do menu
Prato* removerPrato(Prato* menuPratos, char* nome) {

    //verifica e retorna se o menu estiver vazio, ou seja, sem pratos para remover
    if (menuPratos == NULL) {
        return NULL;
    }

    Prato* atual = menuPratos;
    Prato* anterior = NULL;

    // Caso especial: se o prato a ser removido for o único prato do menu
    if (atual->proximo == menuPratos && strcmp(atual->nome, nome) == 0) {
        //remove o prato e libera sua memória alocada
        free(atual->nome);
        free(atual);

        //retorna que, agora, a lista está vazia
        return NULL;  
    }

    // Caso comum: menu com mais de 1 prato
    do {

        //caso o nome da posição atual seja = ao nome recebido, ele inicia o processo de remoção 
        if (strcmp(atual->nome, nome) == 0) {
            
            //caso o elemento atual (a ser removido) seja o 1° elemento do menu:
            if (atual == menuPratos) {

                //ponteiro apenas para percorrer o menu e chegar no final dele
                Prato* percorreMenu = menuPratos;
                while (percorreMenu->proximo != menuPratos) {
                    percorreMenu = percorreMenu->proximo;
                }

                /* com o ponteiro no último elemento, podemos falar que seu próximo elemento (1° elemento do menu)
                receberá o 2° elemento do menu original, tornando-o o 1° elemento da lista */
                percorreMenu->proximo = menuPratos->proximo;
                menuPratos = menuPratos->proximo;
            } 
            
            /* caso o elemento atual (a ser removido) não seja o 1°, o ponteiro do "próximo elemento" do meu anterior
            receberá o próximo do meu atual, ou seja, pulará o elemento "atual", pois é ele que deve ser removido */
            else {
                anterior->proximo = atual->proximo;
            }

            //sendo assim, é liberada a memória alocada para o elemento removido 
            free(atual->nome);
            free(atual);

            //retorna o menu de pratos atualizado
            return menuPratos;
        }

        //se não entrar em nenhum dos "if's", a busca continua
        anterior = atual;
        atual = atual->proximo;
    } 
    
    //a verificação ocorrerá enquanto o elemento atual não seja igual ao 1° elemento de "menuPratos", ou até encontrar
    while (atual != menuPratos);


    // Retorna o menu atualizado (se o prato não foi encontrado, nada muda)
    return menuPratos; 
}



// Função para imprimir o menu de pratos
void imprimirMenu(Prato* menuPratos) {

    //verifica e retorna se o menu estiver vazio
    if (menuPratos == NULL) {
        printf("O menu esta vazio.\n");
        return;
    }

    //ponteiro apenas para percorrer o menu
    Prato* percorreMenu = menuPratos;

    printf("\nMenu de pratos:\n");

    //percorre todo o menu utilizando o ponteiro e printa na tela o nome de cada prato
    do {
        printf("- %s\n", percorreMenu->nome);
        percorreMenu = percorreMenu->proximo;
    } 
    while (percorreMenu != menuPratos);
}



// Função principal para testar a lista circular de pratos utilizando valores pré-definidos
void main(void) {

    setlocale(LC_ALL,"Portuguese");
    Prato* menuPratos = NULL;

    // Adiciona pratos
    menuPratos = adicionarPrato(menuPratos, "Lasanha");
    menuPratos = adicionarPrato(menuPratos, "Pizza");
    menuPratos = adicionarPrato(menuPratos, "Salada");

    // Imprime o menu
    imprimirMenu(menuPratos);

    // Busca um prato
    buscarPrato(menuPratos, "Pizza");

    // Conta a quantidade de pratos
    contarPratos(menuPratos);

    // Remove um prato
    removerPrato(menuPratos, "Pizza");
    printf("\nMenu apos remover Pizza:\n");
    imprimirMenu(menuPratos);

    // Conta novamente a quantidade de pratos
    contarPratos(menuPratos);

    // Limpa a memória alocada
    while (menuPratos != NULL) {
        menuPratos = removerPrato(menuPratos, menuPratos->nome);
    }

}



