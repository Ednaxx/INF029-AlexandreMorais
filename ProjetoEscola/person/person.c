#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "person.h"


int comparePersonsByBirthday(const void *a, const void *b) {
    Person **personA = (Person **)a;
    Person **personB = (Person **)b;

    if ((*personA)->birthday.tm_year < (*personB)->birthday.tm_year) {
        return -1;
    } else if ((*personA)->birthday.tm_year > (*personB)->birthday.tm_year) {
        return 1;
    } else {
        if ((*personA)->birthday.tm_mon < (*personB)->birthday.tm_mon) {
            return -1;
        } else if ((*personA)->birthday.tm_mon > (*personB)->birthday.tm_mon) {
            return 1;
        } else {
            return (*personA)->birthday.tm_mday - (*personB)->birthday.tm_mday;
        }
    }
}

int comparePersonsByName(const void *a, const void *b) {
    Person **personA = (Person **)a;
    Person **personB = (Person **)b;

    return strcmp((*personA)->name, (*personB)->name);
}

void getPersonsOrderedByBirthday(Person persons[], int numPersons) {
  Person *personPointers[numPersons];
  for (int i = 0; i < numPersons; i++) personPointers[i] = &persons[i];

  qsort(personPointers, numPersons, sizeof(Person *), comparePersonsByBirthday);

  for (int i = 0; i < numPersons; i++) {
    if (personPointers[i]->active == 1) printf("%ld - %s\n", personPointers[i]->id, personPointers[i]->name);
  }
}

void getPersonsOrderedByName(Person persons[], int numPersons) {
  Person *personPointers[numPersons];
  for (int i = 0; i < numPersons; i++) personPointers[i] = &persons[i];

  qsort(personPointers, numPersons, sizeof(Person *), comparePersonsByName);

  for (int i = 0; i < numPersons; i++) {
    if (personPointers[i]->active == 1) printf("%ld - %s\n", personPointers[i]->id, personPointers[i]->name);
  }
}

void getPerson(Person person) {
  printf("Matrícula: %ld\n", person.id);
  printf("Nome: %s\n", person.name);
  printf("Sexo: %s\n", (person.gender == 0) ? "Masculino" : "Feminino");
  printf("CPF: %ld\n", person.CPF);

  printf("Aniversário: ");
  printf(( (person.birthday.tm_mday >= 10) ? "%d/" : "%0d/" ), person.birthday.tm_mday);
  printf(( (person.birthday.tm_mon >= 10) ? "%d/" : "%0d/" ), person.birthday.tm_mon);
  printf("%d\n", person.birthday.tm_year);
}
