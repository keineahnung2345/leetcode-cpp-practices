//Runtime: 44 ms, faster than 5.97% of C++ online submissions for Remove Outermost Parentheses.
//Memory Usage: 8.9 MB, less than 95.00% of C++ online submissions for Remove Outermost Parentheses.

class Solution {
public:
    string removeOuterParentheses(string S) {
        int left = -1, right = -1;
        int balance = 0;
        int i = 0;
        while(i < S.size()){
            if(S[i] == '('){
                if(left == -1) left = i;
                balance++;
            }else if(S[i] == ')'){
                balance--;
            }
            // cout << i << " " <<  S << " " <<  left << " " << right << " " << balance << endl;
            if(balance == 0){
                right = i;
                // cout << i << " " <<  S << " " << left << " " << right << " " << balance << endl;
                //remember to erase the latter character first!
                //first erase right and then left!
                S.erase(S.begin() + right);
                S.erase(S.begin() + left);
                left = -1;
                right = -1;
                //-2 for the erased '(' and ')'
                //+1 for go next
                i = i - 2 + 1;
            }else{
                i++;
            }
        }
        return S;
    }
};
