#include <stdio.h>
#include <stdlib.h>

#include "./student/student.h"
#include "./teacher/teacher.h"
#include "./person/person.h"
#include "./subject/subject.h"


int main(void) {
  Person students[MAX_RECORDS];
  int studentAmount = 0;

  Person teachers[MAX_RECORDS];
  int teacherAmount = 0;

  Subject subjects[MAX_RECORDS];
  int subjectAmount = 0;


  while (1) {
    puts("Bem vindo ao Projeto Escola - Escolha a opção desejada:");
    puts("1 - Aluno");
    puts("2 - Professor");
    puts("3 - Disciplina");
    puts("4 - Aniversariantes do mês.");
    puts("5 - Busque por uma pessoa cadastrada.");
    puts("6 - Sair\n");

    int option;
    scanf("%d", &option);

    if (option == 1) studentMenu(students, &studentAmount);
    else if (option == 2) teacherMenu(teachers, &teacherAmount);
    else if (option == 3) subjectMenu(subjects, &subjectAmount, students, &studentAmount, teachers, &teacherAmount);
    else if (option == 4) getCurrentMonthsBirthday(teachers, &teacherAmount, students, &studentAmount);
    else if (option == 5) searchPersonByString(teachers, &teacherAmount, students, &studentAmount);
    else if (option == 6) break;
    else puts("Opção inválida.\n");
  };
  
  return 0;
}
