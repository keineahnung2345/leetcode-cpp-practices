//Time Limit Exceeded
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int count = 0, n = nums.size();
        vector<int> ones(n, 0);
        
        int cur_max = *max_element(nums.begin(), nums.end());
        
        while(adjacent_find(nums.begin(), nums.end(), not_equal_to<>()) != nums.end()){
            sort(nums.begin(), nums.end());
            // std::copy(nums.begin(), nums.end(),
            //     std::ostream_iterator<int>(std::cout, " "));
            // std::cout << std::endl;
            
            // int second_largest = nums[n-1];
            // for(int i = n-2; i >= 0; i--){
            //     if(second_largest != nums[i]){
            //         second_largest = nums[i];
            //         break;
            //     }
            // }

            // int diff = nums[n-1] - second_largest;
            long diff = nums[n-1] - nums[0];
            // long diff = *max_element(nums.begin(), nums.end())  - *min_element(nums.begin(), nums.end());
            fill(ones.begin(), ones.end()-1, diff);
            transform(nums.begin(), nums.end(), 
                     ones.begin(), nums.begin(),
                     plus<long>());
            count += diff;
        }
        
        return count;
    }
};
