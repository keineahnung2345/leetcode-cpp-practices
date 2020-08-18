//Backtrack
//Runtime: 4 ms, faster than 77.11% of C++ online submissions for Numbers With Same Consecutive Differences.
//Memory Usage: 8.4 MB, less than 24.87% of C++ online submissions for Numbers With Same Consecutive Differences.
class Solution {
public:
    int N, K;
    vector<int> ans;
    
    void backtrack(int cur){
        int digit = (cur == 0) ? 1 : log10(cur)+1;
        // cout << "cur: " << cur << ", " << digit << endl;
        if(digit == N){
            ans.push_back(cur);
        }else{
            int last = cur%10;
            
            if(last-K >= ((cur == 0) ? 1 : 0)) backtrack(cur*10 + last-K);
            //K!=0: to avoid duplicate
            if(K != 0 && last+K <= 9) backtrack(cur*10 + last+K);
        }
    }
    
    vector<int> numsSameConsecDiff(int N, int K) {
        this->N = N;
        this->K = K;
        
        if(N == 1) ans.push_back(0);
        
        /*
        here we skip 0,
        because it may generate duplicate number
        
        For example, N=3 and K=7:
        cur: 0->7->70->707
        and 
        cur: 7->70->707
        */
        for(int i = 1; i <= 9; ++i){
            backtrack(i);
        }
        
        return ans;
    }
};
