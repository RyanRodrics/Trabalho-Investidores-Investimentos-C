#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include "investidores.h"
#include "investimentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct investidores *p_investidores = NULL;
int c_investidores = 0;


//CONTROLE E BUSCA DA MEMORIA
void ler(char msg[], char valor[])
{
    valor[0] = 0;
    valor[1] = 0;
    printf("%s", msg);
    fflush(stdin);
    gets(valor);
}

int controle_investidores()
{
    return c_investidores;
}

void limpar_memoria_investidor(int index)
{
    // limpar todos os campos da struct
    int i;
    for (i=0; i<255; i++)
    {
        p_investidores[index].nome[i] = 0;
        p_investidores[index].endereco[i] = 0;
    }
    for (i=0; i<10; i++)
    {
        p_investidores[index].codigo_investidor[i] = 0;
    }
    for (i=0; i<13; i++)
    {
        p_investidores[index].cpf[i] = 0;
    }
    for (i=0; i<3; i++)
    {
        p_investidores[index].nascimento[i]=0;
    }
    p_investidores[index].salario = 0;
    p_investidores[index].patrimonio = 0;
    for (i=0; i<3; i++)
    {
        p_investidores[index].tipo_do_investimento[i] = 0;
    }
}

void iniciar_memoria_investidor()
{
    //alocar
    if (c_investidores == 0)
        p_investidores = malloc(50 * sizeof(struct investidores));
    //p = realloc(p, c_investidores+1);
    //limpar a memoria alocada
    limpar_memoria_investidor(c_investidores);
}

int buscar_investidor_codigo(char busca[])
{
    for (int i = 0; i <= c_investidores; i++)
    {
        if (strcmp(p_investidores[i].codigo_investidor, busca) == 0)
        {
            return i;
        }
    }
    return -1;
}

int buscar_investidor_cpf(char busca[])
{
    for (int i = 0; i <= c_investidores; i++)
    {
        if (strcmp(p_investidores[i].cpf, busca) == 0)
        {
            return i;
        }
    }
    return -1;
}

int buscar_investidor_patrimonio(float valor)
{
    for (int i = 0; i <= c_investidores; i++)
    {
        if (p_investidores[i].patrimonio == valor)
        {
            return i;
        }
    }
    return -1;
}

//INSERIR, ALTERAR E EXCLUIR
void inserir_investidor_codigo(int index)
{
    char codigo[10];
    while (1)
    {
        while(1)
        {
            ler("\nCodigo investidor (8 digitos): ", codigo);
            if (codigo[0] == '\0' || codigo[0] == ' ')
            {
                printf("Nao deixe esse campo em branco! ");
                continue;
            }
            else break;
        }

        if (buscar_investidor_codigo(codigo) == -1)
        {
            strcpy(p_investidores[index].codigo_investidor, codigo);
            break;
        }
        else
        {
            printf("Esse codigo ja esta cadastrado, tente novamente! \n");
        }
    }
}

void inserir_investidor_cpf(int index)
{
    char codigo[13];
    while (1)
    {
        while(1)
        {
            ler("\nCPF (11 digitos): ", codigo);
            if (codigo[0] == '\0' || codigo[0] == ' ')
            {
                printf("Nao deixe esse campo em branco! ");
                continue;
            }
            else break;
        }

        if (buscar_investidor_cpf(codigo) == -1)
        {
            strcpy(p_investidores[index].cpf, codigo);
            break;
        }
        else
        {
            printf("Esse cpf ja esta cadastrado, tente novamente! \n");
        }
    }
}

