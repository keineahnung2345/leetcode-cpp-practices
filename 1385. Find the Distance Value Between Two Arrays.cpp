//Runtime: 12 ms, faster than 86.09% of C++ online submissions for Find the Distance Value Between Two Arrays.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for Find the Distance Value Between Two Arrays.
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
        for(int e1 : arr1){
            auto it = find_if(arr2.begin(), arr2.end(), 
                             [&e1, &d](int e2){
                                 return abs(e1 - e2) <= d;
                             });
            
            if(it == arr2.end()){
                ans++;
            }
        }
            
        return ans;
    }
};
