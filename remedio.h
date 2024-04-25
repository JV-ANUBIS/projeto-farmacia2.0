#ifndef H_REMEDIO
#define H_REMEDIO

typedef struct usuario Usuario;

typedef struct item Item;

typedef struct no No;

typedef struct lista Lista;

void lerLista(Lista *lista);

void adicionaFim(Lista *lista, Item e);

void mostrar(Lista lista);

void ler(Item *e);

void adicionarItem();

void listarItens();

void editarItem();

void excluirItem();

void ordenarItensPorId();

void salvarItens();

void carregarItens();

void adicionarUsuario();

int login();

void registrarUsuario();

void mensagemBoasVindas();

void buscarItem();

void salvarUsuarios();

void carregarUsuarios();

void exibirMenu();

void salvaLista(Lista *lista);

#endif

