//Greedy
//Runtime: 256 ms, faster than 40.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
//Memory Usage: 25.7 MB, less than 20.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        
        while(any_of(nums.begin(), nums.end(), [](const int& e){return e >= 2;})){
            for(int& num : nums){
                if(num&1){
                    ++ans;
                    --num;
                }
            }
            
            transform(nums.begin(), nums.end(), nums.begin(), [](int& x){return x>>1;});
            ++ans;
        }
        
        ans += accumulate(nums.begin(), nums.end(), 0);
        
        return ans;
    }
};

//Bit counts, greedy
//https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/discuss/805740/JavaC%2B%2BPython-Bit-Counts
//Runtime: 180 ms, faster than 40.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
//Memory Usage: 25.4 MB, less than 100.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int maxbits = 0;
        int op1 = 0; //the count of operation 1(add by 1)
        
        for(int& num : nums){
            int bits = 0;
            
            // cout << num << " ";
            
            while(num){
                ++bits;
                maxbits = max(maxbits, bits);
                op1 += num&1;
                num >>= 1;
            }
            
            // cout << bits << " " << op1 << endl;
        }
        
        /*
        operation 2(multiply by 2) is shared,
        the count of operation 2 needed is the 
        max length of nums's numbers' bit representation-1
        
        for example, 5 is 101:
        101 -> 100 -> 10 -> 1 -> 0
        and we need 2 operation two
        */
        return op1 + maxbits-1;
    }
};
