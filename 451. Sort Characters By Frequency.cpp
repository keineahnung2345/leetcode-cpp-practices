//Runtime: 592 ms, faster than 5.01% of C++ online submissions for Sort Characters By Frequency.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Sort Characters By Frequency.
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> counter;
        
        for(char c : s){
            counter[c]++;
        }
        
        sort(s.begin(), s.end(), 
            [&counter](const char a, const char b){
                return (counter[a] == counter[b]) ? a < b : counter[a] > counter[b];
            });
        
        return s;
    }
};
