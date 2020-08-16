//Runtime: 8 ms, faster than 50.00% of C++ online submissions for Three Consecutive Odds.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Three Consecutive Odds.
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int count = 0;
        for(int& e : arr){
            if(e&1){
                ++count;
                if(count == 3) return true;
            }else{
                count = 0;
            }
        }
        return false;
    }
};
