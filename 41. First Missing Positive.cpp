//sorting
//Runtime: 4 ms, faster than 83.82% of C++ online submissions for First Missing Positive.
//Memory Usage: 10.1 MB, less than 8.45% of C++ online submissions for First Missing Positive.
//time: O(NlogN), space: O(N)
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        set<int> unums;
        
        for(int& num : nums){
            if(num > 0){
                unums.insert(num);
            }
        }
        
        if(unums.size() == 0){
            return 1;
        }
        
        vector<int> vnums(unums.begin(), unums.end());
        
        sort(vnums.begin(), vnums.end());
        
        if(vnums[0] > 1){
            return 1;
        }
        
        for(int i = 0; i < vnums.size(); ++i){
            if(vnums[i] != i+1){
                return i+1;
            }
        }
        
        return vnums.size()+1;
    }
};

//swap element to its right place
//https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c%2B%2B-solution-O(1)-space-and-O(n)-time
//Runtime: 4 ms, faster than 83.82% of C++ online submissions for First Missing Positive.
//Memory Usage: 9.8 MB, less than 63.74% of C++ online submissions for First Missing Positive.
//time: O(N), because in each iteration of while loop, we put one element into its right position, 
//and after an element is in its right position, we won't do anything with it,
//and there are N elements, so the time complexity is O(N)
//space: O(1)
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        /*
        if nums is [1,n], 
        then the first missing positive number is n+1,
        otherwise there's some number in [`,n] missing in nums,
        so the first missing positive number is in [1,n].
        To summary, first missing positive number's range
        should be in 1 to n+1.
        */
        for(int i = 0; i < n; ++i){
            /*
            swap every number in [1,n] to its correct position
            for example, if we find a 5,
            we should put it into position 4
            
            nums[i] should be put in the 'nums[i]-1'th position
            */
            /*
            it's "while", not "if"!!!
            that is because we also want to put 
            the swapped element in the right place
            for the testcase [-1,4,3,1],
            it will become [-1,1,3,4] -> [1,-1,3,4]
            */
            while(nums[i] >= 1 && nums[i] <= n && nums[i] != nums[nums[i]-1]){
                swap(nums[i], nums[nums[i]-1]);
                // for(int num : nums){
                //     cout << num << " ";
                // }
                // cout << endl;
            }
        }
        
        for(int i = 0; i < n; ++i){
            /*
            the number i+1 is not in its correct position,
            so it must be missing
            */
            if(nums[i] != i+1){
                return i+1;
            }
        }
        
        return n+1;
    }
};
