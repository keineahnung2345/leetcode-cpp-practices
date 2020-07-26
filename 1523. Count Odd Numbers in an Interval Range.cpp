//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Count Odd Numbers in an Interval Range.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Count Odd Numbers in an Interval Range.
class Solution {
public:
    int countOdds(int low, int high) {
        if(low % 2 ==0) ++low;
        if(high % 2 == 0) --high;
        
        return (high-low)/2+1;
    }
};
