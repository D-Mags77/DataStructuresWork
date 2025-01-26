#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Students {

public:
	string Name;
	string School;
	int Grade;


    //Constructor
    Students(string name, string school, int grade) : Name(name), School(school), Grade(grade) {}

    void display() const {
        cout << "Name: " << Name << ", School: " << School << ", Grade: " << Grade << "%" << endl;
    }

};



int main() {

    vector<Students> students = {
        Students("Alice", "Lawrence Technological University", 85),
        Students("Bob", "Lawrence Technological University", 92),
        Students("Charlie", "Lawrence Technological University", 76),
        Students("Diana", "Lawrence Technological University", 89),
        Students("Eve", "Lawrence Technological University", 98),
        Students("Frank", "Lawrence Technological University", 67),
        Students("Grace", "Lawrence Technological University", 81),
        Students("Hank", "Lawrence Technological University", 43),
        Students("Ivy", "Lawrence Technological University", 74),
        Students("Jack", "Lawrence Technological University", 90)
    };


    cout << "Students at Lawrence Technological University:" << endl;
    for (const auto& student : students) {
        student.display();
    }

    // Sort students by Grade in descending order using bubble sort
    for (size_t i = 0; i < students.size() - 1; ++i) {
        for (size_t j = i + 1; j < students.size(); ++j) {
            if (students[i].Grade < students[j].Grade) {
                swap(students[i], students[j]);
            }
        }
    }

    cout << endl << "Students at Lawrence Technological University Sorted By Highest Grade to Lowest Grade:" << endl;
    for (const auto& student : students) {
        student.display();
    }

    return 0;
}