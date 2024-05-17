#include "Segment.hh"

Segment::Segment() : data("") {} // Default constructor

Segment::Segment(const std::string& data) : data(data) {}

std::string Segment::getData() const {
    return data;
}
