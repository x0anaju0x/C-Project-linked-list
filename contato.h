
typedef struct cliente{
    char nome[255], empresa[255], depart[255], email[255];
    char telefone[15], celular[15];
    int codigo;
}CLIENTE;


typedef struct elemento {
    CLIENTE dados;
    struct elemento *prox;
} ELEM;


typedef struct elemento* Lista;


Lista *criaLista();

void abortaPrograma();

void apagaLista(Lista *li);

int tamanhoLista(Lista *li);

int listaVazia(Lista *li);

int coletaDados(Lista *li, CLIENTE *cli);

int insereDados(Lista *li, CLIENTE cli);

void exibeLista(Lista *li);

int consultaCodigo(Lista *li, int cod, CLIENTE *cli);

int consultaNome(Lista *li, char *nome, CLIENTE *cli);

int editaDados(Lista *li, int cod, CLIENTE *cli);

int removeDados(Lista *li, int cod);

int salvaDados(Lista *li, FILE *f);

