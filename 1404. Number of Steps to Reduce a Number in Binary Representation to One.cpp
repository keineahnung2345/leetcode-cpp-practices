//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Steps to Reduce a Number in Binary Representation to One.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Number of Steps to Reduce a Number in Binary Representation to One.
class Solution {
public:
    int numSteps(string s) {
    //runtime error, string length too long!
//         int num = 0;
//         for(char c : s){
//             num = (num << 1) + (c - '0');
//         }
//         // cout << num << endl;
        
//         int ans = 0;
//         while(num != 1){
//             if(num % 2 == 1){
//                 num++;
//                 ans++;
//             }
            
//             while(num % 2 == 0){
//                 num >>= 1;
//                 ans++;
//             }
//         }
        
        int ans = 0;
        int i = s.size()-1;
        
        while(s != "1"){
            if(s[s.size()-1] == '1'){
                s[s.size()-1] = '0';
                //carry in
                int j = s.size()-1-1;
                while(j >= 0 && s[j] == '1'){
                    s[j] = '0';
                    j--;
                }
                if(j == -1){
                    s = '1' + s;
                }else{
                    s[j] = '1';
                }
                ans++;
            }
            
            // cout << "s: " << s << ", ans: " << ans << endl;
            
            while(s[s.size()-1] == '0'){
                s.erase(s.size()-1, 1);
                ans++;
            }
            
            // cout << "s: " << s << ", ans: " << ans << endl;
        }
        
        
        return ans;
    }
};
