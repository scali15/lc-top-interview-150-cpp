#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class VectorUtils {
public:
    static std::vector<int> parseList(std::string list) {
        vector<int> nums;

        string s = list.substr(1, list.size()-2);             // "[1,2,0,5,7,3,4]" => "1,2,0,5,7,3,4"
        stringstream ss(s);
        string token;

        while (getline(ss, token, ',')) {
            nums.push_back(stoi(token));
        }
        return nums;
    }

    template<typename T>
    static std::string printVec(const std::vector<T>& vec) {
        if (vec.size() > 500) { return "[absolutely massive vector]"; }
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
