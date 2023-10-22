#ifndef TRABALHO_INVESTIDORES_INVESTIMENTOS_H
#define TRABALHO_INVESTIDORES_INVESTIMENTOS_H

struct investimentos{
    char codigo_investimento[10];
    char codigo_do_investidor[10];
    enum tipos {Acao=1, CDB, CRA, CRI ,LCA, LCI} tipo;
    float valor;
    char descricao[255];
    int tempo;
    float rent_anual;
    int data_aplicacao[3];
    int prazo;
    float valorizacao;
};

int controle_investimentos();

void iniciar_memoria_investimento();
int buscar_investimento_codigo(char busca[]);
void limpar_memoria_investimento(int index);

void inserir_investimento();
void inserir_investimento_codigo(int index);
void inserir_investimento_investidor(int index);
void inserir_investimento_tipo(int index);
void inserir_investimento_rent(int index);

char exportar_investimento_tipo(char codigo[], int tipo);
float exportar_investimento_valorizacao(char codigo[], int index);

void inserir_investimento_valor(int index);
void inserir_investimento_descricao(int index);
void inserir_investimento_data(int index);
void inserir_investimento_prazo(int index);

void calcular_investimento_tempo(int index);
void calcular_valorizacao(int index);


void alterar_investimento();
void excluir_investimento();

void mostrar_investimento_index(int index);
void mostrar_investimento_codigo();
void mostrar_investimento_investidor();
void mostrar_alfabetica();

void criar_arquivo_investimentos();

#endif
