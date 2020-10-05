//bfs
//TLE
//127 / 308 test cases passed.
class Solution {
public:
    int minimumOneBitOperations(int n) {
        queue<int> q;
        int level = 0;
        
        q.push(0);
        
        unordered_set<int> visited;
        visited.insert(0);
        
        while(!q.empty()){
            int levelSize = q.size();
            
            while(levelSize-- > 0){
                int cur = q.front(); q.pop();
                
                if(cur == n){
                    return level;
                }
                
                if(visited.find(cur^1) == visited.end()){
                    q.push(cur^1);
                    visited.insert(cur^1);
                }
                
                for(int i = 0, mask = 1; cur >= 1<<i; ++i, mask += 1<<i){
                    // cout << "cur: " << cur << ", i: " << i << ", mask: " << mask << endl;
                    if((cur & mask) == (1<<i)){
                        int next = cur^(1<<(i+1));
                        // cout << "next: " << next << endl;
                        if(visited.find(next) == visited.end()){
                            q.push(next);
                            visited.insert(next);
                        }
                        break;
                    }
                }
                
            }
            
            ++level;
        }
        
        return -1;
    }
};

//greedy, recursion
//https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/discuss/877741/C%2B%2B-solution-with-explanation
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Minimum One Bit Operations to Make Integers Zero.
//Memory Usage: 6.3 MB, less than 50.00% of C++ online submissions for Minimum One Bit Operations to Make Integers Zero.
class Solution {
public:
    int minimumOneBitOperations(int n) {
        //base case
        if(n <= 1) return n;
        /*
        1 -> 0: 1
        10 -> 11 -> 01 -> ... : 2+1=3
        100 -> 101 -> 111 -> 110 -> 010: 4+2+1=7
        1000 -> 1001 -> 1011 -> 1010 -> 1110 -> 1111 -> 1101 -> 1100 -> 0100: 8+4+2+1=15
        turn 1<<n to 0 needs (1<<(n+1))-1
        */
        
        int bit = 0;
        while(1<<bit <= n){
            ++bit;
        }
        --bit;
        
        /*
        for n = 1000, 1<<bit = 1000
        for n = 1110, 1<<bit = 1000
        
        f(1000) = f(1110) + f(0110)
        f(1110) = f(1000) - f(0110)
        */
        
        //process the MSB first: from 0 to 1<<bit: (1<<bit+1)-1
        //then recursively process later bits
        return ((1<<bit+1)-1) - minimumOneBitOperations(n-(1<<bit));
    }
};
