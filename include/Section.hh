#ifndef SECTION_HH
#define SECTION_HH

#include <string>
#include <unordered_map>

class Section {
public:
    Section(const std::string& name);
    std::string get_name() const;

    static const Section& get(const std::string& name);
    static void add(const std::string& name);

private:
    std::string name;
    static std::unordered_map<std::string, Section> sections;
};

#endif
