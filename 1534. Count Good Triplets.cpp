//Runtime: 20 ms, faster than 100.00% of C++ online submissions for Count Good Triplets.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Count Good Triplets.
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(abs(arr[i]-arr[j]) <= a){
                    for(int k = j+1; k < n; ++k){
                        if(abs(arr[j]-arr[k]) <= b && abs(arr[i]-arr[k]) <= c){
                            ++ans;
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};
