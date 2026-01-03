#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <cstddef> // pour size_t
#include <algorithm> // pour std::min

template <typename T>
std::vector<T> subvector(const std::vector<T>& vec, size_t start, size_t length) {
    if (start >= vec.size()) return {}; // retour vide si start trop grand

    size_t end = std::min(start + length, vec.size());
    return std::vector<T>(vec.begin() + start, vec.begin() + end);
}

#endif //  __UTILS_HPP__

