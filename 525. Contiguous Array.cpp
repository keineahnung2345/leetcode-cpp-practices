//Approach #1 Brute Force
//TLE
//32 / 555 test cases passed.
//time: O(N^2), space: O(1)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int ans = 0;
        
        for(int start = 0; start < nums.size(); start++){
            int zeros = 0, ones = 0;
            for(int end = start; end < nums.size(); end++){
                if(nums[end] == 0){
                    zeros++;
                }else{
                    ones++;
                }
                if(zeros == ones){
                    ans = max(ans, end-start+1);
                }
            }
        }
        
        return ans;
    }
};

//Approach #2 Using Extra Array [Accepted]
//Runtime: 96 ms, faster than 90.38% of C++ online submissions for Contiguous Array.
//Memory Usage: 20 MB, less than 41.67% of C++ online submissions for Contiguous Array.
//time: O(N), space: O(N)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        /*
        key: count, ranges from -n to n
        (shifted n to the right, so count = -n takes the index 0)
        value: the end index of previous subarray whose count is the key
        */
        vector<int> arr(2*nums.size()+1, -2);
        
        /*
        the start of subarray with count equaling to 0 starts from index 0,
        this is equivalent to saying a previous subarray with count 0 ends at index -1
        */
        arr[nums.size()] = -1; //arr[nums.size()] corresponds to count = 0
        int ans = 0, count = 0;
        
        for(int i = 0; i < nums.size(); i++){
            count += (nums[i] == 0 ? -1 : 1);
            //the index "count + nums.size()" corresponds to count = "count"
            if(arr[count + nums.size()] >= -1){
                /*
                the initial value in "arr" is -2, 
                so if its value >= -1, the value is meaningful
                
                when count is 0, we will enter this part automatically,
                e.g. [0, 0, 1, 1], when "i" is 3, 
                i-arr[count+nums.size()] will be 4,
                that means we can find a continuous array from the start of nums
                
                i is the ending index of current subarray with specific count,
                arr[count+nums.size()] is previous subarray with the same count
                i-arr[count+nums.size()] is then the length of subarray with count equaling to 0 
                */
                ans = max(ans, i-arr[count+nums.size()]);
            }else{
                /*
                the value in current index is meaningless,
                so we update it
                
                subarray of "count" ends at i
                next time when we meet subarray with the same count,
                we can calculate the length of that subarray by 
                subtracting arr[count+nums.size()] from index at that time 
                */
                arr[count+nums.size()] = i;
            }
        }
        
        return ans;
    }
};

//Approach #3 Using HashMap [Accepted]
//Runtime: 180 ms, faster than 46.37% of C++ online submissions for Contiguous Array.
//Memory Usage: 17.7 MB, less than 100.00% of C++ online submissions for Contiguous Array.
//time: O(N), space: O(N)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        //count can range from -n to n
        unordered_map<int, int> count2index;
        count2index[0] = -1;
        
        int ans = 0, count = 0;
        
        for(int i = 0; i < nums.size(); i++){
            count += (nums[i] == 0 ? -1 : 1);
            if(count2index.find(count) != count2index.end()){
                // cout << i << ": " << count << " -> len: " << i-count2index[count] << endl;
                /*
                the interval [0, count2index[count]] has count2index[count] more 1 than 0,
                and so does  the interval [0, i], 
                so the interval [count2index[count]+1, i] has equal 0s and  1s
                */
                ans = max(ans, i-count2index[count]);
            }else{
                // cout << i << ": " << count << " -> ix: " << i << endl;
                count2index[count] = i;
            }
        }
        
        return ans;
    }
};
