#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define V 7
int matriz [V][V];

//Estutura do NO para a Pilha
typedef struct NO{

    int valor;
    struct NO *prox;

}NO;


//Estrutura da Pilha
typedef struct PILHA{

    NO *topo;

}PILHA;


//Inicializa a pilha com o topo vazio
void inicializarPilha(PILHA *pilha){

    pilha->topo = NULL;

}

//Função para empilhar um novo valor
void empilhar(int valor, PILHA *pilha){

    NO *ponteiro = (NO*)malloc(sizeof(NO));
    if (ponteiro == NULL){
        printf("Erro de alocação de memória\n");
        return;
    }
    else {
        ponteiro->valor = valor;
        ponteiro->prox = pilha->topo;
        pilha->topo = ponteiro;
    }
}


//Função para desempilhar um valor
void desempilhar(PILHA *pilha){

    NO *ponteiro = pilha->topo;
    int valor;
    if(ponteiro == NULL){
        printf("Pilha vazia - Erro no Desempilhar\n");
        return;
    }
    else {
        pilha->topo = ponteiro->prox;
        ponteiro->prox = NULL;
        valor = ponteiro->valor;
        free(ponteiro);
        return valor;
    }

}


//Função para imprimir a pilha na ordem de leitura (da base para o topo)
void imprimirPilha(PILHA *pilha){

    NO *ponteiro = pilha->topo;
    int valores[V]; // Vetor temporário para armazenar os valores da pilha
    int i = 0;

    if (ponteiro == NULL) {
        printf("Pilha vazia - Erro ao Imprimir\n");
        return;
    }

    // Armazena os valores da pilha no array
    while (ponteiro != NULL) {
        valores[i++] = ponteiro->valor;
        ponteiro = ponteiro->prox;
    }

    // Imprime os valores do array em ordem de caminho
    printf("Caminho: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d ", valores[j]);
    }
    printf("\n");
}

//Função para imprimir o grafo em formato de matriz
void imprimirMatriz(int vertices){

	int i,j,k;
	printf("    ");
	for(k = 0; k < vertices; k++) printf("V%d ",k+1);
	printf("\n");
	for(i = 0;i < vertices; i++){
		for(j = 0;j < vertices; j++){
			if(j == 0) printf("V%d  ",i+1);
			printf("%d  ",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

//Função de busca em profundidade
void buscaProfundidade(int vOrigem, int vDestino, PILHA *pilhaVertices, int vertices){

    int vO = vOrigem - 1;
	int vD = vDestino - 1;
    int vetorPassou[V] = {0};

    //Caso o vértice de origem seja igual ao de destino
	if(matriz[vO][vD] == 1) printf("\n\nCaminho: %d => %d", vOrigem, vDestino);

    //Caso contrário, realiza a busca em profundidade
	else{       
        empilhar(vOrigem, pilhaVertices);  //Empilha o vértice de origem
        vetorPassou[vO] = 1; //Marca o vértice de origem como já visitado

        //Laço de repetição para realizar a busca em profundidade
        for(int i = 0; i <= vertices; i++){

            printf("Realizando caminho...\n");
            imprimirPilha(pilhaVertices);
            int encontrou = 0; //Variável que indica se achou algum vértice com ligação válida

            for (int j = 0; j <= vertices; j++){

                //Verifica se o vértice atual tem ligação válida com o vértice "j" e se o vértice "j" ainda não foi visitado
                if(matriz[vO][j] == 1 && vetorPassou[j] != 1){

                    vO = j; //Atualiza o vértice de origem
                    vetorPassou[vO] = 1; //Marca o novo vértice de origem como já visitado
                    empilhar(vO + 1, pilhaVertices); //empilha o novo vértice de origem
                    encontrou = 1; //Indica que encontrou um vértice com ligação válida

                    //Verifica se o vértice de origem é igual ao vértice de destino. Caso seja, ele imprime o caminho e encerra a função
                    if (vO == vD){
                        printf("\nCaminho concluido! \n");
                        imprimirPilha(pilhaVertices);
                        return;
                        }
                    /*O break é utilizado para sair do laço de repetição caso encontre um vértice com ligação válida
                    permitindo imprimir o caminho enquanto estiver sendo montado*/
                    break;
                    }       
                }
            //Se, ao final do "for" de "j", não encontrou nenhum vértice com ligação válida, ele retorna para o último vértice da pilha e reinicia o "for" de "j"
            if (encontrou == 0){
                printf("\nBeco sem saidas validas, retornando...\n");
                desempilhar(pilhaVertices);
                //Caso a função desempilhe e não tenha mais nenhum vertice válido para o caminho, ele imprime a mensagem de erro e encerra a função
                if (pilhaVertices->topo == NULL){
                    printf("\nNenhum caminho válido encontrado\n");
                    return;
                }
                vO--;
            }
        }
	}
}

void main (void){

    setlocale(LC_ALL, "Portuguese");

    //Inicializa o ponteiro da pilha
    PILHA *pilhaVertices = (PILHA*)malloc(sizeof(PILHA));
    inicializarPilha(pilhaVertices);

    int vertices;
    int ligacao;
    int vOrigem;
    int vDestino;
    int validaOrigemDestino;
    int validaQtdeVertice = -1;

    //Soliciata ao usuário a quantidade de vértices do grafo
    while (validaQtdeVertice != 0){

        printf("Digite a quantidade de vertices: \n");
        scanf("%d", &vertices);

        if(vertices > V){
            printf("Quantidade de vertices maior do que o permitido. Tamanho maximo: %d\n", V);
            validaQtdeVertice = -1;
        }
        else{
            validaQtdeVertice = 0;
        }
    }

    //Laço de repetição para preencher a matriz de adjacência com tratativas de erro
    for (int i = 0; i < vertices; i++){
        for (int j = 0; j < vertices; j++){
            if (i == j){
                if (i == vertices-1){
                    break;
                }
                else{
                    j++;
                }
            }
            printf("Vertice %d se liga com o vertice %d ? (1 para Sim, 0 para Nao)\n", i+1, j+1);
            scanf("%d", &ligacao);

            if (ligacao == 1){
                matriz [i][j] = 1;
            }
            else if (ligacao == 0){
                matriz [i][j] = 0;
            }
            else{
                printf("Opcao invalida\n");
                j--;
            }    
        }
    }

    //Solicita ao usuário o vértice de origem e destino para a busca em profundidade
    while (validaOrigemDestino != 2)
    {
        validaOrigemDestino = 0;
        imprimirMatriz(vertices);

        printf("Qual o vertice de origem?\n");
        scanf("%d", &vOrigem);

        printf("Qual o vertice de destino?\n");
        scanf("%d", &vDestino);

         //Tratativas de erro
        if (vOrigem > vertices || vDestino > vertices || vOrigem < 1 || vDestino < 1){
            printf("Vertice de origem ou destino invalido\n");
        }
        else{
            buscaProfundidade(vOrigem, vDestino, pilhaVertices, vertices);

            printf("\nDeseja fazer uma nova busca no mesmo grafo? (Digite 2 para encerrar/Qualquer coisa para continuar)\n");
            scanf("%d", &validaOrigemDestino);
        }
    }
    
    free(pilhaVertices);
}
