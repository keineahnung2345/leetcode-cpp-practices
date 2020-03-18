//https://leetcode.com/problems/4sum-ii/discuss/93917/Easy-2-lines-O(N2)-Python
//Runtime: 464 ms, faster than 10.57% of C++ online submissions for 4Sum II.
//Memory Usage: 49.8 MB, less than 9.09% of C++ online submissions for 4Sum II.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        map<int, int> ABSumCounter, CDSumCounter;
        
        for(int a : A){
            for(int b : B){
                ABSumCounter[a+b] += 1;
            }
        }
        
        for(int c : C){
            for(int d : D){
                CDSumCounter[c+d] += 1;
            }
        }
        
        int ans = 0;
        
        for(auto abit = ABSumCounter.begin(); abit != ABSumCounter.end(); abit++){
            auto cdit = CDSumCounter.find(-abit->first);
            if(cdit != CDSumCounter.end()){
                //we are finding +`++combination, so use product
                ans += (abit->second * cdit->second);
            }
        }
        
        return ans;
    }
};
