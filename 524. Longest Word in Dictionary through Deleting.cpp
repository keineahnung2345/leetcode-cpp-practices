//Approach 1: Recursive Brute Force
//time: O(2^n), space: O(2^n)

//Approach 2: Iterative Brute Force
//time: O(2^n), space: O(2^n)

//Approach 3: Sorting and Checking Subsequence
//Runtime: 88 ms, faster than 64.35% of C++ online submissions for Longest Word in Dictionary through Deleting.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Longest Word in Dictionary through Deleting.
//time: O((nlogn + n)*x), x refers to average string length
//space: O(logn)
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end(), [](const string& a, const string& b){
            return (a.size() == b.size()) ? a < b : a.size() > b.size();
        });
        
        for(string& word : d){
            int wi = 0, si = 0;
            while(wi < word.size() && si < s.size()){
                if(word[wi] == s[si]){
                    wi++;
                    si++;
                }else{
                    si++;
                }
            }
            // cout << wi << "/" << word.size() << " " << si << "/" << s.size() << endl;
            if(wi == word.size()){
                return word;
            }
        }
        
        return "";
    }
};

//Approach 4: Without Sorting
//Runtime: 92 ms, faster than 44.98% of C++ online submissions for Longest Word in Dictionary through Deleting.
//Memory Usage: 23 MB, less than 7.69% of C++ online submissions for Longest Word in Dictionary through Deleting.
//time: O(nx), space: O(x)
class Solution {
public:
    bool isSubsequence(string sub, string super){
        //check whether sub is a substring of super
        int i = 0, j = 0;
        while(i < sub.size() && j < super.size()){
            if(sub[i] == super[j]){
                i++;
                j++;
            }else{
                j++;
            }
        }
        return i == sub.size();
    };
    
    string findLongestWord(string s, vector<string>& d) {
        string ans = "";
        for(string& word : d){
            if(word.size() > ans.size() || 
               (word.size() == ans.size() && word < ans)){
                if(isSubsequence(word, s)){
                    ans = word;
                }
            }
        }
        return ans;
    }
};
