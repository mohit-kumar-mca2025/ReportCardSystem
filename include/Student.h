#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

namespace ReportCard
{

    /**
     * @class Student
     * @brief Holds data for one student and provides grade/result calculations.
     */
    class Student
    {
    public:
        // --- Constructors ---
        /**
         * Objective:
         *  Create an empty student object.
         *
         * Input: None
         * Output: Default constructed Student
         * Approach: Initializes values to safe defaults.
         */
        Student();

        /**
         * Objective:
         *  Create a student object with all basic data and marks.
         *
         * Input:
         *  @param name std::string - student name
         *  @param className std::string - class/section
         *  @param roll int - roll number (unique within class)
         *  @param marks std::vector<int> - marks per subject
         *
         * Output: Constructed Student
         * Approach: Copies inputs into object and updates computed fields.
         */
        Student(const std::string &name, const std::string &className, int roll, const std::vector<int> &marks);

        // --- Accessors ---
        const std::string &getName() const;
        const std::string &getClassName() const;
        int getRoll() const;
        const std::vector<int> &getMarks() const;
        int getTotal() const;
        double getPercentage() const;
        std::string getGrade() const;
        bool isPass() const;

        // --- Operations ---
        /**
         * Objective:
         *  Recalculate total, percentage, grade and pass/fail flag from marks.
         *
         * Input: None (uses internal marks)
         * Output: Updates internals: total, percentage, grade, passFlag
         * Approach: Sum marks; percentage = total / (marks.size() * 100) * 100; assign grade by bracket.
         */
        void recalculate();

        /**
         * Objective:
         *  Serialize student to a single CSV line for file storage.
         *
         * Input: None
         * Output: std::string CSV line
         * Approach: escape name/class if needed and join fields; marks stored comma-separated in a quoted field.
         */
        std::string toCSV() const;

        /**
         * Objective:
         *  Parse a CSV line (as produced by toCSV) and populate the Student object.
         *
         * Input:
         *  @param line std::string - CSV line
         * Output: true if success, false otherwise
         * Approach: Split fields carefully, parse marks list and other fields.
         */
        static bool fromCSV(const std::string &line, Student &outStudent);

        /**
         * Objective:
         *  Pretty print report card text block for the student.
         *
         * Input: None
         * Output: std::string containing formatted report card
         * Approach: Compose a multi-line string with student details and marks.
         */
        std::string formattedReportCard() const;

    private:
        std::string name_;
        std::string className_;
        int roll_;
        std::vector<int> marks_;

        // computed
        int total_;
        double percentage_;
        std::string grade_;
        bool pass_;
    };

} // namespace ReportCard

#endif // STUDENT_H
