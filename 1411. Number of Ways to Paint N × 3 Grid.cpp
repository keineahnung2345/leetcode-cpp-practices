//https://www.geeksforgeeks.org/ways-color-3n-board-using-4-colors/
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Ways to Paint N × 3 Grid.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Number of Ways to Paint N × 3 Grid.
class Solution {
public:
    int solve(int A) {
        // When we to fill single column 
        long int color3 = 6; //P 3 takes 3
        long int color2 = 6; //(C 3 takes 2) * (2 possible position)
        long int temp = 0; 

        for (int i = 2; i <= A; i++)  
        { 
            temp = color3; //previous color3
            /*
            when current row is of three color
            next row could have 2 possible two color comb and 
            2 possible three color comb
            
            when current row is of two color
            next row could have 3 possible two color comb and 
            2 possible three color comb
            */
            color3 = (2 * color3 + 2 * 
                  color2 ) % 1000000007; 

            color2 = ( 2 * temp + 3 * 
                  color2 ) % 1000000007; 
        } 

        long num = (color3 + color2) 
                           % 1000000007; 

        return (int)num; 
    } 
  
    
    int numOfWays(int n) {
        return solve(n);
    }
};
