#ifndef PERSON_H
#define PERSON_H

#include "../util/utils.h"
#include "../subject/subject.h"
#include "time.h"

struct subject;
typedef struct subject Subject;


typedef struct person {
  long id;
  char name[MAX_NAME_SIZE];
  int gender;
  char CPF[MAX_CPF_SIZE];
  Date birthday;
  int active;
  Subject *subjects[10];
  int subjectAmount;
} Person;


void getPerson(Person *person);

int comparePersonsByBirthday(const void *a, const void *b);

int comparePersonsByName(const void *a, const void *b);

void getOrderedPersons(Person persons[], int numPersons, int (*func)(const void *a, const void *b));

void setPerson(Person *person, Person *persons, int *personAmount);

void getCurrentMonthsBirthday(Person *teachers, int *teacherAmount, Person *students, int *studentAmount);

void searchPersonByString(Person *teachers, int *teacherAmount, Person *students, int *studentAmount);

#endif
