//Runtime: 968 ms, faster than 52.07% of C++ online submissions for The k Strongest Values in an Array.
//Memory Usage: 80.6 MB, less than 100.00% of C++ online submissions for The k Strongest Values in an Array.
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        
        sort(arr.begin(), arr.end(),
            [&median](const int& x, const int& y){
                return (abs(x-median) == abs(y-median)) ? (x > y) : (abs(x-median) > abs(y-median));
            });
        
        return vector<int>(arr.begin(), arr.begin()+k);
    }
};
