#define MAX_RECORDS 10


typedef struct date {
  int day;
  int month;
  int year;
} Date;

typedef struct person {
  long id;
  char name[50];
  int gender;
  long CPF;
  Date birthday;
  int active;
} Person;
