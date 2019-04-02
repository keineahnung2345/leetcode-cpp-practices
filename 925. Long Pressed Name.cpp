//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Long Pressed Name.
//Memory Usage: 8.4 MB, less than 98.25% of C++ online submissions for Long Pressed Name.

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int cur = 0;
        char last = typed[0];
        
        for(char c : name){
            char typedc = typed[cur++];
            //ignore the redundant char
            while(typedc != c && typedc == last){
                typedc = typed[cur++];
            }
            // cout << c << " " << typedc << " " << last << endl;
            //if(typedc != c && typedc != last), then it must be wrong
            if(typedc != c && typedc != last) return false;
            //if(typedc == c), it matches
            last = typedc;
        }
        return true;
    }
};

/**
Approach 1: Group into Blocks
**/

/**
Complexity Analysis

Time Complexity: O(N+T)O(N+T), where N, TN,T are the lengths of name and typed.

Space Complexity: O(N+T)O(N+T). 
**/

/**
class Group{
public:
    string key;
    vector<int> count;
    Group(string k, vector<int> c){
        key = k;
        count = c;
    }
};

class Solution {
public:
    Group groupify(string s){
        string key;
        vector<int> count;
        int anchor = 0;
        int N = s.size();
        for(int i = 0; i < N; i++){
            if(i == N-1 || s[i] != s[i+1]){
                key += s[i];
                count.push_back(i - anchor + 1);
                anchor = i+1;
            }
        }
        return Group(key, count);
    }
    bool isLongPressedName(string name, string typed) {
        Group g1 = groupify(name);
        Group g2 = groupify(typed);
        if(g1.key != g2.key) return false;
        
        for(int i = 0; i < g1.count.size(); i++){
            if(g2.count[i] < g1.count[i]) return false;
        }
        return true;
    }
};
**/

