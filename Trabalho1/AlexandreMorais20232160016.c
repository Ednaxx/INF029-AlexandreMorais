// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Alexandre Morais
//  email: xandre2setembro2002@hotmail.com
//  Matrícula: 20232160016
//  Semestre: 2024.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AlexandreMorais20232160016.h" // Substitua pelo seu arquivo de header renomeado

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x) { //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a) {
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}



DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if (i == 1 || i == 2) sDia[i] = '\0';
	else {
		dq.valido = 0;
    return dq;
  }  


	int j = i + 1;
	i = 0;

	while (data[j] != '/') {
		sMes[i] = data[j];
		i++;
    j++;
	}

	if (i == 1 || i == 2) sMes[i] = '\0';
  else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1;
	i = 0;
	
	while (data[j] != '\0') {
	 	sAno[i] = data[j];
	 	i++;
    j++;
	}

	if (i == 2 || i == 4) sAno[i] = '\0';
	else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

  if (dq.iAno < 100) dq.iAno += 2000;

	dq.valido = 1;
  
  return dq;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

int mesNaoTem31Dias(int mes) {
  int mesesNaoTem31dias[] = {2, 4, 6, 9, 11};

  for (int i = 0; i < 5; i++) {
    if (mes == mesesNaoTem31dias[i]) return 1;
  }

  return 0;
}

