/**
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
**/

//Runtime: 288 ms, faster than 5.17% of C++ online submissions for Degree of an Array.
//Memory Usage: 13 MB, less than 92.86% of C++ online submissions for Degree of an Array.

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        map<int, int> count;
        
        for(int num : nums){
            if(count.find(num) == count.end()){
                count[num] = 1;
            }else{
                count[num] += 1;
            }
        }
        
        int maxfreq, maxele;
        vector<int> candidates;
        
        map<int, int>::iterator it = max_element(count.begin(), count.end(), [] (const pair<int, int> & p1, const pair<int, int> & p2) {return p1.second < p2.second;});
        maxfreq = it->second;
        
        for(map<int, int>::iterator it = count.begin(); it!=count.end(); it++){
            if(it->second == maxfreq){
                candidates.push_back(it->first);
            }
        }
        
        int ans = INT_MAX;
        for(int candidate : candidates){
            vector<int> tofind = {candidate};
            int substart = find(nums.begin(), nums.end(), candidate) - nums.begin();
            int subend = find_end(nums.begin(), nums.end(), tofind.begin(), tofind.end()) - nums.begin();
            cout << maxele << " " << substart << " " << subend << endl;
            ans = min(ans, subend - substart + 1);
        }
        return ans;
    }
};
