#include "../util/utils.h"
#include "time.h"

typedef struct person {
  long id;
  char name[MAX_NAME_SIZE];
  int gender;
  long CPF;
  Date birthday;
  int active;
} Person;

void getPerson(Person person);

void getPersonsOrderedByBirthday(Person persons[], int numPersons);

void getPersonsOrderedByName(Person persons[], int numPersons);
