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

/**
Approach 2: Two Pointer
Intuition

As in Approach 1, we want to check the key and the count. We can do this on the fly.

Suppose we read through the characters name, and eventually it doesn't match typed.

There are some cases for when we are allowed to skip characters of typed. Let's use a tuple to denote the case (name, typed):

In a case like ('aab', 'aaaaab'), we can skip the 3rd, 4th, and 5th 'a' in typed because we have already processed an 'a' in this block.

In a case like ('a', 'b'), we can't skip the 1st 'b' in typed because we haven't processed anything in the current block yet.

Algorithm

This leads to the following algorithm:

For each character in name, if there's a mismatch with the next character in typed:
If it's the first character of the block in typed, the answer is False.
Else, discard all similar characers of typed coming up. The next (different) character coming must match.
Also, we'll keep track on the side of whether we are at the first character of the block.
**/

/**

Complexity Analysis

Time Complexity: O(N+T)O(N+T), where N, TN,T are the lengths of name and typed.

Space Complexity: O(1)O(1) in additional space complexity. (In Java, .toCharArray makes this O(N)O(N), but this can be easily remedied.) 
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Long Pressed Name.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Long Pressed Name.

/**
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int j = 0;
        for(char c : name){
            //run through typed, but still visiting name
            if(j == typed.size()) return false;
            
            if(typed[j] != c){
                //0th char must match
                //or not equal to the last char
                if(j == 0 || typed[j] != typed[j-1]) return false;
                
                char cur = typed[j];
                //ignore all redundant chars
                while(j < typed.size() && typed[j] == cur) j++;
                
                //typed[j] is the char just behind all redundant chars
                //if j is invalid, return false
                //or if typed[j] is not equal to c, return false
                if(j == typed.size() || typed[j] != c) return false;
            }
            
            //go to next char
            j++;
        }
        
        return true;
    }
};
**/
