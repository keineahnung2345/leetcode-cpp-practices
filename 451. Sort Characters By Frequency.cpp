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

//bucket sort, O(n) time
//Runtime: 64 ms, faster than 19.59% of C++ online submissions for Sort Characters By Frequency.
//Memory Usage: 16.5 MB, less than 17.65% of C++ online submissions for Sort Characters By Frequency.
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> counter;
        
        for(char c : s){
            counter[c]++;
        }
        
        /*
        reserve the space
        the count of a char(or chars) -> string formed by chars of this count
        */
        vector<string> buckets(s.size()+1);
        
        for(auto it = counter.begin(); it != counter.end(); it++){
            buckets[it->second] += string(it->second, it->first);
        }
        
        string ans;
        
        //iterate from larger count
        for(int i = buckets.size()-1; i >= 0; i--){
            if(buckets[i] != ""){
                ans += buckets[i];
            }
        }
        
        return ans;
    }
};

//bucket sort, space optimized
//Runtime: 44 ms, faster than 33.25% of C++ online submissions for Sort Characters By Frequency.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Sort Characters By Frequency.
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> counter;
        
        for(char c : s){
            counter[c]++;
        }
        
        /*
        reserve the space
        the count of a char(or chars) -> string formed by chars of this count
        */
        map<int, string> buckets;
        
        for(auto it = counter.begin(); it != counter.end(); it++){
            buckets[it->second] += string(it->second, it->first);
        }
        
        string ans;
        
        //iterate from larger count
        for(auto it = buckets.rbegin(); it != buckets.rend(); it++){
            ans += it->second;
        }
        
        return ans;
    }
};
