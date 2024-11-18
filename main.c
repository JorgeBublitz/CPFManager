#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 100
#define MAX_ENDERECO 150
#define MAX_TELEFONE 15
#define MAX_CPF 12

// Definindo a estrutura do No da Arvore AVL
typedef struct Nodo {
    char cpf[MAX_CPF];
    char nome[MAX_NOME];
    char nascimento[11];
    char endereco[MAX_ENDERECO];
    char telefone[MAX_TELEFONE];
    struct Nodo *esquerda;
    struct Nodo *direita;
    int altura;
} Nodo;

typedef struct {
    Nodo *raiz;
} ArvoreAVL;

// Funcão para calcular a altura de um No
int altura(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

// Função para calcular o fator de balanceamento de um No
int fator_balanceamento(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->esquerda) - altura(nodo->direita);
}

// Função para realizar a rotação a direita
Nodo *rotacao_direita(Nodo *y) {
    Nodo *x = y->esquerda;
    Nodo *T2 = x->direita;
    
    x->direita = y;
    y->esquerda = T2;
    
    y->altura = (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita)) + 1;
    x->altura = (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita)) + 1;
    
    return x;
}

// Função para realizar a rotação a esquerda
Nodo *rotacao_esquerda(Nodo *x) {
    Nodo *y = x->direita;
    Nodo *T2 = y->esquerda;
    
    y->esquerda = x;
    x->direita = T2;
    
    x->altura = (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita)) + 1;
    y->altura = (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita)) + 1;
    
    return y;
}

