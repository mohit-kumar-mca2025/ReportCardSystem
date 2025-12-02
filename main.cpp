#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "StudentManager.h"
#include "Utils.h"

using namespace std;
using namespace ReportCard;
using namespace RCUtils;

int main()
{
    cout << "Student Report Card Management System\n";

    // Manager responsible for storing, loading, and handling student records
    StudentManager mgr("data/students.csv");

    while (true)
    {
        // Display menu
        cout << "\nSelect:\n";
        cout << "1. Add Student\n";
        cout << "2. View All Report Cards\n";
        cout << "3. Search by Roll\n";
        cout << "4. Show Topper\n";
        cout << "5. Sort by Percentage (desc)\n";
        cout << "6. Edit Student Marks\n";
        cout << "7. Delete Student\n";
        cout << "8. View Students by Class\n";
        cout << "9. Exit\n";

        int choice = readInt("Choose option: ");

        // ------------------------ ADD STUDENT ------------------------
        if (choice == 1)
        {
            string name = readLine("Name: ");
            string className = readLine("Class: ");

            // Ensure roll number is unique within the same class
            int roll;
            while (true)
            {
                roll = readInt("Roll no: ");

                bool conflict = false;
                for (const auto &s : mgr.getAll())
                {
                    if (s.getRoll() == roll && s.getClassName() == className)
                    {
                        conflict = true;
                        break;
                    }
                }

                if (conflict)
                {
                    cout << "Error: Roll " << roll << " already exists in class "
                         << className << ". Try another.\n";
                    continue;
                }

                break; // roll is valid
            }

            // Read marks for each subject
            int subjects = readInt("Number of subjects: ");
            vector<int> marks;
            for (int i = 0; i < subjects; ++i)
            {
                int m = readMark("Mark for subject " + to_string(i + 1) + " (0-100): ");
                marks.push_back(m);
            }

            // Create and add student
            Student s(name, className, roll, marks);
            if (mgr.addStudent(s))
                cout << "Student added.\n";
            else
                cout << "Failed to add student (duplicate roll?).\n";

            pause();
        }

        // ------------------------ VIEW ALL ------------------------
        else if (choice == 2)
        {
            const auto &all = mgr.getAll();

            // Display all saved report cards
            if (all.empty())
            {
                cout << "No students found.\n";
            }
            else
            {
                for (const auto &s : all)
                    cout << s.formattedReportCard();
            }

            pause();
        }

        // ------------------------ SEARCH BY ROLL ------------------------
        else if (choice == 3)
        {
            int roll = readInt("Enter roll to search: ");
            Student *s = mgr.findByRoll(roll);

            // Display result
            if (s)
                cout << s->formattedReportCard();
            else
                cout << "Not found.\n";

            pause();
        }

        // ------------------------ SHOW TOPPER ------------------------
        else if (choice == 4)
        {
            const Student *t = mgr.getTopper();

            // Show student with highest percentage
            if (t)
                cout << "Class Topper:\n"
                     << t->formattedReportCard();
            else
                cout << "No students available.\n";

            pause();
        }

        // ------------------------ SORT BY PERCENTAGE ------------------------
        else if (choice == 5)
        {
            mgr.sortByPercentageDesc(); // highest first
            cout << "Sorted by percentage (descending).\n";
            pause();
        }

        // ------------------------ EDIT MARKS ------------------------
        else if (choice == 6)
        {
            int roll = readInt("Roll to edit marks: ");
            Student *s = mgr.findByRoll(roll);

            // Validate student exists
            if (!s)
            {
                cout << "Not found.\n";
                pause();
                continue;
            }

            // Show existing marks
            cout << "Current marks: ";
            for (int m : s->getMarks())
                cout << m << " ";
            cout << "\n";

            // Replace marks
            int subjects = readInt("Number of subjects (replace): ");
            vector<int> marks;
            for (int i = 0; i < subjects; ++i)
            {
                int m = readMark("Mark for subject " + to_string(i + 1) + " (0-100): ");
                marks.push_back(m);
            }

            // Save changes
            if (mgr.editMarks(roll, marks))
                cout << "Marks updated.\n";
            else
                cout << "Failed to update marks.\n";

            pause();
        }

        // ------------------------ DELETE STUDENT ------------------------
        else if (choice == 7)
        {
            int roll = readInt("Roll to delete: ");

            // Remove student by roll number
            if (mgr.removeByRoll(roll))
                cout << "Deleted.\n";
            else
                cout << "Not found.\n";

            pause();
        }
        // ------------------------ VIEW STUDENTS BY CLASS ------------------------
        else if (choice == 8)
        {
            string className = readLine("Enter class name: ");
            // Get list of students in the specified class
            auto list = mgr.getStudentsByClass(className);

            if (list.empty())
            {     // No students found
                cout << "No students found in class " << className << ".\n";
            }
            else
            {    // Display students
                cout << "Students in class " << className << ":\n";
                for (const auto &s : list)
                {
                    cout << s.formattedReportCard() << "\n";
                }
            }

            pause();
        }

        // ------------------------ EXIT APP ------------------------
        else if (choice == 9)
        {
            cout << "Exiting. Goodbye!\n";
            break;
        }

        // ------------------------ INVALID OPTION ------------------------
        else
        {
            cout << "Invalid choice.\n";
            pause();
        }
    }

    return 0;
}
