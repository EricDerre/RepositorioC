#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// Estrutura para representar uma carta
typedef struct Carta {
    int id;
    char nome[30];
    char evolucao[30];
    int pontos_saude;
    char elemento[20];
    char habilidade[50];
    char descricao_habilidade[100];
    int custo_habilidade;
    char fraqueza[20];
    char resistencia[20];
    char autor[50];
    char descricao_autor[90];
    struct Carta *prox;
} Carta;
// Estrutura para representar um nó da fila de cartas da mão
typedef struct NoFila {
    Carta *carta;
    struct NoFila *prox;
} NoFila;
// Estrutura para representar a fila de cartas da mão
typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaCartas;
// Função para criar uma nova fila de cartas
FilaCartas* criarFila() {
    FilaCartas *novaFila = (FilaCartas*)malloc(sizeof(FilaCartas));
    novaFila->inicio = novaFila->fim = NULL;
    return novaFila;
}
// Função para enfileirar uma carta na fila
void enfileirar(FilaCartas *fila, Carta *carta) {
    NoFila *novoNo = (NoFila*)malloc(sizeof(NoFila));
    novoNo->carta = carta;
    novoNo->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}
// Função para mostrar a fila
void mostrarFila(FilaCartas *fila) {
    NoFila *temp = fila->inicio;
    printf("Fila de acoes: ");
    while (temp != NULL) {
        printf("%d ", temp->carta->id);
        temp = temp->prox;
    }
    printf("\n");
}
// Função para mostrar a próxima carta da fila
void mostrarProximaCartaFila(FilaCartas *fila) {
    if (fila->inicio == NULL) {
        printf("A fila de cartas está vazia!\n");
        return;
    }
    printf("\nNome: %s\n", fila->inicio->carta->nome);
    printf("\nHabilidade: %s\n", fila->inicio->carta->habilidade);
    printf("\nDescricao da Habilidade: %s\n", fila->inicio->carta->descricao_habilidade);
}
// Função para desenfileirar uma carta da fila
Carta* desenfileirar(FilaCartas *fila) {
    if (fila->inicio == NULL) {
        printf("A fila de cartas esta vazia!\n");
        return NULL;
    }
    NoFila *temp = fila->inicio;
    Carta *carta = temp->carta;
    fila->inicio = fila->inicio->prox;
    free(temp);
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    return carta;
}
// Função cria carta
Carta* criarCarta(int id, char nome[], char evolucao[], int pontos_saude, char elemento[], char habilidade[], char descricao_habilidade[], int custo_habilidade, char fraqueza[], char resistencia[], char autor[], char descricao_autor[]) {
    Carta *nova_carta = (Carta*)malloc(sizeof(Carta));
    if (nova_carta == NULL) {
        printf("Erro ao alocar memória para a carta.\n");
        exit(1);
    }
    nova_carta->id = id;
    strcpy(nova_carta->nome, nome);
    strcpy(nova_carta->evolucao, evolucao);
    nova_carta->pontos_saude = pontos_saude;
    strcpy(nova_carta->elemento, elemento);
    strcpy(nova_carta->habilidade, habilidade);
    strcpy(nova_carta->descricao_habilidade, descricao_habilidade);
    nova_carta->custo_habilidade = custo_habilidade;
    strcpy(nova_carta->fraqueza, fraqueza);
    strcpy(nova_carta->resistencia, resistencia);
    strcpy(nova_carta->autor, autor);
    strcpy(nova_carta->descricao_autor, descricao_autor);
    nova_carta->prox = NULL;
    return nova_carta;
}
// Função para inserir carta no final da lista
void inserirCarta(Carta **deck, Carta *nova_carta) {
    if (*deck == NULL) {
        *deck = nova_carta;
    } else {
        Carta *temp = *deck;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = nova_carta;
    }
}
// Função para inserir carta na mão
void inserirCartaMao(Carta **minha_mao, Carta *nova_carta) {
    if (*minha_mao == NULL) {
        *minha_mao = nova_carta;
    } else {
        Carta *temp = *minha_mao;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = nova_carta;
    }
}
// Função para verificar se uma carta já existe no deck
int cartaExiste(Carta *deck, int id) {
    Carta *temp = deck;
    int count = 0;
    while (temp != NULL) {
        if (temp->id == id) {
            count++;
        }
        temp = temp->prox;
    }
    return count;
}
// Função para remover uma carta do deck pelo ID
void removerCartaDeck(Carta **deck, int id) {
    Carta *atual = *deck;
    Carta *anterior = NULL;
    // Verifica se a carta a ser removida é a primeira da lista
    if (atual != NULL && atual->id == id) {
        *deck = atual->prox;
        free(atual);
        printf("Carta removida com sucesso!\n");
        return;
    }
    // Procura a carta a ser removida na lista
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }
    // Se o ID não foi encontrado na lista
    if (atual == NULL) {
        printf("Carta com ID %d nao encontrada no deck.\n", id);
        return;
    }
    // Remove a carta da lista
    anterior->prox = atual->prox;
    free(atual);
    printf("Carta removida com sucesso!\n");
}
void removerCartaMao(Carta **minha_mao, int id) {
    Carta *atual = *minha_mao;
    Carta *anterior = NULL;
    // Verifica se a carta a ser removida é a primeira da lista
    if (atual != NULL && atual->id == id) {
        *minha_mao = atual->prox;
        free(atual);
        return;
    }
    // Procura a carta a ser removida na lista
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }
    // Se o ID não foi encontrado na lista
    if (atual == NULL) {
        printf("Carta com ID %d nao encontrada na mao.\n", id);
        return;
    }
    // Remove a carta da lista
    anterior->prox = atual->prox;
    free(atual);
    printf ("Carta %d jogada", id);
}
// Função para exibir os detalhes de uma carta
void exibirDetalhesCarta(Carta *carta) {
    printf("\n-----------------------------------\n");
    printf("ID: %d\n", carta->id);
    printf("Nome: %s\n", carta->nome);
    printf("Evolucao: %s\n", carta->evolucao);
    printf("Pontos de Saude: %d\n", carta->pontos_saude);
    printf("Elemento: %s\n\n", carta->elemento);
    printf("Habilidade: %s\n", carta->habilidade);
    printf("Descricao da Habilidade: %s\n", carta->descricao_habilidade);
    printf("Custo da Habilidade: %d\n\n", carta->custo_habilidade);
    printf("Fraqueza: %s\n", carta->fraqueza);
    printf("Resistencia: %s\n", carta->resistencia);
    printf("Autor: %s\n", carta->autor);
    printf("Descricao do Autor: %s\n", carta->descricao_autor);
    printf("\n-----------------------------------\n");
}
// Função para exibir o resumo de uma carta
void exibirCartaResumo(Carta *carta) {
    printf("\n-----------------------------------\n");
    printf("ID: %d\n", carta->id);
    printf("Nome: %s\n", carta->nome);
    printf("Pontos de Saude: %d\n", carta->pontos_saude);
    printf("Elemento: %s\n\n", carta->elemento);
    printf("Habilidade: %s\n", carta->habilidade);
    printf("Descricao da Habilidade: %s\n", carta->descricao_habilidade);
    printf("Fraqueza: %s\n", carta->fraqueza);
    printf("Resistencia: %s\n", carta->resistencia);
    printf("\n-----------------------------------\n");
}
// Função para simular a compra de cartas
void comprarCartas(Carta **deck, int quantidade, Carta **minha_mao) {
    printf("\nComprando %d carta(s):\n", quantidade);
    // Criar um deck secundário
    Carta *deck_secundario = NULL;
    Carta *temp = *deck;
    while (temp != NULL) {
        inserirCarta(&deck_secundario, criarCarta(temp->id, temp->nome, temp->evolucao, temp->pontos_saude, temp->elemento, temp->habilidade, temp->descricao_habilidade, temp->custo_habilidade, temp->fraqueza, temp->resistencia, temp->autor, temp->descricao_autor));
        temp = temp->prox;
    }
    for (int i = 0; i < quantidade; i++) {
        // Verifica se o deck está vazio
        if (deck_secundario == NULL) {
            printf("O deck está vazio!\n");
            return;
        }
        // Conta o tamanho do deck
        int tamanho = 0;
        temp = deck_secundario;
        while (temp != NULL) {
            tamanho++;
            temp = temp->prox;
        }
        // Escolhe uma posição aleatória para a carta
        int posicao = rand() % tamanho;
        // Encontra a carta na posição escolhida
        Carta *anterior = NULL;
        temp = deck_secundario;
        for (int j = 0; j < posicao; j++) {
            anterior = temp;
            temp = temp->prox;
        }
        // Exibe a carta comprada
        exibirCartaResumo(temp);
        // Adiciona a carta à lista minha_mao
        inserirCartaMao(minha_mao, criarCarta(temp->id, temp->nome, temp->evolucao, temp->pontos_saude, temp->elemento, temp->habilidade, temp->descricao_habilidade, temp->custo_habilidade, temp->fraqueza, temp->resistencia, temp->autor, temp->descricao_autor));
        // Remove a carta do deck
        if (anterior == NULL) {
            deck_secundario = temp->prox;
        } else {
            anterior->prox = temp->prox;
        }
        free(temp);
    }
}
// Função para liberar a memória alocada para o deck
void liberarDeck(Carta *deck) {
    Carta *temp;
    while (deck != NULL) {
        temp = deck;
        deck = deck->prox;
        free(temp);
    }
}
// Função para exibir o menu de opções
int menu() {
    int opcao;
    printf("\n-------------------------------\n");
    printf("\nMenu:\n");
    printf("1. Verificar cartas no Deck\n");
    printf("2. Mostrar detalhes de uma carta\n");
    printf("3. Editar Deck\n");
    printf("4. Simular Partida\n");
    printf("0. Sair\n");
    printf("\n-------------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
// Função para exibir as cartas no deck e o ID
void exibirCartasDeck(Carta *deck) {
    printf("\nCartas do Deck:\n");
    Carta *temp = deck;
    while (temp != NULL) {
        printf("ID da Carta %d - %s\n", temp->id, temp->nome);
        temp = temp->prox;
    }
}
void exibirCartasMao(Carta *minha_mao) {
    printf("\nCartas da Mao:\n");
    Carta *temp = minha_mao;
    while (temp != NULL) {
        printf("ID da Carta %d - %s\n", temp->id, temp->nome);
        temp = temp->prox;
    }
}
void exibirCartasLista(Carta *lista_cartas) {
    printf("\nLista de Cartas:\n");
    Carta *temp = lista_cartas;
    while (temp != NULL) {
        printf("ID da Carta %d - %s\n", temp->id, temp->nome);
        temp = temp->prox;
    }
}
void exibirMinhaMao(Carta *minha_mao) {
    if (minha_mao == NULL) {
        printf("\nSua mao esta vazia!\n");
        return;
    }
    printf("\nSua mao:\n");
    exibirCartasMao (minha_mao); 
    }
//busca uma carta no deck
void buscarCarta(Carta *lista_cartas, int id) {
    Carta *temp = lista_cartas;
    while (temp != NULL) {
        if (temp->id == id) {
            exibirDetalhesCarta(temp);
            return;
        }
        temp = temp->prox;
    }
    printf("Carta com ID %d nao encontrada no deck.\n", id);
}
void definirCartaTemp (Carta *deck){
    Carta *temp = deck;
}
// Função principal
int main() {
    // Lista da mão
    Carta *minha_mao = NULL;
    FilaCartas *fila = criarFila();
     // Lista pré-determinada de cartas
    Carta *lista_cartas = NULL;
    lista_cartas = criarCarta(1, "Ho-Oh", "", 130, "Fogo", "Rajada de Fogo", "Causa 120 de dano", 3, "Eletrico", "terra", "Ash Ketchum", "O treinador mais famoso de Kanto");
        inserirCarta(&lista_cartas, criarCarta(2, "Reshiram", "", 130, "Fogo", "Chama Negra", "Causa 80 de dano", 3, "Agua", "", "", "um pokemon lendario sem dono, livre "));
        inserirCarta(&lista_cartas, criarCarta(3, "Kyogre", "", 130, "Agua", "Surfar", "Causa 120 de dano", 3, "Eletrico", "", "Archie", "parte e chefe da equipe aqua"));
        inserirCarta(&lista_cartas, criarCarta(4, "Palkia", "", 130, "Agua", "Golpe exaustivo", "Causa 80 de dano", 3, "eletrico", "", " Cyrus", "O lider da equipe galactia"));
        inserirCarta(&lista_cartas, criarCarta(5, "Pikachu", "Raichu", 60, "eletrico", "Choque do trovao", "causa 30 de dano", 2, "terra", "", "Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(6, "Pikachu voador", "Raichu", 190, "eletrico", "trovoada de choques", "Causa 120 de dano", 3, "eletrico", "terra", "Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(7, "Pikachu surfista", "Raichu", 200, "eletrico", "surfar", "causa 150 de dano", 3, "terra", "","Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(8, "Zekrom", "", 130, "eletrico", "Trovao branco", "Causa 80 de dano", 3, "terra", "", "N", "N é um lider da equipe plasma"));
        inserirCarta(&lista_cartas, criarCarta(9, "Mew", "", 60, " Psíquico", "tiro  Psíquico", "causa 30 de dano", 2, "Sombrio", "terra", "selvagem", "um pokemon misterioso"));
        inserirCarta(&lista_cartas, criarCarta(10, "Xerneas", "", 120, " Psíquico", "chifres da Aurora", "causa 100 de dano", 3, "metal", "", "", "ser mistico e defensor da natureza"));
        inserirCarta(&lista_cartas, criarCarta(11, "Cosmog", "Cosmoem", 60, " Psíquico", "Protecao estelar", "evita danos causados pelo oponente", 1, "sombrio", "terra", "Melanie", "uma garotinha doce"));
        inserirCarta(&lista_cartas, criarCarta(12, "Cosmoem", "Lunala/Solgaleo", 90, " Psíquico", "Protecao estelar", "evita danos causados pelo oponente", 1, "sombrio", "terra", "Melanie", "uma garotinha doce"));
        inserirCarta(&lista_cartas, criarCarta(13, "Lunala", "", 160, " Psíquico", "Dor lunar", "duplica o dano causado no oponente", 2, "sombrio", "terra", "Melanie", "uma garotinha doce"));
        inserirCarta(&lista_cartas, criarCarta(14, "Zacian", "", 220, " Psíquico", "Talho Tempestuoso", "Causa 60 de dano", 3, "metal", "", "Iris", "a lider de ginasio"));
        inserirCarta(&lista_cartas, criarCarta(15, "Groudon", "", 130, "Terra", "Vulcao Magma", "Causa 80 de dano", 3, "Planta", "", "Archie", "lider da equipe magma"));
        inserirCarta(&lista_cartas, criarCarta(16, "Zamazenta", "", 220, "Terra", "Impacto Pesado", "Causa 150 de dano", 3, "psiquico", "", "", "protetor da regiao de Galar"));
        inserirCarta(&lista_cartas, criarCarta(17, "Yveltal", "", 120, "sombrio", "Pena Sombria", "Causa 100 de dano", 3, "eletrico", "Terra", "", "Conhecido pela destruicao e morte"));
        inserirCarta(&lista_cartas, criarCarta(18, "Dialga", "", 130, "Metal", "Reversao Temporal", "Compre 1 Carta", 1, "Fogo", "Planta", "", "controlador do tempo e protetor do temporal"));
        inserirCarta(&lista_cartas, criarCarta(19, "Solgaleo", "", 170, "Metal", "Geiser Solar", "Causa 100 de dano",2, "Fogo", "Planta", "", "Associado ao Sol"));
        inserirCarta(&lista_cartas, criarCarta(20, "Lugia", "", 130, "Normal", "Aerobola", "Causa 20 de dano", 2, "eletrico", "Terra", "", "o guardiao dos mares"));
        inserirCarta(&lista_cartas, criarCarta(21, "Blastoise", "", 100, "agua", "Jato d'agua", "Cauusa 40 de dano", 3, "eletrico", "","Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(22, "Charizard", "", 120, "Fogo", "Chama fuuracao", "causa 100 de dano", 4, "agua", "Terra", "Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(23, "Claydol", "", 80, "Terra", "Ataque giratorio", "causa 40 de dano", 2, "Planta", "", "Professor Carvalho", "o melhor pesquisador pokemon"));
        inserirCarta(&lista_cartas, criarCarta(24, "Venusaur", "", 100, "Normal", "Raio de Sol", "Causa 60 de dano", 4, "Fogo", "", "Ash Ketchum", "O treinador mais famoso de Kanto"));
        inserirCarta(&lista_cartas, criarCarta(25, "Gyarados", "", 70, "agua", "Raio congelante", "Causa 30 de dano e atordoa o oponente", 3, "Planta", "Terra", "James", "membro da temida equipe Rocket"));
    Carta *deck = NULL;
    Carta *temp = lista_cartas;
    int id, op_simula, opcao, tamanho_deck = 0;
    // Opção para criar um deck
    do {
        printf("\nBem vindo ao Deck Builder!\n");
        printf("\n-------------------------------\n");
        printf("1. Criar um Deck com 25 cartas\n");
        printf("0. Sair\n");
        printf("\n-------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("\nEscolha as cartas para o seu deck (insira o ID da carta):\n");
                while (temp != NULL && tamanho_deck < 25) {
                    if (cartaExiste(deck, temp->id) < 4) {
                        printf("%d. %s\n", temp->id, temp->nome);
                    }
                    temp = temp->prox;
                }
                printf("\n-------------------------------\n");
                printf("\n99. Remover carta do Deck\n");
                printf("\n100. Visualizar deck\n");
                printf("\n101. Detalhar carta\n\n");
                printf("\n-------------------------------\n");
                int id_carta;
                do {
                    printf("Insira o ID da carta: ");
                    scanf("%d", &id_carta);
                    if (id_carta == 0) {
                        break;
                    }
                    if (id_carta == 99){
                        exibirCartasDeck (deck);
                        printf ("\n");
                        printf ("Digite a carta que deseja retirar do deck:\n");
                        scanf ("%d", &id);
                        removerCartaDeck (&deck, id);
                        tamanho_deck--;
                        printf ("\n");
                        exibirCartasDeck (deck);
                        printf ("\n\n");
                    }
                    if (id_carta == 100 && tamanho_deck != 0){
                        exibirCartasDeck (deck);
                    } 
                    if (id_carta == 100 && tamanho_deck == 0){
                        printf ("\nDeck esta vazio\n");
                    }
                    if (id_carta == 101){
                    printf("\nDigite o ID da carta que deseja ver: ");
                    scanf("%d", &id);
                    buscarCarta(lista_cartas, id);
                    }
                        //verifica se já existem 4 cartas com o mesmo ID no deck
                    if (cartaExiste(deck, id_carta) >= 4) {
                        printf("Voce ja possui 4 cartas dessa no deck.\n");
                    }
                    // adiciona a carta na lista - limitado a 25 cartas no deck
                    else {
                        temp = lista_cartas;
                        while (temp != NULL) {
                            if (temp->id == id_carta) {
                                inserirCarta(&deck, criarCarta(temp->id, temp->nome, temp->evolucao, temp->pontos_saude, temp->elemento, temp->habilidade, temp->descricao_habilidade, temp->custo_habilidade, temp->fraqueza, temp->resistencia, temp->autor, temp->descricao_autor));
                                tamanho_deck++;
                                break;
                            }
                            temp = temp->prox;
                        }
                    }
                while (getchar() != '\n'); // Limpa o buffer de entrada
                } while (tamanho_deck < 25);
                break;
            case 0:
            printf ("\nFechando programa...\n");
            liberarDeck(deck);
            return 0;
            default:
                printf("\nOpcao invalida.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
        }
        if (opcao == 1) {
            break;
        }
    } while (tamanho_deck <= 25);
    do {
        printf ("\n\n");
        opcao = menu();
        switch (opcao) {
            case 1:
                exibirCartasDeck(deck);
                break;
            //editar deck
            case 3:
            do {
                printf("\nEscolha as cartas para o seu deck (insira o ID da carta):\n");
                exibirCartasLista (lista_cartas);
                while (temp != NULL && tamanho_deck < 25) {
                    temp = temp->prox;
                }
                printf("\n-------------------------------\n");
                printf("\n99. Remover carta do Deck\n");
                printf("\n100. Visualizar deck\n");
                printf("\n101. Detalhar carta\n\n");
                printf("\n-------------------------------\n");
                int id_carta;
                do {
                    printf("Insira o ID da carta: ");
                    scanf("%d", &id_carta);
                    if (id_carta == 0) {
                        break;
                    }
                    if (id_carta == 99){
                        exibirCartasDeck (deck);
                        printf ("\n");
                        printf ("Digite a carta que deseja retirar do deck:\n");
                        scanf ("%d", &id);
                        removerCartaDeck (&deck, id);
                        tamanho_deck--;
                        printf ("\n");
                        exibirCartasDeck (deck);
                        printf ("\n\n");
                    }
                    if (id_carta == 100 && tamanho_deck != 0){
                        exibirCartasDeck (deck);
                    } 
                    if (id_carta == 100 && tamanho_deck == 0){
                        printf ("\nDeck esta vazio\n");
                    }
                        //verifica se já existem 4 cartas com o mesmo ID no deck
                    if (cartaExiste(deck, id_carta) >= 4) {
                        printf("Voce ja possui 4 cartas dessa no deck.\n");
                    }
                    // adiciona a carta na lista - limitado a 25 cartas no deck
                    else {
                        temp = lista_cartas;
                        while (temp != NULL) {
                            if (temp->id == id_carta) {
                                inserirCarta(&deck, criarCarta(temp->id, temp->nome, temp->evolucao, temp->pontos_saude, temp->elemento, temp->habilidade, temp->descricao_habilidade, temp->custo_habilidade, temp->fraqueza, temp->resistencia, temp->autor, temp->descricao_autor));
                                tamanho_deck++;
                                break;
                            }
                            temp = temp->prox;
                        }
                    }
                while (getchar() != '\n'); // Limpa o buffer de entrada
                } while (tamanho_deck < 25);
                break;
        if (opcao == 1) {
            break;
        }
        } while (tamanho_deck <= 25);
        break;
            case 4:
                    printf("\n-------------------------------");
                    printf("\nSimulando Turno!\n");
                    printf("\nRealizando a compra inicial\n");
                    printf("\n-------------------------------\n");
                    //realiza a compra de cartas inicial
                    comprarCartas(&deck, 7, &minha_mao);
                do{
                    printf("\n-------------------------------");
                    printf("\nMenu de Simulacao\n");
                    printf("\n-------------------------------");
                    printf("\n1.Jogar Card");
                    printf("\n2.Visualizar mao");
                    printf("\n3.Detalhar carta");
                    printf("\n0.Finalizar Jogada\n");
                    printf("\n-------------------------------");
                    printf("\nEscolha uma opcao:\n");
                    scanf ("%d", &op_simula);
                    printf("\n-------------------------------");
                    if (op_simula == 1)   {
                        printf ("\nEscolha o card que deseja jogar:\n");
                        scanf ("%d", &id);
                        FilaCartas* criarFila();
                        Carta *temp = minha_mao;
                        while (temp != NULL) {
                            if (temp->id == id) {
                            enfileirar (fila, temp);
                            removerCartaMao (&minha_mao, id);
                            printf ("\n\n");
                            mostrarFila (fila);
                            break;
                            }
                            temp = temp->prox;
                           }
                    }  
                    if (op_simula == 2)   {
                        exibirMinhaMao (minha_mao);
                    }  
                    if (op_simula == 3)   {
                        printf("\nDigite o ID da carta que deseja ver: ");
                        scanf("%d", &id);
                        buscarCarta (lista_cartas, id);
                    }
                    if (op_simula == 0)   {
                        printf ("\nResolvendo fila de acoes:");
                        printf("\n-------------------------------");
                        while (fila->inicio!= NULL){
                        mostrarProximaCartaFila (fila);
                        printf ("\n");
                        desenfileirar (fila);
                        }
                    }              
                } while (op_simula != 0);
                break;
            case 2:
                printf("\nDigite o ID da carta que deseja ver: ");
                scanf("%d", &id);
                buscarCarta(lista_cartas, id);
                break;
               
                if (temp == NULL) {
                    printf("Carta nao encontrada no deck.\n");
                }
                break;
            case 0:
                printf("\nSaindo do programa.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    } while (opcao != 0);
    liberarDeck(deck);
    free (fila);
    return 0;
}
