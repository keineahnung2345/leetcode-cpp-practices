//TLE
//22 / 24 test cases passed.
class Solution {
public:
    string lastSubstring(string s) {
        int maxIdx = 0;
        char maxC = '\0';
        for(int i = 0; i < s.size(); i++){
            if(s[i] > maxC){
                maxIdx = i;
                maxC = s[i];
            }
        }
        
        vector<string> candidates;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == maxC){
                candidates.push_back(s.substr(i));
            }
        }
        
        // cout << candidates.size() << endl;
        
        // sort(candidates.begin(), candidates.end(),
        //            [](const string& a, const string& b){
        //                return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
        //            });
        
        nth_element(candidates.begin(), candidates.begin()+candidates.size()-1, candidates.end(),
                   [](const string& a, const string& b){
                       return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
                   });
        
        return candidates[candidates.size()-1];
    }
};

//https://leetcode.com/problems/last-substring-in-lexicographical-order/discuss/363662/Short-python-code-O(n)-time-and-O(1)-space-with-proof-and-visualization
//Runtime: 104 ms, faster than 77.02% of C++ online submissions for Last Substring in Lexicographical Order.
//Memory Usage: 14.4 MB, less than 34.68% of C++ online submissions for Last Substring in Lexicographical Order.
class Solution {
public:
    string lastSubstring(string s) {
        int i = 0; //the start index of final substr
        int j = i+1; //the start index of the substr for comparison
        int k = 0; //k = the length of final substr - 1
        int n = s.size();
        
        while(j + k < n){
            // cout << s.substr(i, k+1) << " " << s.substr(j, k+1) << endl;
            if(s[i+k] == s[j+k]){
                ++k;
            }else if(s[i+k] < s[j+k]){
                /*
                all char in s[i+1...j-1] are smaller than s[j],
                so we can safely skip them
                */
                i = j;
                ++j;
                k = 0;
            }else{
                //s[i+k] > s[j+k]
                /*
                because s[j...j+k] must be <= s[i],
                (otherwise i will be updated by j),
                so we can start from j+k+1
                */
                j = j+k+1;
                k = 0;
            }
        }
        
        return s.substr(i);
    }
};
