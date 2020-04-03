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
