//TLE
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        for(int i = 0; i < nums.size(); i++){
            for(int j=i+1; (j <=i+k) && (j < nums.size()); j++){
                // cout << "i: " << i << "j: " << j << endl;
                if(nums[i] == nums[j]) return true;
            }
        }
        // cout << endl;
        return false;
    }
};

//Runtime: 1648 ms, faster than 5.45% of C++ online submissions for Contains Duplicate II.
//Memory Usage: 10.1 MB, less than 100.00% of C++ online submissions for Contains Duplicate II.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        for(int i = 0; i+1 < nums.size(); i++){
            // cout << "[" << i+1 << ", " << i+k << "]" << endl;
            int finish = min((int)nums.size(), i+k+1);
            if(find(nums.begin()+i+1, nums.begin()+finish, nums[i])
              != nums.begin()+finish){
                // cout << endl;
                return true;
            }
        }
        // cout << endl;
        return false;
    }
};

//https://leetcode.com/problems/contains-duplicate-ii/discuss/61372/Simple-Java-solution
//Sliding window
//Runtime: 40 ms, faster than 34.36% of C++ online submissions for Contains Duplicate II.
//Memory Usage: 14.8 MB, less than 82.35% of C++ online submissions for Contains Duplicate II.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        set<int> myset;
        for(int i = 0; i < nums.size(); i++){
            //window : [i-k, i]
            //so (i-k-1)th goes out of the window, need to remove it
            if(i-k-1 >= 0) myset.erase(nums[i-k-1]);
            /*
            The single element versions (1) return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set. The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
            */
            if(!myset.insert(nums[i]).second) return true;
        }
        return false;
    }
};
