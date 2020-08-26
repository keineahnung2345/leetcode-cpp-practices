//Greedy + recursion
//https://leetcode.com/problems/remove-duplicate-letters/discuss/76768/A-short-O(n)-recursive-greedy-solution
//Runtime: 16 ms, faster than 17.06% of C++ online submissions for Remove Duplicate Letters.
//Memory Usage: 8.8 MB, less than 5.05% of C++ online submissions for Remove Duplicate Letters.
class Solution {
public:
    string removeDuplicateLetters(string s) {
        int n = s.size();
        
        if(n == 0)
            return "";
        
        vector<int> counter(26, 0);
        
        for(char& c : s){
            ++counter[c-'a'];
        }
        
        int start = 0;
        for(int i = 0; i < n; ++i){
            if(s[i] < s[start]){
                start = i;
            }
            --counter[s[i]-'a'];
            //there are counter[s[i]-'a'] s[i] in s[i+1...]
            if(counter[s[i]-'a'] == 0){
                //skip those index s.t. s[i] is missing
                break;
            }
        }
        
        string nexts = s.substr(start+1);
        auto it = remove(nexts.begin(), nexts.end(), s[start]);
        nexts = std::string(nexts.begin(), it);
        // cout << "remove " << s[start] << ", next: " << nexts << endl;
        return s[start]+removeDuplicateLetters(nexts);
    }
};
