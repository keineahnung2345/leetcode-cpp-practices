//Runtime: 584 ms, faster than 15.78% of C++ online submissions for Check If Array Pairs Are Divisible by k.
//Memory Usage: 60.4 MB, less than 100.00% of C++ online submissions for Check If Array Pairs Are Divisible by k.
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        for(int& num : arr){
            num = (num%k + k) % k;
        }
        
        int zeroCount = count_if(arr.begin(), arr.end(), [](int num){return num == 0;});
        if(zeroCount % 2 != 0) return false;
        
        arr.erase(remove(arr.begin(), arr.end(), 0), arr.end());
        
        sort(arr.begin(), arr.end());
        
        // for(int& num : arr){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        int n = arr.size();
        
        for(int i = 0; i < n/2; ++i){
            // cout << i << " and " << n-i-1 << " : " << arr[i] << " and " << arr[n-1-i] << endl;
            if((arr[i] + arr[n-1-i])%k != 0){
                return false;
            }
        }
        
        return true;
    }
};

//remainder frequency
//https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/discuss/709331/Weak-TC-passes-my-1-liner-or-Correct-Solution-Using-Reminder-Frequency
//Runtime: 272 ms, faster than 71.67% of C++ online submissions for Check If Array Pairs Are Divisible by k.
//Memory Usage: 61.8 MB, less than 100.00% of C++ online submissions for Check If Array Pairs Are Divisible by k.
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<int> remainderFreq(k);
        
        for(int& num : arr){
            ++remainderFreq[(num%k+k)%k];
        }
        
        if(remainderFreq[0] % 2 != 0)
            return false;
        
        for(int remainder = 1; remainder < k - remainder; ++remainder){
            if(remainderFreq[remainder] != remainderFreq[k-remainder]){
                return false;
            }
        }
        
        return true;
    }
};