void inserir_investidor_nome(int index)
{
    while(1)
    {
        ler("\nNome: ", p_investidores[index].nome);
        if (p_investidores[index].nome[0] == '\0' || p_investidores[index].nome[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }
}

void inserir_investidor_endereco(int index)
{
    ler("\nEndereco: ", p_investidores[index].endereco);
}

void inserir_investidor_nascimento(int index)
{
   char dia[4], mes[4], ano[6];
   printf("\nData de nascimento: \n");

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

   p_investidores[index].nascimento[0] = atoi(dia);
   p_investidores[index].nascimento[1] = atoi(mes);
   p_investidores[index].nascimento[2] = atoi(ano);
}

void inserir_investidor_salario(int index)
{
    char salario[10];
    while(1)
    {
        ler("\nSalario: ", salario);
        if (salario[0] == '\0' || salario[0] == ' ')
        {
            printf("Nao deixe esse campo em branco! ");
            continue;
        }
        else break;
    }
    p_investidores[index].salario = atof(salario);
}

void inserir_investidor_patrimonio(int index, float valorizacao)
{
    p_investidores[index].patrimonio += valorizacao;
    //inserir tratamento de erros
}

void inserir_investidor_patrimonio2(int index)
{
    for (int i=0; i<controle_investimentos(); i++)
    {
        p_investidores[index].patrimonio += exportar_investimento_valorizacao(p_investidores[index].codigo_investidor, i);
    }
}

void inserir_tipo_do_investimento(int index)
{
    if (controle_investimentos() != 0)
    {
        for (int i=0; i<6; i++)
        {
            p_investidores[index].tipo_do_investimento[i] = exportar_investimento_tipo(p_investidores[index].codigo_investidor, i+1);
        }
    }
}

void inserir_investidor()
{
    iniciar_memoria_investidor();
    printf("\n");
    printf("=== Preencha os campos abaixo === \n");
    inserir_investidor_codigo(c_investidores);
    inserir_investidor_cpf(c_investidores);
    inserir_investidor_nome(c_investidores);
    inserir_investidor_endereco(c_investidores);
    inserir_investidor_nascimento(c_investidores);
    inserir_investidor_salario(c_investidores);
    inserir_tipo_do_investimento(c_investidores);
    if (controle_investimentos() != 0) inserir_investidor_patrimonio2(c_investidores);

    printf("\nInvestidor Cadastrado com sucesso! "
           "\nLembre-se do codigo do investidor se quiser acessa-lo no futuro! \n");


    c_investidores++;
}

void alterar_investidor()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investidor que deseja encontrar: ", busca);
        index = buscar_investidor_codigo(busca);

        if (index == -1)
        {
            printf("Nao existe nenhum investidor cadastrado com esse codigo! \n");
        }
        else
        {
            int op;
            char valor[2];
            printf("\nQual campo deseja alterar? \n");
            printf("[1] CPF \n"
                   "[2] Nome \n"
                   "[3] Endereco \n"
                   "[4] Data de nascimento \n"
                   "[5] Salario \n");
            while (1) {
                op = 0;
                ler("Sua opcao: ", valor);
                op = atoi(valor);
                printf(" ");
                if (op >= 1 && op <= 5) break;
            }

            switch (op) {
                case 1:
                    inserir_investidor_cpf(index);
                    break;
                case 2:
                    inserir_investidor_nome(index);
                    break;
                case 3:
                    inserir_investidor_endereco(index);
                    break;
                case 4:
                    inserir_investidor_nascimento(index);
                    break;
                case 5:
                    inserir_investidor_salario(index);
                    break;
            }
        }
    }
}

void excluir_investidor()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investidor que deseja encontrar: ", busca);
        index = buscar_investidor_codigo(busca);

        if (index == -1)
        {
            printf("Nao existe nenhum investidor cadastrado com esse codigo! \n");
        }
        else
        {
            limpar_memoria_investidor(index);
            printf("Investidor excluido com sucesso! \n");
        }
    }
}

