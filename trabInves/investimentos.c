#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include "investidores.h"
#include "investimentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct investimentos *p_investimentos = NULL;
int c_investimento = 0;

//CONTROLE E BUSCA DA MEMORIA
int controle_investimentos()
{
    return c_investimento;
}

void limpar_memoria_investimento(int index)
{
    // limpar todos os campos da struct
    int i;
    for (i=0; i<255; i++)
    {
        p_investimentos[index].descricao[i] = 0;
    }
    for (i=0; i<10; i++)
    {
        p_investimentos[index].codigo_investimento[i] = 0;
        p_investimentos[index].codigo_do_investidor[i] = 0;
    }
    for (i=0; i<3; i++)
    {
        p_investimentos[index].data_aplicacao[i] = 0;
    }
    p_investimentos[index].tipo = 0;
    p_investimentos[index].valor = 0;
    p_investimentos[index].tempo = 0;
    p_investimentos[index].rent_anual = 0;
    p_investimentos[index].prazo = 0;
    p_investimentos[index].valorizacao = 0;
}

void iniciar_memoria_investimento()
{
    //alocar
    if (c_investimento == 0) p_investimentos = malloc(50 * sizeof(struct investimentos));
    //p_investimentos = realloc(p_investimentos, c_investimento+1);
    //limpar a memoria alocada
    limpar_memoria_investimento(c_investimento);
}

int buscar_investimento_codigo(char busca[])
{
    for (int i = 0; i <= c_investimento; i++)
    {
        if (strcmp(p_investimentos[i].codigo_investimento, busca) == 0)
        {
            return i;
        }
    }
    return -1;
}


//INSERIR, ALTERAR E EXCLUIR
void inserir_investimento_codigo(int index)
{
    char codigo[10];
    while (1)
    {
        while(1)
        {
            ler("\nCodigo investimento (8 digitos): ", codigo);
            if (codigo[0] == '\0' || codigo[0] == ' ')
            {
                printf("Nao deixe esse campo em branco! ");
                continue;
            }
            else break;
        }

        if (buscar_investimento_codigo(codigo) == -1)
        {
            strcpy(p_investimentos[index].codigo_investimento, codigo);
            break;
        }
        else
        {
            printf("Esse codigo ja esta cadastrado, tente novamente! \n");
        }
    }
}

