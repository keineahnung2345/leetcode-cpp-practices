//TLE
//2 for loop, O(n^2)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> ans;
        for(int i = 0; i < T.size(); i++){
            bool found = false;
            for(int j = i+1; j < T.size(); j++){
                if(T[j] > T[i]){
                    ans.push_back(j-i); 
                    found = true;
                    break;
                }
            }
            if(!found) ans.push_back(0);
        }
        return ans;
    }
};

//Approach #1: Next Array(use a map)
//Runtime: 204 ms, faster than 32.99% of C++ online submissions for Daily Temperatures.
//Memory Usage: 14.1 MB, less than 100.00% of C++ online submissions for Daily Temperatures.
//N: size of T, W: range of T's value, time:O(NW), space: O(N+W)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> ans(T.size());
        vector<int> temp2ix(101, INT_MAX); //the maximum value of temperature is 100
        
        for(int i = T.size()-1; i >= 0; i--){
            int warmer_index = INT_MAX;
            for(int t = T[i] + 1; t <= 100; t++){
                warmer_index = min(warmer_index, temp2ix[t]);
            }
            if(warmer_index < INT_MAX)
                ans[i] = warmer_index - i;
            temp2ix[T[i]] = i;
        }
        
        return ans;
    }
};

//Approach #2: Stack
//Runtime: 188 ms, faster than 88.60% of C++ online submissions for Daily Temperatures.
//Memory Usage: 13.9 MB, less than 100.00% of C++ online submissions for Daily Temperatures.

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> ans(T.size());
        stack<int> stk;
        
        for(int i = T.size()-1; i >= 0; i--){
            //pop all values < current value
            while(!stk.empty() && T[stk.top()] <= T[i]){
                stk.pop();
            }
            ans[i] = stk.empty()?0:stk.top()-i;
            stk.push(i);
        }
        return ans;
    }
};
