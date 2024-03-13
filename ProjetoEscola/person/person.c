#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../util/utils.h"
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

  for (size_t i = 0; i < strlen(name); i++) {
      if (!isalpha(name[i]) && !isspace(name[i])) {
          return 0;
      }
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
  long invalidFormats[10] = {
    00000000000, 11111111111, 22222222222, 
    33333333333, 44444444444, 55555555555, 
    66666666666, 77777777777, 88888888888, 
    99999999999};
  
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
  memset(&tm_date, 0, sizeof(Date));

  if (sscanf(birthdayInput, "%d/%d/%d", &tm_date.tm_mday, &tm_date.tm_mon, &tm_date.tm_year) != 3) {
      return 0;
  }

  if (mktime(&tm_date) == -1) {
      return 0;
  }

  return 1;
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

void getCurrentMonthsBirthday(Person *teachers, int *teacherAmount, Person *students, int *studentAmount) {
  time_t currentTime;
  Date *localTime;

  time(&currentTime);
  localTime = localtime(&currentTime);

  puts("Aniversariantes do mês:");

  puts("\nProfessores:");
  
  for (int i = 0; i < *teacherAmount; i++) {
    if (teachers[i].birthday.tm_mon == (localTime->tm_mon + 1) && teachers[i].active) {
      printf("%s - ", teachers[i].name);
      printf(( (teachers[i].birthday.tm_mday >= 10) ? "%d/" : "0%d/" ), teachers[i].birthday.tm_mday);
      printf(( (teachers[i].birthday.tm_mon >= 10) ? "%d/" : "0%d/" ), teachers[i].birthday.tm_mon);
      printf("%d\n", teachers[i].birthday.tm_year);
    }
  }

  puts("\nAlunos:");

  for (int i = 0; i < *studentAmount; i++) {
    if (students[i].birthday.tm_mon == (localTime->tm_mon + 1) && students[i].active) {
      printf("%s - ", students[i].name);
      printf(( (students[i].birthday.tm_mday >= 10) ? "%d/" : "0%d/" ), students[i].birthday.tm_mday);
      printf(( (students[i].birthday.tm_mon >= 10) ? "%d/" : "0%d/" ), students[i].birthday.tm_mon);
      printf("%d\n", students[i].birthday.tm_year);
    }
  }
}

void searchPersonByString(Person *teachers, int *teacherAmount, Person *students, int *studentAmount) {
  char searchString[MAX_NAME_SIZE];
  
  while(getchar() != '\n');

  puts("Pesquisar (Mínimo 3 caracteres):");

  fgets(searchString, MAX_NAME_SIZE, stdin);
  clearBuffer(searchString);

  if (strlen(searchString) < 3) {
    puts("Insira pelo menos 3 caracteres.");
    return;
  }

  puts("\nProfessor/Aluno - Matrícula - Nome\n");

  for (int i = 0; i < *teacherAmount; ++i) {
    if (strstr(teachers[i].name, searchString) != NULL) {
        printf("Professor - %ld - %s\n", teachers[i].id, teachers[i].name);
    }
  }

  for (int i = 0; i < *studentAmount; ++i) {
    if (strstr(students[i].name, searchString) != NULL) {
        printf("Aluno - %ld - %s\n", students[i].id, students[i].name);
    }
  }
  
}
