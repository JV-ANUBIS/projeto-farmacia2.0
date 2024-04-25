#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remedio.h"

#define MAX_EMAIL_LENGTH 80
#define MAX_USERS 100
#define MAX_ITEMS 100
#define FILENAME_USERS "usuarios.dat"
#define FILENAME_ITENS "itens.dat"

struct usuario{
    char nome[50];
    char senha[50];
    char email[MAX_EMAIL_LENGTH];
};

struct item {
    int idItem;
    char nomeItem[50];
    float preco;
};

struct no{
    Item dado;
    struct no *prox;
};

struct lista{
    No *inicio;
};

Usuario usuarios[MAX_USERS];
Item itens[MAX_ITEMS];
Lista listaItens;
int numUsuarios = 0;
int numItens = 0;

void lerLista(Lista *lista) {
    FILE *file = fopen(FILENAME_ITENS, "rb");
    Item e;
    while (fread(&e, sizeof(Item), 1, file)) {
        adicionaFim(lista, e);
    }
    fclose(file);
}

void adicionaFim(Lista *lista, Item e) {
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = e;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }
    else {
        No* pi;
        for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}

void mostrar(Lista lista) {
    No* pi;
    for (pi = lista.inicio; pi != NULL; pi = pi->prox) {
        Item dado = pi->dado;
        printf("ID: %d, Nome: %s, Preço: %.2f\n", dado.idItem, dado.nomeItem, dado.preco);
    }
}

void ler(Item *e) {
    printf("Informe os dados do item:\n");
    scanf("%d %s %f", &e->idItem, e->nomeItem, &e->preco);
}

void adicionarItem() {
    Item novoItem;
    ler(&novoItem);
    adicionaFim(&listaItens, novoItem);
    numItens++;

    FILE *file = fopen(FILENAME_ITENS, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }

    fwrite(&novoItem, sizeof(Item), 1, file);

    fclose(file);
}

void listarItens() {
    FILE *file = fopen(FILENAME_ITENS, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }

    Item e;
    printf("Itens:\n");
    while (fread(&e, sizeof(Item), 1, file)) {
        printf("ID: %d, Nome: %s, Preço: %.2f\n", e.idItem, e.nomeItem, e.preco);
    }

    fclose(file);
}

void editarItem() {
    int id;
    printf("Digite o ID do item a ser editado: ");
    scanf("%d", &id);

    FILE *file = fopen(FILENAME_ITENS, "r+b");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }

    Item e;
    while (fread(&e, sizeof(Item), 1, file)) {
        if (e.idItem == id) {
            printf("Digite o novo nome do remédio: ");
            scanf("%s", e.nomeItem); // Corrigido para scanf("%s", e.nomeItem);
            printf("Digite o novo preço: ");
            scanf("%f", &e.preco);
            fseek(file, -sizeof(Item), SEEK_CUR);
            fwrite(&e, sizeof(Item), 1, file);
            fclose(file);
            printf("Item editado com sucesso.\n");
            return;
        }
    }

    fclose(file);
    printf("Item não encontrado.\n");
}

void excluirItem() {
    int id;
    printf("Digite o ID do item a ser excluído: ");
    scanf("%d", &id);

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        return;
    }

    FILE *file = fopen(FILENAME_ITENS, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        fclose(temp);
        return;
    }

    Item e;
    int encontrado = 0;
    while (fread(&e, sizeof(Item), 1, file)) {
        if (e.idItem == id) {
            encontrado = 1;
        } else {
            fwrite(&e, sizeof(Item), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME_ITENS);
    rename("temp.dat", FILENAME_ITENS);

    if (encontrado) {
        printf("Item excluído com sucesso.\n");
    } else {
        printf("Item não encontrado.\n");
    }
}

void ordenarItensPorId() {
    No *atual = listaItens.inicio;
    No *proximo = NULL;
    Item temp;

    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual->prox != NULL) {
        proximo = atual->prox;
        while (proximo != NULL) {
            if (atual->dado.idItem > proximo->dado.idItem) {
                temp = atual->dado;
                atual->dado = proximo->dado;
                proximo->dado = temp;
            }
            proximo = proximo->prox;
        }
        atual = atual->prox;
    }

    printf("Itens ordenados por ID.\n");
}

