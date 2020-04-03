//Approach 1: Rejection Sampling
//Runtime: 68 ms, faster than 69.59% of C++ online submissions for Implement Rand10() Using Rand7().
//Memory Usage: 7.2 MB, less than 100.00% of C++ online submissions for Implement Rand10() Using Rand7().
//time: O(1) average, O(infinite) for worst case, space: O(1)
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int row, col, idx;
        do{
            row = rand7();
            col = rand7();
            idx = (row - 1)*7 + col;
        }while(idx > 40);
        //idx's range : [1-40]
        //idx-1: [0-39]
        //(idx-1)%10 : [0-9]
        //(idx-1)%10+1 : [1-10]
        return (idx-1) % 10+ 1;
    }
};
