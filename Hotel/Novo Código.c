#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUARTOS 5
#define MAX_NOME 50

// Estrutura para representar um hóspede
typedef struct {
    char nome[MAX_NOME];
    int quarto;
} Hospede;

// Variável global para armazenar os hóspedes
Hospede hospedes[MAX_QUARTOS];
int numHospedes = 0;

// Função para carregar os dados dos hóspedes de um arquivo
void carregarHospedesDoArquivo() {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "Quarto %d: %[^\n]", &hospedes[numHospedes].quarto, hospedes[numHospedes].nome);
        numHospedes++;
    }

    fclose(arquivo);
    printf("Dados dos hospedes carregados do arquivo com sucesso.\n");
}

// Função para inserir um hóspede em um quarto vazio
void inserirHospede() {
    int num_quarto;
    if (numHospedes < MAX_QUARTOS) {
        printf("Digite o nome do hospede: ");
        scanf("%s", hospedes[numHospedes].nome);
        printf("Digite o número do quarto: ");
        scanf("%d", &num_quarto);
        hospedes[numHospedes].quarto = num_quarto;
        numHospedes++;
        printf("Hospede inserido com sucesso em um quarto vazio %d.\n", numHospedes);
    } else {
        printf("Nao ha quartos disponiveis.\n");
    }
}

// Função para listar hóspedes em ordem alfabética
void listarHospedes() {
    if (numHospedes == 0) {
        printf("Nenhum hospede registrado.\n");
        return;
    }
    
    Hospede temp;
    for (int i = 0; i < numHospedes - 1; i++) {
        for (int j = i + 1; j < numHospedes; j++) {
            if (strcmp(hospedes[i].nome, hospedes[j].nome) > 0) {
                temp = hospedes[i];
                hospedes[i] = hospedes[j];
                hospedes[j] = temp;
            }
        }
    }
    
    printf("Hospedes registrados em ordem alfabetica:\n");
    for (int i = 0; i < numHospedes; i++) {
        printf("Quarto %d: %s\n", hospedes[i].quarto, hospedes[i].nome);
    }
}

// Função para buscar um hóspede pelo nome
void buscarHospede() {
    char nomeBusca[MAX_NOME];
    printf("Digite o nome do hospede: ");
    scanf("%s", nomeBusca);
    
    for (int i = 0; i < numHospedes; i++) {
        if (strcmp(hospedes[i].nome, nomeBusca) == 0) {
            printf("Hospede esta no quarto %d.\n", hospedes[i].quarto);
            return;
        }
    }
    
    printf("Hospede nao encontrado.\n");
}

// Função para editar os dados de um hóspede
void editarHospede() {
    char nomeEdit[MAX_NOME];
    printf("Digite o nome do hospede a ser editado: ");
    scanf("%s", nomeEdit);
    
    for (int i = 0; i < numHospedes; i++) {
        if (strcmp(hospedes[i].nome, nomeEdit) == 0) {
            printf("Digite o novo nome do hospede: ");
            scanf("%s", hospedes[i].nome);
            printf("Dados do hospede atualizados.\n");
            return;
        }
    }
    
    printf("Hospede nao encontrado.\n");
}

// Função para liberar um quarto
void liberarQuarto() {
    int numQuarto;
    printf("Digite o numero do quarto a ser liberado: ");
    scanf("%d", &numQuarto);
    

    for (int i = 0; i < numHospedes; i++) {
        printf("Quarto %d \n", hospedes[i].quarto );
        if (hospedes[i].quarto == numQuarto) {

            for (int j = i; j < numHospedes - 1; j++) {
                hospedes[j] = hospedes[j + 1];
            }
            i--;

            numHospedes--;
            printf("Quarto %d liberado.\n", numQuarto);
        }
    }
    
    printf("Quarto nao encontrado ou ja esta vazio.\n");
}

// Função para mostrar os números dos quartos vazios
void mostrarQuartosVazios() {
    printf("Quartos vazios:\n");
    for (int i = 0; i < MAX_QUARTOS; i++) {
        int ocupado = 0;
        for (int j = 0; j < numHospedes; j++) {
            if (hospedes[j].quarto == i + 1) {
                ocupado = 1;
                break;
            }
        }
        if (!ocupado) {
            printf("%d\n", i + 1);
        }
    }
}

// Função para salvar a lista de hóspedes em um arquivo
void salvarLista() {
    FILE *arquivo;
    arquivo = fopen("hospedes.txt", "w");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    for (int i = 0; i < numHospedes; i++) {
        fprintf(arquivo, "Quarto %d: %s\n", hospedes[i].quarto, hospedes[i].nome);
    }
    
    fclose(arquivo);
    printf("Lista de hospedes salva com sucesso no arquivo 'hospedes.txt'.\n");
}

// Função principal
int main() {
    carregarHospedesDoArquivo();
    int opcao;
    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir hospede\n");
        printf("2. Listar hospedes (ordem alfabetica)\n");
        printf("3. Buscar hospede\n");
        printf("4. Editar hospede\n");
        printf("5. Liberar um quarto\n");
        printf("6. Mostrar os quartos vazios\n");
        printf("7. Salvar\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirHospede();
                break;
            case 2:
                listarHospedes();
                break;
            case 3:
                buscarHospede();
                break;
            case 4:
                editarHospede();
                break;
            case 5:
                liberarQuarto();
                break;
            case 6:
                mostrarQuartosVazios();
                break;
            case 7:
                salvarLista();
                break;
            case 0:
                printf("Encerrando\n");
                break;
            default:
                printf("Acao invalida\n");
                break;
        }
    } while (opcao != 0);
    
    return 0;
}
