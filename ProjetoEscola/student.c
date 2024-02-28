#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

Person students[MAX_RECORDS];
int studentAmount = 0;

int generateID() {
  static long num = 0;
  num++;
  return num;
}

void createStudent() {
  Person newStudent;
  Date newBirthday;
  
  puts("Insira o nome do aluno:");
  scanf("%s", newStudent.name);

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &newStudent.gender);

  puts("Insira o CPF do aluno:");
  scanf("%ld", &newStudent.CPF);

  puts("Insira o aniversário do aluno (dd/mm/yyyy):");
  scanf("%d/%d/%d", &newBirthday.day, &newBirthday.month, &newBirthday.year);
  newStudent.birthday = newBirthday;

  newStudent.id = generateID();

  students[studentAmount] = newStudent;
  studentAmount++;

  puts("\nAluno registrado com sucesso.\n");
}

void getAllStudents() {
  puts("\nMatrícula - Nome do aluno");
  for (int i = 0; i < studentAmount; i++) {
    printf("%ld - %s", students[i].id, students[i].name);
  }
  puts("");
}

void getStudent() {
  long input;
  
  puts("\nInsira a matrícula do aluno:");
  scanf("%ld", &input);

  // TODO: Look for data
  
}

void studentMenu() {
  int option = 0;
  
  while (1) {
    puts("\nAlunos - Escolha a opção desejada:");
    puts("1 - Listar todos os alunos.");
    puts("2 - Buscar aluno por matrícula.");
    puts("3 - Matricular aluno.");
    puts("4 - Atualizar aluno.");
    puts("5 - Excluir aluno.");
    puts("6 - Voltar ao menu principal.\n");

    scanf("%d", &option);
    
    if (option == 1) getAllStudents();
    else if (option == 2) getStudent();
    else if (option == 3) createStudent();
    else if (option == 4) return;
    else if (option == 5) return;
    else if (option == 6) return;
    else puts("Opção inválida.\n\n");
  }
}

