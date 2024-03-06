#include <stdio.h>
#include <stdlib.h>

#include "./student/student.h"

int main(void) {
  Person students[MAX_RECORDS];
  int studentAmount = 0;

  int option;

  while (1) {
    puts("Bem vindo ao Projeto Escola - Escolha a opção desejada:");
    puts("1 - Aluno");
    puts("2 - Professor");
    puts("3 - Disciplina");
    puts("4 - Sair\n");

    scanf("%d", &option);

    if (option == 1) studentMenu(students, &studentAmount);
    if (option == 2) break;
    if (option == 3) break;
    if (option == 4) break;
    else puts("Opção inválida.\n");
  };
  
  return 0;
}
