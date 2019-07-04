#include "foundational/allocation/bytes.hpp"
#include <ostream>

std::ostream& foundational::allocation::operator<<(std::ostream& os, Bytes b) {
    os << b.b_count() << "b";
    return os;
}

std::ostream& foundational::allocation::operator<<(std::ostream& os, KBytes b) {
    os << b.k_count() << "kb";
    return os;
}

std::ostream& foundational::allocation::operator<<(std::ostream& os, MBytes b) {
    os << b.m_count() << "mb";
    return os;
}

std::ostream& foundational::allocation::operator<<(std::ostream& os, GBytes b) {
    os << b.g_count() << "gb";
    return os;
}
