// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo contém exemplos de testes das questões do trabalho.
//  o aluno pode incrementar os testes

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 19/08/2016 - 12/12/2018

// #################################################

#include <stdio.h>
#include <string.h>

#include "AlexandreMorais20232160016.h"

void testSomar();    //função utilizada para testes
void testFatorial(); //função utilizada para testes
void testQ1();
void testQ2();
void testQ3();
void testQ4();
void testQ5();
void testQ6();
void testQ7();

int main() {
  // testSomar();
  // testFatorial();
  testQ1();
  testQ2();
  testQ3();
  testQ4();
  testQ5();
  testQ6();
}

void testSomar() {
  printf("%d\n", somar(3, 4) == 7);
  printf("%d\n", somar(-1, -3) == -4);
  printf("%d\n", somar(-6, 6) == 0);
  printf("%d\n", somar(74, 9) == 83);
  printf("%d\n", somar(30, -9) == 21);
  printf("%d\n", somar(-2, 8) == 6);
  printf("%d\n", somar(1000, 99) == 1099);
}

void testFatorial() {
  printf("%d\n", fatorial(3) == 6);
  printf("%d\n", fatorial(1) == 1);
  printf("%d\n", fatorial(5) == 120);
}

void testQ1() {
  char str[11];
  strcpy(str, "29/02/2015");
  printf("%d\n", q1(str) == 0);

  strcpy(str, "29/02/2012");
  printf("%d\n", q1(str) == 1);

  strcpy(str, "9/13/2014");
  printf("%d\n", q1(str) == 0);

  strcpy(str, "45/4/2014");
  printf("%d\n", q1(str) == 0);

  strcpy(str, "/9/2014");
  printf("%d\n", q1(str) == 0);

  strcpy(str, "02/02/02");
  printf("%d\n", q1(str) == 1);

  strcpy(str, "30/02/02");
  printf("%d\n", q1(str) == 0);

  strcpy(str, "29/02/2024");
  printf("%d\n", q1(str) == 1);

  strcpy(str, "29/02/2023");
  printf("%d\n", q1(str) == 0);
}

void testQ2() {
  char datainicial[11], datafinal[11];
  int qtdDias, qtdMeses, qtdAnos;
  DiasMesesAnos dma;

  //teste 1
  puts("Teste 1\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial, "01/06/2015");
  strcpy(datafinal, "01/06/2016");
  dma = q2(datainicial, datafinal);
  printf("%d\n", dma.retorno == 1);
  // Optei por ser preciso na quantidade de dias.
  printf("%d\n", dma.qtdDias == 1);
  printf("%d\n", dma.qtdMeses == 0);
  printf("%d\n", dma.qtdAnos == 1);

  //teste 2 - retornos
  puts("\nTeste 2\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"01/30/2015");
  strcpy(datafinal,"01/06/2016");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 2);

  strcpy(datainicial,"01/3/2015");
  strcpy(datafinal,"40/06/2016");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 3);

  strcpy(datainicial,"01/06/2016");
  strcpy(datafinal,"01/06/2015");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 4);

  //teste 3
  puts("\nTeste 3\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"06/06/2017");
  strcpy(datafinal,"07/07/2017");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 1);
  printf("%d\n",dma.qtdMeses == 1);
  printf("%d\n",dma.qtdAnos == 0);

  //teste 4
  puts("\nTeste 4\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"06/06/2017");
  strcpy(datafinal,"05/07/2018");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 29);
  printf("%d\n",dma.qtdMeses == 0);
  printf("%d\n",dma.qtdAnos == 1);

  //teste 5
  puts("\nTeste 5\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"26/07/2017");
  strcpy(datafinal,"25/08/2017");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 30);
  printf("%d\n",dma.qtdMeses == 0);
  printf("%d\n",dma.qtdAnos == 0);

  //teste 6
  puts("\nTeste 6\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"26/06/2017");
  strcpy(datafinal,"26/07/2017");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 0);
  printf("%d\n",dma.qtdMeses == 1);
  printf("%d\n",dma.qtdAnos == 0);

  //teste 8
  puts("\nTeste 8\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"27/02/2016");
  strcpy(datafinal,"03/03/2017");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 5);
  printf("%d\n",dma.qtdMeses == 0);
  printf("%d\n",dma.qtdAnos == 1);

  //teste 9
  puts("\nTeste 9\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"27/02/2015");
  strcpy(datafinal,"03/03/2016");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 5);
  printf("%d\n",dma.qtdMeses == 0);
  printf("%d\n",dma.qtdAnos == 1);

  //teste 10
  puts("\nTeste 10\n");
  qtdDias = -1;
  qtdMeses = -1;
  qtdAnos = -1;

  strcpy(datainicial,"28/01/2016");
  strcpy(datafinal,"29/02/2016");
  dma = q2(datainicial, datafinal);
  printf("%d\n",dma.retorno == 1);
  printf("%d\n",dma.qtdDias == 1);
  printf("%d\n",dma.qtdMeses == 1);
  printf("%d\n",dma.qtdAnos == 0);
}

