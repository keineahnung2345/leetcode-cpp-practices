//Runtime: 4 ms, faster than 63.72% of C++ online submissions for Play with Chips.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Play with Chips.

class Solution {
public:
    int minCostToMoveChips(vector<int>& chips) {
        int odd_count = 0, even_count = 0;
        for(int chip : chips){
            if(chip % 2 == 1) odd_count++;
            else even_count++;
        }
        //assume we have change all odd chip to 1 and all even chip to 0
        //now we want to either change all 0 to 1 or all 1 to 1
        //we choose to change all 0 to 1 if 0's count is less and vice versa
        return min(even_count, odd_count);
    }
};
