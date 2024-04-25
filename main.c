#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remedio.h"

void exibirMenu() {
    printf("1. Adicionar Item\n");
    printf("2. Listar Itens\n");
    printf("3. Editar Item\n");
    printf("4. Excluir Item\n");
    printf("5. Buscar Item\n");
    printf("6. Ordenar Itens por ID\n");
    printf("7. Logout\n");
    printf("0. Sair\n");
}

int main() {
    carregarUsuarios();
    carregarItens();

    int escolha;
    int logado = 0;

    while (1) {
        printf("===========================\n");
        printf("BEM VINDO A FARMACIA ROLIM\n");
        printf("===========================\n");
        printf("1. Login\n");
        printf("2. Registrar\n");
        printf("0. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar(); 

        switch (escolha) {
            case 1:
                logado = login();
                break;
            case 2:
                registrarUsuario();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                salvarUsuarios(); 
                salvarItens(); 
                exit(0);
            default:
                printf("Escolha inválida. Por favor, tente novamente.\n");
        }

        while (logado) {
            mensagemBoasVindas();
            exibirMenu();

            printf("Digite sua escolha: ");
            scanf("%d", &escolha);
            getchar(); 

            switch (escolha) {
                case 1:
                    adicionarItem();
                    break;
                case 2:
                    listarItens();
                    break;
                case 3:
                    editarItem();
                    break;
                case 4:
                    excluirItem();
                    break;
                case 5:
                    ordenarItensPorId();
                    break;
                case 6:
                    logado = 0;
                    printf("Logout realizado com sucesso.\n");
                    break;
                case 7:
                    printf("Salvando itens...\n");
                    salvarItens();
                    break;
                case 8:
                    printf("Carregando itens...\n");
                    carregarItens();
                    break;
                case 0:
                    printf("Encerrando o programa.\n");
                    salvarUsuarios(); 
                    salvarItens(); 
                    exit(0);
                default:
                    printf("Escolha inválida. Por favor, tente novamente.\n");
            }
        }
    }

    return 0;
}


