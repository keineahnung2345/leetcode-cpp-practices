//Runtime: 1648 ms, faster than 16.67% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
//Memory Usage: 60.1 MB, less than 100.00% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        set<string> codes;
        
        for(int i = 0; i+k-1 < s.size(); i++){
            codes.insert(s.substr(i, k));
        }
        
        return codes.size() == pow(2, k);
    }
};

//sliding window + set
//https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/discuss/660632/Incorrect-problem-statement!!!
//Runtime: 1048 ms, faster than 30.69% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
//Memory Usage: 61.3 MB, less than 100.00% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        /*
        choose deque so that we can use .begin() and .end()
        */
        deque<char> q;
        /*
        set<string> gives us TLE!!!
        so use unordered_set here!
        */
        unordered_set<string> subset;
        for(char c : s){
            q.push_back(c);
            if(q.size() == k){
                // cout << string(q.begin(), q.end()) << endl;
                subset.insert({q.begin(), q.end()});
                q.pop_front();
            }
        }
        
        return subset.size() == (1 << k);
    }
};

//replace deque with string to speed up
//Runtime: 636 ms, faster than 61.41% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
//Memory Usage: 58.3 MB, less than 100.00% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        string window;
        unordered_set<string> subset;
        for(char c : s){
            window += c;
            if(window.size() == k){
                // cout << window << endl;
                subset.insert(window);
                /*
                string.erase(starting_pos, char_count)!
                need to set the second argument to 1 o.w.
                it will erase to the end!!
                */
                window.erase(0, 1);
            }
        }
        
        return subset.size() == (1 << k);
    }
};
