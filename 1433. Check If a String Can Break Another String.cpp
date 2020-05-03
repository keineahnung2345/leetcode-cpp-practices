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

//O(n) solution, using map, from definition of "break"
//https://leetcode.com/problems/check-if-a-string-can-break-another-string/discuss/608668/Python-O(n).
//Runtime: 84 ms, faster than 100.00% of C++ online submissions for Check If a String Can Break Another String.
//Memory Usage: 11.8 MB, less than 100.00% of C++ online submissions for Check If a String Can Break Another String.
class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        int n = s1.size();
        vector<int> counter1(26, 0), counter2(26, 0);
        for(int i = 0; i < n; i++){
            counter1[s1[i]-'a']++;
            counter2[s2[i]-'a']++;
        }
        
        int diff1 = 0, diff2 = 0;
        bool break1 = true, break2 = true;
        for(int i = 0; i < 26; i++){
            diff1 += counter1[i] - counter2[i];
            diff2 += counter2[i] - counter1[i];
            if(diff1 < 0) break1 = false;
            if(diff2 < 0) break2 = false;
        }
        
        return break1 || break2;
    }
};
