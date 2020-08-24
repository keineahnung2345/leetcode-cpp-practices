//https://leetcode.com/problems/substring-with-concatenation-of-all-words/discuss/13658/Easy-Two-Map-Solution-(C%2B%2BJava)
//Runtime: 544 ms, faster than 56.37% of C++ online submissions for Substring with Concatenation of All Words.
//Memory Usage: 23.1 MB, less than 56.80% of C++ online submissions for Substring with Concatenation of All Words.
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        int m = words.size();
        
        vector<int> ans;
        
        if(m == 0){
            return ans;
        }
        
        int l = words[0].size();
        
        unordered_map<string, int> word2count;
        
        for(string& word : words){
            ++word2count[word];
        }
        
        //m*l: words' total length
        for(int i = 0; i + m*l - 1 < n; ++i){
            int j; //index to "words"
            
            unordered_map<string, int> word2visited;
            
            for(j = 0; j < m; ++j){
                string subs(s.begin()+i+j*l, s.begin()+i+(j+1)*l);
                if(word2count.find(subs) == word2count.end()){
                    break;
                }
                ++word2visited[subs];
                if(word2visited[subs] > word2count[subs]){
                    break;
                }
            }
            
            if(j == m){
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
