//Runtime: 12 ms, faster than 88.68% of C++ online submissions for Binary Prefix Divisible By 5.
//Memory Usage: 10.8 MB, less than 78.57% of C++ online submissions for Binary Prefix Divisible By 5.
class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        vector<bool> ans(A.size());
        int acc = 0;
        for(int i = 0; i < A.size(); i++){
            //(x*2) % 5 = (x%5) * 2
            //(x+y) % 5 = x%5 + y%5
            acc = ((acc << 1) +  A[i]) % 5;
            if(acc == 0){
                ans[i] = true;
            }
        }
        return ans;
    }
};
