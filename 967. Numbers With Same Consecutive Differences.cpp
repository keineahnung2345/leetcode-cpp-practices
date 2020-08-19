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

//Approach 1: DFS (Depth-First Search)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Numbers With Same Consecutive Differences.
//Memory Usage: 8 MB, less than 46.79% of C++ online submissions for Numbers With Same Consecutive Differences.
//time: O(N*2^N), we have 9*(2^(N-1)) potention combinations, and to generate each combination, we need O(N) for recursion
//space: O(2^N), recursion space: O(N), answer space: O(9*(2^(N-1))) = O(2^N)
class Solution {
public:
    int K;
    vector<int> ans;
    
    void dfs(int N, int num){
        if(N == 0){
            ans.push_back(num);
        }else{
            int d = num%10;
            
            if(d-K >= 0){
                dfs(N-1, num*10 + (d-K));
            }
            
            if(K != 0 && d+K <= 9){
                dfs(N-1, num*10 + (d+K));
            }
        }
    }
    
    vector<int> numsSameConsecDiff(int N, int K) {
        this->K = K;
        
        if(N == 1) ans.push_back(0);
        
        for(int num = 1; num <= 9; ++num){
            dfs(N-1, num);
        }
        
        return ans;
    }
};

//Approach 2: BFS (Breadth-First Search)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Numbers With Same Consecutive Differences.
//Memory Usage: 7.1 MB, less than 96.29% of C++ online submissions for Numbers With Same Consecutive Differences.
//time: O(N*2^N), we have 9*(2^(N-1)) potention combinations, and to generate each combination, we need O(N)
//space: O(2^N), in the queue, we could have at most two level of elements, for first level, it takes O(9*2^(N-1)), for 2nd level, it takes O(9*2^(N-1-1))
class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        if(N == 1){
            return {0,1,2,3,4,5,6,7,8,9};
        }
        
        queue<int> q;
        
        for(int i = 1; i <= 9; ++i){
            q.push(i);
        }
        
        int level = 1;
        vector<int> ans;
        
        while(level <= N){
            int level_size = q.size();
            
            while(level_size-- > 0){
                int cur = q.front(); q.pop();
                
                if(level == N){
                    ans.push_back(cur);
                }else{
                    int d = cur%10;
            
                    if(d-K >= 0){
                        q.push(cur*10 + (d-K));
                    }

                    if(K != 0 && d+K <= 9){
                        q.push(cur*10 + (d+K));
                    }
                }
            }
            
            ++level;
        }
        
        return ans;
    }
};
