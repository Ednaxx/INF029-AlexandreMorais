#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../person/person.h"
#include "../subject/subject.h"


void readStudentsCSV(Person *students, int *studentAmount) {
  FILE *file = fopen("students.csv", "r");

  if (file == NULL) {
    file = fopen("students.csv", "w");
    fclose(file);
    return;
  }

  char line[1024];
  
  while (fgets(line, sizeof(line), file)) {
    Person *student = &students[*studentAmount];
  
    sscanf(line, "%ld,%49[^,],%d,%14[^,],%d/%d/%d,%d", &student->id, student->name, &student->gender, student->CPF,
      &student->birthday.tm_mday, &student->birthday.tm_mon, &student->birthday.tm_year, &student->subjectAmount);

    student->active = 1;
    
    (*studentAmount)++;
  }

  fclose(file); 
}

void readTeachersCSV(Person *teachers, int *teacherAmount) {
  FILE *file = fopen("teachers.csv", "r");

  if (file == NULL) {
    file = fopen("teachers.csv", "w");
    fclose(file);
    return;
  }

  char line[1024];
  
  while (fgets(line, sizeof(line), file)) {
    Person *teacher = &teachers[*teacherAmount];

    sscanf(line, "%ld,%49[^,],%d,%14[^,],%d/%d/%d", &teacher->id, teacher->name, &teacher->gender, teacher->CPF,
      &teacher->birthday.tm_mday, &teacher->birthday.tm_mon, &teacher->birthday.tm_year);
    
    teacher->active = 1;

    (*teacherAmount)++;
  }
  
  fclose(file); 
}

void setStudentSubjectRelationship(char line[1024], Subject *subject, Subject *subjects, Person *students, int *studentAmount) {
  char *token = strtok(line, ",");

  for (int tokenCount = 0; token != NULL; tokenCount++) {
    if (tokenCount > 3) {
      long studentID;
      sscanf(token, "%ld", &studentID);

      for (int i = 0; i < *studentAmount; i++) {
        if (students[i].id == studentID) {
          subject->students[subject->studentAmount] = &students[i];
          subject->studentAmount++;
          
          students[i].subjects[students[i].subjectAmount] = subject;
          students[i].subjectAmount++;
          
          break;
        }
      }
    }
    token = strtok(NULL, ",");
  }
}

void readSubjectsCSV(Subject *subjects, int *subjectAmount, Person *teachers, int *teacherAmount, Person *students, int *studentAmount) {
  FILE *file = fopen("subjects.csv", "r");

  if (file == NULL) {
    file = fopen("subjects.csv", "w");
    fclose(file);
    return;
  }

  char line[1024];
  
  while (fgets(line, sizeof(line), file)) {
    Subject *subject = &subjects[*subjectAmount];

    long subjectTeacherID;

    sscanf(line, "%49[^,],%19[^,],%ld,%d", subject->name, subject->subjectCode,
      &subjectTeacherID, &subject->semester);

    // Find and set teacher
    for (int i = 0; i < *teacherAmount; i++) {
      if (teachers[i].id == subjectTeacherID) {
        subject->teacher = &teachers[i];
        break;
      }
    }

    setStudentSubjectRelationship(line, subject, subjects, students, studentAmount);
    
    subject->active = 1;
    (*subjectAmount)++;
  }
  
  fclose(file); 
}


void writeStudentsToCSV(Person *students, int *studentAmount) {
  FILE *file = fopen("students.csv", "w");

  if (file == NULL) {
      printf("Error opening file %s\n", "students.csv");
      return;
  }

  for (int i = 0; i < *studentAmount; i++) {
      if (students[i].active == 1) {
        fprintf(file, "%ld,%s,%d,%s,%d/%d/%d\n", 
          students[i].id, students[i].name, students[i].gender, students[i].CPF, 
          students[i].birthday.tm_mday, students[i].birthday.tm_mon, students[i].birthday.tm_year
        );
        students[i].subjectAmount = 0;
        break;
      }
  }

  fclose(file);
}

void writeTeachersToCSV(Person *teachers, int *teacherAmount) {
  FILE *file = fopen("teachers.csv", "w");

  if (file == NULL) {
      printf("Error opening file %s\n", "teachers.csv");
      return;
  }

  for (int i = 0; i < *teacherAmount; i++) {
      if (teachers[i].active == 1) {
        fprintf(file, "%ld,%s,%d,%s,%d/%d/%d\n", 
          teachers[i].id, teachers[i].name, teachers[i].gender, teachers[i].CPF, 
          teachers[i].birthday.tm_mday, teachers[i].birthday.tm_mon, teachers[i].birthday.tm_year
        );
      }
  }

  fclose(file);
}

void writeSubjectsToCSV(Subject *subjects, int *subjectAmount, Person *students, int *studentAmount) {
  FILE *file = fopen("subjects.csv", "w");

  if (file == NULL) {
      printf("Error opening file %s\n", "subjects.csv");
      return;
  }

  for (int i = 0; i < *subjectAmount; i++) {
    if (subjects[i].active == 1) {
      fprintf(file, "%s,%s,%ld,%d", 
        subjects[i].name, subjects[i].subjectCode, subjects[i].teacher->id, subjects[i].semester);
      
      for (int j = 0; j < subjects[i].studentAmount; j++) {
        if (subjects[i].students[j] != NULL) fprintf(file, ",%ld", subjects[i].students[j]->id);
      }
      fprintf(file, "\n");
    }
  }

  fclose(file);
}
