#ifndef TRABALHO_INVESTIDORES_INVESTIDORES_H
#define TRABALHO_INVESTIDORES_INVESTIDORES_H

struct investidores{
    char codigo_investidor[10];
    char cpf[13];
    char nome[255];
    char endereco[255];
    int nascimento[3];
    float salario;
    float patrimonio;
    char tipo_do_investimento[8];
};

void ler(char msg[], char valor[]);
int controle_investidores();

void iniciar_memoria_investidor();
int buscar_investidor_codigo(char busca[]);
int buscar_investidor_cpf(char busca[]);
int buscar_investidor_patrimonio(float valor);
void limpar_memoria_investidor (int index);

void inserir_investidor();
void inserir_investidor_codigo(int index);
void inserir_investidor_cpf(int index);
void inserir_investidor_nome(int index);
void inserir_investidor_endereco(int index);
void inserir_investidor_nascimento(int index);
void inserir_investidor_salario(int index);
void inserir_investidor_patrimonio(int index, float valorizacao);
void inserir_investidor_patrimonio2(int index);
void inserir_tipo_do_investimento(int index);

void alterar_investidor();
void excluir_investidor();

int mostrar_investidor_index(int index);
void mostrar_investidor_codigo();
void mostrar_investidor_investimento();
void mostrar_todos();
void mostrar_crescente();

void criar_arquivo_investidores();

#endif
