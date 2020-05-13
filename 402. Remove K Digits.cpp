//stack, greedy
//https://leetcode.com/problems/remove-k-digits/discuss/88708/Straightforward-Java-Solution-Using-Stack
//Runtime: 8 ms, faster than 62.37% of C++ online submissions for Remove K Digits.
//Memory Usage: 7.1 MB, less than 100.00% of C++ online submissions for Remove K Digits.
class Solution {
public:
    string removeKdigits(string num, int k) {
        if(k >= num.size()) return "0";
        
        stack<int> stk;
        
        for(int i = 0; i < num.size(); i++){
            //k > 0: only discard char when k> 0
            //it's "while", not "if" here!!
            //it's ">", not ">=" here!!
            while(k > 0 && !stk.empty() && stk.top() > num[i]){
                stk.pop(); //discard the larger and the former char
                k--;
            }
            
            stk.push(num[i]);
        }
        
        while(k-- > 0){
            stk.pop();
        }
        
        string ans = "";
        
        while(!stk.empty()){
            //56ms
            // ans = string(1, stk.top()) + ans;
            //8ms!!
            ans += stk.top();
            stk.pop();
        }
        
        //8ms!!
        std::reverse(ans.begin(), ans.end());
        
        //remove leading 0
        while(ans.size() > 1 && ans[0] == '0'){
            ans.erase(0, 1);
        }
        
        return ans;
    }
};
