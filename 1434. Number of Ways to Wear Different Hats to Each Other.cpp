//TLE
//46 / 65 test cases passed.
class Solution {
public:
    vector<bool> used;
    vector<vector<int>> hats;
    int count;
    int MOD = 1e9+7;
    
    void backtrack(int s){
        if(s == hats.size()){
            count = (count+1)%MOD;
            // cout << endl;
            return ;
        }
        
        for(int h : hats[s]){
            if(used[h]) continue;
            used[h] = true;
            // cout << h << " ";
            backtrack(s+1);
            used[h] = false;
        }
        s++;
    };
    
    int numberWays(vector<vector<int>>& hats) {
        sort(hats.begin(), hats.end(), 
            [](const vector<int>& a, const vector<int>& b){
                return a.size() < b.size();
            });
        
        count = 0;
        used = vector<bool>(41, false);
        this->hats = hats;
        backtrack(0);
        // cout << endl;
        return count;
    }
};

//DP + Bitmask
//https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/discuss/608686/C%2B%2B-Bit-masks-and-Bottom-Up-DP
//Runtime: 32 ms, faster than 100.00% of C++ online submissions for Number of Ways to Wear Different Hats to Each Other.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Number of Ways to Wear Different Hats to Each Other.
class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        int m = 40; //kinds of hats
        const int n = hats.size(); //number of people
        const int MOD = 1e9+7;
            
        vector<vector<int>> people(m);
        
        //record the counts of each state from 0 to 11...1(n 1s)
        vector<int> stateCounts(1 << n);
        /*
        state 0 means that all people do not wear a hat,
        and there could only be 1 possible combination of that state 
        */
        stateCounts[0] = 1;
        
        /*
        hats[i] lists the hats person i likely to wear
        */
        for(int i = 0; i < n; i++){
            for(int h : hats[i]){
                //the hat "h" can be worn by person i
                people[h-1].emplace_back(i);
            }
        }
        
        for(int h = 0; h < m; h++){
            // for(int j = 0; j < 1 << n; j++){
            for(int j = (1 << n)-1; j >= 0; j--){
                //hat 'h' can be distributed to person 'p'
                for(int p : people[h]){
                    //skip the state in which person 'p' already has a hat
                    /*
                    the result of (j & (1 << p)) will be 1<<p,
                    so we can not check with ((j & (1 << p)) == 1)
                    */
                    if((j & (1 << p)) != 0) continue;
                    stateCounts[j | (1 << p)] += stateCounts[j];
                    stateCounts[j | (1 << p)] %= MOD;
                }
            }
        }
        
        return stateCounts[(1<<n)-1];
    }
};
