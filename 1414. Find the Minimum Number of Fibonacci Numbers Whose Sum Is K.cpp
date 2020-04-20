//Runtime: 4 ms, faster than 80.46% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for Find the Minimum Number of Fibonacci Numbers Whose Sum Is K.
class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        vector<int> fNums = {1, 1};
        int i;
        
        while(fNums[fNums.size()-1] < k){
            fNums.push_back(fNums[fNums.size()-1] + fNums[fNums.size()-2]);
        }
        
        // for(int i = 0; i < fNums.size(); i++){
        //     cout << fNums[i] << " ";
        // }
        // cout << endl;
        
        int ans = 0;
        i = fNums.size()-1;
        
        while(k > 0){
            while(i >= 0 && fNums[i] > k){
                i--;
            }
            //the first fibonacci number <= k
            // cout << i << " " << fNums[i] << " ";
            k -= fNums[i];
            ans++;
        }
        // cout << endl;
        // cout << endl;
        
        return ans;
    }
};
