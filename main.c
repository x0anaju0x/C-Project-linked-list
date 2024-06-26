#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include "contato.h">


int main()
{
    setlocale(LC_ALL, "Portuguese");

    printf("\t\t\tBem-vindo ao Sistema de Gest�o de Contatos da ACME S.A.\n\n");
    printf("Nosso sistema facilita o gerenciamento de contatos de clientes, oferecendo"
    " funcionalidades para inser��o, busca, edi��o e remo��o de informa��es essenciais.\n");

    Lista *li = criaLista();
    if (li == NULL) {
        abortaPrograma();
    }

    int codigo, escolha;
    char certeza;
    CLIENTE cli_consulta;

    FILE *f = fopen ("arquivodados.txt", "rb");
    if(f != NULL){
        while(fread(&cli_consulta, sizeof(CLIENTE), 1, f)){
        insereDados(li, cli_consulta);
        }
        printf("\nClientes recuperados: %d\n", tamanhoLista(li));
    }


        while(1){
        printf("\nMenu de Op��es:\n");
        printf("1. Inserir novo cliente\n");
        printf("2. Visualizar lista completa de clientes\n");
        printf("3. Consultar cliente via c�digo\n");
        printf("4. Consultar cliente via nome\n");
        printf("5. Editar dados de um cliente\n");
        printf("6. Remover cliente via codigo\n");
        printf("7. Sair do sistema\n");
        scanf("%d", &escolha);

        switch(escolha){
        case 1:
            system("cls");
            coletaDados(li, &cli_consulta);
            break;

        case 2:
            system("cls");
            exibeLista(li);
            break;

        case 3:
            system("cls");
            if (listaVazia(li)) {
                printf("\nAinda n�o h� clientes adicionados na lista.\n");
            } else {
                printf("Insira o c�digo que deseja consultar: ");
                scanf("%d", &codigo);
                // Chama a fun��o para procurar o cliente pelo c�digo que foi inserido
                int x = consultaCodigo(li, codigo, &cli_consulta);
                if (x) {
                    printf("C�digo: %d\n", cli_consulta.codigo);
                    printf("Nome: %s", cli_consulta.nome);
                    printf("Empresa: %s", cli_consulta.empresa);
                    printf("Departamento: %s", cli_consulta.depart);
                    printf("Telefone: %s", cli_consulta.telefone);
                    printf("Celular: %s", cli_consulta.celular);
                    printf("Email: %s", cli_consulta.email);
                    printf("\n\n\n");
                } else {
                    printf("\nC�digo %d n�o encontrado.\n\n", codigo);
                }
            }
            break;

        case 4:
            system("cls");
            if (listaVazia(li)) {
                printf("\nAinda n�o h� clientes adicionados na lista.\n");
            } else {
                char nome[255];
                printf("Insira o nome de cliente que deseja consultar: ");
                fflush(stdin);
                fgets(nome, 255, stdin);
                // ao usar fgets h� um /n automatico e isso estava atrapalhando na compara��o de strings por isso foi necessario remove-lo
                for (int i = 0; nome[i] != '\0'; i++) {
                    if (nome[i] == '\n') {
                        nome[i] = '\0';
                        break;
                    }
                }
                int x = consultaNome(li, nome, &cli_consulta);
                if (!x) {
                    printf("\nCliente %s n�o encontrado.\n\n", nome);
                }
            }
            break;

        case 5:
            system("cls");
            //confere se tem clientes inseridos
            if (listaVazia(li)) {
                printf("\nAinda n�o h� clientes adicionados na lista.\n");
            } else {
                //aqui segue a mesma parte da consulta por c�digo simples
                printf("Insira o c�digo do cliente que deseja editar: ");
                scanf("%d", &codigo);
                int x = consultaCodigo(li, codigo, &cli_consulta);
                if (x) {
                    printf("C�digo: %d\n", cli_consulta.codigo);
                    printf("Nome: %s", cli_consulta.nome);
                    printf("Empresa: %s", cli_consulta.empresa);
                    printf("Departamento: %s", cli_consulta.depart);
                    printf("Telefone: %s", cli_consulta.telefone);
                    printf("Celular: %s", cli_consulta.celular);
                    printf("Email: %s", cli_consulta.email);
                    printf("\n\n\n");
                    //pergunta se tem certeza mesmo e retorna pro menu se cancelar
                    printf("Tem certeza que deseja editar os dados desse cliente? (s/n)\n");
                    scanf(" %c", &certeza);
                    if (tolower(certeza) == 's') {
                        //quando a certeza � consultada, chama a fun��o de editar pro c�digo inserido
                        editaDados(li, codigo, &cli_consulta);
                    } else {
                        printf("Edi��o cancelada\n");
                    }
                } else {
                    printf("\nC�digo %d n�o encontrado.\n\n", codigo);
                }
            }
            break;

        case 6:
            system("cls");
            //mesma ideia seguida na consulta por c�digo simples e na de edi��o
            if (listaVazia(li)) {
                printf("\nAinda n�o h� clientes adicionados na lista.\n");
            } else {
                printf("Insira o c�digo do cliente que deseja remover: ");
                scanf("%d", &codigo);
                int x = consultaCodigo(li, codigo, &cli_consulta);
                if (x) {
                    printf("C�digo: %d\n", cli_consulta.codigo);
                    printf("Nome: %s", cli_consulta.nome);
                    printf("Empresa: %s", cli_consulta.empresa);
                    printf("Departamento: %s", cli_consulta.depart);
                    printf("Telefone: %s", cli_consulta.telefone);
                    printf("Celular: %s", cli_consulta.celular);
                    printf("Email: %s", cli_consulta.email);
                    printf("\n\n\n");
                    //consulta a certeza e volta pro menu caso n�o responda 's'
                    printf("\nTem certeza que deseja remover esse cliente? (s/n)\n");
                    scanf(" %c", &certeza);
                    if (tolower(certeza) == 's') {
                        system("cls");
                        printf("Cliente removido com sucesso!\n");
                        //chama a fun��o que deleta os dados do cliente com o c�digo informado
                        removeDados(li, codigo);
                    } else {
                        printf("Remo��o n�o conclu�da.\n");
                    }
                } else {
                    printf("\nC�digo %d n�o encontrado.\n\n", codigo);
                }
            }
            break;
        case 7:
            system("cls");
            printf("\n\nOs dados ser�o automaticamente salvos ao sair do sistema...\n");
            printf("O programa est� sendo encerrado!");
            printf("\n\n\n");
            FILE *f = fopen ("arquivodados.txt", "wb");
            if(f == NULL){
                printf("Erro na abertura do arquivo1\n");
                system("pause");
                exit(1);
            }
            salvaDados(li, f);
            fclose(f);
            return 0;
            break;
        default:
            system("cls");
            printf("\nALERTA!\n");
            printf("Escolha inv�lida, selecione novamente\n\n");
        }
    }

    apagaLista(li);
}
