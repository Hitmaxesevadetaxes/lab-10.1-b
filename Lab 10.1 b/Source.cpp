#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ������ ��� ������������ ��������
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, ECONOMICS, INFORMATICS };

// ��������� ��� ��������� ���������� ��� ��������
struct Student {
    string surname; // ������� ��������
    unsigned course; // ���� ��������
    Specialization specialization; // ������������ ��������
    union {
        int programming; // ������ � ������������� (��� ������������ "����'����� �����")
        int numericalMethods; // ������ � ��������� ������ (��� ������������ "�����������")
        int pedagogy; // ������ � ��������� (��� ����� ��������������)
    } thirdGrade; // ����� ������ ������� �� ������������
    struct {
        int physics; // ������ � ������
        int math; // ������ � ����������
    } grades;
};

// ������� ��� ����� ��������
void inputStudents(Student* students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        cout << "Enter data for student #" << i + 1 << ":\n";
        cout << "Surname: ";
        cin >> students[i].surname;

        cout << "Course (1-5): ";
        cin >> students[i].course;

        int spec;
        cout << "Specialization (0 - Comp. Sci., 1 - Math, 2 - Physics, 3 - Eng., 4 - Econ., 5 - Informatics): ";
        cin >> spec;
        students[i].specialization = (Specialization)spec;

        cout << "Physics grade: ";
        cin >> students[i].grades.physics;
        cout << "Math grade: ";
        cin >> students[i].grades.math;

        // ������� ����� ������ � ��������� �� ������������
        if (students[i].specialization == COMPUTER_SCIENCE) {
            cout << "Programming grade: ";
            cin >> students[i].thirdGrade.programming;
        }
        else if (students[i].specialization == INFORMATICS) {
            cout << "Numerical methods grade: ";
            cin >> students[i].thirdGrade.numericalMethods;
        }
        else {
            cout << "Pedagogy grade: ";
            cin >> students[i].thirdGrade.pedagogy;
        }
    }
}

// ������� ��� ��������� �������� ��� �����
int countExcellentAndGoodStudents(Student* students, int numStudents) {
    int count = 0;
    for (int i = 0; i < numStudents; i++) {
        bool allGoodOrExcellent = (students[i].grades.physics > 3 && students[i].grades.math > 3);

        // �������� ��� ������ ������ � ��������� �� ������������
        if (students[i].specialization == COMPUTER_SCIENCE) {
            allGoodOrExcellent &= (students[i].thirdGrade.programming > 3);
        }
        else if (students[i].specialization == INFORMATICS) {
            allGoodOrExcellent &= (students[i].thirdGrade.numericalMethods > 3);
        }
        else {
            allGoodOrExcellent &= (students[i].thirdGrade.pedagogy > 3);
        }

        if (allGoodOrExcellent) {
            count++;
        }
    }
    return count;
}

// ������� ��� ���������� ������� �������� � ������� ����� ������ �� 4
double calculatePercentageBelowFour(Student* students, int numStudents) {
    int countBelowFour = 0;
    for (int i = 0; i < numStudents; i++) {
        double average = (students[i].grades.physics + students[i].grades.math);

        // ��������� �� ���������� ���� ������ ������
        if (students[i].specialization == COMPUTER_SCIENCE) {
            average += students[i].thirdGrade.programming;
        }
        else if (students[i].specialization == INFORMATICS) {
            average += students[i].thirdGrade.numericalMethods;
        }
        else {
            average += students[i].thirdGrade.pedagogy;
        }

        average /= 3.0; // ���������� ������� ���

        if (average < 4.0) {
            countBelowFour++;
        }
    }
    return ((double)countBelowFour / numStudents) * 100;
}

// ������� ��� ����������� �������� � ������ �������
void displayStudentsTable(Student* students, int numStudents) {
    cout << setw(4) << "No" << setw(12) << "Surname" << setw(8) << "Course" << setw(15) << "Specialization"
        << setw(8) << "Physics" << setw(8) << "Math" << setw(12) << "Third Grade" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < numStudents; i++) {
        cout << setw(4) << i + 1
            << setw(12) << students[i].surname
            << setw(8) << students[i].course
            << setw(15) << (students[i].specialization == COMPUTER_SCIENCE ? "Comp. Sci." :
                students[i].specialization == MATHEMATICS ? "Math" :
                students[i].specialization == PHYSICS ? "Physics" :
                students[i].specialization == ENGINEERING ? "Engineering" :
                students[i].specialization == ECONOMICS ? "Economics" : "Informatics")
            << setw(8) << students[i].grades.physics
            << setw(8) << students[i].grades.math;

        // ��������� ������ ������ � ��������� �� ������������
        if (students[i].specialization == COMPUTER_SCIENCE) {
            cout << setw(12) << students[i].thirdGrade.programming;
        }
        else if (students[i].specialization == INFORMATICS) {
            cout << setw(12) << students[i].thirdGrade.numericalMethods;
        }
        else {
            cout << setw(12) << students[i].thirdGrade.pedagogy;
        }

        cout << endl;
    }
}

int main() {
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;

    // ��������� ����� ��������
    Student* students = new Student[numStudents];

    // ��� ����� ��������
    inputStudents(students, numStudents);

    // ϳ�������� �������� ��� �����
    int countNoThrees = countExcellentAndGoodStudents(students, numStudents);
    cout << "Number of students with grades only 'good' or 'excellent': " << countNoThrees << endl;

    // ³������ �������� � ������� ����� ������ �� 4
    double percentageBelowFour = calculatePercentageBelowFour(students, numStudents);
    cout << "Percentage of students with an average grade below 4: " << fixed << setprecision(2) << percentageBelowFour << "%" << endl;

    // ��������� ����� � ������ �������
    displayStudentsTable(students, numStudents);

    // ��������� ���'��
    delete[] students;

    return 0;
}
