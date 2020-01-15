//Runtime: 52 ms, faster than 76.15% of C++ online submissions for Replace Elements with Greatest Element on Right Side.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for Replace Elements with Greatest Element on Right Side.

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int curMax = 0, tmp; //1 <= arr[i] <= 10^5
        
        for(int i = arr.size() - 1; i >= 0; i--){
            tmp = arr[i];
            if(i == arr.size() - 1){
                arr[i] = -1;
            }else{
                arr[i] = curMax;
            }
            //prepared for next iteration
            curMax = max(curMax, tmp);
        }
        
        return arr;
    }
};
