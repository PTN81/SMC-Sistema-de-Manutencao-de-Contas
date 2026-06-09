#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numeroConta;     
    char nome[50];        
    double saldo;         
} Cliente;

#define TAMANHO_REGISTRO sizeof(Cliente)
#define ARQUIVO "contas.dat"

void inicializarArquivo() {
    FILE *ptr = fopen(ARQUIVO, "rb");
    if (ptr == NULL) {
        ptr = fopen(ARQUIVO, "wb");
        if (ptr != NULL) fclose(ptr);
    } else {
        fclose(ptr);
    }
}

void cadastrarCliente() {
    FILE *ptr = fopen(ARQUIVO, "r+b");
    if (ptr == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int posicao;
    printf("Digite a posição (a partir de 0) para cadastrar: ");
    scanf("%d%*c", &posicao);

    if (posicao < 0) {
        printf("Posição inválida.\n");
        fclose(ptr);
        return;
    }

    fseek(ptr, posicao * TAMANHO_REGISTRO, SEEK_SET);

    Cliente c;
    printf("Digite o número da conta: ");
    scanf("%d%*c", &c.numeroConta);
    printf("Digite o nome: ");
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0; 
    printf("Digite o saldo inicial: ");
    scanf("%lf%*c", &c.saldo);

    fwrite(&c, TAMANHO_REGISTRO, 1, ptr);
    printf("Cliente cadastrado na posição %d.\n", posicao);

    fclose(ptr);
}

void consultarCliente() {
    FILE *ptr = fopen(ARQUIVO, "rb");
    if (ptr == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    int numeroConta;
    printf("Digite o número da conta: ");
    scanf("%d%*c", &numeroConta);

    Cliente c;
    int encontrado = 0;
    while (fread(&c, TAMANHO_REGISTRO, 1, ptr) == 1) {
        if (c.numeroConta == numeroConta && c.numeroConta != 0) {
            printf("Cliente encontrado:\n");
            printf("Conta: %d\n", c.numeroConta);
            printf("Nome: %s\n", c.nome);
            printf("Saldo: %.2f\n", c.saldo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }

    fclose(ptr);
}

void atualizarSaldo() {
    FILE *ptr = fopen(ARQUIVO, "r+b");
    if (ptr == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    int numeroConta;
    printf("Digite o número da conta: ");
    scanf("%d%*c", &numeroConta);

    Cliente c;
    long pos = 0;
    int encontrado = 0;

    while (fread(&c, TAMANHO_REGISTRO, 1, ptr) == 1) {
        if (c.numeroConta == numeroConta && c.numeroConta != 0) {
            encontrado = 1;
            break;
        }
        pos = ftell(ptr);
    }

    if (encontrado) {
        double novoSaldo;
        printf("Saldo atual: %.2f\n", c.saldo);
        printf("Digite o novo saldo: ");
        scanf("%lf%*c", &novoSaldo);
        c.saldo = novoSaldo;

        fseek(ptr, pos, SEEK_SET);
        fwrite(&c, TAMANHO_REGISTRO, 1, ptr);
        printf("Saldo atualizado com sucesso.\n");
    } else {
        printf("Cliente não encontrado.\n");
    }

    fclose(ptr);
}

void encerrarConta() {
    FILE *ptr = fopen(ARQUIVO, "r+b");
    if (ptr == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    int numeroConta;
    printf("Digite o número da conta a encerrar: ");
    scanf("%d%*c", &numeroConta);

    Cliente c;
    long pos = 0;
    int encontrado = 0;

    while (fread(&c, TAMANHO_REGISTRO, 1, ptr) == 1) {
        if (c.numeroConta == numeroConta && c.numeroConta != 0) {
            encontrado = 1;
            break;
        }
        pos = ftell(ptr);
    }

    if (encontrado) {
        c.numeroConta = 0;
        strcpy(c.nome, "");
        c.saldo = 0.0;

        fseek(ptr, pos, SEEK_SET);
        fwrite(&c, TAMANHO_REGISTRO, 1, ptr);
        printf("Conta encerrada com sucesso.\n");
    } else {
        printf("Conta não encontrada.\n");
    }

    fclose(ptr);
}

void listarClientes() {
    FILE *ptr = fopen(ARQUIVO, "rb");
    if (ptr == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    Cliente c;
    int cont = 0;
    printf("\n--- Lista de Clientes ---\n");
    while (fread(&c, TAMANHO_REGISTRO, 1, ptr) == 1) {
        if (c.numeroConta != 0) {
            printf("Posição %d:\n", cont);
            printf("  Conta: %d\n", c.numeroConta);
            printf("  Nome: %s\n", c.nome);
            printf("  Saldo: %.2f\n\n", c.saldo);
        }
        cont++;
    }

    fclose(ptr);
}

int main() {
    inicializarArquivo();

    int opcao;
    do {
        printf("\n=== Sistema de Manutenção de Contas ===\n");
        printf("1. Cadastrar novo cliente em posição específica\n");
        printf("2. Consultar cliente pelo número da conta\n");
        printf("3. Atualizar saldo de um cliente\n");
        printf("4. Encerrar conta (remover)\n");
        printf("5. Listar todos os clientes\n");
        printf("6. Rewind() - Restaurar leitura do início\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d%*c", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                consultarCliente();
                break;
            case 3:
                atualizarSaldo();
                break;
            case 4:
                encerrarConta();
                break;
            case 5:
                listarClientes();
                break;
            case 6: {
                FILE *ptr = fopen(ARQUIVO, "rb");
                if (ptr != NULL) {
                    rewind(ptr);
                    printf("Leitura restaurada para o início do arquivo (rewind executado).\n");
                    fclose(ptr);
                } else {
                    printf("Arquivo não encontrado.\n");
                }
                break;
            }
            case 7:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);

    return 0;
}