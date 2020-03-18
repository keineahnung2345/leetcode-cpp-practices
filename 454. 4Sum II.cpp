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

//vector and find
//TLE
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        vector<int> abSum, cdSum;
        int N = A.size();
        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                abSum.push_back(A[i] + B[j]);
            }
        }
        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cdSum.push_back(C[i] + D[j]);
            }
        }
        
        sort(abSum.begin(), abSum.end());
        sort(cdSum.begin(), cdSum.end());
        
//         for(int e : abSum){
//             cout << e << " ";
//         }
//         cout << endl;
        
//         for(int e : cdSum){
//             cout << e << " ";
//         }
//         cout << endl;
        
        int ans = 0, curCount;
        for(int i = 0; i < abSum.size(); i++){
            if(i > 0 && abSum[i] == abSum[i-1]){
                // cout << i << " add last curCount" << endl;
                ans += curCount;
                continue;
            }
            // cout << "finding " << -abSum[i] << endl;
            auto leftIt = find(cdSum.begin(), cdSum.end(), -abSum[i]);
            if(leftIt != cdSum.end()){
                auto rightIt = find(cdSum.rbegin(), cdSum.rend(), -abSum[i]);
                int left = leftIt - cdSum.begin();
                int right = cdSum.rend() - rightIt - 1;
                curCount = right-left+1;
                // cout << left << " " << right << " " << curCount << endl;
                ans += curCount;
            }else{
                curCount = 0;
            }
        }
        
        return ans;
    }
};
