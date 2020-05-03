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
