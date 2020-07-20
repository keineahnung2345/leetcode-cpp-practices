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

//O(logN)
//https://leetcode.com/problems/water-bottles/discuss/743148/JavaPython-3-O(logN)-and-O(1)-codes-w-brief-analysis.
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Water Bottles.
//Memory Usage: 6 MB, less than 100.00% of C++ online submissions for Water Bottles.
//time: O(logN), space: O(1)
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        //drink
        int ans = numBottles;
        
        //while we can exchange for a full bottle
        while(numBottles >= numExchange){
            //exchange and drink
            ans += numBottles/numExchange;
            numBottles = numBottles/numExchange + numBottles%numExchange;
        }
        return ans;
    }
};
