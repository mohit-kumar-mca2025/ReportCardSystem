#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "StudentManager.h"

using namespace std;
using namespace ReportCard;

static void pause()
{
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int readInt(const string &prompt)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        else
        {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static string readLine(const string &prompt)
{
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

static int readMark(const string &prompt)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (x >= 0 && x <= 100)
                return x;

            cout << "Marks must be between 0 and 100. Try again.\n";
        }
        else
        {
            cout << "Invalid input. Enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    cout << "Student Report Card Management System\n";
    StudentManager mgr("data/students.csv");

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. View All Report Cards\n";
        cout << "3. Search by Roll\n";
        cout << "4. Show Topper\n";
        cout << "5. Sort by Percentage (desc)\n";
        cout << "6. Edit Student Marks\n";
        cout << "7. Delete Student\n";
        cout << "8. Exit\n";
        int choice = readInt("Choose option: ");

        if (choice == 1)
        {
            string name = readLine("Name: ");
            string className = readLine("Class: ");

            int roll;
            while (true)
            {
                roll = readInt("Roll no: ");

                // check roll + class uniqueness
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
                    cout << "Error: Roll " << roll << " already exists in class " << className << ". Try another.\n";
                    continue;
                }

                break; // valid
            }

            int subjects = readInt("Number of subjects: ");
            vector<int> marks;
            for (int i = 0; i < subjects; ++i)
            {
                int m = readMark("Mark for subject " + to_string(i + 1) + " (0-100): ");
                marks.push_back(m);
            }
            Student s(name, className, roll, marks);
            if (mgr.addStudent(s))
            {
                cout << "Student added.\n";
            }
            else
            {
                cout << "Failed to add student (duplicate roll?).\n";
            }
            pause();
        }
        else if (choice == 2)
        {
            const auto &all = mgr.getAll();
            if (all.empty())
            {
                cout << "No students found.\n";
            }
            else
            {
                for (const auto &s : all)
                {
                    cout << s.formattedReportCard();
                }
            }
            pause();
        }
        else if (choice == 3)
        {
            int roll = readInt("Enter roll to search: ");
            Student *s = mgr.findByRoll(roll);
            if (s)
                cout << s->formattedReportCard();
            else
                cout << "Not found.\n";
            pause();
        }
        else if (choice == 4)
        {
            const Student *t = mgr.getTopper();
            if (t)
            {
                cout << "Class Topper:\n"
                     << t->formattedReportCard();
            }
            else
            {
                cout << "No students available.\n";
            }
            pause();
        }
        else if (choice == 5)
        {
            mgr.sortByPercentageDesc();
            cout << "Sorted by percentage (descending).\n";
            pause();
        }
        else if (choice == 6)
        {
            int roll = readInt("Roll to edit marks: ");
            Student *s = mgr.findByRoll(roll);
            if (!s)
            {
                cout << "Not found.\n";
                pause();
                continue;
            }
            cout << "Current marks: ";
            for (int m : s->getMarks())
                cout << m << " ";
            cout << "\n";
            int subjects = readInt("Number of subjects (replace): ");
            vector<int> marks;
            for (int i = 0; i < subjects; ++i)
            {
                int m = readInt("Mark for subject " + to_string(i + 1) + ": ");
                marks.push_back(m);
            }
            if (mgr.editMarks(roll, marks))
                cout << "Marks updated.\n";
            else
                cout << "Failed to update marks.\n";
            pause();
        }
        else if (choice == 7)
        {
            int roll = readInt("Roll to delete: ");
            if (mgr.removeByRoll(roll))
                cout << "Deleted.\n";
            else
                cout << "Not found.\n";
            pause();
        }
        else if (choice == 8)
        {
            cout << "Exiting. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
            pause();
        }
    }

    return 0;
}
