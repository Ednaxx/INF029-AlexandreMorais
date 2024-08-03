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

            printf("Insira a posicao da estrutura\n");
            scanf("%d", &posicao);
            printf("Insira o valor\n");
            scanf("%d", &valor);

            retorno = inserirNumeroEmEstrutura(posicao, valor);

            if (retorno == SUCESSO) printf("Inserido com sucesso\n");
            else if (retorno == SEM_ESPACO) printf("Estrutura sem espaço\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) {
                int tamanho;
                printf("Sem estrutura auxiliar, por favor insira o tamanho da estrutura a ser inicializada\n");
                scanf("%d", &tamanho);

                retorno = criarEstruturaAuxiliar(posicao, tamanho);

                if (retorno == SUCESSO) inserirNumeroEmEstrutura(posicao, valor);
                else if (retorno == SEM_ESPACO_DE_MEMORIA) 
                    printf("Sem espaco de memoria. Libere memoria ou utilize uma estrutura de tamanho menor.\n");
                else if (retorno == TAMANHO_INVALIDO) printf("Tamanho invalido (deve ser > 1)");
                else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida (deve ser >= 1 e <= 10)");
            }
        }

        else if (opcao == 2) {
            
        }

        else if (opcao == 3) {
            
        }

        else if (opcao == 4) {
            int quantidadeTotal = 0;

            for (int i = 0; i < 10; i++) {
                quantidadeTotal += getQuantidadeElementosEstruturaAuxiliar(i + 1);
            }
            
            // PROBLEMAS DE RETORNO

            // int vetorAux[quantidadeTotal];
            // getDadosOrdenadosDeTodasEstruturasAuxiliares(vetorAux);

            // for (int i = 0; i < quantidadeTotal; i++) printf("%d ", vetorAux[i]);
        }

        else if (opcao == 5) {
            int posicao;
            int valor;

            printf("Insira a posicao da estrutura\n");
            scanf("%d", &posicao);

            printf("Insira o valor\n");
            scanf("%d", &valor);

            retorno = excluirNumeroEspecificoDeEstrutura(posicao, valor);

            if (retorno == SUCESSO) printf("Sucesso.\n");
            else if (retorno == ESTRUTURA_AUXILIAR_VAZIA) printf("Estrutura vazia.\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) printf("Sem estrutura auxiliar.\n");
            else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida.\n");
            else if (retorno == NUMERO_INEXISTENTE) printf("Numero inexistente.\n");
        }

        else if (opcao == 6) {
            int posicao;
            int tamanho;

            printf("Insira a posicao.\n");
            scanf("%d", &posicao);

            printf("Insira o tamanho a ser adicionado.\n");
            scanf("%d", &tamanho);

            retorno = modificarTamanhoEstruturaAuxiliar(posicao, tamanho);

            if (retorno == SUCESSO) printf("Sucesso.\n");
            else if (retorno == SEM_ESTRUTURA_AUXILIAR) printf("Sem estrutura auxiliar.\n");
            else if (retorno == POSICAO_INVALIDA) printf("Posicao invalida.\n");
            else if (retorno == TAMANHO_INVALIDO) printf("O tamanho nao pode ser negativo.\n");
            else if (retorno == SEM_ESPACO_DE_MEMORIA) printf("Erro na alocação do novo valor.\n");
        }

        else if (opcao == 7) {
            finalizar();
            break;
        }

        else printf("opcao inválida\n");
    }

    return 0;
}
