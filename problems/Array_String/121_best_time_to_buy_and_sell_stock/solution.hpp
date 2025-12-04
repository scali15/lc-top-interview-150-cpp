#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n < 2) return 0;
        int lowPrice = prices[0];
        int bestProfit = 0;

        for (int i = 1; i < n; i++){
            if (prices[i] <= lowPrice) lowPrice = prices[i];
            else{
                int profit = prices[i] - lowPrice;
                bestProfit = max(profit, bestProfit);
            }
        }

        return bestProfit;
    }
};