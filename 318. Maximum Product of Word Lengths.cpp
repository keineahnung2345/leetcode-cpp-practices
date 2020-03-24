//Runtime: 100 ms, faster than 28.36% of C++ online submissions for Maximum Product of Word Lengths.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Maximum Product of Word Lengths.
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int N = words.size();
        vector<int> hashs(N);
        int ans = 0;
        
        //convert them into int(bit representation)
        for(int i = 0; i < N; i++){
            for(char c : words[i]){
                hashs[i] |= (1 << (c-'a'));
            }
        }
        
        for(int i = 0; i < N; i++){
            vector<int>::iterator it = hashs.begin()+i;
            while(it != hashs.end()){
                it = find_if(it+1, hashs.end(), 
                   [&hashs, i](const int& e){
                       return ((hashs[i] & e) == 0);
                   });
                //if we can find hashs[j] s.t. hashs[i] & hashs[i] is 0
                if(it != hashs.end()){
                    ans = max(ans, (int)words[i].size() * (int)words[it-hashs.begin()].size());
                }
            }
        }
        
        return ans;
    }
};
