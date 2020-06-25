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

//https://leetcode.com/problems/prison-cells-after-n-days/discuss/266854/Java%3A-easy-to-understand
//time: O(1), space: O(1)
//Runtime: 20 ms, faster than 10.15% of C++ online submissions for Prison Cells After N Days.
//Memory Usage: 12.6 MB, less than 23.83% of C++ online submissions for Prison Cells After N Days.
class Solution {
public:
    vector<int> getNext(vector<int>& cells){
        int n = cells.size();
        vector<int> next(n, 0);
        
        for(int i = 1; i < n-1; ++i){
            next[i] = (cells[i-1]==cells[i+1]);
        }
        
        return next;
    };
    
    int toNum(vector<int>& cells){
        int n = cells.size();
        int num = 0;
        
        for(int i = 0; i < n; ++i){
            num += (1 << i) * cells[i];
        }
        
        return num;
    }
    
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        int key;
        unordered_map<int, int> state2index;
        int cycle, remaining;
        
        for(int i = 0; i < N; ++i){
            key = toNum(cells);
            if(state2index.find(key) != state2index.end()){
                //cycle's size: current index - index of previous same state
                cycle = i - state2index[key];
                //have passed days: [0,i-1], remaining days: [i,N-1]
                remaining = (N-i)%cycle;
                break;
            }
            
            state2index[key] = i;
            cells = getNext(cells);
            // for(int cell : cells){
            //     cout << cell << " ";
            // }
            // cout << endl;
        }
        
        while(remaining-- > 0){
            cells = getNext(cells);
            // for(int cell : cells){
            //     cout << cell << " ";
            // }
            // cout << endl;
        }
        
        return cells;
    }
};
