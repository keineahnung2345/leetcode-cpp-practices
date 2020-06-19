//iteration + memorization
//TLE
//1 / 258 test cases passed.
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        int n = cells.size(), state = 0;
        vector<int> memo(1<<n);
        
        for(int i = 0; i < n; i++){
            state += (cells[i] << i);
        }
        
        while(N-- > 0){
            if(memo[state] != 0){
                state = memo[state];
                continue;
            }
            
            int tmp = 0;
            
            for(int i = 1; i < n-1; ++i){
                // cout << i << ": " << (state&(1<<(i-1))) << ", " << (state&(1<<(i+1))) << endl;
                if((bool)(state&(1<<(i-1))) == (bool)(state&(1<<(i+1)))){
                    tmp |= (1 << i);
                    // cout << i << " ";
                }
            }
            // cout << endl;
            
            state = memo[state] = tmp;
        }
        
        for(int i = 0; i < n; i++){
            cells[i] = ((state & (1 << i)) > 0);
        }
        
        return cells;
    }
};
