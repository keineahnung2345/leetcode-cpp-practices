//Greedy + recursion
//https://leetcode.com/problems/remove-duplicate-letters/discuss/76768/A-short-O(n)-recursive-greedy-solution
//Runtime: 16 ms, faster than 17.06% of C++ online submissions for Remove Duplicate Letters.
//Memory Usage: 8.8 MB, less than 5.05% of C++ online submissions for Remove Duplicate Letters.
class Solution {
public:
    string removeDuplicateLetters(string s) {
        int n = s.size();
        
        if(n == 0)
            return "";
        
        vector<int> counter(26, 0);
        
        for(char& c : s){
            ++counter[c-'a'];
        }
        
        int start = 0;
        for(int i = 0; i < n; ++i){
            if(s[i] < s[start]){
                start = i;
            }
            --counter[s[i]-'a'];
            //there are counter[s[i]-'a'] s[i] in s[i+1...]
            if(counter[s[i]-'a'] == 0){
                //skip those index s.t. s[i] is missing
                break;
            }
        }
        
        string nexts = s.substr(start+1);
        auto it = remove(nexts.begin(), nexts.end(), s[start]);
        nexts = std::string(nexts.begin(), it);
        // cout << "remove " << s[start] << ", next: " << nexts << endl;
        return s[start]+removeDuplicateLetters(nexts);
    }
};

//Greedy + stack
//https://leetcode.com/problems/remove-duplicate-letters/discuss/76769/Java-solution-using-Stack-with-comments
//Runtime: 4 ms, faster than 95.18% of C++ online submissions for Remove Duplicate Letters.
//Memory Usage: 6.7 MB, less than 59.72% of C++ online submissions for Remove Duplicate Letters.
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> counter(26, 0);
        
        //the stack stores the char used to construct the answer
        stack<char> stk;
        //a look up table for the stack, used to check whether a char is added into the stack
        vector<bool> visited(26, false);
        
        int n = s.size();
        
        for(int i = 0; i < n; ++i){
            ++counter[s[i]-'a'];
        }
        
        for(char& c : s){
            --counter[c-'a'];
            
            //skip duplicate char
            if(visited[c-'a'])
                continue;
            
            /*
            current char is smaller,
            after ensuring that there are more "stk.top()" after current char,
            we can safely remove it from stack
            (the char "stk.top()" will later be added again)
            */
            
            /*
            for large char, after it is pushed into stack, 
            it will be popped again, 
            so it will be put as later as possible
            */
            while(!stk.empty() && c < stk.top() && counter[stk.top()-'a'] > 0){
                char topc = stk.top();
                stk.pop();
                visited[topc-'a'] = false;
            }
            
            /*
            for small char, after it is pushed into stack, 
            it won't be popped again, 
            so it can be put at former place in the final string
            */
            stk.push(c);
            visited[c-'a'] = true;
        }
        
        string ans;
        
        while(!stk.empty()){
            ans = stk.top() + ans;
            stk.pop();
        }
        
        return ans;
    }
};
