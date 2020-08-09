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

//not understand
//Binary search
//https://leetcode.com/problems/kth-missing-positive-number/discuss/779999/JavaC%2B%2BPython-O(logN)
//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Kth Missing Positive Number.
//Memory Usage: 9.7 MB, less than 50.00% of C++ online submissions for Kth Missing Positive Number.
//time: O(logN), space: O(1)
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        //i: consider arr[1...i], index is 1-based
        int l = 0, r = arr.size();
        int m;
        
        while(l < r){
            m = (l+r+1) >> 1;
            // cout << l << ", " << m << ", " << r << endl;
            // if(m > 0) cout << "m: " << arr[m-1] - m << endl;
            
            /*
            arr[1...m] - m: 
            in the range arr[1...m](index is 1-based),
            there are m numbers not missing,
            so the number of missing numbers is arr[m] - m
            */
            if(m == 0 || arr[m-1] - m < k){
                l = m;
            }else{
                r = m-1;
            }
        }
        
        return l + k;
    }
};
