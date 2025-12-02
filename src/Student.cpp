#include "Student.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace ReportCard
{

    Student::Student()
        : name_(""), className_(""), roll_(0), marks_(), total_(0), percentage_(0.0), grade_("F"), pass_(false),teacherComment_("") {}

    Student::Student(const string &name, const string &className, int roll, const vector<int> &marks)
        : name_(name), className_(className), roll_(roll), marks_(marks),,
          teacherComment_("")
    {
        recalculate();
    }

    const string &Student::getName() const { return name_; }
    const string &Student::getClassName() const { return className_; }
    int Student::getRoll() const { return roll_; }
    const vector<int> &Student::getMarks() const { return marks_; }
    int Student::getTotal() const { return total_; }
    double Student::getPercentage() const { return percentage_; }
    string Student::getGrade() const { return grade_; }
    bool Student::isPass() const { return pass_; }

    void Student::recalculate()
    {
        total_ = 0;
        for (int m : marks_)
            total_ += m;
        int maxTotal = static_cast<int>(marks_.size()) * 100;
        if (maxTotal > 0)
        {
            percentage_ = (100.0 * total_) / maxTotal;
        }
        else
        {
            percentage_ = 0.0;
        }

        // Determine grade (simple convention)
        if (percentage_ >= 90)
            grade_ = "A+";
        else if (percentage_ >= 80)
            grade_ = "A";
        else if (percentage_ >= 70)
            grade_ = "B+";
        else if (percentage_ >= 60)
            grade_ = "B";
        else if (percentage_ >= 50)
            grade_ = "C";
        else
            grade_ = "F";

        pass_ = (percentage_ >= 35.0); // pass threshold 35%
    }

    static string escapeCSVField(const string &s)
    {
        if (s.find(',') != string::npos || s.find('"') != string::npos)
        {
            string out = "\"";
            for (char c : s)
            {
                if (c == '"')
                    out += "\"\"";
                else
                    out += c;
            }
            out += "\"";
            return out;
        }
        return s;
    }

    string Student::toCSV() const
    {
        // fields: name,class,roll,marks-semi-colon-separated,total,percentage,grade,pass
        ostringstream oss;
        oss << escapeCSVField(name_) << "," << escapeCSVField(className_) << "," << roll_ << ",\"";
        for (size_t i = 0; i < marks_.size(); ++i)
        {
            if (i)
                oss << ";";
            oss << marks_[i];
        }
        oss << "\"," << total_ << "," << fixed << setprecision(2) << percentage_ << "," << grade_ << "," << (pass_ ? "1" : "0");

        // 🌟 NEW FIELD 9: Teacher Comment (must be escaped)
    oss << "," << escapeCSVField(teacherComment_); 

    // Assuming history implementation is next (field 10). If you skipped history, this part is removed.
    // 🌟 If history is implemented, the existing history serialization logic goes here, prefixed by a comma.
    /*
    oss << ",\"";
    // ... history serialization logic ...
    oss << "\""; 
    */

        return oss.str();
    }

    static string unescapeField(const string &s)
    {
        if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        {
            string inner = s.substr(1, s.size() - 2);
            string out;
            for (size_t i = 0; i < inner.size(); ++i)
            {
                if (inner[i] == '"' && i + 1 < inner.size() && inner[i + 1] == '"')
                {
                    out.push_back('"');
                    ++i;
                }
                else
                {
                    out.push_back(inner[i]);
                }
            }
            return out;
        }
        return s;
    }

    bool Student::fromCSV(const string &line, Student &outStudent)
    {
        // naive CSV split that handles quoted field for marks.
        vector<string> fields;
        string cur;
        bool inQuotes = false;
        for (size_t i = 0; i < line.size(); ++i)
        {
            char c = line[i];
            if (c == '"')
            {
                inQuotes = !inQuotes;
                cur.push_back(c);
            }
            else if (c == ',' && !inQuotes)
            {
                fields.push_back(cur);
                cur.clear();
            }
            else
            {
                cur.push_back(c);
            }
        }
        fields.push_back(cur);

        // 🌟 CHECK FIELD COUNT: 
    // 9 fields if history is NOT implemented (8 existing + 1 comment)
    // 10 fields if history IS implemented (8 existing + 1 comment + 1 history)
        if (fields.size() < 9)
            return false; // we expect at least 8 fields

        string name = unescapeField(fields[0]);
        string className = unescapeField(fields[1]);
        int roll = stoi(fields[2]);

        string marksField = unescapeField(fields[3]);
        vector<int> marks;
        if (!marksField.empty())
        {
            stringstream sm(marksField);
            string token;
            while (getline(sm, token, ';'))
            {
                try
                {
                    marks.push_back(stoi(token));
                }
                catch (...)
                {
                    marks.push_back(0);
                }
            }
        }

        Student s(name, className, roll, marks);
        // recalculate ensures computed fields match
        s.recalculate();
  
        // 🌟 NEW FIELD PARSING: Teacher Comment (Field 8 if 0-indexed, or index fields.size() - 2 if history is the last field)
    // Assuming the order is: ...,pass,teacherComment,history
    size_t commentIndex = 8; 

    string comment = unescapeField(fields[commentIndex]);
    s.teacherComment_ = comment; // Set the new member

        outStudent = s;
        return true;
    }

    string Student::formattedReportCard() const
    {
        ostringstream oss;
        oss << "------------------------------------------\n";
        oss << "Report Card\n";
        oss << "Name    : " << name_ << "\n";
        oss << "Class   : " << className_ << "\n";
        oss << "Roll No.: " << roll_ << "\n";
        oss << "Marks   : ";
        for (size_t i = 0; i < marks_.size(); ++i)
        {
            oss << marks_[i];
            if (i + 1 < marks_.size())
                oss << ", ";
        }
        oss << "\n";
        oss << "Total   : " << total_ << "\n";
        oss << "Percent : " << fixed << setprecision(2) << percentage_ << "%\n";
        oss << "Grade   : " << grade_ << "\n";
        oss << "Result  : " << (pass_ ? "PASS" : "FAIL") << "\n";

        // 🌟 NEW DISPLAY FIELD
    oss << "------------------------------------------\n";
    oss << "Teacher Comments:\n";
    oss << teacherComment_ << "\n";
    oss << "------------------------------------------\n"; 
    
        oss << "------------------------------------------\n";
        return oss.str();
    }

} // namespace ReportCard
