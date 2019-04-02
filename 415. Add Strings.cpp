//Runtime: 8 ms, faster than 96.87% of C++ online submissions for Add Strings.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Add Strings.

class Solution {
public:
    string addStrings(string num1, string num2) {
        int N = max(num1.size(), num2.size());
        string ans;
        int carry = 0;
        int d1, d2;
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        for(int i = 0; i < N; i++){
            if(i < num1.size())d1 = num1[i]-'0';
            else d1 = 0;
            if(i < num2.size())d2 = num2[i]-'0';
            else d2 = 0;
            ans += ((d1+d2+carry)%10 + '0');
            carry = (d1+d2+carry)/10;
        }
        if(carry > 0 )ans += (carry + '0');
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
