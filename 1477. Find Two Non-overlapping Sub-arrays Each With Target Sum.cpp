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
