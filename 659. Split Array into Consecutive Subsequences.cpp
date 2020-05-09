//binary search
//Runtime: 320 ms, faster than 15.61% of C++ online submissions for Split Array into Consecutive Subsequences.
//Memory Usage: 54.4 MB, less than 20.00% of C++ online submissions for Split Array into Consecutive Subsequences.
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        vector<int> tails; //should be sorted in ascending order
        vector<int>::iterator it;
        
        while(!nums.empty()){
            int head = nums[0];
            //find the "last"(acheived by prev(upper_bound(...))) head-1 in tails, 
            if(tails.size() == 0 || (it = upper_bound(tails.begin(), tails.end(), head-1)) == tails.begin() || (*(it = prev(it)) != head-1)){
                // cout << "cannot find " << head-1 << " in tails? " << (it == tails.begin()) << endl;
                //if head-1 not in tails
                nums.erase(nums.begin());
                it = find(nums.begin(), nums.end(), head+1);
                if(it == nums.end()) return false;
                nums.erase(it);
                it = find(nums.begin(), nums.end(), head+2);
                if(it == nums.end()) return false;
                nums.erase(it);
                //need a new subsequence
                tails.push_back(head+2);
                // cout << "nums.size(): " << nums.size() << endl;
            }else{
                // cout << "cannot find " << head-1 << " in tails? " << (it == tails.begin()) << endl;
                //append to a old subsequence
                /*
                note that since "it" points to the last "head-1" in tails, 
                so tails can be kept "ascending"
                */
                *it = head;
                it = find(nums.begin(), nums.end(), head);
                if(it == nums.end()) return false;
                nums.erase(it);
            }
            
//             for(int num : nums){
//                 cout << num << " ";
//             }
//             cout << endl;
            
//             for(int tail : tails){
//                 cout << tail << " ";
//             }
//             cout << endl;
         }
                     
        return true;
    }
};
