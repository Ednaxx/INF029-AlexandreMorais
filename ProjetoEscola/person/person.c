#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "person.h"


int comparePersonsByBirthday(const void *a, const void *b) {
  Person **personA = (Person **)a;
  Person **personB = (Person **)b;

  if ((*personA)->birthday.tm_year < (*personB)->birthday.tm_year) return -1;
  else if ((*personA)->birthday.tm_year > (*personB)->birthday.tm_year) return 1;
  else {
      if ((*personA)->birthday.tm_mon < (*personB)->birthday.tm_mon) return -1;
      else if ((*personA)->birthday.tm_mon > (*personB)->birthday.tm_mon) return 1;
      else return (*personA)->birthday.tm_mday - (*personB)->birthday.tm_mday;
  }
}

int comparePersonsByName(const void *a, const void *b) {
  Person **personA = (Person **)a;
  Person **personB = (Person **)b;

  return strcmp((*personA)->name, (*personB)->name);
}

void getOrderedPersons(Person persons[], int numPersons, int (*func)(const void *a, const void *b)) {
  Person *personPointers[numPersons];
  for (int i = 0; i < numPersons; i++) personPointers[i] = &persons[i];

  qsort(personPointers, numPersons, sizeof(Person *), func);

  for (int i = 0; i < numPersons; i++) {
    if (personPointers[i]->active == 1) printf("%ld - %s\n", personPointers[i]->id, personPointers[i]->name);
  }
}

void getPerson(Person *person) {
  printf("Matrícula: %ld\n", person->id);
  printf("Nome: %s\n", person->name);
  printf("Sexo: %s\n", (person->gender == 0) ? "Masculino" : "Feminino");
  printf("CPF: %ld\n", person->CPF);

  printf("Aniversário: ");
  printf(( (person->birthday.tm_mday >= 10) ? "%d/" : "%0d/" ), person->birthday.tm_mday);
  printf(( (person->birthday.tm_mon >= 10) ? "%d/" : "%0d/" ), person->birthday.tm_mon);
  printf("%d\n", person->birthday.tm_year);
}

void setPerson(Person *person) {
  char bufferNewLine;
  scanf("%c", &bufferNewLine);
  puts("Insira o nome:");
  fgets(person->name, MAX_NAME_SIZE, stdin);
  if ((strlen(person->name) > 0) && (person->name[strlen (person->name) - 1] == '\n'))
    person->name[strlen (person->name) - 1] = '\0';

  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &person->gender);

  puts("Insira o CPF:");
  scanf("%ld", &person->CPF);

  puts("Insira o aniversário (dd/mm/yyyy):");
  scanf("%d/%d/%d", &person->birthday.tm_mday, &person->birthday.tm_mon, &person->birthday.tm_year);
}
