#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/utils.h"
#include "../person/person.h"
#include "../subject/subject.h"


void createStudent(Person *students, int *studentAmount) {
  setPerson(&students[*studentAmount]);
  students[*studentAmount].id = *studentAmount;
  students[*studentAmount].active = 1;
  students[*studentAmount].subjectAmount = 0;

  (*studentAmount)++;

  puts("\nAluno registrado com sucesso.\n");
}

void getAllStudents(Person *students, int *studentAmount) {
  puts("\nMatrícula - Nome do aluno");
  for (int i = 0; i < *studentAmount; i++) {
    if (students[i].active == 1) printf("%ld - %s\n", students[i].id, students[i].name);
  }
}

void getAllStudentsOrderedByBirthday(Person *students, int *studentAmount) {
  puts("\nMatrícula - Nome do aluno");
  getOrderedPersons(students, *studentAmount, comparePersonsByBirthday);
}

void getAllStudentsOrderedByName(Person *students, int *studentAmount) {
  puts("\nMatrícula - Nome do aluno");
  getOrderedPersons(students, *studentAmount, comparePersonsByName);
}

void getAllStudentsBySex(Person *students, int *studentAmount) {
  int option;

  puts("Selecione o sexo do aluno: (0 - Masculino | 1 - Feminino).");
  scanf("%d", &option);
  
  if (option == 1) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < *studentAmount; i++) {
      if (students[i].active == 1 && students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else if (option == 0) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < *studentAmount; i++) {
      if (students[i].active == 1 && !students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else puts("Opção inválida.\n\n");
};

int getStudent(Person *students, int *studentAmount) {
  int student = -1;
  long id;

  puts("\nInsira a matrícula:");
  scanf("%ld", &id);

  for (int i = 0; i < *studentAmount; i++) {
    if (students[i].id == id && students[i].active) student = i;
    break;
  }
  if (student < 0) {
    puts("Aluno não encontrado.");
    return -1;
  };
  
  getPerson(&students[student]);
  return student;
}

void updateStudent(Person *students, int *studentAmount) {
  int student = getStudent(students, studentAmount);
  
  if (student < 0) return;
  
  setPerson(&students[student]);

  puts("\nAluno atualizado com sucesso.\n");
}

void deleteStudent(Person *students, int *studentAmount) {
  int student = getStudent(students, studentAmount);

  if (student < 0) return;

  studentAmount--;
  for (int i = student; i < *studentAmount; i++) {
    students[i] = students[i + 1];
  }
  students[*studentAmount].active = 0;

  puts("\nAluno removido com sucesso.\n");
}


void enrollStudentIntoSubject(Person *students, int *studentAmount, Subject *subjects, int *subjectAmount) {
  int studentPosition = getStudent(students, studentAmount);
  Subject *subject = getSubject(subjects, subjectAmount);

  Person student = students[studentPosition];

  student.subjects[student.subjectAmount] = subject;
  student.subjectAmount++;

  printf("Aluno matriculado em %s com sucesso.\n", subject->name);
}


void getAllStudentsMenu(Person *students, int *studentAmount) {
  int option = 0;
  
  puts("\nListar alunos.");
  puts("1 - Listar todos os alunos.");
  puts("2 - Listar alunos em ordem alfabética.");
  puts("3 - Listar todos alunos em ordem de aniversário.");
  puts("4 - Listar alunos por gênero.");
  puts("5 - Voltar ao menu anterior.");

  scanf("%d", &option);

  if (option == 1) getAllStudents(students, studentAmount);
  else if (option == 2) getAllStudentsOrderedByName(students, studentAmount);
  else if (option == 3) getAllStudentsOrderedByBirthday(students, studentAmount);
  else if (option == 4) getAllStudentsBySex(students, studentAmount);
  else if (option == 5) return;
  else puts("Opção inválida.\n\n");
};

void studentMenu(Person *students, int *studentAmount, Subject *subjects, int *subjectAmount) {
  int option = 0;
  
  while (1) {
    puts("\nAlunos - Escolha a opção desejada:");
    puts("1 - Listar alunos.");
    puts("2 - Buscar aluno por matrícula.");
    puts("3 - Matricular aluno.");
    puts("4 - Atualizar aluno.");
    puts("5 - Excluir aluno.");
    puts("6 - Matricular aluno em uma disciplina.");
    puts("7 - Voltar ao menu principal.\n");

    scanf("%d", &option);
    
    if (option == 1) getAllStudentsMenu(students, studentAmount);
    else if (option == 2) getStudent(students, studentAmount);
    else if (option == 3) createStudent(students, studentAmount);
    else if (option == 4) updateStudent(students, studentAmount);
    else if (option == 5) deleteStudent(students, studentAmount);
    else if (option == 6) enrollStudentIntoSubject(students, studentAmount, subjects, subjectAmount);
    else if (option == 7) return;
    else puts("Opção inválida.\n\n");
  }
}
