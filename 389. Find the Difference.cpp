//Runtime: 4 ms, faster than 96.78% of C++ online submissions for Find the Difference.
//Memory Usage: 6.7 MB, less than 52.00% of C++ online submissions for Find the Difference.
class Solution {
public:
    char findTheDifference(string s, string t) {
        vector<int> counter(26, 0);
        
        for(char c : t){
            ++counter[c-'a'];
        }
        
        for(char c : s){
            --counter[c-'a'];
        }
        
        return 'a' + find(counter.begin(), counter.end(), 1)-counter.begin();
    }
};
