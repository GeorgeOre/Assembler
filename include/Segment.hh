#ifndef SEGMENT_HH
#define SEGMENT_HH

#include <string>

class Segment {
public:
    Segment();
    Segment(const std::string& data);

    std::string getData() const;

private:
    std::string data;
};

#endif
