//TLE
//48 / 51 test cases passed.
class Solution {
public:
    string minInteger(string num, int k) {
        int n = num.size();
        for(int i = 0; i < n && k > 0; ++i){
            //find the smallest number in window size k
            //[i:i+k]
            // cout << "i: " << i << endl;
            auto min_it = min_element(num.begin()+i, num.begin()+min(n, i+k+1));
            
            if(*min_it < num[i]){
                //do swap
                int min_idx = min_it - num.begin();
                //[0,i-1] + [i, min_idx], [min_idx+1,n-1]
                //num = num.substr(0, i) + *min_it + num.substr(i, min_idx-i) + num.substr(min_idx+1);
                // cout << "i: " << i << ", min_idx: " << min_idx << endl;
                // cout << num << "->";
                num.replace(i, min_idx-i+1, *min_it + num.substr(i, min_idx-i));
                // cout << num << endl;
                //swap from min_idx to i, that is (min_idx - i) times
                k -= (min_idx - i);
            }
        }
        
        return num;
    }
};

//recursion
//https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/discuss/720215/The-constraint-was-not-very-helpful...-C%2B%2BPython-Clean-56ms-O(n2)-solution
//TLE
//50 / 51 test cases passed.
//time: O(N^2)
class Solution {
public:
    string minInteger(string num, int k) {        
        if(k <= 0) return num;
        
        int n = num.size();
        
        if(k >= n*(n-1)/2){
            sort(num.begin(), num.end());
            return num;
        }
        
        //find '0'~'9'
        for(int i = 0; i < 10; ++i){
            int idx = num.find(to_string(i));
            if(idx >= 0 && idx <= k){
                //k-idx: move the char from idx to 0 cost "idx" swaps
                return num[idx] + minInteger(num.substr(0, idx) + num.substr(idx+1), k - idx);
            }
        }
        
        return num;
    }
};
