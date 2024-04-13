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
#include "AlexandreMorais20232160016.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
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
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}



DataQuebrada quebraData(char data[]){
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
  int meses30dias[] = {2, 4, 6, 9, 11};

  for (int i = 0; i < 5; i++) {
    if (mes == meses30dias[i]) return 1;
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

int converterDataParaDias(DataQuebrada dataQuebrada) {
  int dias = dataQuebrada.iDia;
  
  for (int i = 1; i < dataQuebrada.iMes; i++) {
    if (!mesNaoTem31Dias(i)) dias += 31;
    else if (i == 2) dias += (ehAnoBissexto(dataQuebrada.iAno) ? 29 : 28);
    else dias += 30;
  }

  for (int i = 1; i < dataQuebrada.iAno; i++) dias += 365;

  return dias;
}

DiasMesesAnos converterDiasParaData(int dias) {
  DiasMesesAnos data;
  data.qtdDias = 0;
  data.qtdMeses = 0;
  data.qtdAnos = 0;
  
  while (dias >= 365) {
    if (ehAnoBissexto(data.qtdAnos + 1) && (dias < 366)) break;
    if (ehAnoBissexto(data.qtdAnos + 1) && (dias >= 366)) dias--;
    dias -= 365;
    data.qtdAnos++;
  }

  if (dias > 30) {
    dias -= 30;
    data.qtdMeses++;
    
    if (dias > 28) {
      dias -= 28;
      data.qtdMeses++;
    }
  }

  while (dias > 30) {
    if (!mesNaoTem31Dias(data.qtdMeses + 1)) dias--;
    dias -= 30;
    data.qtdMeses++;
  }

  data.qtdDias += dias;
    
  return data;
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  DataQuebrada dataInicialQuebrada = quebraData(datainicial);
  DataQuebrada dataFinalQuebrada = quebraData(datafinal);
  DiasMesesAnos dma;

    
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

  printf("\n%d/%d/%d - %d/%d/%d\n", 
    dataFinalQuebrada.iDia, dataFinalQuebrada.iMes, dataFinalQuebrada.iAno,
    dataInicialQuebrada.iDia, dataInicialQuebrada.iMes, dataInicialQuebrada.iAno);
  
  int diasDataInicial = converterDataParaDias(dataInicialQuebrada);
  int diasDataFinal = converterDataParaDias(dataFinalQuebrada);
  
  int diferencaDeDias = diasDataFinal - diasDataInicial;
  printf("\n%d dias de diferenca\n", diferencaDeDias);
  dma = converterDiasParaData(diferencaDeDias);
  dma.retorno = 1;

  printf("\n%d/%d/%d\n", dma.qtdDias, dma.qtdMeses, dma.qtdAnos);
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
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int qtdOcorrencias = -1;

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

int q5(int num)
{

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

int q6(int numerobase, int numerobusca)
{
  int qtdOcorrencias;
  return qtdOcorrencias;
}
