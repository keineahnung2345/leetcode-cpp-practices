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

/**
Approach #1: Left and Right Index [Accepted]
Intuition and Algorithm

An array that has degree d, must have some element x occur d times. If some subarray has the same degree, then some element x (that occured d times), still occurs d times. The shortest such subarray would be from the first occurrence of x until the last occurrence.

For each element in the given array, let's know left, the index of its first occurrence; and right, the index of its last occurrence. For example, with nums = [1,2,3,2,5] we have left[2] = 1 and right[2] = 3.

Then, for each element x that occurs the maximum number of times, right[x] - left[x] + 1 will be our candidate answer, and we'll take the minimum of those candidates.
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the length of nums. Every loop is through O(N)O(N) items with O(1)O(1) work inside the for-block.

Space Complexity: O(N)O(N), the space used by left, right, and count.
**/

//Runtime: 76 ms, faster than 14.18% of C++ online submissions for Degree of an Array.
//Memory Usage: 14.4 MB, less than 44.90% of C++ online submissions for Degree of an Array.
/**
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        map<int, int> left, right, count;
        int degree = 0;
        
        for(int i = 0; i < nums.size(); i++){
            int x = nums[i];
            if(left.find(x) == left.end()){
                left[x] = i;
            }
            right[x] = i;
            if(count.find(x) == count.end()){
                count[x] = 1;
            }else{
                count[x] += 1;
            }
            degree = max(degree, count[x]);
        }
        
        int ans = nums.size();
        
        for(map<int, int>::iterator it = count.begin(); it != count.end(); it++){
            int x = it->first;
            if(count[x] == degree){
                ans = min(ans, right[x] - left[x] + 1);
            }
        }
        
        return ans;
    }
};
**/
