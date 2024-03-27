#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/utils.h"
#include "../person/person.h"


void createTeacher(Person *teachers, int *teacherAmount) {
  Person *teacher = &teachers[*teacherAmount];
  
  setPerson(teacher, teachers, teacherAmount);
  teacher->id = *teacherAmount;
  teacher->active = 1;

  (*teacherAmount)++;

  puts("\nProfessor registrado com sucesso.\n");
  getPerson(teacher);
}

void getAllTeachers(Person *teachers, int *teacherAmount) {
  if (*teacherAmount == 0) {
    puts("Nenhum professor matriculado.\n");
    return;
  }
  
  puts("\nMatrícula - Nome do professor");
  for (int i = 0; i < *teacherAmount; i++) {
    if (teachers[i].active == 1) printf("%ld - %s\n", teachers[i].id, teachers[i].name);
  }
}

void getAllTeachersOrderedByBirthday(Person *teachers, int *teacherAmount) {
  puts("\nMatrícula - Nome do professor");
  getOrderedPersons(teachers, *teacherAmount, comparePersonsByBirthday);
}

void getAllTeachersOrderedByName(Person *teachers, int *teacherAmount) {
  puts("\nMatrícula - Nome do professor");
  getOrderedPersons(teachers, *teacherAmount, comparePersonsByName);
}

void getAllTeachersBySex(Person *teachers, int *teacherAmount) {
  int option;

  puts("Selecione o sexo do professor: (0 - Masculino | 1 - Feminino).");
  scanf("%d", &option);

  if (option == 1) {
    puts("\nMatrícula - Nome do professor");
    for (int i = 0; i < *teacherAmount; i++) {
      if (teachers[i].active == 1 && teachers[i].gender) printf("%ld - %s\n", teachers[i].id, teachers[i].name);
    }
  }
  else if (option == 0) {
    puts("\nMatrícula - Nome do professor");
    for (int i = 0; i < *teacherAmount; i++) {
      if (teachers[i].active == 1 && !teachers[i].gender) printf("%ld - %s\n", teachers[i].id, teachers[i].name);
    }
  }
  else puts("Opção inválida.\n");
};

int getTeacher(Person *teachers, int *teacherAmount) {
  if (*teacherAmount == 0) {
    puts("Nenhum professor matriculado.\n");
    return -1;
  }
  
  long id;

  puts("\nInsira a matrícula do professor:");
  scanf("%ld", &id);

  for (int i = 0; i < *teacherAmount; i++) {
    if (teachers[i].id == id && teachers[i].active) return i;
  }
  
  puts("Professor não encontrado.\n");
  return -1;
}


Person * getTeacherPointer(Person *teachers, int *teacherAmount) {
  int teacher = -1;
  long id;

  puts("\nInsira a matrícula do professor:");
  scanf("%ld", &id);

  for (int i = 0; i < *teacherAmount; i++) {
    if (teachers[i].id == id && teachers[i].active) teacher = i;
    break;
  }
  if (teacher < 0) {
    puts("Professor não encontrado.\n");
    return NULL;
  };

  return &teachers[teacher];
}

void updateTeacher(Person *teachers, int *teacherAmount) {
  int teacher = getTeacher(teachers, teacherAmount);

  if (teacher < 0) return;

  setPerson(&teachers[teacher], teachers, teacherAmount);

  puts("\nProfessor atualizado com sucesso.\n");
}

void deleteTeacher(Person *teachers, int *teacherAmount) {
  int teacher = getTeacher(teachers, teacherAmount);

  if (teacher < 0) return;

  (*teacherAmount)--;
  for (int i = teacher; i < *teacherAmount; i++) {
    teachers[i] = teachers[i + 1];
  }
  teachers[*teacherAmount].active = 0;

  puts("\nProfessor removido com sucesso.\n");
}

void getAllTeachersMenu(Person *teachers, int *teacherAmount) {
  int option = 0;

  puts("\nListar professores.");
  puts("1 - Listar todos os professores.");
  puts("2 - Listar professores em ordem alfabética.");
  puts("3 - Listar todos professores em ordem de aniversário.");
  puts("4 - Listar professores por gênero.");
  puts("5 - Voltar ao menu anterior.");

  scanf("%d", &option);

  if (option == 1) getAllTeachers(teachers, teacherAmount);
  else if (option == 2) getAllTeachersOrderedByName(teachers, teacherAmount);
  else if (option == 3) getAllTeachersOrderedByBirthday(teachers, teacherAmount);
  else if (option == 4) getAllTeachersBySex(teachers, teacherAmount);
  else if (option == 5) return;
  else puts("Opção inválida.\n");
};

void teacherMenu(Person *teachers, int *teacherAmount) {
  int option = 0;

  while (1) {
    puts("\nProfessores - Escolha a opção desejada:");
    puts("1 - Listar professores.");
    puts("2 - Buscar professor por matrícula.");
    puts("3 - Matricular professor.");
    puts("4 - Atualizar professor.");
    puts("5 - Excluir professor.");
    puts("6 - Voltar ao menu principal.\n");

    scanf("%d", &option);

    if (option == 1) getAllTeachersMenu(teachers, teacherAmount);
      
    else if (option == 2) {
      int teacher = getTeacher(teachers, teacherAmount);
      if (teacher >= 0) getPerson(&teachers[teacher]);
    }
      
    else if (option == 3) createTeacher(teachers, teacherAmount);
    else if (option == 4) updateTeacher(teachers, teacherAmount);
    else if (option == 5) deleteTeacher(teachers, teacherAmount);
    else if (option == 6) return;
    else puts("Opção inválida.\n");
  }
}
