typedef struct _no No;
typedef struct _tabelaHash TabelaHash;

int hash(const int chave);
TabelaHash *criarTabelaHash();
void inserirDado(TabelaHash *tabela, const int chave, const char *nome);
void imprimir(const TabelaHash *tabela);