//Runtime: 4 ms, faster than 98.48% of C++ online submissions for Fizz Buzz.
//Memory Usage: 7.4 MB, less than 87.67% of C++ online submissions for Fizz Buzz.
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans(n);

        for(int i = 0; i < n; ++i){
            if((i+1)%15 == 0){
                ans[i] = "FizzBuzz";
            }else if((i+1)%3 == 0){
                ans[i] = "Fizz";
            }else if((i+1)%5 == 0){
                ans[i] = "Buzz";
            }else{
                ans[i] = to_string(i+1);
            }
        }

        return ans;
    }
};
