//DP, bitmask
//https://leetcode.com/problems/maximum-students-taking-exam/discuss/503686/A-simple-tutorial-on-this-bitmasking-problem
//Runtime: 4 ms, faster than 84.94% of C++ online submissions for Maximum Students Taking Exam.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Maximum Students Taking Exam.
class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        //0th element for padding
        vector<int> validity(m+1, 0);
        
        for(int i = 1; i <= m; i++){
            /*
            rowValid has n bits,
            if jth bit(from right to left) is 1, 
            jth seat(from left to right) is able to sit
            */
            int rowValid = 0;
            for(int j = 0; j < n; j++){
                rowValid += ((seats[i-1][j] == '.') << j);
            }
            validity[i] = rowValid;
        }
        
        //-1 means that state is invalid
        vector<vector<int>> dp(m+1, vector(1 << n, -1));
        /*
        0th row is imaginary,
        only 0(all seats are not available) is its valid state
        */
        dp[0][0] = 0;
        
        //iterate through rows
        for(int i = 1; i <= m; i++){
            //get current row's validity
            int valid = validity[i];
            
            //iterate through all possible states of current row
            /*
            if a bit in j is 1, that bit is seated by a person
            */
            for(int j = 0; j < 1 << n; j++){
                //there are two people seating adjacently
                if(j & j >> 1) continue;
                /*
                bits in valid specify the positions of available seats,
                bits in j specify the position of seated seat,
                so j should be a subset of valid
                
                e.g.
                valid = 1011,
                j should be 1010, 1001, 0011, ...,
                but not 1111, 
                since 2nd bit(counting start from right)'s seat is broken
                */
                if((j & valid) != j) continue;
                //now j is a valid state
                
                //iterate through previous row's state
                for(int k = 0; k < 1 << n; k++){
                    //invalid, not initialized
                    if(dp[i-1][k] == -1) continue;
                    //there's person in up-left or up-right position
                    if(j & k >> 1 || k & j >> 1) continue;
                    dp[i][j] = max(dp[i][j], dp[i-1][k] + __builtin_popcount(j));
                }
            }
        }
        
        return *max_element(dp[m].begin(), dp[m].end());
    }
};
