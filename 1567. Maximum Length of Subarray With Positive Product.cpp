//Runtime: 252 ms, faster than 40.00% of C++ online submissions for Maximum Length of Subarray With Positive Product.
//Memory Usage: 58.7 MB, less than 20.00% of C++ online submissions for Maximum Length of Subarray With Positive Product.
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        int neg = 0;
        int len = 0;
        int ans = 0;
        vector<int> negs;
        
        int i = 0;
        while(i < n){
            int j;
            for(j = i; j < n && nums[j] != 0; ++j){
                if(nums[j] < 0){
                    negs.push_back(j);
                }
            }
            
            // cout << "negs: " << negs.size() << endl;
            
            if(negs.size() % 2 == 0){
                len = j-i;
            }else if(negs.size() == 1){
                // cout << negs[0]-i << " or " << j-1-(negs[0]+1)+1 << endl;
                len = max(negs[0]-i, j-1-(negs[0]+1)+1);
            }else{
                int first = negs[0], last = negs.back();
                // cout << last-i << " or " << j-1-(first+1)+1 << endl;
                len = max(last-i, j-1-(first+1)+1);
            }
            
            ans = max(ans, len);
            negs.clear();
            
            i = j+1;
        }
        
        ans = max(ans, len);
        
        return ans;
    }
};
