//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Convert Integer to the Sum of Two No-Zero Integers.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for Convert Integer to the Sum of Two No-Zero Integers.

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        for(int i = 1; i < n; i++){
            int j = n - i;
            string si = to_string(i), sj = to_string(j);
            // cout << si << ", " << sj << endl;
            
            if(!count(si.begin(), si.end(), '0') &&
               !count(sj.begin(), sj.end(), '0')){
                return {i, j};
            }
        }
        return {0,0};
    }
};
