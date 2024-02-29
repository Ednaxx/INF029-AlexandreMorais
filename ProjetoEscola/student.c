#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

Person students[MAX_RECORDS];
int studentAmount = 0;

// Fix string whitespace in name
// Fix search after delete

int findStudentPositionById() {
  long id;
  int position;

  puts("\nInsira a matrícula do aluno:");
  scanf("%ld", &id);
  
  for (int i = 0; i < studentAmount; i++) {
    if (students[i].id == id && students[i].active == 1) position = i;
  }

  return position;
}

void createStudent() {
  puts("Insira o nome do aluno:");
  scanf("%s", students[studentAmount].name);

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &students[studentAmount].gender);

  puts("Insira o CPF do aluno:");
  scanf("%ld", &students[studentAmount].CPF);

  puts("Insira o aniversário do aluno (dd/mm/yyyy):");
  scanf("%d/%d/%d", &students[studentAmount].birthday.day,
    &students[studentAmount].birthday.month,
    &students[studentAmount].birthday.year);
  students[studentAmount].birthday = students[studentAmount].birthday;

  students[studentAmount].id = studentAmount;

  students[studentAmount].active = 1;

  studentAmount++;

  puts("\nAluno registrado com sucesso.\n");
}

void getAllStudents() {
  puts("\nMatrícula - Nome do aluno");
  for (int i = 0; i < studentAmount; i++) {
    if (students[i].active == 1) printf("%ld - %s\n", students[i].id, students[i].name);
  }
}

void getStudent() {
  int student = -1;
  student = findStudentPositionById();

  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };
  
  printf("Matrícula: %ld\n", students[student].id);
  printf("Nome: %s\n", students[student].name);
  printf("Sexo: %s\n", (students[student].gender == 0) ? "Masculino" : "Feminino");
  printf("CPF: %ld\n", students[student].CPF);
  printf("Aniversário: %d/%d/%d\n", students[student].birthday.day, students[student].birthday.month, students[student].birthday.year);
}

void updateStudent() {
  int student = -1;
  student = findStudentPositionById();
  
  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };

  printf("Matrícula: %ld\n", students[student].id);
  printf("Nome: %s\n", students[student].name);
  printf("Sexo: %s\n", (students[student].gender == 0) ? "Masculino" : "Feminino");
  printf("CPF: %ld\n", students[student].CPF);
  printf("Aniversário: %d/%d/%d\n\n", students[student].birthday.day, students[student].birthday.month, students[student].birthday.year);
  
  puts("Insira o nome do aluno:");
  scanf("%s", students[student].name);

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &students[student].gender);

  puts("Insira o CPF do aluno:");
  scanf("%ld", &students[student].CPF);

  puts("Insira o aniversário do aluno (dd/mm/yyyy):");
  scanf("%d/%d/%d", &students[student].birthday.day,
    &students[student].birthday.month,
    &students[student].birthday.year);
  students[student].birthday = students[student].birthday;
}

void deleteStudent() {
  int student = -1;
  student = findStudentPositionById();

  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };

  for (int i = student; i < studentAmount; i++) {
    students[i] = students[i + 1];
  }
  
  students[studentAmount - 1].active = 0;
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
    else if (option == 4) updateStudent();
    else if (option == 5) deleteStudent();
    else if (option == 6) return;
    else puts("Opção inválida.\n\n");
  }
}
