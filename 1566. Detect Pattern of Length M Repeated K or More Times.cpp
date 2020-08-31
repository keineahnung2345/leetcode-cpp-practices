//Brute force
//Runtime: 4 ms, faster than 50.00% of C++ online submissions for Detect Pattern of Length M Repeated K or More Times.
//Memory Usage: 8.8 MB, less than 25.00% of C++ online submissions for Detect Pattern of Length M Repeated K or More Times.
//time: O(N^3)
class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = arr.size();
        
        for(int i = 0; i+m*k <= n; ++i){
            vector<int> pattern(arr.begin()+i, arr.begin()+i+m);
            bool found = true;
            for(int t = 1; t < k; ++t){
                // cout << "[" << i+m*t << ", " << i+m*(t+1) << ")" << endl;
                if(pattern != vector<int>(arr.begin()+i+m*t, arr.begin()+i+m*(t+1))){
                    found = false;
                    break;
                }
            }
            // if(found){
            //     for(int e : pattern){
            //         cout << e << " ";
            //     }
            //     cout << endl;
            // }
            if(found) return true;
        }
        
        return false;
    }
};

//One Pass
//https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/discuss/819361/Simple-c%2B%2B-solution(0ms)-100-fast
//time: O(N)
class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int cnt = 0;
        int n = arr.size();
        
        for(int i = 0; i+m < n; ++i){
            if(arr[i] != arr[i+m]){
                cnt = 0;
            }else{
                ++cnt;
            }
            
            if(cnt == (k-1)*m)
                return true;
        }
        
        return false;
    }
};
