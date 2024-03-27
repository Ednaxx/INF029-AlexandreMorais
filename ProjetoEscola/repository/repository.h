#include "../person/person.h"
#include "../subject/subject.h"

void readStudentsCSV(Person *students, int *studentAmount);

void readTeachersCSV(Person *teachers, int *teacherAmount);

void readSubjectsCSV(Subject *subjects, int *subjectAmount, Person *teachers, int *teacherAmount, Person *students, int *studentAmount);

void writeStudentsToCSV(Person *students, int *studentAmount);

void writeTeachersToCSV(Person *teachers, int *teacherAmount);

void writeSubjectsToCSV(Subject *subjects, int *subjectAmount, Person *students, int *studentAmount);
