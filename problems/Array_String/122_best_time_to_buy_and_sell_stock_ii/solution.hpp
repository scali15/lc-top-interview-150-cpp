#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // confusing but I remember solving this one for the LC 75
    // it's literally just add up all positive increases in stock
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n < 2) { return 0; }

        int profit = 0;

        for (int i = 1; i < n; i++){
            if (prices[i] > prices[i-1]) { profit += prices[i]-prices[i-1]; }
        }

        return profit;
    }
};
