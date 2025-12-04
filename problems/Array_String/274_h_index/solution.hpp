#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Solution {
public:
    // approach: not sure how to do this off rip
    // naive is just make a vector of size 1000 and mark each but thats like O(n * 1000) and large space too
    // actually maybe sorting
    // yeah, then iterate backward until a number of citations <= number seen
    // if this never happens then h index is just i
    // should be capped by nlogn quicksort, which isint much worse than O(n)
    // probably not optimal, but its a start

    // got 69/83 and failed on this test case: [0,0,2]
    int hIndex(vector<int>& citations) {
        int n = citations.size();

        sort(citations.begin(), citations.end(), greater<int>());

        int i = 0;
        while (i < n) {
            if (i+1 >= citations[i]){
                return max(i, citations[i]);    // changed this to return max instead of just citations[i]
            }
            i++;
        }
        return i;
    }

    // wow, I guess that was it. got 0ms. only top ~30% for space tho, but its already O(1) so idc
    // and yeah time complexity is O(nlogn)
};
