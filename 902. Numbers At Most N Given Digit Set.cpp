//DP
//Runtime: 4 ms, faster than 40.00% of C++ online submissions for Numbers At Most N Given Digit Set.
//Memory Usage: 8.3 MB, less than 18.52% of C++ online submissions for Numbers At Most N Given Digit Set.
//time: O(log10(N)), space: O(log10(N))
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string S = to_string(N);
        int K = S.size();
        //dp[i]: count of permutations starting from ith digit
        vector<int> dp(K+1);
        
        /*
        edge case
        for N = 123, D = ["1","3","5","7"], 
        when i = 2, Si is 3, 
        and when stoi(d) is "3",
        we will add dp[K] to dp[K-1],
        that means we are constructing x,
        and x could be 3(one possible permutation)
        */
        dp[K] = 1;
        
        for(int i = K-1; i >= 0; i--){
            int Si = S[i] - '0';
            for(string d : D){
                // cout << "i: " << i << ", Si: " << Si << ", d: " << d << endl;
                if(stoi(d) < Si){
                    /*
                    for N = 123, D = ["1","3","5","7"], 
                    when i = 1, Si is 2, 
                    and when stoi(d) is "1",
                    we are considerting 1x,
                    because 1 < 2, so x can be anything from D,
                    so we can construct 4 permutations: 11, 13, 15, 17
                    */
                    dp[i] += pow(D.size(), K-i-1);
                    // cout << "dp[" << i << "]: " << dp[i] << endl;
                }else if(stoi(d) == Si){
                    /*
                    for N = 123, D = ["1","3","5","7"], 
                    when i = 0, Si is 1, 
                    and when stoi(d) is "1",
                    we are constructing 1xx,
                    for the last 2 digits,
                    we can just use what we have got from i=1 th digit
                    (11, 13, 15, 17),
                    and build 111, 113, 115, 117
                    */
                    dp[i] += dp[i+1];
                    // cout << "dp[" << i << "]: " << dp[i] << endl;
                }/*else if(stoi(d) > Si){
                    //we cannot construct a number in this case!
                }*/
            }
        }
        
        for(int i = 1; i < K; i++){
            /*
            say N has K digits,
            here we are counting the permutations of D to form a i-digit number,
            i ranges from 1 to K-1
            
            for N = 123, D = ["1","3","5","7"]
            1-digit permutation:
            1,3,5,7
            2-digit permutation:
            11,13,15,17,31,33,35,37,51,53,55,57,71,73,75,77
            */
            dp[0] += pow(D.size(), i);
            // cout << "i: " << i << ", dp[0]: " << dp[0] << endl;
        }
        
        return dp[0];
    }
};
