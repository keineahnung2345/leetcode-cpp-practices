//Runtime: 812 ms, faster than 20.00% of C++ online submissions for Check If a String Can Break Another String.
//Memory Usage: 11.6 MB, less than 100.00% of C++ online submissions for Check If a String Can Break Another String.
class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        int n = s1.size();
        
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        
        bool ab = true, ba = true;
        
        for(int i = 0; i < n; i++){
            if(s1[i] < s2[i]) ab = false;
            if(s2[i] < s1[i]) ba = false;
        }
        
        return ab || ba;
    }
};
