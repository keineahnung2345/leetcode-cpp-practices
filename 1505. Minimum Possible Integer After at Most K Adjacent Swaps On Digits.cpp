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
