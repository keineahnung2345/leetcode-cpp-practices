//Runtime: 8 ms, faster than 97.18% of C++ online submissions for Find Lucky Integer in an Array.
//Memory Usage: 10.4 MB, less than 100.00% of C++ online submissions for Find Lucky Integer in an Array.
class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int, int> counter;
        
        int maxCount = 0;
        
        for(int num : arr){
            counter[num]+=1;
            maxCount = max(maxCount, counter[num]);
        }

        int ans = -1;
        for(auto it = counter.begin(); it != counter.end(); it++){
            if(it->first == it->second){
                ans = max(ans, it->first);
            }
        }
        
        return ans;
    }
};
