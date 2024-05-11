// Operand.hh

#ifndef Operand_HH
#define Operand_HH

#include <string>  // Include necessary header file for string
// #include <iostream> // Include necessary header file for cout

using namespace std;  // Include std namespace for string usage

template <typename O>
class Operand {
private:
    /// @brief Size of the operand in bits
    int size;
    /// @brief Raw string that was parsed
    string raw;  

protected:
    /// @brief Type flexible value representation
    O value;

public:
    // Constructors

    /**
     * Initialize a default operand.
     */
    Operand();
    /**
     * Initialize an operand with chosen parameters.
     *
     * @param size the size of the operand in bits
     * @param raw the raw string info
     * @param value type flexible value representation
     */
    Operand(int size, string raw, O value);

    /**
     * Destruct an operand.
     */
    ~Operand();


    // Member functions
    void printValue() const {
        cout << "Parent value: " << value << endl;
    }

    // Accessors and modifiers

    /**
     * Get the value of the operand bit size
     */
    int operand_get_size() const;
    /**
     * Get the value of the operand's raw string
     */
    std::string operand_get_raw() const;
    /**
     * Get the value of the operand value
     */
    O operand_get_value() const;

    /**
     * Set the value of the operand bit size
     *
     * @param size the size of the operand in bits
     */
    void operand_set_size(int size);
    /**
     * Set the value of the operand's raw string
     *
     * @param raw the raw string info
     */
    void operand_set_raw(const std::string& raw);
    /**
     * Set the value of the operand value
     *
     * @param value type flexible value representation
     */
    void operand_set_value(const O& value);
};


#endif