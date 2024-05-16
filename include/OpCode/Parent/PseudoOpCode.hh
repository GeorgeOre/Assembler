#ifndef PSEUDOOPCODE_HH
#define PSEUDOOPCODE_HH

#include <string>
#include <unordered_map>

class PseudoOpCode {
public:
    PseudoOpCode(const std::string& name);
    std::string get_name() const;

    static const PseudoOpCode& get(const std::string& name);
    static void add(const std::string& name);

private:
    std::string name;
    static std::unordered_map<std::string, PseudoOpCode> pseudo_op_codes;
};

#endif
