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