int ehAnoBissexto(int ano) {
  return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int q1(char data[])
{
  DataQuebrada dataQuebrada = quebraData(data);
  if (dataQuebrada.valido == 0) return 0;

  if (dataQuebrada.iAno < 1 || dataQuebrada.iMes < 1 || dataQuebrada.iMes > 12
    || dataQuebrada.iDia < 1 || dataQuebrada.iDia > 31) return 0;

  if (dataQuebrada.iDia == 31 && mesNaoTem31Dias(dataQuebrada.iMes)) return 0;

  if (dataQuebrada.iDia > 29 && dataQuebrada.iMes == 2) return 0;

  if (!ehAnoBissexto(dataQuebrada.iAno) && dataQuebrada.iMes == 2 && dataQuebrada.iDia == 29) return 0;

  return 1;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */

DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  int diasDoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  DataQuebrada dataInicialQuebrada = quebraData(datainicial);
  DataQuebrada dataFinalQuebrada = quebraData(datafinal);
    
  DiasMesesAnos dma;
  dma.qtdDias = 0;
  dma.qtdMeses = 0;
  dma.qtdAnos = 0;
  dma.retorno = 0;


  if (q1(datainicial) == 0) {
    dma.retorno = 2;
    return dma;
  }

  if (q1(datafinal) == 0) {
    dma.retorno = 3;
    return dma;
  }

  if (dataFinalQuebrada.iAno < dataInicialQuebrada.iAno) {
    dma.retorno = 4;
    return dma;
  };

  if (dataFinalQuebrada.iAno == dataInicialQuebrada.iAno && dataFinalQuebrada.iMes < dataInicialQuebrada.iMes) {
    dma.retorno = 4;
    return dma;
  };

  if (dataFinalQuebrada.iAno == dataInicialQuebrada.iAno 
    && dataFinalQuebrada.iMes == dataInicialQuebrada.iMes
    && dataFinalQuebrada.iDia < dataInicialQuebrada.iDia) {
    dma.retorno = 4;
    return dma;
  };

    
  dma.qtdAnos = dataFinalQuebrada.iAno - dataInicialQuebrada.iAno;
  dma.qtdMeses = dataFinalQuebrada.iMes - dataInicialQuebrada.iMes;
  dma.qtdDias = dataFinalQuebrada.iDia - dataInicialQuebrada.iDia;

  if (dma.qtdDias < 0) {
    dma.qtdDias += diasDoMes[dataInicialQuebrada.iMes - 1];
    dma.qtdMeses--;
  }
  if (dma.qtdMeses < 0) {
    dma.qtdMeses += 12;
    dma.qtdAnos--;
  }

  for (int i = dataInicialQuebrada.iAno; i <= dataFinalQuebrada.iAno; i++) {
    if (ehAnoBissexto(i)) {
      if (i == dataInicialQuebrada.iAno && i != dataFinalQuebrada.iAno && dataInicialQuebrada.iMes <= 2)
        dma.qtdDias++;
      if (i == dataFinalQuebrada.iAno && dataFinalQuebrada.iMes > 2) dma.qtdDias++;
    }
  }

  dma.retorno = 1;
  return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
  int qtdOcorrencias = 0;

  if (isCaseSensitive) {
    for (int i = 0; texto[i] != '\0'; i++) {
      if (texto[i] == c) qtdOcorrencias++;
    }
    return qtdOcorrencias;
  }

  if (c < 97) c += 32;

  if (!isCaseSensitive) {
    for (int i = 0; texto[i] != '\0'; i++) {
      if (texto[i] == c || texto[i] + 32 == c) qtdOcorrencias++;
    }
    return qtdOcorrencias;
  }

  return -1;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
    
int q4(char strTexto[], char strBusca[], int posicoes[30]) {
  int qtdOcorrencias = 0;
  int qtdAcentos = 0;
  int posicaoParaAcrescentar = 0;
    

  for (int i = 0; strTexto[i] != '\0'; i++) {
    if (strTexto[i] < 0) {
      qtdAcentos++;
      i++;
      continue;
    };
    
    if (strTexto[i] != strBusca[0]) continue;

    
    int presente = 1;
    int auxTexto = i;
    int iteradorBusca = 0;
    
    while (strBusca[iteradorBusca + 1] != '\0' && presente) {
      auxTexto++;
      iteradorBusca++;

      if (strTexto[auxTexto] != strBusca[iteradorBusca] || strTexto[auxTexto] == '\0') {
        presente = 0;
        break;
      };
    }
    
    if (presente) {
      posicoes[posicaoParaAcrescentar] = i + 1 - qtdAcentos ;
      posicoes[posicaoParaAcrescentar + 1] = i + 1 + iteradorBusca - qtdAcentos;
    
      posicaoParaAcrescentar += 2;
      qtdOcorrencias++;
      i += iteradorBusca;
    }
  }
    
  return qtdOcorrencias;
}

    
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
  int ordemDeGrandeza = 0;
  int aux = num;

  while (aux > 0) {
    aux /= 10;
    ordemDeGrandeza++;
  }
    
    
  int *numeroInversoArray = malloc(ordemDeGrandeza * sizeof(int));
    
  for (int i = 0; i < ordemDeGrandeza; i++) {
    numeroInversoArray[i] = num % 10;
    num /= 10;
  }

  for (int i = 0; i < ordemDeGrandeza; i++) {
    num += numeroInversoArray[i];
    num *= 10;
  }

  num /= 10;
  
  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numeroBase, int numeroBusca) {
  int qtdOcorrencias = 0;
  int ordemDeGrandezaNumeroBusca = 0;
  int ordemDeGrandezaNumeroBase = 0;

    
  int aux = numeroBusca;
  while (aux > 0) {
    aux /= 10;
    ordemDeGrandezaNumeroBusca++;
  }

  aux = numeroBase;
  while (aux > 0) {
    aux /= 10;
    ordemDeGrandezaNumeroBase++;
  }
  

  for (int i = 0; i < ordemDeGrandezaNumeroBase; i++) {
    if (numeroBase % 10 != numeroBusca % 10) {
      numeroBase /= 10;
      continue;
    };

    numeroBase /= 10;

    int presente = 1;
    int aux1 = numeroBusca;
    int aux2 = numeroBase;
    
    for (int j = 1; j < ordemDeGrandezaNumeroBusca && presente; j++) {
      aux1 /= 10;
      aux2 /= 10;

      if (aux2 % 10 != aux1 % 10) {
        presente = 0;
        break;
      }
    }

    if (presente) qtdOcorrencias++;
  }
    
  return qtdOcorrencias;
}
