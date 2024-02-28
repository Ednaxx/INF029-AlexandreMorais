#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

Person students[MAX_RECORDS];
int studentAmount = 0;

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

  newStudent.id = studentAmount;

  newStudent.active = 1;

  students[studentAmount] = newStudent;
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
  long id;
  
  puts("\nInsira a matrícula do aluno:");
  scanf("%ld", &id);

  for (int i = 0; i < studentAmount; i++) {
    if (students[i].id != id && students[i].active == 1) break;

    printf("Matrícula: %ld\n", students[i].id);
    printf("Nome: %s\n", students[i].name);
    printf("Sexo: %s\n", (students[i].gender == 0) ? "Masculino" : "Feminino");
    printf("CPF: %ld\n", students[i].CPF);
    printf("Aniversário: %d/%d/%d\n", students[i].birthday.day, students[i].birthday.month, students[i].birthday.year);
    break;
  }
  
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

