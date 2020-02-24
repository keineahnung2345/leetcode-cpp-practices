//https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/discuss/328841/JavaC%2B%2BPython-O(1)-Extra-Space-Except-Output
//sol 1
//Runtime: 20 ms, faster than 96.89% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.
//Memory Usage: 9.4 MB, less than 100.00% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int Adepth = 0, Bdepth = 0;
        vector<int> ans(seq.size(), 0);
        for(int i = 0; i < seq.size(); i++){
            if(seq[i] == '('){
                //here the condition is Adepth <= Bdepth
                if(Adepth <= Bdepth){
                    Adepth++;
                    ans[i] = 0;
                }else{
                    Bdepth++;
                    ans[i] = 1;
                }
            }else{
                //here the condition is Adepth > Bdepth
                //(the opposite of Adepth <= Bdepth)
                if(Adepth > Bdepth){
                    Adepth--;
                    ans[i] = 0;
                }else{
                    Bdepth--;
                    ans[i] = 1;
                }
            }
        }
        return ans;
    }
};

//sol2
//Runtime: 20 ms, faster than 96.89% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int depth = 0, cur = 0;
        vector<int> ans(seq.size());
        
        for(char c : seq){
            if(c == '('){
                cur++;
                depth = max(depth, cur);
            }else{
                cur--;
            }
        }
        
        for(int i = 0; i < seq.size(); i++){
            if(seq[i] == '(' && ++cur > depth/2) ans[i] = 1;
            else if(seq[i] == ')' && cur-- > depth/2) ans[i] = 1;
        }
        
        return ans;
    }
};

//sol 0, by parity
//Runtime: 20 ms, faster than 96.89% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Maximum Nesting Depth of Two Valid Parentheses Strings.

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans(seq.size(), 0);
        for(int i = 0; i < seq.size(); i++){
            if(seq[i] == '('){
                ans[i] = i&1;
            }else{
                ans[i] = 1 - i&1;
            }
        }
        
        return ans;
    }
};
