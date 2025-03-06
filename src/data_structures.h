#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H


typedef struct Commit {
    char *message;
    struct Commit *next;
} Commit;

typedef struct Branch {
    char *name;
    Commit *commits;
    struct Branch *next;
} Branch;


typedef struct Branch_Commit{
    char *name;
    char *commit;
}Branch_Commit;


typedef struct lista_temp{
    char *name;
    struct lista_temp *next;
}lista_temp;



typedef struct hashEnderAberto {
    int qtd, TABLE_SIZE;
    Branch **itens;
} Hash;


Branch_Commit *create_branch_commit(Branch *found_branch);


Commit *create_commit(char *message);
//Branch *create_branch(char *name);
Branch *create_branch(char *name, Branch *current_branch);
void add_commit(Branch *branch, char *message);
Branch *find_branch(Branch *branches, char *name);
//void add_branch(Branch **branches, char *name);
void add_branch(Branch **branches, char *name, Branch *current_branch);

void print_branch_commits(Branch *branch);
void print_commits(Branch *branch);
void free_commits(Commit *commits);
void free_branches(Branch *branches);
void recebe_nome(char* vetor_comando, char* vetor_nome, int tamanho, int n);
int verifica_git ( Branch *branches, Branch *current_branch, char *message, char* nome, int tamanho);
int verfica_comando(Branch *branches, Branch *current_branch, char* message, char* nome, char* vetor, int tamanho, int i);
int ignora_espaco(char* vetor, int i);

/*
typedef struct hashEnderSeparado {
    int qtd, TABLE_SIZE;
    ListaAlunos **itens;
} HashSeparado;
*/

// Funcoes para manipulacao da tabela hash com enderecamento aberto
Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);


/*
// Funcoes para manipulacao da tabela hash com enderecamento separado
HashSeparado* criaHashSeparado(int TABLE_SIZE);
void liberaHashSeparado(HashSeparado *ha);
*/


// Funcoes hash
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);

// Converter string para int
int valorString(char *str);

// Funcoes de sondagem
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHash(int H1, int chave, int i, int TABLE_SIZE);

// Funcoes de insercao, busca e remocao na tabela hash sem colisao
int insereHash_SemColisao(Hash *ha, Branch al);
int buscaHash_SemColisao(Hash *ha, int mat, Branch *al);
int removeHash_SemColisao(Hash *ha, int mat);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento aberto)
int insereHash_EnderAberto(Hash *ha, Branch *al);
int buscaHash_EnderAberto(Hash *ha, char *mat, Branch *al);
int removeHash_EnderAberto(Hash *ha, int mat);

/*
// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento separado)
int insereHash_EnderSeparado(HashSeparado *ha, Aluno al);
int buscaHash_EnderSeparado(HashSeparado *ha, int mat, Aluno *al);
int removeHash_EnderSeparado(HashSeparado *ha, int mat);

// Funcoes auxiliares
void imprimeHash(Hash *ha);
void imprimeHashSeparado(HashSeparado *ha);
*/








void imprimeAluno(Branch_Commit* al);
void transfere(Branch_Commit* al, Branch* branches,Branch *current_branch);





#endif