void salvarItens() {
    FILE *file = fopen(FILENAME_ITENS, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de itens.\n");
        return;
    }

    No *atual = listaItens.inicio;
    while (atual != NULL) {
        fwrite(&atual->dado, sizeof(Item), 1, file);
        atual = atual->prox;
    }

    fclose(file);
}

void carregarItens() {
    FILE *file = fopen(FILENAME_ITENS, "rb");
    if (file == NULL) {
        printf("Arquivo de itens não encontrado. Criando novo arquivo.\n");
        return;
    }

    Item e;
    while (fread(&e, sizeof(Item), 1, file)) {
        adicionaFim(&listaItens, e);
        numItens++;
    }

    fclose(file);
}

void adicionarUsuario() {
    if (numUsuarios >= MAX_USERS) {
        printf("Número máximo de usuários atingido.\n");
        return;
    }

    printf("Digite o nome de usuário: ");
    scanf("%s", usuarios[numUsuarios].nome);
    printf("Digite a senha: ");
    scanf("%s", usuarios[numUsuarios].senha);

    while (1) {
        printf("Digite o email: ");
        scanf("%s", usuarios[numUsuarios].email);
          char *ptr = strchr(usuarios[numUsuarios].email, '@');
              if (ptr == NULL) {
            printf("Email inválido. Certifique-se de incluir um email válido.\n");
        } else {
            break; 
        }
    }

    numUsuarios++;

    salvarUsuarios(); 
}


int login() {
    char nome[50];
    char senha[50];
    int tentativas_restantes = 5; 

    while (tentativas_restantes > 0) {
        printf("Digite o nome de usuário: ");
        scanf("%s", nome);
        printf("Digite a senha: ");
        scanf("%s", senha);

        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
                printf("Login realizado com sucesso. Bem-vindo, %s!\n", usuarios[i].nome);
                return 1; 
            }
        }

        printf("Login falhou. Nome de usuário ou senha incorretos. Tentativas restantes: %d\n", --tentativas_restantes);
    }

    printf("Tente novamente outra hora.\n");
    exit(0); 
}

void registrarUsuario() {
    adicionarUsuario();
    printf("Usuário registrado com sucesso!\n");
}

void mensagemBoasVindas() {
    printf("===========================\n");
    printf("      FARMACIA ROLIM\n");
    printf("===========================\n");
}

void buscarItem() {
    char termoBusca[50];
    printf("Digite o ID ou nome do remédio a ser buscado: ");
    scanf("%s", termoBusca);

    for (int i = 0; i < numItens; i++) {
        if (itens[i].idItem == atoi(termoBusca) || strcmp(itens[i].nomeItem, termoBusca) == 0) {
            printf("Remédio encontrado - ID: %d, Nome: %s, Preço: R$%.2f\n", itens[i].idItem, itens[i].nomeItem, itens[i].preco);
            return;
        }
    }

    printf("Remédio não encontrado.\n");
}

void salvarUsuarios() {
    FILE *file = fopen(FILENAME_USERS, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(&numUsuarios, sizeof(int), 1, file);
    fwrite(usuarios, sizeof(Usuario), numUsuarios, file);

    fclose(file);
}

void carregarUsuarios() {
    FILE *file = fopen(FILENAME_USERS, "rb");
    if (file == NULL) {
        printf("Arquivo de usuários não encontrado. Criando novo arquivo.\n");
        return;
    }

    fread(&numUsuarios, sizeof(int), 1, file);
    fread(usuarios, sizeof(Usuario), numUsuarios, file);

    fclose(file);
}