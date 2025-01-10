#include <iostream>
#include <cstring>

using namespace std;

struct studentRecord {
    int id;
    char *lastname;
    char *firstname;
    int *quizMarks;
};

struct studentList {
    studentRecord *sr;
    studentList *next;
};

void addStudent(studentList *& l,
                string lastname,
                string firstname,
                int quizMarks[],
                int nQuizzes);

void removeStudent(studentList *& l,
                   int studentID);

studentRecord *findStudentByID(const studentList *l,
                               int studentID);

studentList *findStudentsByLastName(const studentList *l,
                                    string lastname,
                                    int nQuizzes);


double quizAverage(const studentList *l, int quizNum);
