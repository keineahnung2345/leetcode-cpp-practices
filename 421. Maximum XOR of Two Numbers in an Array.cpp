//TLE
//28 / 29 test cases passed.
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        for(int i = 0; i < nums.size()-1; i++){
            for(int j = i+1; j < nums.size(); j++){
                ans = max(ans, nums[i]^nums[j]);
            }
        }
        return ans;
    }
};

//https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap
//Runtime: 344 ms, faster than 5.11% of C++ online submissions for Maximum XOR of Two Numbers in an Array.
//Memory Usage: 38 MB, less than 80.00% of C++ online submissions for Maximum XOR of Two Numbers in an Array.
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int ans = 0;
        int mask = 0;
        
        for(int i = 31; i >= 0; i--){
            //100..00(it has 31 0s ), 1100..00, ..., 1..10(31 1s), 1..1(32 1s)
            mask |= (1 << i);
            
            set<int> leftPartOfNums;
            
            for(int num : nums){
                leftPartOfNums.insert(num & mask);
            }
            
            //if ans is 1100, and i is 1 now, we wish we can make ans 1110
            int greedyTry = ans | (1 << i);
            
//             if(i <= 5){
//                 cout << "mask: " << endl;
//                 cout << bitset<32>(mask).to_string() << endl;

//                 cout << "greedyTry: " << endl;
//                 cout << bitset<32>(greedyTry).to_string() << endl;
//             }
            
            for(int leftPartOfNum : leftPartOfNums){
                /*
                we wish there is a "anotherNum" s.t.
                leftPartOfNum ^ anotherNum = greedyTry, 
                we can calculate anotherNum by leftPartOfNum ^ greedyTry,
                then we need to check if it exists in the set
                */
                int anotherNum = leftPartOfNum ^ greedyTry;
            
                // if(i <= 5){
                //     cout << "anotherNum: " << endl;
                //     cout << bitset<32>(anotherNum).to_string() << endl;
                // }
                
                if(leftPartOfNums.find(anotherNum) != leftPartOfNums.end()){
                    /*
                    we can find a anotherNum s.t. 
                    leftPartOfNum ^ anotherNum = 
                    leftPartOfNum ^ leftPartOfNum ^ greedyTry = 
                    greedyTry
                    */
                    ans = greedyTry;
                    break;
                }
            }
            
        }
        return ans;
    }
};