// MOSTRAR POR FILTROS
int mostrar_investidor_index(int index)
{
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
    printf("Investidor: ");
    printf("%s \n", p_investidores[index].codigo_investidor);
    printf("CPF: ");
    printf("%s \n", p_investidores[index].cpf);
    printf("Nome: ");
    printf("%s \n", p_investidores[index].nome);
    printf("Endereco: ");
    printf("%s \n", p_investidores[index].endereco);
    printf("Data de nascimento: ");
    printf("%d/%d/%d \n", p_investidores[index].nascimento[0], p_investidores[index].nascimento[1], p_investidores[index].nascimento[2]);
    printf("Salario: ");
    printf("R$%.2f \n", p_investidores[index].salario);
    printf("Patrimonio: ");
    printf("R$%.2f \n", p_investidores[index].patrimonio);
    //printf("Tipo: ");
    //printf("%s \n", p[index].tipo_do_investimento);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
}

void mostrar_investidor_codigo()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        int index;
        char busca[11];
        ler("Digite o codigo do investidor que deseja encontrar: ", busca);
        index = buscar_investidor_codigo(busca);

        if (index == -1) printf("Nao existe um investidor com esse codigo! \n");
        else mostrar_investidor_index(index);
    }
}

void mostrar_investidor_investimento()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        int op;
        char valor[2];
        printf("\nQuer mostrar os investidores que possuem qual tipo de investimento: \n");
        printf("[1] Acao \n"
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
        for (int i=0; i<c_investidores; i++)
        {
            if (p_investidores[i].tipo_do_investimento[op-1] == '1') mostrar_investidor_index(i);
        }
    }

    //conectado com a parte de investimentos
}

void mostrar_todos()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        for (int i=0; i<c_investidores; i++)
        {
            mostrar_investidor_index(i);
            printf("\n");
        }
    }
}

void mostrar_crescente()
{
    if (c_investidores == 0) printf("Ainda nao ha nenhum investidor cadastrado! \n");
    else
    {
        float patrimonios[c_investidores], aux;
        int i;

        for (i=0; i<c_investidores; i++)
        {
            patrimonios[i] = p_investidores[i].patrimonio;
        }

        for (i=0; i<c_investidores; i++)
        {
            for (int j=i+1; j<c_investidores; j++)
            {
                if (patrimonios[i] > patrimonios[j])
                {
                    aux = patrimonios[i];
                    patrimonios[i] = patrimonios[j];
                    patrimonios[j] = aux;
                }
            }
        }

        for (i=0; i<c_investidores; i++)
        {
            mostrar_investidor_index(buscar_investidor_patrimonio(patrimonios[i]));
            printf("\n");
        }
    }
}

//SALVAR DADOS EM ARQUIVO
void criar_arquivo_investidores()
{
    FILE *file_investidores;
    file_investidores = fopen("C:\\Users\\Ryan\\CLionProjects\\Trabalho_Investidores\\Investidores.txt", "w");
    //inserir path de local onde deseja criar o arquivo -^
    for (int i=0; i<c_investidores; i++)
    {
        fprintf(file_investidores, "\n-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
        fprintf(file_investidores, "Investidor: ");
        fprintf(file_investidores, "%s \n", p_investidores[i].codigo_investidor);
        fprintf(file_investidores, "CPF: ");
        fprintf(file_investidores, "%s \n", p_investidores[i].cpf);
        fprintf(file_investidores, "Nome: ");
        fprintf(file_investidores, "%s \n", p_investidores[i].nome);
        fprintf(file_investidores, "Endereco: ");
        fprintf(file_investidores, "%s \n", p_investidores[i].endereco);
        fprintf(file_investidores, "Data de nascimento: ");
        fprintf(file_investidores, "%d/%d/%d \n", p_investidores[i].nascimento[0], p_investidores[i].nascimento[1], p_investidores[i].nascimento[2]);
        fprintf(file_investidores, "Salario: ");
        fprintf(file_investidores, "R$%.2f \n", p_investidores[i].salario);
        fprintf(file_investidores, "Patrimonio: ");
        fprintf(file_investidores, "R$%.2f \n", p_investidores[i].patrimonio);
        fprintf(file_investidores, "-=-=-=-=-=-=-=-=-=-=-=-=-=- \n");
        fprintf(file_investidores, "\n");
    }

    fclose(file_investidores);
}

#pragma clang diagnostic pop