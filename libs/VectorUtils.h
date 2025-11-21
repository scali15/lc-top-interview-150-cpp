#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class VectorUtils {
public:
    template<typename T>
    static std::string printVec(const std::vector<T>& vec) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < vec.size(); i++) {
            oss << vec[i];
            if (i + 1 < vec.size()) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    template<typename T>
    static std::string printVec2D(const std::vector<std::vector<T>>& vec2d) {
        std::ostringstream oss;
        for (size_t i = 0; i < vec2d.size(); i++) {
            oss << printVec(vec2d[i]);
            if (i + 1 < vec2d.size()) oss << "\n";
        }
        return oss.str();
    }
    
};
