#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include "contato.h"


Lista *criaLista() {
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}


void abortaPrograma() {
    printf("ERRO! Lista não alocada, ");
    printf("O programa será encerrado...\n\n\n");
    system("pause");
    exit(1);
}


void apagaLista(Lista *li) {
    if (li != NULL) {
        ELEM *no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}


int tamanhoLista(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    int acum = 0;
    ELEM *no = *li;
    while (no != NULL) {
        acum++;
        no = no->prox;
    }
    return acum;
}


int listaVazia(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}



//coleta através dos ponteiros inserindo as informações do cliente específico
int coletaDados(Lista *li, CLIENTE *cli) {
    printf("\n\tInserção de Novo Cliente\n");
    //variavel para evitar repetição do codigo ou invalidez
    int codok = 0;
    //enquanto codok nao for valido loopa o inserir codigo do cliente
    while (!codok) {
        printf("Digite o código do cliente:\n");
        scanf("%d", &cli->codigo);
        if (consultaCodigo(li, cli->codigo, cli)) {
            printf("Esse código já existe ou é inválido!\n");
        } else {
            //sai do loop quando o codigo nao for repetido ou inválido
            codok = 1;
        }
    }
    getchar();
    printf("Digite o nome do cliente:\n");
    fgets(cli->nome, 255, stdin);
    printf("Digite a empresa onde trabalha:\n");
    fgets(cli->empresa, 255, stdin);
    printf("Digite o departamento:\n");
    fgets(cli->depart, 255, stdin);
    printf("Digite o telefone fixo:\n");
    fgets(cli->telefone, 15, stdin);
    printf("Digite o celular:\n");
    fgets(cli->celular, 15, stdin);
    printf("Digite o email:\n");
    fgets(cli->email, 255, stdin);
    system("cls");
    //chama a função de inserir dados na lista para os novos dados coletados e avisa via texto o operador
    int ok = insereDados(li, *cli);
    if(ok == 0){
        printf("Erro! Cliente não inserido.");
    }else{
         printf("Cliente inserido com sucesso");
        return cli->codigo;
    }
}


int insereDados(Lista *li, CLIENTE cli) {
    if (li == NULL) {
        abortaPrograma();
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no == NULL) {
        return 0;
    }
    no->dados = cli;
     // insere no início se lista estiver vazia ou o novo cliente for o menor código
    if (listaVazia(li)) {
        no->prox = (*li);
        *li = no;
    } else {
        // procura a posição na lista para inserir o cliente pelo código, em ordem
        ELEM *ant, *atual = *li;
        while (atual != NULL && atual->dados.codigo < cli.codigo) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = ant->prox;
            ant->prox = no;
        }
    }
    return cli.codigo;
}


void exibeLista(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    if (listaVazia(li)) {
        printf("\nAinda não há clientes adicionados na lista.\n");
        return;
    }
    //se a lista nao for nula e nem estiver vazia *verficado acima* coloca o ponteiro no começo da lista para começar a exibição
    ELEM *no = *li;
    printf("\n\t\t\tLista de clientes\n\n");
    int x = tamanhoLista(li);
    printf("Número total de clientes: %d\n", x);
    printf("\n--------------------------------------------------------------------------------------------\n");
    //exibe dados de cada cliente em um loop que enquanto houver outro ele continua a rodar
    while (no != NULL) {
        printf("Código: %d\n", no->dados.codigo);
        printf("Nome: %s", no->dados.nome);
        printf("Empresa: %s", no->dados.empresa);
        printf("Departamento: %s", no->dados.depart);
        printf("Telefone: %s", no->dados.telefone);
        printf("Celular: %s", no->dados.celular);
        printf("Email: %s", no->dados.email);
        printf("\n--------------------------------------------------------------------------------------------\n");
        no = no->prox;
    }
}


int consultaCodigo(Lista *li, int cod, CLIENTE *cli) {
    if (li == NULL) {
        abortaPrograma();
    }
    //coloca o ponteiro no começo da lista
    ELEM *no = *li;
    //percorre a lista até chegar ao final ou encontrar o código desejado
    while (no != NULL && no->dados.codigo != cod) {
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    } else {
        *cli = no->dados;
        return 1;
    }
}


int consultaNome(Lista *li, char *nome, CLIENTE *cli) {
    if (li == NULL) {
        abortaPrograma();
    }
    ELEM *no = *li;

    int achei = 0;
    char nomeMin[255];
    char cliMin[255];

    // converte as letras da busca para minuscula
    for (int i = 0; nome[i]; i++) {
        nomeMin[i] = tolower((unsigned char)nome[i]);
    }
    nomeMin[strlen(nome)] = '\0';
    // Percorre a lista
    while (no != NULL) {
        // muda as letras do nome cadastrado para minuscula
        for (int i = 0; no->dados.nome[i]; i++) {
            cliMin[i] = tolower((unsigned char)no->dados.nome[i]);
        }
        cliMin[strlen(no->dados.nome)] = '\0';

        if (strstr(cliMin, nomeMin)) {
            *cli = no->dados;
            achei = 1;
            printf("\n\nCódigo: %d\n", cli->codigo);
            printf("Nome: %s", cli->nome);
            printf("Empresa: %s", cli->empresa);
            printf("Departamento: %s", cli->depart);
            printf("Telefone: %s", cli->telefone);
            printf("Celular: %s", cli->celular);
            printf("Email: %s", cli->email);
            printf("\n--------------------------------------------------------------------------------------------\n");
        }
        no = no->prox;
    }
    // return 1 se encontrar o nome na lista , se nao return 0
    return achei;
}

int editaDados(Lista *li, int cod, CLIENTE *cli) {
    //variável que copia o código
    int salvacodigo =  cli->codigo;
    //apaga os dados anteriores
    removeDados(li, cod);
    cli->codigo = salvacodigo;
    //pede os novos dados
    printf("\nEditando cliente %d\n",cli->codigo);
    getchar();
    printf("Digite o nome do cliente:\n");
    fgets(cli->nome, 255, stdin);
    printf("Digite a empresa onde trabalha:\n");
    fgets(cli->empresa, 255, stdin);
    printf("Digite o departamento:\n");
    fgets(cli->depart, 255, stdin);
    printf("Digite o telefone fixo:\n");
    fgets(cli->telefone, 15, stdin);
    printf("Digite o celular:\n");
    fgets(cli->celular, 15, stdin);
    printf("Digite o email:\n");
    fgets(cli->email, 255, stdin);
    system("cls");
    //insere os novos dados na lista
    insereDados(li, *cli);
    return cli->codigo;
}




int removeDados(Lista *li, int cod) {
    //se a lista for nula, aborta
    if (li == NULL) {
        abortaPrograma();
    }
    //ponteiros auxiliares, ant anterior e no atual

    ELEM *ant, *no = *li;

    //busca o elemento especificado
    while (no != NULL && no->dados.codigo != cod) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    }
    //ajusta pra ver se é o primeiro da lista e atualiza pra apontar pro proximo, e se nao for passa a ser ali no else
    if (no == *li) {
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }
    //libera a memoria do removido
    free(no);
    return 1;
}


int salvaDados(Lista *li, FILE *f) {
    //se a lista for nula, aborta
    if (li == NULL) {
        abortaPrograma();
    }
    //ponteiro auxiliar pra nao mexer na cabeça da lista
    ELEM *aux = *li;
    //percorre por toda a lista, salvando a cada passada
    while (aux != NULL) {
        fwrite(&(aux->dados), sizeof(CLIENTE), 1, f);
        aux = aux->prox;
    }
    return 1;
}
