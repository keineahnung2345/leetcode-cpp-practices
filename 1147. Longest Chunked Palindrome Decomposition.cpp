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