void inserir_investimento_investidor(int index)
{
    while(1)
    {
        ler("\nCodigo do investidor (8 digitos): ", p_investimentos[index].codigo_do_investidor);
        if (p_investimentos[index].codigo_do_investidor[0] == '\0' || p_investimentos[index].codigo_do_investidor[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }
}

void inserir_investimento_tipo(int index)
{
    char valor[2];
    int op;
    printf("\nTipo de investimento: \n"
           "[1] Acao \n"
           "[2] CDB \n"
           "[3] CRA \n"
           "[4] CRI \n"
           "[5] LCA \n"
           "[6] LCI \n");
    while (1) {
        ler("Sua opcao: ", valor);
        op = atoi(valor);
        printf(" ");
        if (op >= 1 && op <= 6) break;
    }
    p_investimentos[index].tipo = op;
}

char exportar_investimento_tipo(char codigo[], int tipo)
{
    for (int i=0; i<c_investimento; i++)
    {
        if (strcmp(p_investimentos[i].codigo_do_investidor, codigo)==0)
        {
            if (p_investimentos[i].tipo == tipo)
            return '1';
        }
    }
    return '0';
    // retornar o  tipo (entre 1 e 6) do investimento
}

float exportar_investimento_valorizacao(char codigo[], int index)
{
    float patrimonio=0;
    for (int i=0; i<c_investimento; i++)
    {
        if (strcmp(p_investimentos[i].codigo_do_investidor, codigo)==0)
        {
            patrimonio += p_investimentos[index].valorizacao;
        }
    }
    return patrimonio;
}

void inserir_investimento_rent(int index)
{
    char rent[10];
    while(1)
    {
        ler("\nRentabilidade anual (%): ", rent);
        if (rent[0] == '\0' || rent[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }

    p_investimentos[index].rent_anual = atof(rent);
}

void inserir_investimento_valor(int index)
{
    char valor[10];
    while(1)
    {
        ler("\nValor do investimento: ", valor);
        if (valor[0] == '\0' || valor[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }

    p_investimentos[index].valor = atof(valor);
}

void inserir_investimento_descricao(int index)
{
    while(1)
    {
        ler("\nDescricao: ", p_investimentos[index].descricao);
        if (p_investimentos[index].descricao[0] == '\0' || p_investimentos[index].descricao[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }
}

void calcular_investimento_tempo(int index)
{
    int tempo;
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    int dia_atual = data_atual->tm_mday;
    int mes_atual = data_atual->tm_mon + 1;
    int ano_atual = data_atual->tm_year + 1900;

    time_t aplicacao, atual;
    struct tm data_aplicacao;
    data_aplicacao.tm_year = p_investimentos[index].data_aplicacao[2] - 1900;
    data_aplicacao.tm_mon = p_investimentos[index].data_aplicacao[1] - 1;
    data_aplicacao.tm_mday = p_investimentos[index].data_aplicacao[0];
    data_aplicacao.tm_hour = 0;
    data_aplicacao.tm_min = 0;
    data_aplicacao.tm_sec = 0;
    data_aplicacao.tm_isdst = -1;
    aplicacao = mktime(&data_aplicacao);
    atual = mktime(data_atual);

    tempo = (int) difftime(atual, aplicacao) / (60 * 60 * 24);
    p_investimentos[index].tempo = tempo;
}

void inserir_investimento_data(int index)
{
    char dia[4], mes[4], ano[6];
    printf("\nData de aplicacao: \n");

    while(1)
    {
        ler(" -Dia: ", dia);
        if (dia[0] == '\0' || dia[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! \n");
            continue;
        }
        else break;
    }
    while(1)
    {
        ler("-Mes: ", mes);
        if (mes[0] == '\0' || mes[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! \n");
            continue;
        }
        else break;
    }
    while(1)
    {
        ler("-Ano: ", ano);
        if (ano[0] == '\0' || ano[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! \n");
            continue;
        }
        else break;
    }

    p_investimentos[index].data_aplicacao[0] = atoi(dia);
    p_investimentos[index].data_aplicacao[1] = atoi(mes);
    p_investimentos[index].data_aplicacao[2] = atoi(ano);
}

void inserir_investimento_prazo(int index)
{
    char valor[10];
    ler("\nPrazo do investimento (dias): ", valor);
    p_investimentos[index].prazo = atoi(valor);
    //inserir tratamento de erros
}

void calcular_valorizacao(int index)
{
    //calculo baseado no tempo, valor e rent
    if (p_investimentos[index].tempo < 365) p_investimentos[index].valorizacao = 0;
    else
    {
        if (p_investimentos[index].tempo < p_investimentos[index].prazo)
        {
            float capital = p_investimentos[index].valor;
            float juros = p_investimentos[index].rent_anual / 100;
            float anos = ((float)p_investimentos[index].tempo / 365.0);
            p_investimentos[index].valorizacao = capital * pow(1+juros, anos);
        }
        else
        {
            float capital = p_investimentos[index].valor;
            float juros = p_investimentos[index].rent_anual / 100;
            float anos = ((float)p_investimentos[index].prazo / 365.0);
            p_investimentos[index].valorizacao = capital * pow(1+juros, anos);
        }
    }
    if(controle_investidores() != 0)
    {
        inserir_investidor_patrimonio(buscar_investidor_codigo(p_investimentos[index].codigo_do_investidor) ,p_investimentos[index].valorizacao);
    }
}

void inserir_investimento()
{
    iniciar_memoria_investimento();
    printf("\n");
    printf("\n=== Preencha os campos abaixo === \n");
    inserir_investimento_codigo(c_investimento);
    inserir_investimento_investidor(c_investimento);
    inserir_investimento_tipo(c_investimento);
    inserir_investimento_rent(c_investimento);
    inserir_investimento_valor(c_investimento);
    inserir_investimento_descricao(c_investimento);
    inserir_investimento_data(c_investimento);
    inserir_investimento_prazo(c_investimento);

    calcular_investimento_tempo(c_investimento);
    calcular_valorizacao(c_investimento);



    printf("\nInvestimento Cadastrado com sucesso! "
           "\nLembre-se do codigo do investimento se quiser acessa-lo no futuro! \n");

    c_investimento++;

    if (controle_investidores() != 0)
    {
        inserir_tipo_do_investimento(buscar_investidor_codigo(p_investimentos[c_investimento - 1].codigo_do_investidor)); //inserir em investidores
    }
}

void alterar_investimento()
{
    if (c_investimento == 0) printf("Ainda nao ha nenhum investimento cadastrado! \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investimento que deseja encontrar: ", busca);
        index = buscar_investimento_codigo(busca);

        if (index == -1)
        {
            printf("Nao existe nenhum investidor cadastrado com esse codigo! \n");
        }
        else
        {
            int op;
            printf("\nQual campo deseja alterar? \n");
            printf("[1] Tipo \n"
                   "[2] Valor \n"
                   "[3] Descricao \n"
                   "[4] Data de aplicacao \n"
                   "[5] Prazo \n");
            while (1) {
                op = 0;
                char valor[2];
                ler("Sua opcao: ", valor);
                op = atoi(valor);
                printf(" ");
                if (op >= 1 && op <= 5) break;
            }

            switch (op) {
                case 1:
                    inserir_investimento_tipo(index);
                    if (controle_investidores() != 0)
                    {
                        inserir_tipo_do_investimento(buscar_investidor_codigo(p_investimentos[index - 1].codigo_do_investidor));
                    }
                    break;
                case 2:
                    inserir_investimento_valor(index);
                    inserir_investidor_patrimonio(buscar_investidor_codigo(p_investimentos[index].codigo_do_investidor) ,-(p_investimentos[index].valorizacao));
                    calcular_valorizacao(index);
                    break;
                case 3:
                    inserir_investimento_descricao(index);
                    break;
                case 4:
                    inserir_investimento_data(index);
                    inserir_investidor_patrimonio(buscar_investidor_codigo(p_investimentos[index].codigo_do_investidor) ,-(p_investimentos[index].valorizacao));
                    calcular_valorizacao(index);
                    break;
                case 5:
                    inserir_investimento_prazo(index);
                    inserir_investidor_patrimonio(buscar_investidor_codigo(p_investimentos[index].codigo_do_investidor) ,-(p_investimentos[index].valorizacao));
                    calcular_valorizacao(index);
                    break;
            }
        }
    }
}

void excluir_investimento()
{
    if (c_investimento == 0) printf("Ainda nao ha nenhum investimento cadastrado! \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investimento que deseja encontrar: ", busca);
        index = buscar_investimento_codigo(busca);
        int index_investidor = buscar_investidor_codigo(p_investimentos[index].codigo_do_investidor);

        if (index == -1)
        {
            printf("Nao existe nenhum investidor cadastrado com esse codigo! \n");
        }
        else
        {
            inserir_investidor_patrimonio(index_investidor ,-(p_investimentos[index].valorizacao));
            limpar_memoria_investimento(index);
            inserir_tipo_do_investimento(index_investidor);
        }
    }
}

//MOSTRAR POR FILTROS
void mostrar_investimento_index(int index)
{
    char matriz [][6] =
            {
                "Acao",
                "CDB",
                "CRA",
                "CRI",
                "LCA",
                "LCI"
            };

    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
    printf("Investimento: ");
    printf("%s \n", p_investimentos[index].codigo_investimento);
    printf("Investidor: ");
    printf("%s \n", p_investimentos[index].codigo_do_investidor);
    printf("Tipo de investimento: ");
    printf("%s \n", matriz[p_investimentos[index].tipo-1]);
    printf("Rentabilidade anual: ");
    printf("%.2f%% \n", p_investimentos[index].rent_anual);
    printf("Valor: ");
    printf("R$%.2f \n", p_investimentos[index].valor);
    printf("Descricao: ");
    printf("%s \n", p_investimentos[index].descricao);
    printf("Tempo investido: ");
    printf("%d dias \n", p_investimentos[index].tempo);
    printf("Data de aplicacao: ");
    printf("%d/%d/%d \n", p_investimentos[index].data_aplicacao[0], p_investimentos[index].data_aplicacao[1], p_investimentos[index].data_aplicacao[2]);
    printf("Prazo: ");
    printf("%d dias \n", p_investimentos[index].prazo);
    printf("Valorizacao: ");
    printf("R$%.2f \n", p_investimentos[index].valorizacao);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
}

void mostrar_investimento_codigo()
{
    if (c_investimento == 0) printf("Ainda nao ha nenhum investidor cadastrado. \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investimento que deseja encontrar: ", busca);
        index = buscar_investimento_codigo(busca);
        if (index == -1) printf("Nao existe um investidor com esse codigo \n");
        else mostrar_investimento_index(index);
    }
}

void mostrar_investimento_investidor()
{
    if (c_investimento == 0) printf("Ainda nao ha nenhum investimento cadastrado! \n");
    else
    {
        char busca[11];
        int v = 0;
        ler("Digite o codigo do investidor que deseja encontrar: ", busca);

        for (int i = 0; i <= c_investimento; i++)
        {
            if (strcmp(p_investimentos[i].codigo_do_investidor, busca) == 0)
            {
                mostrar_investimento_index(i);
                v++;
            }
        }
        if (v == 0) printf("Nao ha investidores com esse codigo! \n");
    }
}

void mostrar_alfabetica()
{
    if (c_investimento == 0) printf("Ainda nao ha nenhum investimento cadastrado! \n");
    int i;
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 1)
        {
            mostrar_investimento_index(i);
        }
    }
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 2)
        {
            mostrar_investimento_index(i);
        }
    }
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 3)
        {
            mostrar_investimento_index(i);
        }
    }
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 4)
        {
            mostrar_investimento_index(i);
        }
    }
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 5)
        {
            mostrar_investimento_index(i);
        }
    }
    for (i=0; i<=c_investimento; i++)
    {
        if (p_investimentos[i].tipo == 6)
        {
            mostrar_investimento_index(i);
        }
    }
}

