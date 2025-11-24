#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <vector>
#include <string>

namespace ReportCard
{

    /**
     * @class StudentManager
     * @brief Manages collection of Student objects, file operations and UI-level operations.
     */
    class StudentManager
    {
    public:
        /**
         * Objective:
         *  Create manager bound to a filename for persistence.
         *
         * Input:
         *  @param filename std::string - path to CSV storage file
         * Output: constructed StudentManager
         * Approach: store filename and try to load existing records.
         */
        explicit StudentManager(const std::string &filename);

        /**
         * Objective:
         *  Add a new student and persist to disk.
         *
         * Input:
         *  @param s const Student& - student to add
         * Output: true if added (no duplicate roll), false otherwise
         * Approach: check duplicate roll, append to in-memory container, and save to file.
         */
        bool addStudent(const Student &s);

        /**
         * Objective:
         *  Get all students currently in memory.
         *
         * Input: None
         * Output: const reference to vector<Student>
         * Approach: returns internal container reference for read-only operations.
         */
        const std::vector<Student> &getAll() const;

        /**
         * Objective:
         *  Find student by roll number.
         *
         * Input:
         *  @param roll int - roll number to search
         * Output: pointer to student in container or nullptr if not found
         * Approach: linear search by roll (data is small; simple).
         */
        Student *findByRoll(int roll);

        /**
         * Objective:
         *  Delete a student by roll number.
         *
         * Input:
         *  @param roll int
         * Output: true if removed, false if not found
         * Approach: remove from vector and save file.
         */
        bool removeByRoll(int roll);

        /**
         * Objective:
         *  Edit student's marks (replace marks vector) and recalc.
         *
         * Input:
         *  @param roll int
         *  @param newMarks const std::vector<int>&
         * Output: true if edited, false if student not found
         * Approach: find student, replace marks, recalc, save file.
         */
        bool editMarks(int roll, const std::vector<int> &newMarks);

        /**
         * Objective:
         *  Return the topper (highest percentage). If tie, first highest is returned.
         *
         * Input: None
         * Output: pointer to topper or nullptr if no students
         * Approach: linear scan tracking max percentage.
         */
        const Student *getTopper() const;

        /**
         * Objective:
         *  Sort in-memory students by percentage descending.
         *
         * Input: None
         * Output: sorts container and returns void
         * Approach: std::sort with comparator and then save file.
         */
        void sortByPercentageDesc();

        /**
         * Objective:
         *  Load students from file into memory (replaces memory).
         *
         * Input: None
         * Output: true if success, false if file could not be opened
         * Approach: read CSV lines and call Student::fromCSV
         */
        bool loadFromFile();

        /**
         * Objective:
         *  Save current in-memory students into file (atomic write).
         *
         * Input: None
         * Output: true if success
         * Approach: write to temporary file then rename for safety.
         */
        bool saveToFile() const;

        /**
         * Objective:
         *  Check if a roll number already exists.
         *
         * Input:
         *  @param roll int - roll number to check
         *
         * Output:
         *  true if exists, false otherwise
         *
         * Approach:
         *  Scan students_ vector for matching roll.
         */
        bool rollExists(int roll) const;

    private:
        std::string filename_;
        std::vector<Student> students_;
    };

} // namespace ReportCard

#endif // STUDENT_MANAGER_H
