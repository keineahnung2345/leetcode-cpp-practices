//TLE
//53 / 57 test cases passed.
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        
        vector<vector<int>> v;
        // deque<vector<int>> deq;
        
//         for(int i = 0; i < n; i++){
//             if(arr[i] == target){
//                 v.push_back({i, i});
//                 // deq.push_back({i, i});
//                 // cout << i << ", " << i << endl;
//             }else if(arr[i] < target){
//                 int remain = target - arr[i];
//                 int j;
//                 for(j = i+1; j < n && remain > 0; remain -= arr[j++]){
                    
//                 }
//                 if(remain == 0){
//                     j--;
//                     v.push_back({i, j});
//                     // cout << i << ", " << j << endl;
//                 }
//             }
//         }
        
        int windowSum = 0, slow = 0, fast = 0;
        for(;fast < n;fast++){
            while(fast < n && windowSum < target){
                windowSum += arr[fast++];
            }
            fast--;
            if(windowSum == target){
                v.push_back({slow, fast});
                // cout << slow << ", " << fast << ", " << windowSum << endl;
                windowSum -= arr[slow++];
            }else{
                while(windowSum > target){
                    cout << slow << ", " << fast << ", " << windowSum << endl;
                    windowSum -= arr[slow++];
                    // cout << slow << ", " << fast << ", " << windowSum << endl;
                    if(windowSum == target){
                        v.push_back({slow, fast});
                    }
                }
                // windowSum -= arr[slow];
            }
            // cout << slow << ", " << fast << ", " << windowSum << endl;
            // windowSum -= arr[slow];
            // slow++;
        }
        
        // cout << endl;
        
        if(v.size() < 2) return -1;
        
        sort(v.begin(), v.end(), [](const vector<int>& a, const vector<int>& b){
            return a[1]-a[0] < b[1]-b[0];
        });
        
        int start = v[0][0], end = v[0][1];
        
        for(int i = 1; i < v.size(); i++){
            if(v[i][1] < start || v[i][0] > end){
                return (end-start+1) + (v[i][1]-v[i][0]+1);
            }
        }
        
        return -1;
    }
};

//DP
/*
Hint 1: Let's create two arrays prefix and suffix where 
prefix[i] is the minimum length of sub-array ends before i and has sum = k, 
suffix[i] is the minimum length of sub-array starting at or after i and has sum = k.

Hint 2: The answer we are searching for is min(prefix[i] + suffix[i]) 
for all values of i from 0 to n-1 where n == arr.length.

Hint 3: If you are still stuck with how to build prefix and suffix, 
you can store for each index i the length of the sub-array starts at i 
and has sum = k or infinity otherwise, 
and you can use it to build both prefix and suffix.
*/
//Runtime: 304 ms, faster than 80.00% of C++ online submissions for Find Two Non-overlapping Sub-arrays Each With Target Sum.
//Memory Usage: 77.1 MB, less than 40.00% of C++ online submissions for Find Two Non-overlapping Sub-arrays Each With Target Sum.
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        /*
        1 <= arr.length <= 10^5,
        so "ans = min(prefix[i] + suffix[i])" 's max possible value is
        1e5+1e5,
        here we set MAX as 2e5+1, 
        this is the value just above the max possible value
        */
        int MAX = 2e5+1;
        //the minimum length of subarray ends "before" i having sum = target
        vector<int> prefix(n, MAX);
        //the minimum length of subarray starts "at" or "after" i having sum = target
        vector<int> suffix(n, MAX);
        
        int slow = 0, fast = 0;
        //the window is [slow, fast]
        int windowSum = 0;
        while(fast < n){
            windowSum += arr[fast];
            
            while(slow <= fast && windowSum > target){
                windowSum -= arr[slow++];
            }
            
            if(windowSum == target){
                if(fast+1 < n){
                    prefix[fast+1] = fast-slow+1;
                }
            }
            
            fast++;
        }
        
        slow = n-1;
        fast = n-1;
        windowSum = 0;
        //the window is [fast, slow]
        while(fast >= 0){
            windowSum += arr[fast];
            
            while(slow >= fast && windowSum > target){
                windowSum -= arr[slow--];
            }
            
            if(windowSum == target){
                suffix[fast] = slow-fast+1;
            }
            
            fast--;
        }
        
        for(int i = 1; i < n; i++){
            prefix[i] = min(prefix[i], prefix[i-1]);
        }
        
        for(int i = n-2; i >= 0; i--){
            suffix[i] = min(suffix[i], suffix[i+1]);
        }
        
//         for(int e : prefix){
//             cout << e << " ";
//         }
//         cout << endl;
        
//         for(int e : suffix){
//             cout << e << " ";
//         }
//         cout << endl;
        
        int ans = INT_MAX;
        
        for(int i = 0; i < n; i++){
            /*
            since prefix[i] ends at j <= i-1,
            and suffix[i] starts at j >= i,
            so the two subarrays won't overlap!
            */
            ans = min(ans, prefix[i] + suffix[i]);
        }
        
        return (ans >= MAX) ? -1 : ans;
    }
};