// Função para inserir um novo No na Arvore AVL
Nodo *inserir(Nodo *raiz, char cpf[], char nome[], char nascimento[], char endereco[], char telefone[]) {
    if (raiz == NULL) {
        Nodo *novo_nodo = (Nodo *)malloc(sizeof(Nodo));
        strcpy(novo_nodo->cpf, cpf);
        strcpy(novo_nodo->nome, nome);
        strcpy(novo_nodo->nascimento, nascimento);
        strcpy(novo_nodo->endereco, endereco);
        strcpy(novo_nodo->telefone, telefone);
        novo_nodo->esquerda = NULL;
        novo_nodo->direita = NULL;
        novo_nodo->altura = 1;
        return novo_nodo;
    }

    if (strcmp(cpf, raiz->cpf) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, cpf, nome, nascimento, endereco, telefone);
    } else if (strcmp(cpf, raiz->cpf) > 0) {
        raiz->direita = inserir(raiz->direita, cpf, nome, nascimento, endereco, telefone);
    } else {
        return raiz; // CPF ja existe, nao insere
    }

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    int balance = fator_balanceamento(raiz);

    if (balance > 1 && strcmp(cpf, raiz->esquerda->cpf) < 0) {
        return rotacao_direita(raiz);
    }

    if (balance < -1 && strcmp(cpf, raiz->direita->cpf) > 0) {
        return rotacao_esquerda(raiz);
    }

    if (balance > 1 && strcmp(cpf, raiz->esquerda->cpf) > 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    if (balance < -1 && strcmp(cpf, raiz->direita->cpf) < 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

// Função para procurar um CPF na Arvore
Nodo *buscar(Nodo *raiz, char cpf[]) {
    if (raiz == NULL || strcmp(raiz->cpf, cpf) == 0) {
        return raiz;
    }
    if (strcmp(cpf, raiz->cpf) < 0) {
        return buscar(raiz->esquerda, cpf);
    }
    return buscar(raiz->direita, cpf);
}

// Função para exibir todos os registros em ordem
void listar(Nodo *raiz) {
    if (raiz != NULL) {
        listar(raiz->esquerda);
        printf("  |     CPF: %s\n  |        Nome: %s\n  |        Nascimento: %s\n  |        Endereco: %s\n  |        Telefone: %s\n  |\n",
               raiz->cpf, raiz->nome, raiz->nascimento, raiz->endereco, raiz->telefone);
        listar(raiz->direita);
    }
}

// Função para validar o CPF (apenas checando o formato e se possui 11 digitos)
int validar_cpf(char cpf[]) {
    int i;
	if (strlen(cpf) != 11) return 0;
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para atualizar um registro
void atualizar(Nodo *raiz, char cpf[], char nome[], char nascimento[], char endereco[], char telefone[]) {
    Nodo *registro = buscar(raiz, cpf);
    if (registro != NULL) {
        if (strlen(nome) > 0) strcpy(registro->nome, nome);
        if (strlen(nascimento) > 0) strcpy(registro->nascimento, nascimento);
        if (strlen(endereco) > 0) strcpy(registro->endereco, endereco);
        if (strlen(telefone) > 0) strcpy(registro->telefone, telefone);
        printf("  |     Registro atualizado com sucesso!\n");
    } else {
        printf("  |     CPF nÃ£o encontrado!\n");
    }
}

// Função para remover um registro da Arvore
Nodo *remover(Nodo *raiz, char cpf[]) {
    if (raiz == NULL) return raiz;
    
    if (strcmp(cpf, raiz->cpf) < 0) {
        raiz->esquerda = remover(raiz->esquerda, cpf);
    } else if (strcmp(cpf, raiz->cpf) > 0) {
        raiz->direita = remover(raiz->direita, cpf);
    } else {
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            Nodo *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            Nodo *temp = raiz->direita;
            while (temp && temp->esquerda != NULL) temp = temp->esquerda;
            strcpy(raiz->cpf, temp->cpf);
            raiz->direita = remover(raiz->direita, temp->cpf);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    int balance = fator_balanceamento(raiz);

    if (balance > 1 && fator_balanceamento(raiz->esquerda) >= 0) {
        return rotacao_direita(raiz);
    }

    if (balance < -1 && fator_balanceamento(raiz->direita) <= 0) {
        return rotacao_esquerda(raiz);
    }

    if (balance > 1 && fator_balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    if (balance < -1 && fator_balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

// Função para exportar os dados para um arquivo de texto
void exportar_dados(Nodo *raiz, FILE *arquivo) {
    if (raiz != NULL) {
        exportar_dados(raiz->esquerda, arquivo);
        fprintf(arquivo, "CPF: %s |   Nome: %s |  Nascimento: %s |  Endereco: %s |  Telefone: %s\n",
                raiz->cpf, raiz->nome, raiz->nascimento, raiz->endereco, raiz->telefone);
        exportar_dados(raiz->direita, arquivo);
    }
}

// Função principal que exibe o menu e executa as operaÃ§Ãµes
int main() {
    ArvoreAVL arvore;
    arvore.raiz = NULL;

    int opcao;
    char cpf[MAX_CPF], nome[MAX_NOME], nascimento[11], endereco[MAX_ENDERECO], telefone[MAX_TELEFONE];
    
    do {
        printf("\n  ===========================================\n");
        printf("  |            Menu de Operacoes:           |\n");
        printf("  ===========================================\n");
        printf("  |         1. Inserir Registro             |\n");
        printf("  |         2. Buscar Registro              |\n");
        printf("  |         3. Atualizar Registro           |\n");
        printf("  |         4. Remover Registro             |\n");
        printf("  |         5. Listar Todos os Registros    |\n");
        printf("  |         6. Exportar Dados para Arquivo  |\n");
        printf("  |         7. Sair                         |\n");
        printf("  ===========================================\n");
        printf("  |         Escolha uma Opcao:              |");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n  ===========================================\n");
                printf("  |                  Inserir:               |\n");
                printf("  ===========================================\n");
                printf("\n  |         Digite o CPF: ");
                scanf("%s", cpf);
                if (!validar_cpf(cpf)) {
                    printf("  |  CPF invalido! Deve ter 11 digitos numericos.\n");
                    break;
                }
                printf("  |            Digite o nome: ");
                getchar(); // Limpar o buffer de linha anterior
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remover o \n extra do fgets
                printf("  |    Digite a data de nascimento (DD/MM/AAAA): ");
                scanf("%s", nascimento);
                printf("  |    Digite o Endereco: ");
                getchar();
                fgets(endereco, MAX_ENDERECO, stdin);
                endereco[strcspn(endereco, "\n")] = '\0';
                printf("  |    Digite o telefone: ");
                scanf("%s", telefone);
                
                arvore.raiz = inserir(arvore.raiz, cpf, nome, nascimento, endereco, telefone);
                break;
            case 2:
                printf("\n  ===========================================\n");
                printf("  |                  Buscar:               |\n");
                printf("  ===========================================\n");
                printf("\n  |   Digite o CPF para buscar: ");
                scanf("%s", cpf);
                Nodo *registro = buscar(arvore.raiz, cpf);
                if (registro != NULL) {
                     printf("  ===========================================\n");
                    printf("  |           Registro encontrado:          |\n");
                    printf("  |           CPF: %s\n  |           Nome: %s\n  |           Nascimento: %s\n  |           Endereco: %s\n  |           Telefone: %s       \n",registro->cpf, registro->nome, registro->nascimento, registro->endereco, registro->telefone);
                    printf("  ===========================================\n");
                    
                } else {
                     printf("  ===========================================\n");
                    printf("  |           Registro nao encontrado.      |\n");
                    printf("  ===========================================\n");
                }
                break;
            case 3:
                printf("\n  ===========================================\n");
                printf("  |                  Editar:                |\n");
                printf("  ===========================================\n");
                printf("\n  |           Digite o CPF para atualizar: ");
                scanf("%s", cpf);
                printf("  |     Digite o novo nome (deixe em branco para nao alterar): ");
                getchar();
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("  |     Digite a nova data de nascimento (deixe em branco para nao alterar): ");
                fgets(nascimento, 11, stdin);
                nascimento[strcspn(nascimento, "\n")] = '\0';
                printf("  |     Digite o novo Endereco (deixe em branco para nao alterar): ");
                fgets(endereco, MAX_ENDERECO, stdin);
                endereco[strcspn(endereco, "\n")] = '\0';
                printf("  |     Digite o novo telefone (deixe em branco para nao alterar): ");
                fgets(telefone, MAX_TELEFONE, stdin);
                telefone[strcspn(telefone, "\n")] = '\0';
                                
                atualizar(arvore.raiz, cpf, nome, nascimento, endereco, telefone);
                break;
            case 4:
                printf("\n  ===========================================\n");
                printf("  |                  Remover:               |\n");
                printf("  ===========================================\n");
                printf("\n  |     Digite o CPF para remover: ");
                scanf("%s", cpf);
                arvore.raiz = remover(arvore.raiz, cpf);
                 printf("\n===========================================\n");
                printf("  |          Registro removido              |\n");
                printf("  ===========================================\n");
                break;
            case 5:
                printf("\n  ===========================================\n");
                printf("  |          Listar:                        |\n");
                printf("  ===========================================\n");
                
                listar(arvore.raiz);
                break;
            case 6:
                {
                    FILE *arquivo = fopen("dados.txt", "w");
                    if (arquivo == NULL) {
                        printf("  |     Erro ao abrir o arquivo!\n");
                        break;
                    }
                    exportar_dados(arvore.raiz, arquivo);
                    fclose(arquivo);
                    printf("  |     Dados exportados para dados.txt\n");
                }
                break;
            case 7:
                printf("  ===========================================\n");
                printf("  |     Saindo do sistema..\n");
                printf("  ===========================================\n");
                break;
            default:
                printf("  |     Opcao invalida!\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