//SALVAR DADOS EM ARQUIVO
void criar_arquivo_investimentos()
{
    FILE *file_investimentos;
    file_investimentos = fopen("C:\\Users\\Ryan\\CLionProjects\\Trabalho_Investidores\\Investimentos.txt", "w");
    //inserir path de local onde deseja criar o arquivo -^

    char matriz [][6] =
            {
                    "Acao",
                    "CDB",
                    "CRA",
                    "CRI",
                    "LCA",
                    "LCI"
            };

    for (int i=0; i<c_investimento; i++)
    {


        fprintf(file_investimentos, "\n-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
        fprintf(file_investimentos, "Investimento: ");
        fprintf(file_investimentos, "%s \n", p_investimentos[i].codigo_investimento);
        fprintf(file_investimentos, "Investidor: ");
        fprintf(file_investimentos, "%s \n", p_investimentos[i].codigo_do_investidor);
        fprintf(file_investimentos, "Tipo de investimento: ");
        fprintf(file_investimentos, "%s \n", matriz[p_investimentos[i].tipo-1]);
        fprintf(file_investimentos, "Rentabilidade anual: ");
        fprintf(file_investimentos, "%.2f%% \n", p_investimentos[i].rent_anual);
        fprintf(file_investimentos, "Valor: ");
        fprintf(file_investimentos, "R$%.2f \n", p_investimentos[i].valor);
        fprintf(file_investimentos, "Descricao: ");
        fprintf(file_investimentos, "%s \n", p_investimentos[i].descricao);
        fprintf(file_investimentos, "Tempo investido: ");
        fprintf(file_investimentos, "%d dias \n", p_investimentos[i].tempo);
        fprintf(file_investimentos, "Data de aplicacao: ");
        fprintf(file_investimentos, "%d/%d/%d \n", p_investimentos[i].data_aplicacao[0], p_investimentos[i].data_aplicacao[1], p_investimentos[i].data_aplicacao[2]);
        fprintf(file_investimentos, "Prazo: ");
        fprintf(file_investimentos, "%d dias \n", p_investimentos[i].prazo);
        fprintf(file_investimentos, "Valorizacao: ");
        fprintf(file_investimentos, "R$%.2f \n", p_investimentos[i].valorizacao);
        fprintf(file_investimentos, "-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
        fprintf(file_investimentos, "\n");
    }

    fclose(file_investimentos);
}

#pragma clang diagnostic pop