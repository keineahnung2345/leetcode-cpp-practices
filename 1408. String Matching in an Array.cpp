//Runtime: 8 ms, faster than 40.00% of C++ online submissions for String Matching in an Array.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for String Matching in an Array.
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        int n = words.size();
        
        set<string> ans;
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j && words[i].find(words[j]) != string::npos){
                    ans.insert(words[j]);
                }
            }
        }
        
        return vector<string>(ans.begin(), ans.end());
    }
};
