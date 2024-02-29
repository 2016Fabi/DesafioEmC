#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CONTAS 4
#define MAX_NOME 50
#define MAX_TIPO_CONTA 20
#define MAX_TIPO_CLIENTE 20

typedef struct {
    char tipo_conta[MAX_TIPO_CONTA];
    char tipo_cliente[MAX_TIPO_CLIENTE];
    time_t data_abertura;
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int num_contas;
} Usuario;

void criar_contas(Usuario *usuario, char *tipo_conta, char *tipo_cliente, float saldo_inicial) {
    if (usuario->num_contas < MAX_CONTAS) {
        strcpy(usuario->contas[usuario->num_contas].tipo_conta, tipo_conta);
        strcpy(usuario->contas[usuario->num_contas].tipo_cliente, tipo_cliente);
        usuario->contas[usuario->num_contas].data_abertura = time(NULL);
        usuario->contas[usuario->num_contas].saldo = saldo_inicial;
        usuario->num_contas++;
        printf("Conta criada com sucesso.\n");
    } else {
        printf("Limite de contas atingido.\n");
    }
}

void consultar_saldo(Usuario usuario) {
	int i;
    for (i = 0; i < usuario.num_contas; i++) {
        printf("Conta %d - Tipo de conta: %s, Tipo de cliente: %s, Data de abertura: %s, Saldo: R$ %.2f\n",
               i+1, usuario.contas[i].tipo_conta, usuario.contas[i].tipo_cliente,
               asctime(localtime(&usuario.contas[i].data_abertura)), usuario.contas[i].saldo);
    }
}

void alterar_saldo(Usuario *usuario, int conta, float valor) {
    if (conta > 0 && conta <= usuario->num_contas) {
        usuario->contas[conta-1].saldo += valor;
        printf("Saldo alterado com sucesso.\n");
    } else {
        printf("Conta inválida.\n");
    }
}

void sacar(Usuario *usuario, int conta, float valor) {
    if (conta > 0 && conta <= usuario->num_contas) {
        if (usuario->contas[conta-1].saldo >= valor) {
            usuario->contas[conta-1].saldo -= valor;
            printf("Saque realizado com sucesso.\n");
        } else {
            printf("Saldo insuficiente.\n");
        }
    } else {
        printf("Conta inválida.\n");
    }
}

int main() {
    Usuario usuario;
    usuario.num_contas = 0;
    
    criar_contas(&usuario, "Corrente", "Pessoa Física", 1000.00);
    criar_contas(&usuario, "Poupança", "Pessoa Jurídica", 1500.00);
    criar_contas(&usuario, "Salário", "Pessoa Física", 2000.00);
    criar_contas(&usuario, "Investimento", "Pessoa Jurídica", 3000.00);
    
    int opcao, conta;
    float valor;
    
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Consultar saldo\n");
        printf("2. Alterar saldo\n");
        printf("3. Sacar\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                consultar_saldo(usuario);
                break;
            case 2:
                printf("Informe o numero da conta: ");
                scanf("%d", &conta);
                printf("Informe o valor a ser adicionado/subtraido: ");
                scanf("%f", &valor);
                alterar_saldo(&usuario, conta, valor);
                break;
            case 3:
                printf("Informe o numero da conta: ");
                scanf("%d", &conta);
                printf("Informe o valor a ser sacado: ");
                scanf("%f", &valor);
                sacar(&usuario, conta, valor);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}

