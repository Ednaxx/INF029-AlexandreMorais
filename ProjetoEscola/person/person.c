#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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



int validateName(char *name) {
  if (strlen(name) > 50) return 0;

  for (int i = 0; name[i] != '\0'; i++) {
    if (!isalpha(name[i]) && !isspace(name[i])) return 0;
  }
  return 1;
}

int validateGender(int gender) {
  if (gender != 0 && gender != 1) return 0;
  return 1;
}

// TODO: implement this

int validateCPF(long CPF) {
  return 1;
}

int validateBirthday(char *birthdayInput) {
  struct tm tm_date;
  memset(&tm_date, 0, sizeof(struct tm));

  if (sscanf(date, "%d/%d/%d", &tm_date.tm_mday, &tm_date.tm_mon, &tm_date.tm_year) != 3) {
      return 0;
  }

  if (mktime(&tm_date) == -1) {
      return 0;
  }

  return 1
}



void setPersonName(Person *person) {
  char name[MAX_NAME_SIZE];
  
  puts("Insira o nome (max: 50 caracteres):");
  fgets(name, MAX_NAME_SIZE, stdin);
  if ((strlen(name) > 0) && (name[strlen (name) - 1] == '\n'))
    name[strlen (name) - 1] = '\0';

  if (validateName(name)) {
    person->name = name;
    return;
  }

  puts("Nome inválido. Por favor se atente ao limite de caracteres e só utilize letras.");
  setPersonName(person);
}

setPersonGender(Person *person) {
  int gender;
  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &gender);

  if (validateGender(gender)) {
    person->gender = gender;
    return;
  }

  puts("Sexo inválido. Por favor insira '0' para masculino ou '1' feminino.");
  setPersonGender(person);
}

setPersonCPF(Person *person) {
  char CPF[12];
  
  puts("Insira o CPF:");
  gets(CPF);

  if (validateCPF(CPF)) {
    person->CPF = CPF;
    return;
  }

  puts("CPF inválido.");
  setPersonCPF(person);
}

setPersonBirthday(Person *person) {
  char birthdayInput[12];
  
  puts("Insira o aniversário (dd/mm/yyyy):");
  gets(birthdayInput);

  if (validateBirthday(birthdayInput)) {
    sscanf(date, "%d/%d/%d", &person->birthday.tm_mday, &person->birthday.tm_mon, &person->birthday.tm_year);
    return;
  }

  puts("Aniversário inválido. Por favor insira no formato 'dd/mm/yyyy'.\n");
  setPersonBirthday(person);
}

void setPerson(Person *person) {
  char bufferNewLine;
  scanf("%c", &bufferNewLine);
  
  setPersonName(person);
  setPersonGender(person);
  setPersonCPF(person);
  setPersonBirthday(person);
}
