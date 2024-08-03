#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

int menu();

int menu() {
    int opcao;
    printf("Digite as opção desejada\n");
    printf("1 - Inserir\n");
    printf("2 - Listar tudo\n");
    printf("3 - Listar ordenado\n");
    printf("4 - Listar tudo ordenado\n");
    printf("5 - Excluir valor\n");
    printf("6 - Modificar tamanho da estrutura\n");
    printf("7 - Sair\n");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    inicializar();
    int opcao;
    int retorno;

    while (1) {
        opcao = menu();

        if (opcao == 1) {
            int posicao;
            int valor;

            printf("Insira a posicao da estrutura\n\n");
            scanf("%d", &posicao);
            printf("Insira o valor\n\n");
            scanf("%d", &valor);

            retorno = inserirNumeroEmEstrutura(posicao, valor);

            if (retorno == SUCESSO) printf("Inserido com sucesso\n\n");
            else if (retorno == SEM_ESPACO) printf("Estrutura sem espaço\n\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) {
                int tamanho;
                printf("Sem estrutura auxiliar, por favor insira o tamanho da estrutura a ser inicializada\n\n");
                scanf("%d", &tamanho);

                retorno = criarEstruturaAuxiliar(posicao, tamanho);

                if (retorno == SUCESSO) inserirNumeroEmEstrutura(posicao, valor);
                else if (retorno == SEM_ESPACO_DE_MEMORIA) 
                    printf("Sem espaco de memoria. Libere memoria ou utilize uma estrutura de tamanho menor.\n\n");
                else if (retorno == TAMANHO_INVALIDO) printf("Tamanho invalido (deve ser > 1)");
                else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida (deve ser >= 1 e <= 10)");
            }
        }

        else if (opcao == 2) {
            int quantidades[TAM];
            int existeEstruturaAuxiliar = 0;

            for (int i = 0; i < TAM; i++) {
                if (validarAntesDePegarQuantidadeDeElementos(i + 1) == SUCESSO) {
                    quantidades[i] = getQuantidadeElementosEstruturaAuxiliarSemRetornos(i + 1);
                    existeEstruturaAuxiliar = 1;
                }
            }

            if (!existeEstruturaAuxiliar) printf("Todas as estruturas estao vazias.\n");

            for (int i = 0; i < TAM && validarAntesDePegarQuantidadeDeElementos(i + 1) == SUCESSO; i++) {
                int vetorAux[quantidades[i]];
                getDadosEstruturaAuxiliar(i + 1, vetorAux);

                printf("\nPosicao - %d; %d elementos: ", i + 1, quantidades[i]);
                for (int j = 0; j < quantidades[i]; j++) printf("%d ", vetorAux[j]);
            }
            printf("\n");
        }

        else if (opcao == 3) {
            int posicao;

            printf("Insira a posicao da estrutura\n\n");
            scanf("%d", &posicao);

            retorno = validarAntesDePegarQuantidadeDeElementos(posicao);

            if (retorno == ESTRUTURA_AUXILIAR_VAZIA) 
                printf("Estrutura vazia nessa posicao.");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) printf("Sem estrutura auxiliar nessa posicao.");
            else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida (deve ser >= 1 e <= 10).");
            
            else {
                int quantidade = getQuantidadeElementosEstruturaAuxiliarSemRetornos(posicao);
                int vetorAux[quantidade];
                getDadosOrdenadosEstruturaAuxiliar(posicao, vetorAux);

                for (int i = 0; i < quantidade; i++) printf("%d ", vetorAux[i]);
            }

            printf("\n\n");
        }

        else if (opcao == 4) {
            int quantidadeTotal = 0;

            for (int i = 0; i < TAM; i++) {
                if (validarAntesDePegarQuantidadeDeElementos(i + 1) == SUCESSO)
                    quantidadeTotal = getQuantidadeElementosEstruturaAuxiliarSemRetornos(i + 1);
            }

            if (quantidadeTotal == 0) printf("Todas as estruturas estao vazias.");

            int vetorAux[quantidadeTotal];
            getDadosOrdenadosDeTodasEstruturasAuxiliares(vetorAux);

            for (int i = 0; i < quantidadeTotal; i++) {
                printf("%d ", vetorAux[i]);
            }
            printf("\n\n");
        }

        else if (opcao == 5) {
            int posicao;
            int valor;

            printf("Insira a posicao da estrutura\n\n");
            scanf("%d", &posicao);

            printf("Insira o valor\n\n");
            scanf("%d", &valor);

            retorno = excluirNumeroEspecificoDeEstrutura(posicao, valor);

            if (retorno == SUCESSO) printf("Sucesso.\n\n");
            else if (retorno == ESTRUTURA_AUXILIAR_VAZIA) printf("Estrutura vazia.\n\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) printf("Sem estrutura auxiliar.\n\n");
            else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida.\n\n");
            else if (retorno == NUMERO_INEXISTENTE) printf("Numero inexistente.\n\n");
        }

        else if (opcao == 6) {
            int posicao;
            int tamanho;

            printf("Insira a posicao.\n\n");
            scanf("%d", &posicao);

            printf("Insira o tamanho a ser adicionado.\n\n");
            scanf("%d", &tamanho);

            retorno = modificarTamanhoEstruturaAuxiliar(posicao, tamanho);

            if (retorno == SUCESSO) printf("Sucesso.\n\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) printf("Sem estrutura auxiliar.\n\n");
            else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida.\n\n");
            else if (retorno == TAMANHO_INVALIDO) printf("O tamanho nao pode ser negativo.\n\n");
            else if (retorno == SEM_ESPACO_DE_MEMORIA) printf("Erro na alocação do novo valor.\n\n");
        }

        else if (opcao == 7) {
            finalizar();
            break;
        }

        else printf("opcao inválida\n\n");
    }

    return 0;
}
