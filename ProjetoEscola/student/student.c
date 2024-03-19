#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/utils.h"
#include "../person/person.h"
#include "../subject/subject.h"


void createStudent(Person *students, int *studentAmount) {
  Person *student = &students[*studentAmount];
  
  setPerson(student);
  student->id = *studentAmount;
  student->active = 1;
  student->subjectAmount = 0;

  (*studentAmount)++;

  puts("\nAluno registrado com sucesso:\n");
  getPerson(student);
}

void getAllStudents(Person *students, int *studentAmount) {
  if (*studentAmount == 0) {
    puts("Nenhum aluno matriculado.");
    return;
  }
  
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
  if (*studentAmount == 0) {
    puts("Nenhum aluno matriculado.");
    return -1;
  }
  
  long id;

  puts("\nInsira a matrícula do aluno:");
  scanf("%ld", &id);

  for (int i = 0; i < *studentAmount; i++) {
    if (students[i].id == id && students[i].active) return i;
  }
  
  puts("Aluno não encontrado.");
  return -1;
}

void getStudentsOnFewSubjects(Person *students, int *studentAmount) {
  if (*studentAmount == 0) {
    puts("Nenhum aluno matriculado.");
    return;
  }

  puts("Alunos matriculados em menos de 3 disciplinas (matrícula - nome):\n");

  for (int i = 0; i < *studentAmount; i++) {
    if (students[i].subjectAmount < 3) {
      printf("- %ld - %s\n", students[i].id, students[i].name);
    }
  }
}


void updateStudent(Person *students, int *studentAmount) {
  int student = getStudent(students, studentAmount);
  
  if (student < 0) return;
  
  setPerson(&students[student]);

  puts("\nAluno atualizado com sucesso.\n");
}

void deleteStudent(Person *students, int *studentAmount, Subject *subjects, int *subjectAmount) {
  int studentIndex = getStudent(students, studentAmount);

  if (studentIndex < 0) return;

  for (int i = 0; i < students[studentIndex].subjectAmount; i++) {
     unenrollStudentFromSubject(&students[studentIndex], students, studentAmount, students[studentIndex].subjects[i], subjects, subjectAmount);
  }
  
  (*studentAmount)--;
  for (int i = studentIndex; i < *studentAmount; i++) {
    students[i] = students[i + 1];
  }
  students[*studentAmount].active = 0;

  puts("\nAluno removido com sucesso.\n");
}


void getStudentSubjects(Person *students, int *studentAmount) {
  int studentIndex = getStudent(students, studentAmount);
  if (studentIndex < 0) return;
  
  Person *student = &students[studentIndex];

  if (student->subjectAmount == 0) {
    puts("Aluno não matriculado em nenhuma disciplina");
    return;
  }

  printf("Matérias cursadas por %s:\n", student->name);
  for (int i = 0; i < student->subjectAmount; i++) {
    printf("- %s\n", student->subjects[i]->name);
  }
}


  

void getAllStudentsMenu(Person *students, int *studentAmount) {
  int option = 0;
  
  puts("\nListar alunos.");
  puts("1 - Listar todos os alunos.");
  puts("2 - Listar alunos em ordem alfabética.");
  puts("3 - Listar todos alunos em ordem de aniversário.");
  puts("4 - Listar alunos por gênero.");
  puts("5 - Listar alunos matriculados em menos de 3 matérias.");
  puts("6 - Voltar ao menu anterior.");

  scanf("%d", &option);

  if (option == 1) getAllStudents(students, studentAmount);
  else if (option == 2) getAllStudentsOrderedByName(students, studentAmount);
  else if (option == 3) getAllStudentsOrderedByBirthday(students, studentAmount);
  else if (option == 4) getAllStudentsBySex(students, studentAmount);
  else if (option == 5) getStudentsOnFewSubjects(students, studentAmount);
  else if (option == 6) return;
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
    puts("6 - Listar matérias que um aluno está cursando.");
    puts("7 - Voltar ao menu principal.\n");

    scanf("%d", &option);
    
    
    if (option == 1) getAllStudentsMenu(students, studentAmount);
      
    else if (option == 2) {
      int student = getStudent(students, studentAmount);
      getPerson(&students[student]);
    }
      
    else if (option == 3) createStudent(students, studentAmount);
    else if (option == 4) updateStudent(students, studentAmount);
    else if (option == 5) deleteStudent(students, studentAmount, subjects, subjectAmount);
    else if (option == 6) getStudentSubjects(students, studentAmount);
    else if (option == 7) return;
    else puts("Opção inválida.\n\n");
  }
}
