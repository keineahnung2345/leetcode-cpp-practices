//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Kth Missing Positive Number.
//Memory Usage: 9.9 MB, less than 50.00% of C++ online submissions for Kth Missing Positive Number.
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int count = 0;
        
        for(int i = 0; i < arr.size(); ++i){
            if(i == 0){
                //from 1 to arr[0]-1
                if(count + arr[0]-1 >= k){
                    return k;
                }
                count += arr[0]-1;
            }else{
                //from arr[i-1]+1 to arr[i]
                if(count + arr[i] - arr[i-1] - 1 >= k){
                    return arr[i-1] + (k - count);
                }
                count += arr[i] - arr[i-1] - 1;
            }
            // cout << i << " -> " << count << endl;
            
            // if(count >= k){
            //     return arr[i] + (count-k);
            // }
        }
        
        //count < k
        return arr.back() + (k-count);
    }
};
