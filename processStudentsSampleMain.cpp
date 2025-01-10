#include "processStudents.h"
#include <ctime>
#include <cstdlib>
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

void getSomeQuizMarks(int m[], int nq) {
    for(int i = 0; i < nq; i++)
        m[i] = rand() % 101;
}

void printStudentList(string preamble, const studentList *mylist, int nQuizzes) {
    cout << "Contents of " << preamble << ":" << endl;

    if(mylist == nullptr) {
        cout << '\t' << "<empty>" << endl; return;
    }

    for(const studentList *it = mylist; it != nullptr; it = it->next) {
        cout << '\t'; // Tab
        cout << (it->sr->id) << "; ";
        cout << (it->sr->lastname) << ", ";
        cout << (it->sr->firstname) << "; ";
        for(int i = 0; i < nQuizzes; i++) {
            cout << ((it->sr->quizMarks)[i]) << " ";
        }
        cout << endl;
    }
}

void deallocateStudentList(studentList *l) {
    for(studentList *it = l; it != nullptr; ) {
        studentList *toDelete = it;
        it = it->next;
        delete [] (toDelete->sr->lastname);
        delete [] (toDelete->sr->firstname);
        delete [] (toDelete->sr->quizMarks);
        delete (toDelete->sr);
        delete toDelete;
    }
}

int main() {
    cout << "Hello World" << endl;
    srand(time(0));

    int nQuizzes = (rand() % 4) + 5; // Between 5 and 8 quizzes
    studentList *mylist = nullptr;

    int quizMarks[nQuizzes];


    //first output
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Smith", "Alice", quizMarks, nQuizzes);
    string preamble = "mylist";
    printStudentList(preamble, mylist, nQuizzes);

    //second output
    removeStudent(mylist, 1);
    printStudentList(preamble, mylist, nQuizzes);

    //third output
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Smith", "Alice", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Martin", "Paul", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Wang", "Ruohai", quizMarks, nQuizzes);
    printStudentList(preamble, mylist, nQuizzes);

    //fourth output
    removeStudent(mylist, 2);
    removeStudent(mylist, 10);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Davis Jr.", "Sammy", quizMarks, nQuizzes);
    getSomeQuizMarks(quizMarks, nQuizzes);
    addStudent(mylist, "Smith", "Bob", quizMarks, nQuizzes);
    printStudentList(preamble, mylist, nQuizzes);


    studentList *smiths = findStudentsByLastName(mylist, "Smith", nQuizzes);
    preamble = "smiths";
    printStudentList(preamble, smiths, nQuizzes);

    for(const studentList *it = smiths; it != nullptr; it = it->next) {
        removeStudent(mylist, it->sr->id);
    }
    preamble = "mylist";
    printStudentList(preamble, mylist, nQuizzes);

    deallocateStudentList(smiths);

    int quizNum = rand() % nQuizzes;
    double avg = quizAverage(mylist, quizNum);
    cout << "Average on quiz # " << quizNum << " = " << avg << endl;

    deallocateStudentList(mylist);

    return 0;
}
