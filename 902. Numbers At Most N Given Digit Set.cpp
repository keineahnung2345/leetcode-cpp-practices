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

//Math
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Numbers At Most N Given Digit Set.
//Memory Usage: 8.2 MB, less than 41.15% of C++ online submissions for Numbers At Most N Given Digit Set.
//time: O(log10(N)), space: O(log10(N))
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string S = to_string(N);
        int K = S.size();
        //1-based
        //bijectoin is the bijection representation of largest number that <= N
        vector<int> bijectoin(K);
        int t = 0;
        
        for(char c : S){
            // cout << "c: " << c << endl;
            int c_index = 0;
            bool match = false;
            for(int i = 0; i < D.size(); i++){
                if(c-'0' >= stoi(D[i])){
                    c_index = i+1;
                }
                if(c-'0' == stoi(D[i])){
                    match = true;
                }
            }
            
            // cout << D[t] << " -> " << c_index << endl;
            // cout << "match: " << match << endl;
            /*
            c_index is the index in D(1-based) pointing to
            a number just <= c
            c_index may be 0(it's invalid value)
            */
            bijectoin[t++] = c_index;
            /*
            if we can find c in D,
            we just map current char in S to i+1(1-based)
            and move forward
            */
            if(match) continue;
            
            if(c_index == 0){
                /*
                that means we cannot find a c >= all D[i],
                i.e. c is smaller than all D[i],
                so we need to subtract 1
                
                j starts from t-1: because we want to overwrite 
                previous bijection[t]
                
                j ends at 1: because we will use bijection[j-1]
                */
                for(int j = t-1; j > 0; j--){
                    //?
                    if(bijectoin[j] > 0) break;
                    // bijectoin[j] += D.size();
                    bijectoin[j] = D.size();
                    bijectoin[j-1]--;
                    // cout << D[j] << " -> " << bijectoin[j] << endl;
                    // cout << D[j-1] << " -> " << bijectoin[j-1] << endl;
                }
            }
            
            /*
            D = ['2', '4', '6', '8'], N = 5123
            c_index will be 2 for the most significant digit 5,
            we want bijection become 2444(represents for 4888)
            */
            while(t < K){
                // cout << D[t] << " -> " << D.size() << endl;
                bijectoin[t++] = D.size();
            }
            break;
        }
        
        /*
        convert base-(D.size()) positional notation 
        to base-10 position notation
        */
        int ans = 0;
        
        for(int e : bijectoin){
            ans = ans * D.size() + e;
            // cout << "e: " << e << ", ans: " << ans << endl;
        }
        
        return ans;
    }
};
