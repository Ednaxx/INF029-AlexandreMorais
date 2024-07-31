#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct {
    int * array;
    int tamanho;
    int quantidade;
} EstruturaAuxiliar;

void inicializarEstrutura(EstruturaAuxiliar * estrutura, int tamanho) {
    estrutura->array = (int *) malloc(tamanho * sizeof(int));
    estrutura->tamanho = tamanho;
    estrutura->quantidade = 0;
}

EstruturaAuxiliar * vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1] != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho < 1) return TAMANHO_INVALIDO;

    EstruturaAuxiliar * estruturaAuxiliar = (EstruturaAuxiliar *) malloc(sizeof(EstruturaAuxiliar));
    inicializarEstrutura(estruturaAuxiliar, tamanho);
    vetorPrincipal[posicao - 1] = estruturaAuxiliar;

    if (vetorPrincipal[posicao - 1] == NULL) return SEM_ESPACO_DE_MEMORIA;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;

    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    if (estruturaAuxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (estruturaAuxiliar->tamanho == estruturaAuxiliar->quantidade) return SEM_ESPACO;

    estruturaAuxiliar->array[estruturaAuxiliar->quantidade] = valor;
    estruturaAuxiliar->quantidade++;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;
    
    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    if (estruturaAuxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (estruturaAuxiliar->quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    estruturaAuxiliar->quantidade--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;

    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    if (estruturaAuxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (estruturaAuxiliar->quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;


    int i = 0;
    int achou = 0;

    while (i < estruturaAuxiliar->quantidade && !achou) {
        if (estruturaAuxiliar->array[i] == valor) {
            achou = 1;
            break;
        }
        i++;
    }

    if (!achou) return NUMERO_INEXISTENTE;

    for (int j = i + 1; j < estruturaAuxiliar->quantidade; j++) {
        estruturaAuxiliar->array[j - 1] = estruturaAuxiliar->array[j];
    }

    estruturaAuxiliar->quantidade--;

    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1] == NULL) return SEM_ESTRUTURA_AUXILIAR;

    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    for (int i = 0; i < estruturaAuxiliar->quantidade; i++) vetorAux[i] = estruturaAuxiliar->array[i];

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int compare(const void* a, const void* b) {
     int int_a = *( (int *) a );
     int int_b = *( (int *) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int codigoDeRetorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (codigoDeRetorno != SUCESSO) return codigoDeRetorno;

    qsort(vetorAux, vetorPrincipal[posicao - 1]->quantidade, sizeof(int), compare);

    return codigoDeRetorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int estruturasEncontradas = 0;
    int index = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] == NULL || vetorPrincipal[i]->quantidade == 0) continue;
        EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[i];
        
        for (int j = 0; j < estruturaAuxiliar->quantidade; j++) {
            vetorAux[index] = estruturaAuxiliar->array[j];
            index++;
        }
        estruturasEncontradas++;
    }

    if (estruturasEncontradas == 0) return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    return SUCESSO;
}


/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int codigoDeRetorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (codigoDeRetorno != SUCESSO) return codigoDeRetorno;

    int tamanhoVetor = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] == NULL) continue;
        tamanhoVetor += vetorPrincipal[i]->quantidade;
    }

    qsort(vetorAux, tamanhoVetor, sizeof(int), compare);

    return codigoDeRetorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1] == NULL) return SEM_ESTRUTURA_AUXILIAR;

    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    if (estruturaAuxiliar->tamanho + novoTamanho < 1) return NOVO_TAMANHO_INVALIDO;

    int * novoArray = (int *) malloc((estruturaAuxiliar->tamanho + novoTamanho) * sizeof(int));
    int novaQuantidade = 0;

    while (novaQuantidade < estruturaAuxiliar->quantidade && novaQuantidade < estruturaAuxiliar->tamanho + novoTamanho) {
        novoArray[novaQuantidade] = estruturaAuxiliar->array[novaQuantidade];
        novaQuantidade++;
    }

    free(estruturaAuxiliar->array);
    estruturaAuxiliar->array = novoArray;
    if (estruturaAuxiliar->array == NULL) return SEM_ESPACO_DE_MEMORIA;

    estruturaAuxiliar->tamanho += novoTamanho;
    estruturaAuxiliar->quantidade = novaQuantidade;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1] == NULL) return SEM_ESTRUTURA_AUXILIAR;

    EstruturaAuxiliar * estruturaAuxiliar = vetorPrincipal[posicao - 1];

    if (estruturaAuxiliar->quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;
    
    return estruturaAuxiliar->quantidade;
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
    No * i = *inicio;
    if (i == NULL) return;

    while (i != NULL) {
        No * prox = i->prox;
        free(i);
        i = prox;
    }
    *inicio = NULL;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/

No * inicializarNo() {
    No * no = (No *) malloc(sizeof(No));
    if (no == NULL) return NULL;

    no->conteudo = 0;
    no->prox = NULL;

    return no;
}

No *montarListaEncadeadaComCabecote() {
    int quantidadeTotal = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] == NULL) continue;
        quantidadeTotal += vetorPrincipal[i]->quantidade;
    }

    int todosOsValores[quantidadeTotal];
    if (getDadosDeTodasEstruturasAuxiliares(todosOsValores) != SUCESSO) return NULL;
    
    No * inicio = inicializarNo();
    if (inicio == NULL) return NULL;

    No * tmp = inicio;
    for (int i = 0; i < quantidadeTotal; i++) {
        tmp->conteudo = todosOsValores[i];

        if (i + 1 == quantidadeTotal) break;

        tmp->prox = inicializarNo();
        if (tmp->prox == NULL) {
            destruirListaEncadeadaComCabecote(&inicio);
            return NULL;
            }
        tmp = tmp->prox;
    }

    return inicio;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    if (inicio == NULL) return;
    vetorAux[0] = inicio->conteudo;

    for (int i = 1; inicio->prox != NULL; i++) {
        inicio = inicio->prox;
        vetorAux[i] = inicio->conteudo;
    }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar() {
    for (int i = 0; i < TAM; i++) vetorPrincipal[i] = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) free(vetorPrincipal[i]->array);
        vetorPrincipal[i] = NULL;
    }
}
