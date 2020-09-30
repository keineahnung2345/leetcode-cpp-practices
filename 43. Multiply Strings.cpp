
//Runtime: 4 ms, faster than 98.76% of C++ online submissions for Multiply Strings.
//Memory Usage: 7 MB, less than 32.37% of C++ online submissions for Multiply Strings.
class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size(), n2 = num2.size();
        
        vector<int> res(n1+n2, 0);
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        for(int i = 0; i < n1; ++i){
            for(int j = 0; j < n2; ++j){
                res[i+j] += (num1[i]-'0') * (num2[j]-'0');
            }
        }
        
        int carry = 0;
        for(int i = 0; i < n1+n2; ++i){
            int sum = (carry + res[i]);
            res[i] = sum % 10;
            carry = sum / 10;
            // cout << res[i];
        }
        // cout << endl;
        
        string ans;
        
        int i = n1+n2-1;
        while(i >= 0 && res[i] == 0){
            --i;
        }
        // cout << i << endl;
        
        //res[0...i] is meaningful
        //ans is the reverse of res
        for(; i >= 0; --i){
            ans += (res[i]+'0');
        }
        
        if(ans == "") return "0";
        return ans;
    }
};
