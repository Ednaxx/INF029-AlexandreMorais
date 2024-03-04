#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/utils.h"
#include "../person/person.h"


Person students[MAX_RECORDS];
int studentAmount = 0;


void createStudent() {
  setPerson(&students[studentAmount]);
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

void getAllStudentsOrderedByBirthday() {
  puts("\nMatrícula - Nome do aluno");
  getOrderedPersons(students, studentAmount, comparePersonsByBirthday);
};

void getAllStudentsOrderedByName() {
  puts("\nMatrícula - Nome do aluno");
  getOrderedPersons(students, studentAmount, comparePersonsByName);
};

void getAllStudentsBySex() {
  int option;

  puts("Selecione o sexo do aluno: (0 - Masculino | 1 - Feminino).");
  scanf("%d", &option);
  
  if (option == 1) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < studentAmount; i++) {
      if (students[i].active == 1 && students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else if (option == 0) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < studentAmount; i++) {
      if (students[i].active == 1 && !students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else puts("Opção inválida.\n\n");
};

int getStudent() {
  int student = -1;
  long id;

  puts("\nInsira a matrícula:");
  scanf("%ld", &id);

  for (int i = 0; i < studentAmount; i++) {
    if (students[i].id == id && students[i].active) student = i;
  }
  if (student < 0) {
    puts("Aluno não encontrado.");
    return -1;
  };
  
  getPerson(&students[student]);
  return student;
}

void updateStudent() {
  int student = getStudent();
  
  if (student < 0) return;
  
  char bufferNewLine;
  scanf("%c", &bufferNewLine);
  puts("Insira o nome do aluno:");
  
  setPerson(&students[student]);

  puts("\nAluno atualizado com sucesso.\n");
}

void deleteStudent() {
  int student = getStudent();

  if (student < 0) return;

  studentAmount--;
  for (int i = student; i < studentAmount; i++) {
    students[i] = students[i + 1];
  }
  students[studentAmount].active = 0;
}

void getAllStudentsMenu() {
  int option = 0;
  
  puts("\nListar alunos.");
  puts("1 - Listar todos os alunos.");
  puts("2 - Listar alunos em ordem alfabética.");
  puts("3 - Listar todos alunos em ordem de aniversário.");
  puts("4 - Listar alunos por gênero.");
  puts("5 - Voltar ao menu anterior.");

  scanf("%d", &option);

  if (option == 1) getAllStudents();
  else if (option == 2) getAllStudentsOrderedByName();
  else if (option == 3) getAllStudentsOrderedByBirthday();
  else if (option == 4) getAllStudentsBySex();
  else if (option == 5) return;
  else puts("Opção inválida.\n\n");
};

void studentMenu() {
  int option = 0;
  
  while (1) {
    puts("\nAlunos - Escolha a opção desejada:");
    puts("1 - Listar alunos.");
    puts("2 - Buscar aluno por matrícula.");
    puts("3 - Matricular aluno.");
    puts("4 - Atualizar aluno.");
    puts("5 - Excluir aluno.");
    puts("6 - Voltar ao menu principal.\n");

    scanf("%d", &option);
    
    if (option == 1) getAllStudentsMenu();
    else if (option == 2) getStudent();
    else if (option == 3) createStudent();
    else if (option == 4) updateStudent();
    else if (option == 5) deleteStudent();
    else if (option == 6) return;
    else puts("Opção inválida.\n\n");
  }
}
