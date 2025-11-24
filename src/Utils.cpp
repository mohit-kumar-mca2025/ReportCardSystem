#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

namespace RCUtils
{

    void pause()
    {
        cout << "Press Enter to continue...";
        // flush and wait for enter
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int readInt(const string &prompt)
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

    string readLine(const string &prompt)
    {
        cout << prompt;
        string s;
        getline(cin, s);
        return s;
    }

    int readMark(const string &prompt)
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

} // namespace RCUtils
