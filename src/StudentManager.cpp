#include "StudentManager.h"
#include <fstream>
#include <algorithm>
#include <cstdio> // rename
#include <iostream>

using namespace std;

namespace ReportCard
{

    StudentManager::StudentManager(const string &filename) : filename_(filename)
    {
        loadFromFile();
    }

    bool StudentManager::addStudent(const Student &s)
    {
        for (const auto &st : students_)
        {
            if (st.getRoll() == s.getRoll() && st.getClassName() == s.getClassName())
            {
                return false; // duplicate roll in same class
            }
        }
        students_.push_back(s);
        return saveToFile();
    }

    const vector<Student> &StudentManager::getAll() const
    {
        return students_;
    }

    Student *StudentManager::findByRoll(int roll)
    {
        for (auto &st : students_)
        {
            if (st.getRoll() == roll)
                return &st;
        }
        return nullptr;
    }

    bool StudentManager::removeByRoll(int roll)
    {
        auto it = remove_if(students_.begin(), students_.end(), [roll](const Student &s)
                            { return s.getRoll() == roll; });
        if (it == students_.end())
            return false;
        students_.erase(it, students_.end());
        return saveToFile();
    }

    bool StudentManager::editMarks(int roll, const vector<int> &newMarks)
    {
        Student *s = findByRoll(roll);
        if (!s)
            return false;
        // create a new student with same metadata but new marks
        Student updated(s->getName(), s->getClassName(), s->getRoll(), newMarks);
        *s = updated;
        s->recalculate();
        return saveToFile();
    }

    const Student *StudentManager::getTopper() const
    {
        if (students_.empty())
            return nullptr;
        const Student *topper = &students_[0];
        for (const auto &s : students_)
        {
            if (s.getPercentage() > topper->getPercentage())
                topper = &s;
        }
        return topper;
    }

    void StudentManager::sortByPercentageDesc()
    {
        sort(students_.begin(), students_.end(), [](const Student &a, const Student &b)
             { return a.getPercentage() > b.getPercentage(); });
        saveToFile();
    }

    bool StudentManager::loadFromFile()
    {
        students_.clear();
        ifstream ifs(filename_);
        if (!ifs.is_open())
        {
            // file not present is normal; treat as empty dataset
            return true;
        }
        string line;
        while (getline(ifs, line))
        {
            if (line.empty())
                continue;
            Student s;
            if (Student::fromCSV(line, s))
            {
                students_.push_back(s);
            }
            else
            {
                // skip bad lines but continue
            }
        }
        ifs.close();
        return true;
    }

    bool StudentManager::saveToFile() const
    {
        string tmp = filename_ + ".tmp";
        ofstream ofs(tmp, ios::trunc);
        if (!ofs.is_open())
            return false;
        for (const auto &s : students_)
        {
            ofs << s.toCSV() << "\n";
        }
        ofs.close();
        // rename temp to actual (atomic on most OSes)
        if (std::rename(tmp.c_str(), filename_.c_str()) != 0)
        {
            // attempt fallback: remove original and rename again
            std::remove(filename_.c_str());
            if (std::rename(tmp.c_str(), filename_.c_str()) != 0)
                return false;
        }
        return true;
    }

    bool StudentManager::rollExists(int roll) const
    {
        for (const auto &s : students_)
        {
            if (s.getRoll() == roll)
                return true;
        }
        return false;
    }

} // namespace ReportCard
