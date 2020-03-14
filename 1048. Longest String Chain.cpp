//Runtime: 1240 ms, faster than 6.56% of C++ online submissions for Longest String Chain.
//Memory Usage: 325.5 MB, less than 100.00% of C++ online submissions for Longest String Chain.
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int N = words.size();
        
        sort(words.begin(), words.end(), [](string& a, string& b){
            return (a.size() == b.size()) ? (a < b) : (a.size() < b.size());
        });
        
        //at start, each word forms a chain of length 1
        vector<int> length(N, 1);
        int maxLen = 1;
        
        //start from 2nd last word
        for(int i = N-2; i >= 0; i--){
            string word = words[i];
            
            for(int j = i+1; j < N; j++){
                string successor = words[j];
                if(successor.size() == word.size()+1){
                    //check if word is a predecessor of successor
                    bool found = false;
                    for(int k = 0; k < successor.size(); k++){
                        if(successor.substr(0, k) + successor.substr(k+1) == word)
                            found = true;
                    }
                    if(found){
                        length[i] = max(length[i], length[j]+1);
                    }
                }
            }
            
            maxLen = max(maxLen, length[i]);
        }
        
        return maxLen;
    }
};

//https://leetcode.com/problems/longest-string-chain/discuss/294890/C%2B%2BJavaPython-DP-Solution
//Runtime: 152 ms, faster than 32.27% of C++ online submissions for Longest String Chain.
//Memory Usage: 49.9 MB, less than 100.00% of C++ online submissions for Longest String Chain.
//time: O(NlogN) for sorting
//time: O(NSS) for the for loop, S for the length of each word, S <= 16, second S for the generation of substring
//space: O(NS)
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int N = words.size();
        unordered_map<string, int> length;
        int ans = 1;
        
        sort(words.begin(), words.end(), [](string& a, string& b){
            return a.size() < b.size();
        });
        
        for(string& word : words){
            for(int i = 0; i < word.size(); i++){
                length[word] = max(length[word], length[word.substr(0, i)+word.substr(i+1)]+1);
            }
            ans = max(ans, length[word]);
        }
        
        return ans;
    }
};
