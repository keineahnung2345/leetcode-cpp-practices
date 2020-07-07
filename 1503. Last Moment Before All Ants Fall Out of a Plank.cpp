//Runtime: 124 ms, faster than 11.48% of C++ online submissions for Last Moment Before All Ants Fall Out of a Plank.
//Memory Usage: 23 MB, less than 100.00% of C++ online submissions for Last Moment Before All Ants Fall Out of a Plank.
class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        
        if(left.empty() && right.empty()){
            return 0;
        }else if(left.empty()){
            return n - right[0];
        }else if(right.empty()){
            return left.back();
        }
        
        return max(n-right[0], left.back());
    }
};
