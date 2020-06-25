//Approach #1 Sorting
//time: O(nlogn), space: O(1) for in-place, O(n) o.w.

//Approach #2 Set
//time: O(n), space: O(n)

//Approach #3 Floyd's Tortoise and Hare (Cycle Detection)
//Runtime: 12 ms, faster than 69.11% of C++ online submissions for Find the Duplicate Number.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Find the Duplicate Number.
//time: O(n), space: O(1)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[0];
        
        //phase 1: find the meeting point of Tortoise and Hare
        //move slow and fast until they meet
        do{
            // cout << slow << " " << fast << endl;
            //move one step
            slow = nums[slow];
            //move two steps
            fast = nums[nums[fast]];
        }while(slow != fast);
        // cout << "phase 1 ends: " << endl;
        // cout << slow << " " << fast << endl;
        
        /*
        phase 2:
        tortoise starts from nums[0],
        and now hare's speed is same as tortoise and
        starts from the meeting point
        */
        slow = nums[0];
        while(slow != fast){
            // cout << slow << " " << fast << endl;
            //move one step at a time
            slow = nums[slow];
            fast = nums[fast];
        }
        // cout << "phase 2 ends: " << endl;
        // cout << slow << " " << fast << endl;
        
        //they will meet at the beginning of the cycle
        return slow;
    }
};
