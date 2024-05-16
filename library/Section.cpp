#include "Section.cpp"

// Initialize the static member
std::unordered_map<std::string, Section> Section::sections;

// Constructor
Section::Section(const std::string& name) : name(name) {}

// Get the name
std::string Section::get_name() const {
    return name;
}

// Get a Section by name
const Section& Section::get(const std::string& name) {
    return sections.at(name);
}

// Add a new Section
void Section::add(const std::string& name) {
    sections.emplace(name, Section(name));
}
