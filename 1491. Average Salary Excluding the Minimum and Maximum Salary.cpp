//Runtime: 4 ms, faster than 63.49% of C++ online submissions for Average Salary Excluding the Minimum and Maximum Salary.
//Memory Usage: 7.2 MB, less than 66.67% of C++ online submissions for Average Salary Excluding the Minimum and Maximum Salary.
class Solution {
public:
    double average(vector<int>& salary) {
        int n = salary.size();
        int sum = accumulate(salary.begin(), salary.end(), 0);
        int max_val = *max_element(salary.begin(), salary.end());
        int min_val = *min_element(salary.begin(), salary.end());
        // cout << sum << ", " << max_val << ", " << min_val  << endl;
        return (sum - max_val - min_val)/(double)(n-2);
    }
};
