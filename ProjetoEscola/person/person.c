#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  printf("CPF: %s\n", person->CPF);

  printf("Aniversário: ");
  printf(( (person->birthday.tm_mday >= 10) ? "%d/" : "0%d/" ), person->birthday.tm_mday);
  printf(( (person->birthday.tm_mon >= 10) ? "%d/" : "0%d/" ), person->birthday.tm_mon);
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

int validateCPF(char *CPF) {
  if (strlen(CPF) != 11) return 0;

  for (int i = 0; i < 11; i++) {
      if (!isdigit(CPF[i])) return 0;
  }

  // Check CPF format
  long invalidFormats[10] = {00000000000, 11111111111, 22222222222, 33333333333, 44444444444, 55555555555, 66666666666, 77777777777, 88888888888, 99999999999};
  long cpfValue = atol(CPF);

  for (int i = 0; i < 10; i++) {
    if (cpfValue == invalidFormats[i]) {
      return 0;
    }
  }

  // Validate check digits
  int sum = 0;
  int tempCPF[11];

  for (int i = 0; i < 11; i++) {
    tempCPF[i] = CPF[i] - '0';
    if (i < 9) sum += tempCPF[i] * (10 - i);
  }

  int firstCheckDigit = (sum % 11 < 2) ? 0 : (11 - (sum % 11));

  if (tempCPF[9] != firstCheckDigit) return 0;

  sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += tempCPF[i] * (11 - i);
  }

  int secondCheckDigit = (sum % 11 < 2) ? 0 : (11 - (sum % 11));

  return (tempCPF[10] == secondCheckDigit);
}

int validateBirthday(char *birthdayInput) {
  Date tm_date;
  memset(&tm_date, 0, sizeof(struct tm));

  if (sscanf(birthdayInput, "%d/%d/%d", &tm_date.tm_mday, &tm_date.tm_mon, &tm_date.tm_year) != 3) {
      return 0;
  }

  if (mktime(&tm_date) == -1) {
      return 0;
  }

  return 1;
}


void clearBuffer(char *string) {
  if ((strlen(string) > 0) && (string[strlen(string) - 1] == '\n')) {
      string[strlen(string) - 1] = '\0';
  }
  else {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
  }
}



void setPersonName(Person *person) {  
  char name[MAX_NAME_SIZE];
  
  puts("Insira o nome (max: 50 caracteres):");
  fgets(name, MAX_NAME_SIZE, stdin);
  clearBuffer(name);

  if (validateName(name)) {
    strcpy(person->name, name);
    return;
  }

  puts("Nome inválido. Por favor se atente ao limite de caracteres e só utilize letras.");
  setPersonName(person);
}

void setPersonGender(Person *person) {
  int gender;
  puts("Sexo masculino (0) ou feminino (1)?");
  scanf("%d", &gender);

  while(getchar() != '\n');
  
  if (validateGender(gender)) {
    person->gender = gender;
    return;
  }

  puts("Sexo inválido. Por favor insira '0' para masculino ou '1' feminino.");
  setPersonGender(person);
}

void setPersonCPF(Person *person) {
  char CPF[12];
  
  puts("Insira o CPF:");
  fgets(CPF, 12, stdin);

  clearBuffer(CPF);

  if (validateCPF(CPF)) {
    strcpy(person->CPF, CPF);
    return;
  }

  puts("CPF inválido.");
  setPersonCPF(person);
}

void setPersonBirthday(Person *person) {
  char birthdayInput[12];
  
  puts("Insira o aniversário (dd/mm/yyyy):");
  fgets(birthdayInput, 12, stdin);

  clearBuffer(birthdayInput);

  if (validateBirthday(birthdayInput)) {
    sscanf(birthdayInput, "%d/%d/%d", &person->birthday.tm_mday, &person->birthday.tm_mon, &person->birthday.tm_year);
    return;
  }

  puts("Aniversário inválido. Por favor insira no formato 'dd/mm/yyyy'.\n");
  setPersonBirthday(person);
}

void setPerson(Person *person) {
  while(getchar() != '\n');
  
  setPersonName(person);
  setPersonGender(person);
  setPersonCPF(person);
  setPersonBirthday(person);
}
