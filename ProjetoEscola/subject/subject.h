#ifndef SUBJECT_H
#define SUBJECT_H

#include "../util/utils.h"
#include "../person/person.h"

struct person;
typedef struct person Person;


typedef struct subject {
  char name[MAX_NAME_SIZE];
  char subjectCode[MAX_SUBJECTCODE_SIZE];
  Person *teacher;
  Person *students[50];
  int studentAmount;
  int semester;
  int active;
} Subject;

void unenrollStudentFromSubject(Person *student, Person *students, int *studentAmount, Subject *subject, Subject *subjects, int *subjectAmount);

void subjectMenu(Subject *subjects, int *subjectAmount, Person *students, int *studentAmount, Person *teachers, int *teacherAmount);

#endif
