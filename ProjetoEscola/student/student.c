#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/utils.h"
#include "../person/person.h"


Person students[MAX_RECORDS];
int studentAmount = 0;

int findStudentPositionById() {
  long id;
  int position = -1;

  puts("\nInsira a matrícula do aluno:");
  scanf("%ld", &id);
  
  for (int i = 0; i < studentAmount; i++) {
    if (students[i].id == id && students[i].active) position = i;
  }

  return position;
}

void createStudent() {
  char bufferNewLine;
  
  scanf("%c", &bufferNewLine);
  puts("Insira o nome do aluno:");
  fgets(students[studentAmount].name, MAX_NAME_SIZE, stdin);
  if ((strlen(students[studentAmount].name) > 0) && (students[studentAmount].name[strlen (students[studentAmount].name) - 1] == '\n'))
    students[studentAmount].name[strlen (students[studentAmount].name) - 1] = '\0';

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &students[studentAmount].gender);

  puts("Insira o CPF do aluno:");
  scanf("%ld", &students[studentAmount].CPF);

  puts("Insira o aniversário do aluno (dd/mm/yyyy):");
  scanf("%d/%d/%d", &students[studentAmount].birthday.tm_mday, &students[studentAmount].birthday.tm_mon, &students[studentAmount].birthday.tm_year);

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
  getPersonsOrderedByBirthday(students, studentAmount);
};

void getAllStudentsOrderedByName() {
  puts("\nMatrícula - Nome do aluno");
  getPersonsOrderedByName(students, studentAmount);
};

void getAllStudentsBySex() {
  int option = -1;

  puts("Selecione o sexo do aluno: (0 - Masculino | 1 - Feminino).");
  scanf("%d", &option);
  
  if (option) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < studentAmount; i++) {
      if (students[i].active == 1 && students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else if (!option) {
    puts("\nMatrícula - Nome do aluno");
    for (int i = 0; i < studentAmount; i++) {
      if (students[i].active == 1 && !students[i].gender) printf("%ld - %s\n", students[i].id, students[i].name);
    }
  }
  else puts("Opção inválida.\n\n");
};

void getStudent() {
  int student = findStudentPositionById();

  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };
  
  getPerson(students[student]);
}

void updateStudent() {
  int student = findStudentPositionById();
  
  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };

  printf("Matrícula: %ld\n", students[student].id);
  printf("Nome: %s\n", students[student].name);
  printf("Sexo: %s\n", (students[student].gender == 0) ? "Masculino" : "Feminino");
  printf("CPF: %ld\n", students[student].CPF);
  printf("Aniversário: %d/%d/%d\n\n", students[student].birthday.tm_mday, students[student].birthday.tm_mon, students[student].birthday.tm_year);
  
  char bufferNewLine;
  scanf("%c", &bufferNewLine);
  puts("Insira o nome do aluno:");
  fgets(students[student].name, MAX_NAME_SIZE, stdin);
  if ((strlen(students[student].name) > 0) && (students[student].name[strlen (students[student].name) - 1] == '\n'))
    students[student].name[strlen (students[student].name) - 1] = '\0';

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &students[student].gender);

  puts("Insira o CPF do aluno:");
  scanf("%ld", &students[student].CPF);

  puts("Insira o aniversário do aluno (dd/mm/yyyy):");
  scanf("%d/%d/%d", &students[student].birthday.tm_mday, &students[student].birthday.tm_mon, &students[student].birthday.tm_year);
}

void deleteStudent() {
  int student = findStudentPositionById();

  if (student < 0) {
    printf("Usuário não encontrado.");
    return;
  };

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
