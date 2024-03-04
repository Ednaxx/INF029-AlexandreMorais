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

int comparePersonsByBirthday(const void *a, const void *b);

int comparePersonsByName(const void *a, const void *b);

void getOrderedPersons(Person persons[], int numPersons, int (*func)(const void *a, const void *b));