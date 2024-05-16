#include "Segment.hh"

// Constructor
Segment::Segment(const std::string& data) : data(data) {}

// Destructor
Segment::~Segment() {}

// Member function to check if the segment matches a given string
bool Segment::segment_match(const std::string& matchString) const {
    return data == matchString;
}

// Getter for the data member
const std::string& Segment::getData() const {
    return data;
}
