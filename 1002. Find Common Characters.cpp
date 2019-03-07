/**
Given an array A of strings made only from lowercase letters, 
return a list of all characters that show up in all strings within the list (including duplicates).  
For example, if a character occurs 3 times in all strings but not 4 times, 
you need to include that character three times in the final answer.

You may return the answer in any order.
**/

//Runtime: 48 ms, faster than 6.57% of C++ online submissions for Find Common Characters.
//Memory Usage: 16.7 MB, less than 100.00% of C++ online submissions for Find Common Characters.
class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        vector<map<char, int>> charCounts;
        
        //build maps for strings in A
        for(string s : A){
            map<char, int> charCount;
            for(char c : s){
                if(charCount.find(c)==charCount.end()){
                    charCount[c] = 1;
                }else{
                    charCount[c] += 1;
                }
            }
            charCounts.push_back(charCount);
        }
        
        map<char, int> charCount0 = charCounts[0];
        for(int i = 1; i < charCounts.size(); i++){
            //compare charCount0 and charCounts[i]
            // cout << i << "th" << endl;
            for(map<char, int>::iterator it=charCount0.begin(); it!=charCount0.end(); it++){
                char c = it->first;
                if(charCounts[i].find(c)==charCounts[i].end()){
                    charCount0[c] = 0;
                }else{
                    charCount0[c] = min(charCount0[c], charCounts[i][c]);
                }
                // cout << c << ": " << charCount0[c] << ", ";
            }
            // cout << endl;
        }
        
        // for(const auto& c : charCount0){
        //     cout << c.first << ", " << c.second << endl;
        // }
        // cout << endl;
        
        vector<string> ans;
        for(map<char, int>::iterator it=charCount0.begin(); it!=charCount0.end(); it++){
            while(it->second>0){
                ans.push_back(string(1,it->first));
                it->second-=1;
            }
        }
        
        return ans;
    }
};