void testQ3() {
  char str[250];

  strcpy(str,"Renato Lima Novais");
  printf("%d\n",q3(str, 'a', 0) == 3);
  printf("%d\n",q3(str, 'b', 0) == 0);
  printf("%d\n",q3(str, 'l', 1) == 0);
  printf("%d\n",q3(str, 'l', 0) == 1);
  printf("%d\n",q3(str, 'L', 0) == 1);

  strcpy(str,"Letícia, signifiCa fEliCIdADE");
  printf("%d\n",q3(str, 'c', 0) == 3);
  printf("%d\n",q3(str, 'C', 0) == 3);
  printf("%d\n",q3(str, 'c', 1) == 1);
  printf("%d\n",q3(str, 'C', 1) == 2);
  printf("%d\n",q3(str, 'R', 0) == 0);
  printf("%d\n",q3(str, 'e', 0) == 3);
  printf("%d\n",q3(str, 'E', 1) == 2);
  printf("%d\n",q3(str, 'S', 1) == 0);
}

void testQ4() {
  char strTexto[250];
  char strBusca[50];
  int posicoes[30];
  int i;

  puts("Teste 1\n");
  
  for (i = 0; i < 30; i++) {
    posicoes[i] = -1;
  }
  
  strcpy(strTexto, "Laboratorio de programacao: para ratos de programação");
  strcpy(strBusca, "rato");
  printf("%d\n", q4(strTexto, strBusca, posicoes) == 2);
  printf("%d\n", posicoes[0] == 5);
  printf("%d\n", posicoes[1] == 8);
  printf("%d\n", posicoes[2] == 34);
  printf("%d\n", posicoes[3] == 37);

  puts("Teste 2\n");
  
  for (i = 0; i < 30; i++) {
    posicoes[i] = -1;
  }
  
  strcpy(strTexto, "Olá, o mundo é muito grande. Tem muitas pessoas, e muitos problemas");
  strcpy(strBusca, "mui");
  printf("%d\n", q4(strTexto, strBusca, posicoes) == 3);
  printf("%d\n", posicoes[0] == 16);
  printf("%d\n", posicoes[1] == 18);
  printf("%d\n", posicoes[2] == 34);
  printf("%d\n", posicoes[3] == 36);
  printf("%d\n", posicoes[4] == 52);
  printf("%d\n", posicoes[5] == 54);

  puts("Teste 3\n");
  
  for (i = 0; i < 30; i++) {
    posicoes[i] = -1;
  }

  strcpy(strTexto, "ábaco");
  strcpy(strBusca, "ba");
  printf("%d\n", q4(strTexto, strBusca, posicoes) == 1);
  printf("%d\n", posicoes[0] == 2);
  printf("%d\n", posicoes[1] == 3);

  puts("Teste 4\n");
  
  for (i = 0; i<30; i++){
    posicoes[i] = -1;
  }
  
  strcpy(strTexto,"Programar é legal?");
  strcpy(strBusca,"sim");
  printf("%d\n",q4(strTexto, strBusca, posicoes) == 0);

  puts("Teste 5\n");
  
  for (i = 0; i<30; i++){
    posicoes[i] = -1;
  }
  
  strcpy(strTexto,"maraaaavilha, meu prograaaama funcionou");
  strcpy(strBusca,"aa");
  printf("%d\n",q4(strTexto, strBusca, posicoes) == 4);
  printf("%d\n",posicoes[0]==4);
  printf("%d\n",posicoes[1]==5);
  printf("%d\n",posicoes[2]==6);
  printf("%d\n",posicoes[3]==7);
  printf("%d\n",posicoes[4]==24);
  printf("%d\n",posicoes[5]==25);
  printf("%d\n",posicoes[6]==26);
  printf("%d\n",posicoes[7]==27);
}


void testQ5() {
  printf("%d\n", q5(345) == 543);
  printf("%d\n", q5(78) == 87);
  printf("%d\n", q5(3) == 3);
  printf("%d\n", q5(5430) == 345);
}

void testQ6() {
  printf("%d\n", q6(34567368, 3) == 2);
  printf("%d\n", q6(34567368, 4576) == 0);
  printf("%d\n", q6(3539343, 3) == 4);
  printf("%d\n", q6(321, 123) == 0);
  printf("%d\n", q6(1, 1) == 1);
  printf("%d\n", q6(5013, 0) == 1);
  printf("%d\n", q6(0, 3) == 0);
}
