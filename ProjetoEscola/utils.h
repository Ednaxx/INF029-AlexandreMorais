#define MAX_RECORDS 10
#define MAX_NAME_SIZE 256

typedef struct date {
  int day;
  int month;
  int year;
} Date;

typedef struct person {
  long id;
  char name[MAX_NAME_SIZE];
  int gender;
  long CPF;
  Date birthday;
  int active;
} Person;
