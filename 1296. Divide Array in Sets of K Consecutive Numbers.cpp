//TLE
//36 / 39 test cases passed.
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int N = nums.size();
        if(N % k != 0) return false;
        int times = N/k;
        
        sort(nums.begin(), nums.end());
        
        while(times-- > 0){
            int smallest = nums[0];
            for(int i = smallest; i < smallest + k; i++){
                auto it = find(nums.begin(), nums.end(), i);
                if(it != nums.end()){
                    nums.erase(it);
                }else{
                    return false;
                }
            }
        }
        
        return true;
    }
};

//sort each partition
//TLE
//36 / 39 test cases passed.
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int N = nums.size();
        if(N % k != 0) return false;
        int times = N/k;
        int cursor = 0;
        
        sort(nums.begin(), nums.end());
        
        // for(int num : nums){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        while(times-- > 0){
            //sort each part division before
            sort(nums.begin()+cursor, nums.end());
            // for(auto it = nums.begin()+cursor; it != nums.begin()+cursor+k; it++){
            //     cout << *it << " ";
            // }
            // cout << endl;
            int smallest = nums[cursor];
            for(int i = smallest; i < smallest + k; i++){
                // cout << i << endl;
                if(nums[cursor] != i){
                    auto it = find(nums.begin()+cursor, nums.end(), i);
                    if(it == nums.end()) return false;
                    // cout << "finding " << i << ", swap " << cursor << " and " << it-nums.begin() << endl;
                    swap(nums[it-nums.begin()], nums[cursor]);
                }
                cursor++;
            }
        }
        
        return true;
    }
};
