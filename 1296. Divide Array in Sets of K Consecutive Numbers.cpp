//erase while iterating
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

//not erasing, sort each partition while iterating
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

//optimized by using map(map is ordered by key)
//Runtime: 440 ms, faster than 5.11% of C++ online submissions for Divide Array in Sets of K Consecutive Numbers.
//Memory Usage: 27.9 MB, less than 100.00% of C++ online submissions for Divide Array in Sets of K Consecutive Numbers.
//time: O(NlogN), map is sorted and each lookup takes O(logN)
//space: O(N)
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int N = nums.size();
        if(N % k != 0) return false;
        int times = N/k;
        map<int, int> counter;
        map<int, int>::iterator it;
        
        for(int num : nums){
            counter[num]++;
        }
        
        while(times > 0){
            it = counter.begin();
            int smallest = it->first;
            int freq = it->second;
            for(int i = smallest; i < smallest + k; i++){
                if(counter.find(i) != counter.end() && counter[i] >= freq){
                    counter[i]-=freq;
                    if(counter[i] == 0) counter.erase(i);
                }else{
                    return false;
                }
            }
            times-=freq;
        }
        
        return true;
    }
};
