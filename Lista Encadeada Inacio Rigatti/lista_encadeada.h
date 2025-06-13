typedef struct _no No;
typedef struct _lista_encadeada ListaEncadeada;

ListaEncadeada *criarListaEncadeada();
void imprimir(const ListaEncadeada *lista);
void adicionarNoInicio(ListaEncadeada *lista, int valor);
void adicionarNoFinal(ListaEncadeada *lista, int valor);

void removerPrimeiro(ListaEncadeada *lista);
void removerUltimo(ListaEncadeada *lista);
void removerEspecifico(ListaEncadeada *lista, int valor);
