//Runtime: 0 ms, faster than 100.00% of C++ online submissions for The kth Factor of n.
//Memory Usage: 5.9 MB, less than 66.67% of C++ online submissions for The kth Factor of n.
class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        for(int i = sqrt(n); i >= 1; --i){
            if(n % i == 0){
                factors.insert(factors.begin(), i);
                if(i*i != n) factors.push_back(n/i);
                //--k;
                //if(k == 0) return i;
            }
        }
        
        if(k > factors.size()) return -1;
        return factors[k-1];
    }
};
