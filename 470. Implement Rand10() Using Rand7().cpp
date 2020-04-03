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
            //we can generate 7*7=49 numbers by calling rand7() twice
            row = rand7();
            col = rand7();
            //this is the index on an 2-D table
            idx = (row - 1)*7 + col;
        }while(idx > 40);
        //idx's range : [1-40]
        //idx-1: [0-39]
        //(idx-1)%10 : [0-9]
        //(idx-1)%10+1 : [1-10]
        return (idx-1) % 10+ 1;
    }
};

//Approach 2: Rejection Sampling, Utilizing out-of-range samples(speed up)
//Runtime: 68 ms, faster than 69.59% of C++ online submissions for Implement Rand10() Using Rand7().
//Memory Usage: 7.3 MB, less than 100.00% of C++ online submissions for Implement Rand10() Using Rand7().
// The rand7() API is already defined for you.
//time: O(1) average, O(infinite) for worst case, space: O(1)

// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int row, col, idx;
        while(true){
            row = rand7();
            col = rand7();
            idx = (row - 1)*7 + col;
            if(idx <= 40){
                return (idx-1) % 10+ 1;
            }
            
            row = idx-40; //1 to 9
            col = rand7();
            idx = (row - 1)*7 + col; //1 to 63
            if(idx <= 60){
                return (idx-1) % 10+ 1;
            }
            
            row = idx-60; //1 to 3
            col = rand7();
            idx = (row - 1)*7 + col; //1 to 21
            if(idx <= 20){
                return (idx-1) % 10+ 1;
            }
        }
    }
};
