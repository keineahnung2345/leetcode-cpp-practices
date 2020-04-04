//Runtime: 84 ms, faster than 16.28% of C++ online submissions for Longest Substring Without Repeating Characters.
//Memory Usage: 13.3 MB, less than 31.84% of C++ online submissions for Longest Substring Without Repeating Characters.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        int start = 0, end = 0;
        map<char, int> position;
        
        while(end < s.size()){
            ans = max(ans, end-start+1);
            position[s[end]] = end;
            // cout << start << " " << end << endl;
            // for(auto it = position.begin(); it != position.end(); it++){
            //     cout << it->first << " " << it->second << " | ";
            // }
            // cout << endl;
            if(end+1 < s.size()){
                if(position.find(s[end+1]) == position.end()){
                    end++;
                }else{
                    int newStart = position[s[end+1]]+1;
                    for(int i = start; i < newStart; i++){
                        position.erase(s[i]);
                    }
                    start = newStart;
                    end++;
                    // position.clear();
                }
            }else{
                break;
            }
        }
        
        return ans;
    }
};

//Brute Force
//TLE
//894 / 987 test cases passed.
//time: O(N^3), space: O(min(size_of_string, size_of_charset))
class Solution {
public:
    bool allUnique(string& s, int start, int end){
        set<char> chars;
        
        for(int i = start; i <= end; i++){
            auto res = chars.insert(s[i]);
            if(res.second == false) return false;
        }
        
        return true;
    };
    
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        for(int i = 0; i < s.size(); i++){
            for(int j = i; j < s.size(); j++){
                if(allUnique(s, i, j)){
                    ans = max(ans, j-i+1);
                }
            }
        }
        return ans;
    }
};

//Approach 2: Sliding Window, using set
//Runtime: 80 ms, faster than 16.88% of C++ online submissions for Longest Substring Without Repeating Characters.
//Memory Usage: 13.4 MB, less than 30.85% of C++ online submissions for Longest Substring Without Repeating Characters.
//time: O(N), space: O(min(size_of_string, size_of_charset))
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        set<char> chars;
        int ans = 0, i = 0, j = 0;
        while(i < n && j < n){
            // cout << i << " " << j << endl;
            if(chars.find(s[j]) == chars.end()){
                //move head forward
                chars.insert(s[j]);
                ans = max(ans, j-i+1);
                j++;
            }else{
                //move tail forward
                chars.erase(s[i]);
                i++;
            }
        }
        
        return ans;
    }
};
