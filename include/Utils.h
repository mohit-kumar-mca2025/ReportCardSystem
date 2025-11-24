#ifndef UTILS_H
#define UTILS_H

#include <string>

/// Small collection of console helper functions used across the app.
/// Placed in namespace RCUtils to avoid global name clashes.
namespace RCUtils
{

    /**
     * @brief Pause the console until user presses Enter.
     *
     * Objective:
     *   Give user time to read output before continuing.
     *
     * Input:
     *   None.
     *
     * Output:
     *   Blocks until Enter is pressed.
     *
     * Approach:
     *   Uses std::cin.ignore with large limit to flush leftover input,
     *   then waits for a newline.
     *
     * Side Effects:
     *   - Consumes characters from std::cin input buffer.
     *   - Causes console I/O (printing text to user).
     */
    void pause();

    /**
     * @brief Read an integer from stdin with validation and reprompt.
     *
     * Objective:
     *   Read a whole number from console. Re-prompts on invalid input.
     *
     * Input:
     *   prompt - message printed to user before reading.
     *
     * Output:
     *   Returns a valid int entered by the user.
     *
     * Approach:
     *   Uses std::cin extraction and checks for failure; clears error state
     *   and flushes invalid input when needed.
     *
     * Side Effects:
     *   - Reads from std::cin (console input).
     *   - Prints prompt and error messages to console.
     *   - Modifies std::cin state (clearing failbit, ignoring characters).
     *
     * @param prompt std::string prompt to display
     * @return int parsed integer
     */
    int readInt(const std::string &prompt);

    /**
     * @brief Read a full line (possibly empty) from stdin.
     *
     * Objective:
     *   Read a line of text including spaces.
     *
     * Input:
     *   prompt - message printed to user before reading.
     *
     * Output:
     *   Returns the input line as std::string.
     *
     * Approach:
     *   Uses std::getline after printing the prompt.
     *
     * Side Effects:
     *   - Prints prompt to console.
     *   - Reads from std::cin (console input).
     *
     * @param prompt std::string prompt to display
     * @return std::string the line entered by the user
     */
    std::string readLine(const std::string &prompt);

    /**
     * @brief Read a mark (integer between 0 and 100) with validation.
     *
     * Objective:
     *   Ensure marks entered are integers in the range [0,100].
     *
     * Input:
     *   prompt - message printed to user before reading.
     *
     * Output:
     *   Returns a validated mark (0..100).
     *
     * Approach:
     *   Re-prompts until a valid integer within range is provided.
     *
     * Side Effects:
     *   - Reads from std::cin.
     *   - Prints prompts and error messages to console.
     *   - Clears and updates std::cin state on invalid input.
     *
     * @param prompt std::string prompt to display
     * @return int validated mark (0..100)
     */
    int readMark(const std::string &prompt);

} // namespace RCUtils

#endif // UTILS_H
