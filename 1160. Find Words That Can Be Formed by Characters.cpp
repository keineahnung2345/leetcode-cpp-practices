//Runtime: 64 ms, faster than 96.69% of C++ online submissions for Find Words That Can Be Formed by Characters.
//Memory Usage: 17.4 MB, less than 100.00% of C++ online submissions for Find Words That Can Be Formed by Characters.

class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> count(26), tmp_count(26);
        bool isGood;
        int ans = 0;
        
        for(char c : chars){
            count[c - 'a']++;
        }
        
        for(string word : words){
            fill(tmp_count.begin(), tmp_count.end(), 0);
            isGood = true;
            for(char c : word){
                tmp_count[c - 'a']++;
                if(tmp_count[c - 'a'] > count[c - 'a']){
                    isGood = false;
                    break;
                }
            }
            if(isGood){
                ans += word.size();
            }
        }
        
        return ans;
    }
};
