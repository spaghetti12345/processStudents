#include "processStudents.h"


void addStudent(studentList *&l, string lastname, string firstname,int quizMarks[],int nQuizzes){
    studentRecord *ptrStudent = new studentRecord;

    int max = 0;


    for (const studentList *temp = l; temp != nullptr; temp = temp->next) {
        if (temp->sr->id > max) max = temp->sr->id;
    }
    ptrStudent->id = max + 1;


    ptrStudent->lastname = new char[1+lastname.length()];
    for (std::string::size_type i = 0; i < lastname.length(); i++) {
        (ptrStudent->lastname)[i] = lastname[i];
    }
    (ptrStudent->lastname)[lastname.length()] = '\0';

    ptrStudent->firstname = new char[1+firstname.length()];
    for (std::string::size_type i = 0; i < firstname.length(); i++) {
        (ptrStudent->firstname)[i] = firstname[i];
    }
    ptrStudent->firstname[firstname.length()] = '\0';

    ptrStudent->quizMarks = new int[nQuizzes];
    for (int i = 0; i < nQuizzes; i++) {
        (ptrStudent->quizMarks)[i] = quizMarks[i];
    }

    studentList *listStudent = new studentList;
    listStudent->sr = ptrStudent;
    listStudent->next = l;

    l = listStudent;
}

void removeStudent(studentList *&l, int studentID) {
    if (l == nullptr) {
        return;
    }
    studentList *current = l;
    studentList *previous = nullptr;

    while ((current != nullptr) && (current->sr->id != studentID)) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (previous == nullptr) {
        l = current->next;
    }

    else {
        previous->next = current->next;
    }

    delete[] current->sr->lastname;
    delete[] current->sr->firstname;
    delete[] current->sr->quizMarks;
    delete current->sr;
    delete current;
}
studentRecord *findStudentByID(const studentList *l, int studentID) {
    for (const studentList *temp = l; temp != nullptr; temp = temp->next)
    {
        if(temp->sr->id == studentID) {
            return temp->sr;
        }
    }
    return nullptr;
}

studentList* findStudentsByLastName(const studentList* l, string lastname, int nQuizzes) {
    studentList* lastNameList = nullptr;
    const studentList* current = l;

    while (current != nullptr) {
        if (current->sr && lastname == current->sr->lastname) {
            string firstnameStr = current->sr->firstname;
            int* quizMarks = new int[nQuizzes];
            for (int i = 0; i < nQuizzes; ++i) {
                quizMarks[i] = current->sr->quizMarks[i];
            }

            addStudent(lastNameList, lastname, firstnameStr, quizMarks, nQuizzes);
            lastNameList->sr->id = current->sr->id;

            delete[] quizMarks;
        }
        current = current->next;
    }
    return lastNameList;
}

double quizAverage(const studentList* l, int quizNum) {
    int sum = 0;
    int count = 0;

    const studentList* current = l;
    while (current != nullptr) {
        if (current->sr != nullptr) {
            sum += current->sr->quizMarks[quizNum];
            count += 1;
        }
        current = current->next;
    }

    if (count == 0) return 0.0;
    return static_cast<double>(sum) / count;
}
