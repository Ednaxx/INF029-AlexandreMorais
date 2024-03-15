#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../util/utils.h"
#include "../person/person.h"
#include "../teacher/teacher.h"
#include "../student/student.h"
#include "subject.h"


void getAllSubjects(Subject *subjects, int *subjectAmount) {
  if (*subjectAmount == 0) {
    puts("Nenhuma matéria cadastrada.");
    return;
  }
  
  puts("\nCódigo - Nome da disciplina.");
  for (int i = 0; i < *subjectAmount; i++) {
    if (subjects[i].active == 1) printf("%s - %s\n", subjects[i].subjectCode, subjects[i].name);
  }
}

int getSubject(Subject *subjects, int *subjectAmount) {
  if (*subjectAmount == 0) {
    puts("Nenhuma matéria cadastrada.");
    return -1;
  }
  
  char subjectCode[7];

  while(getchar() != '\n');
  puts("Insira o código da disciplina:");
  fgets(subjectCode, 7, stdin);
  clearBuffer(subjectCode);

  for (int i = 0; i < *subjectAmount; i++) {
    if (strcmp(subjects[i].subjectCode, subjectCode) == 0 && subjects[i].active) return i;
  }
  
  puts("Disciplina não encontrada.");
  return -1;
}

void printSubject(Subject *subject) {
  printf("Código da disciplina: %s\n", subject->subjectCode);
  printf("Nome da disciplina: %s\n", subject->name);
  // printf("Professor da disciplina: %s\n", subject->teacher->name);
  printf("Quantidade de alunos matriculados nessa disciplina: %d\n", subject->studentAmount);
  printf("Semestre: %d\n", subject->semester);
}

void getSubjectStudents(Subject *subject) {
  // TODO: IMPLEMENT THIS
  return;
}


int validateSubjectName(char *name) {
  if (strlen(name) > 50) return 0;

  for (size_t i = 0; i < strlen(name); i++) {
      if (!isalpha(name[i]) && !isspace(name[i])) {
          return 0;
      }
  }

  return 1;
}

int validateSubjectCode(char *code, Subject *subjects, int *subjectAmount) {
  int subject = -1;

  for (int i = 0; i < *subjectAmount; i++) {
    if (strcmp(subjects[i].subjectCode, code) == 0 && subjects[i].active) {
      subject = i;
      break;
    }
  }
  
  if (subject >= 0) return 0;
  
  if (strlen(code) != 6) return 0;

  for (int i = 0; i < 3; i++) {
    if (!isupper(code[i])) return 0;
  }

  for (int i = 3; i < 6; i++) {
    if (!isdigit(code[i])) return 0;
  }
  
  return 1;
}

int validateSubjectSemester(int semester) {
  if (semester <= 0 || semester > 6) return 0;
  
  return 1;
}



void setSubjectName(Subject *subject) {
  char name[MAX_NAME_SIZE];

  puts("Insira o nome da disciplina (max: 50 caracteres):");
  fgets(name, MAX_NAME_SIZE, stdin);
  clearBuffer(name);

  if (validateSubjectName(name)) {
    strcpy(subject->name, name);
    return;
  }

  puts("Nome inválido. Por favor se atente ao limite de caracteres e só utilize letras.");
  setSubjectName(subject);
}

void setSubjectCode(Subject *subject, Subject *subjects, int *subjectAmount) {
  char code[7];

  puts("Insira o código da disciplina (por exemplo, INF029):");
  fgets(code, 7, stdin);
  clearBuffer(code);

  if (validateSubjectCode(code, subjects, subjectAmount)) {
    strcpy(subject->subjectCode, code);
    return;
  }

  puts("Código inválido. Por favor se atente ao formato (ABC123) e se atente para não inserir um código já existente.");
  setSubjectCode(subject, subjects, subjectAmount);
}

void setSubjectTeacher(Subject *subject, Person *teachers, int *teacherAmount) {
  Person *teacher = getTeacherPointer(teachers, teacherAmount);
  
  if (teacher != NULL) {
    subject->teacher = teacher;
    return;
  }

  puts("Professor não encontrado.");
  setSubjectTeacher(subject, teachers, teacherAmount);
}

void setSubjectSemester(Subject *subject) {
  int semester;
  puts("Insira o semestre da disciplina.");
  scanf("%d", &semester);

  while(getchar() != '\n');

  if (validateSubjectSemester(semester)) {
    subject->semester = semester;
    return;
  }

  puts("Semestre inválido. Valor deve ser inteiro, positivo e menor que 7.");
  setSubjectSemester(subject);
}


void setSubject(Subject *subject, Subject *subjects, int *subjectAmount, Person *teachers, int *teacherAmount) {
  while(getchar() != '\n');

  setSubjectCode(subject, subjects, subjectAmount);
  setSubjectName(subject);
  // setSubjectTeacher(subject, teachers, teacherAmount);
  setSubjectSemester(subject);
}



