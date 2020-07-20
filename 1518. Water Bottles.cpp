//Runtime: 4 ms, faster than 33.56% of C++ online submissions for Water Bottles.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Water Bottles.
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int ans = 0;
        int numEmptyBottles = 0;
        
        while(numBottles){
            ans += numBottles;
            // cout << numBottles << ", " << numEmptyBottles << endl;
            int total = numBottles+numEmptyBottles;
            numBottles = total/numExchange;
            numEmptyBottles = total%numExchange;
        }
        
        return ans;
    }
};
