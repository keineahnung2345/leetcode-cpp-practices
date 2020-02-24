//Runtime: 12 ms, faster than 100.00% of C++ online submissions for Sort Integers by The Number of 1 Bits.
//Memory Usage: 9.5 MB, less than 100.00% of C++ online submissions for Sort Integers by The Number of 1 Bits.

class Solution {
public:
    int count_set_bit(int x){
        int bits = 0;
        while(x != 0){
            bits += x&1;
            x >>= 1;
        }
        return bits;
    }
    vector<int> sortByBits(vector<int>& arr) {
        vector<int> sorted;
        for(int e : arr){
            //first sort by set bit count and then by itself
            //* 100000 because the max of arr is 10000
            sorted.push_back(count_set_bit(e) * 100000 + e);
        }
        sort(sorted.begin(), sorted.end());
        for(int i = 0; i < sorted.size(); i++){
            sorted[i] = sorted[i]%100000;
        }
        
        return sorted;
    }
};
