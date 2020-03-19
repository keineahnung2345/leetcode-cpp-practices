//Runtime: 4 ms, faster than 88.52% of C++ online submissions for Longest Chunked Palindrome Decomposition.
//Memory Usage: 10.1 MB, less than 100.00% of C++ online submissions for Longest Chunked Palindrome Decomposition.
class Solution {
public:
    int longestDecomposition(string text) {
        int start = 0, N = text.size();
        int ans = 0;
        
        // cout << "N: " << N << endl;
        
        /*
        for even N, say 4, start should be in [0,1]
        for odd N, say 3, start should be in [0,1] (the middle element should also be start once)
        */
        while(start < (N+1)/2){
            int width = 1;
            /*
            current substring ends at start+width-1, 
            for odd N, say 3, ends at 0 or 1
            for even N, say 4, ends at 0 or 1
            */
            while(start + width < (N+1)/2 && 
                  text.substr(start, width) != text.substr(N-start-width, width)){
                // cout << width <<" "<< text.substr(start, width) << " " << text.substr(N-start-width, width) << endl;
                width++;
            }
            // cout << width <<" "<< text.substr(start, width) << " " << text.substr(N-start-width, width) << endl;
            
            /*
            if start + width >= (N+1)/2, that means current substring ends at the middle for odd N (or just before the middle for even N)
            */
            if((text.substr(start, width) == text.substr(N-start-width, width)) && (start != N-start-width)){
                //the two parts are the same and they are different part in original string
                //tokens in both ends
                ans+=2;
            }else{
                //we come to half
                // cout << start << " " << width << " " << N/2 <<endl;
                ans++;
            }
            
            start += width;
        }
        
        return ans;
    }
};

//Rolling hash, Rabin Karp algorithm, two pointer
//https://leetcode.com/problems/longest-chunked-palindrome-decomposition/discuss/350711/Close-to-O(n)-Python-Rabin-Karp-Algorithm-with-two-pointer-technique-with-explanation-(~40ms)
//WA(long long int overflow)
//62 / 82 test cases passed.
class Solution {
public:
    int longestDecomposition(string text) {
        int magic_prime = 107;
        int low = 0, high = text.size()-1;
        int cur_low_hash = 0, cur_high_hash = 0, cur_hash_length = 0;
        int ans = 0;
        
        while(low < high){
            cur_low_hash = (cur_low_hash * 26)%magic_prime;
            cur_low_hash += (text[low]-'a');
            cur_low_hash %= magic_prime;
            
            //pow(26, cur_hash_length) cannot give corrent result even if using long long int in C++
            cur_high_hash += (text[high]-'a')*((long long int)pow(26, cur_hash_length)%magic_prime);
            cur_high_hash %= magic_prime;
            
            low++;
            high--;
            cur_hash_length++;
            
            if(cur_low_hash == cur_high_hash && text.substr(low-cur_hash_length, cur_hash_length) == text.substr(high+1, cur_hash_length)){
                ans += 2;
                cur_low_hash = 0;
                cur_high_hash = 0;
                cur_hash_length = 0;
            }
        }
        
        //only leave a char in the middle(odd N)
        //cannot find palindrome pair on two sides of the middle(even N)
        if((cur_hash_length == 0 && low == high) || cur_hash_length > 0){
            ans++;
        }
        
        return ans;
    }
};
