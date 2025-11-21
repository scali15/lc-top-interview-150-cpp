#include <string>

using namespace std;

class Solution {
public:
    inline bool asciiAlnum(unsigned char c) {
        return (c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z');
    }

    inline unsigned char asciiLower(unsigned char c) {
        if (c >= 'A' && c <= 'Z') return c + 32;
        return c;
    }

    bool isPalindrome(const string& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            while (left < right && !asciiAlnum(s[left])) left++;
            while (left < right && !asciiAlnum(s[right])) right--;

            // Compare lowercase versions
            if (asciiLower(s[left]) != asciiLower(s[right])) 
                return false;

            left++; right--;
        }
        return true;
    }
};