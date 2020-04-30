//Runtime: 16 ms, faster than 14.29% of C++ online submissions for Maximum Score After Splitting a String.
//Memory Usage: 6.9 MB, less than 100.00% of C++ online submissions for Maximum Score After Splitting a String.
class Solution {
public:
    int maxScore(string s) {
        int ans = 0;
        int n = s.size();
        vector<int> left(n, 0), right(n, 0);
        
        for(int i = 0; i < s.size(); i++){
            left[i] = ((i > 0) ? left[i-1] : 0) + (s[i] == '0');
            right[s.size()-1-i] = ((i > 0) ? right[s.size()-1-i+1] : 0) + (s[s.size()-1-i] == '1');
        }
        
        for(int i = 0; i < n; i++){
            cout << left[i] << " ";
        }
        cout << endl;
        
        for(int i = 0; i < n; i++){
            cout << right[i] << " ";
        }
        cout << endl;
        
        for(int i = 0; i < n-1; i++){
            ans = max(ans, left[i] + right[i+1]);
        }
        
        return ans;
    }
};

//One Pass
//https://leetcode.com/problems/maximum-score-after-splitting-a-string/discuss/597716/Java-5-Liner-(One-Pass)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Maximum Score After Splitting a String.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for Maximum Score After Splitting a String.
class Solution {
public:
    int maxScore(string s) {
        int zeros = 0, ones = 0, ans = INT_MIN;
        int n = s.size();
        /*
        ans 
        = max(lZero+rOne)
        = max(lZero+totalOne-lOne)
        = max(lZero-lOne) + totalOne
        */
        for(int i = 0; i < n; i++){
            if(s[i] == '0') zeros++;
            else ones++;
            /*
            there should be at least one char in the right part,
            so don't update ans in the last iteration
            */
            if(i != n-1) ans = max(ans, zeros-ones);
        }
        
        return ans + ones;
    }
};
