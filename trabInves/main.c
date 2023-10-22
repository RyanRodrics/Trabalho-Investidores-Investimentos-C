#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "investidores.h"
#include "investimentos.h"

void lermain(char msg[], char valor[])
{
    valor[0] = 0;
    valor[1] = 0;
    printf("%s", msg);
    fflush(stdin);
    gets(valor);
}

int main()
{
    int op;
    char valor[2];

    while (1)
    {
        printf("\n----------INVESTIMENTOS AJALMAS--------- \n");
        printf("[1] Acessar Investidores \n"
               "[2] Acessar Investimentos \n");
        while (1) {
            op = 0;
            lermain("Sua opcao: ", valor);
            op = atoi(valor);
            printf(" ");
            if (op == 1 || op == 2) break;
        }

        switch (op) {
            case 1:
                while (1) {
                    printf("\n### INVESTIDORES ### \n");
                    printf("[1] Inserir novo investidor \n"
                           "[2] Alterar investidor \n"
                           "[3] Excluir investidor \n"
                           "[4] Mostrar um unico investidor \n"
                           "[5] Mostrar investidores \n");
                    while (1) {
                        op = 0;
                        lermain("Sua opcao: ", valor);
                        op = atoi(valor);
                        printf(" ");
                        if (op >= 1 && op <= 5) break;
                    }

                    switch (op) {
                        case 1:
                            inserir_investidor();
                            break;
                        case 2:
                            alterar_investidor();
                            break;
                        case 3:
                            excluir_investidor();
                            break;
                        case 4:
                            mostrar_investidor_codigo();
                            break;
                        case 5:
                            printf("\nComo deseja filtrar? \n"
                                   "[1] Por tipo de investimento \n"
                                   "[2] Ordem crescente de patrimonio \n"
                                   "[3] Mostrar todos \n");
                            while (1) {
                                op = 0;
                                lermain("Sua opcao: ", valor);
                                op = atoi(valor);
                                printf(" ");
                                if (op >= 1 && op <= 3) break;
                            }

                            switch (op) {
                                case 1:
                                    mostrar_investidor_investimento();
                                    break;
                                case 2:
                                    mostrar_crescente();
                                    break;
                                case 3:
                                    mostrar_todos();
                                    break;
                            }
                            break; //final case5
                    }
                    op = 0;
                    lermain("\nDigite 1 se quiser continuar navegando em investidores: ", valor);
                    op = atoi(valor);
                    printf(" ");
                    if (op == 1) continue;
                    break; //final do while do case1
                }
                break; //final case1, break no switch

            case 2:
                while (1) {
                    printf("\n### INVESTIMENTOS ### \n");
                    printf("[1] Inserir novo investimento \n"
                           "[2] Alterar investimento \n"
                           "[3] Excluir investimento\n"
                           "[4] Mostrar um unico investimento\n"
                           "[5] Mostrar investimentos\n");
                    while (1) {
                        op = 0;
                        lermain("Sua opcao: ", valor);
                        op = atoi(valor);
                        printf(" ");
                        if (op >= 1 && op <= 5) break;
                    }

                    switch (op) {
                        case 1:
                            inserir_investimento();
                            break;
                        case 2:
                            alterar_investimento();
                            break;
                        case 3:
                            excluir_investimento();
                            break;
                        case 4:
                            mostrar_investimento_codigo();
                            break;
                        case 5:
                            printf("\nComo deseja filtrar? \n"
                                   "[1] Por codigo do investidor \n"
                                   "[2] Mostrar todos em ordem alfabetica\n");
                            while (1) {
                                op = 0;
                                lermain("Sua opcao: ", valor);
                                op = atoi(valor);
                                printf(" ");
                                if (op == 1 || op == 2) break;
                            }

                            switch (op) {
                                case 1:
                                    mostrar_investimento_investidor();
                                    break;
                                case 2:
                                    mostrar_alfabetica();
                                    break;
                            }
                            break; //final do case5
                    }
                    op = 0;
                    lermain("\nDigite 1 se quiser continuar navegando em investimentos: ", valor);
                    op = atoi(valor);
                    printf(" ");
                    if (op == 1) continue;
                    break; //final do while do case2
                }
                break;//final case2, break no switch
        }
        op = 0;
        lermain("\nDigite 1 para voltar ao menu inicial: ", valor);
        op = atoi(valor);
        printf(" ");
        if (op == 1) continue;
        printf("\n");
        break;
    }

    criar_arquivo_investidores();
    criar_arquivo_investimentos();

    return 0;
}

//ALUNOS
//RYAN PIMENTEL BERNARDINO RODRIGUES
//LARISSA DA SILVA ARAÚJO
