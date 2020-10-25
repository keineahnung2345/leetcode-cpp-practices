//Runtime: 28 ms, faster than 11.60% of C++ online submissions for Mean of Array After Removing Some Elements.
//Memory Usage: 10 MB, less than 99.83% of C++ online submissions for Mean of Array After Removing Some Elements.
class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        
        int rem = n*5.0/100;
        
        sort(arr.begin(), arr.end());
        
        return (double)accumulate(arr.begin()+rem, arr.end()-rem, 0)/(n-2*rem);
    }
};

//O(n) nth_element
//https://leetcode.com/problems/mean-of-array-after-removing-some-elements/discuss/900529/C%2B%2B-O(n)-nth_element
//Runtime: 20 ms, faster than 45.74% of C++ online submissions for Mean of Array After Removing Some Elements.
//Memory Usage: 9.8 MB, less than 99.83% of C++ online submissions for Mean of Array After Removing Some Elements.
class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        
        int rem = n*5.0/100;
        
        //[rem, n-rem*2, rem]
        
        //put the first "rem" elements at their right place
        nth_element(arr.begin(), arr.begin()+rem, arr.end());
        //put the second part(n-rem*2 elements) at their right place
        nth_element(arr.begin()+rem, arr.end()-rem, arr.end());
        
        return accumulate(arr.begin()+rem, arr.end()-rem, 0)/(double)(n-rem*2);
    }
};
