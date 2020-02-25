//Runtime: 16 ms, faster than 85.75% of C++ online submissions for Element Appearing More Than 25% In Sorted Array.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Element Appearing More Than 25% In Sorted Array.

class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        int cur = arr[0], count = 0;
        
        for(int i = 0; i < n; i++){
            if(arr[i] == cur){
                count++;
            }else{
                count = 1; //cur is counted
                cur = arr[i];
            }
            // cout << i << ", " << count << endl;
            if(count * 4 > n){
                return arr[i];
            }
        }
        
        return 0;
    }
};