void createSubject(Subject *subjects, int *subjectAmount, Person *teachers, int *teacherAmount) {
  Subject *subject = &subjects[*subjectAmount];
  
  setSubject(subject, subjects, subjectAmount, teachers, teacherAmount);
  subject->active = 1;
  subject->studentAmount = 0;

  (*subjectAmount)++;

  puts("\nDisciplina registrada com sucesso.\n");
}

void updateSubject(Subject *subjects, int *subjectAmount, Person *teachers, int *teacherAmount) {
  int subject = getSubject(subjects, subjectAmount);

  if (subject < 0) return;

  setSubject(&subjects[subject], subjects, subjectAmount, teachers, teacherAmount);

  puts("\nDisciplina atualizada com sucesso.\n");
}

void deleteSubject(Subject *subjects, int *subjectAmount) {
  int subject = getSubject(subjects, subjectAmount);

  if (subject < 0) return;

  (*subjectAmount)--;
  for (int i = subject; i < *subjectAmount; i++) {
    subjects[i] = subjects[i + 1];
  }
  subjects[*subjectAmount].active = 0;

  puts("\nDisciplina removida com sucesso.\n");
}



void enrollStudentIntoSubject(Person *students, int *studentAmount, Subject *subjects, int *subjectAmount) {
  int studentIndex = getStudent(students, studentAmount);
  if (studentIndex < 0) return;

  Person *student = &students[studentIndex];

  if (student->subjectAmount == 10) {
    puts("Número máximo de disciplinas matriculadas (10) já alcançado. Por favor remova pelo menos uma antes de tentar novamente.");
    return;
  }

  int subjectIndex = getSubject(subjects, subjectAmount);
  if (subjectIndex < 0) return;

  Subject *subject = &subjects[subjectIndex];
  
  for (int i = 0; i < student->subjectAmount; i++) {
    if (student->subjects[i] == subject) {
      printf("Aluno já matriculado em %s.\n", subject->name);
      return;
    }
  }

  student->subjects[student->subjectAmount] = subject;
  student->subjectAmount++;

  subject->students[subject->studentAmount];
  subject->studentAmount++;
  
  printf("Aluno matriculado em %s com sucesso.\n", subjects[subjectIndex].name);
}



void removeFromStudentsSubjectArray(Person *student, int position) {
  Subject *newArray[10];
  int newArrayAmount = 0;
  
  for (int i = 0; i < student->subjectAmount; i++) {
    if (i == position) continue;

    newArray[newArrayAmount] = student->subjects[i];
    newArrayAmount++;
  }

  student->subjectAmount -= 1;
}

void removeFromSubjectsStudentArray(Subject *subject, int position) {
  Person *newArray[10];
  int newArrayAmount = 0;

  for (int i = 0; i < subject->studentAmount; i++) {
    if (i == position) continue;

    newArray[newArrayAmount] = subject->students[i];
    newArrayAmount++;
  }

  subject->studentAmount -= 1;
}

void unenrollStudentFromSubject(Person *students, int *studentAmount, Subject *subjects, int *subjectAmount) {
  int studentIndex = getStudent(students, studentAmount);
  if (studentIndex < 0) return;

  Person *student = &students[studentIndex];

  int subjectIndex = getSubject(subjects, subjectAmount);
  if (subjectIndex < 0) return;

  Subject *subject = &subjects[subjectIndex];

  for (int i = 0; i < student->subjectAmount; i++) {
    if (student->subjects[i] == subject) {
      removeFromStudentsSubjectArray(student, i);
      removeFromSubjectsStudentArray(subject, i);
      puts("Aluno desmatriculado com sucesso");
      return;
    }
  }

  puts("Aluno não matriculado nessa matéria.");
  return;
}



void subjectMenu(Subject *subjects, int *subjectAmount, Person *students, int *studentAmount, Person *teachers, int *teacherAmount) {
  int option = 0;

  while (1) {
    puts("\nDisciplinas - Escolha a opção desejada:");
    puts("1 - Listar matérias.");
    puts("2 - Buscar disciplina por código.");
    puts("3 - Cadastrar matéria.");
    puts("4 - Atualizar matéria.");
    puts("5 - Excluir matéria.");
    puts("6 - Matricular aluno em uma disciplina.");
    puts("7 - Desmatricular aluno em uma disciplina.");
    puts("8 - Voltar ao menu principal.\n");

    scanf("%d", &option);

    if (option == 1) getAllSubjects(subjects, subjectAmount);
    else if (option == 2) {
      int subject = getSubject(subjects, subjectAmount);
      printSubject(&subjects[subject]);
    }
    else if (option == 3) createSubject(subjects, subjectAmount, teachers, teacherAmount);
    else if (option == 4) updateSubject(subjects, subjectAmount, teachers, teacherAmount);
    else if (option == 5) deleteSubject(subjects, subjectAmount);
    else if (option == 6) enrollStudentIntoSubject(students, studentAmount, subjects, subjectAmount);
    else if (option == 7) unenrollStudentFromSubject(students, studentAmount, subjects, subjectAmount);
    else if (option == 8) return;
    else puts("Opção inválida.\n\n");
  }
}
