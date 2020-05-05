/**
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
**/

//Runtime: 40 ms, faster than 86.06% of C++ online submissions for First Unique Character in a String.
//Memory Usage: 12.8 MB, less than 99.44% of C++ online submissions for First Unique Character in a String.

class Solution {
public:
    int firstUniqChar(string s) {
        if(s.size() == 0) return -1;
        
        vector<int> start(26), count(26);
        int ans = INT_MAX;
        
        for(int i = 0; i < s.size(); i++){
            int cix = s[i] - 'a';
            if(count[cix]==0){
                start[cix] = i;
                count[cix] = 1;
            }else{
                count[cix] += 1;
            }
        }
        
        for(int i = 0; i < 26; i++){
            if(count[i] == 1){
                ans = min(ans, start[i]);
            }
        }
        
        if(ans == INT_MAX) return -1;
        
        return ans;
    }
};

/**
Complexity Analysis

Time complexity : O(N) since we go through the string of length N two times.
Space complexity : O(N) since we have to keep a hash map with N elements.
**/

//Runtime: 40 ms, faster than 86.06% of C++ online submissions for First Unique Character in a String.
//Memory Usage: 12.9 MB, less than 98.51% of C++ online submissions for First Unique Character in a String.
class Solution {
public:
    int firstUniqChar(string s) {
        int n = s.size();
        
        vector<int> count(26);
        
        for(char c : s){
            count[c-'a'] += 1;
        }
        
        for(int i = 0; i < n; i++){
            if(count[s[i]-'a'] == 1) return i;
        }
        
        return -1;
    }
};

//Runtime: 200 ms, faster than 8.30% of C++ online submissions for First Unique Character in a String.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for First Unique Character in a String.
class Solution {
public:
    int firstUniqChar(string s) {
        vector<pair<char, int>> v;
        for(int i = 0; i < s.size(); i++){
            char c = s[i];
            auto it = find_if(v.begin(), v.end(), 
                [&c](const pair<char, int>& p){return p.first == c;});
            if(it == v.end()){
                //first meet
                v.push_back(make_pair(c, i));
            }else{
                it->second = -1;
            }
        }
        
        int ans = -1;
        
        for(pair<char,int>& p : v){
            if(p.second != -1){
                ans = p.second;
                break;
            }
        }
        
        return ans;
    }
};
