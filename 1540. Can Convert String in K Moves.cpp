//Runtime: 212 ms, faster than 100.00% of C++ online submissions for Can Convert String in K Moves.
//Memory Usage: 176.3 MB, less than 33.33% of C++ online submissions for Can Convert String in K Moves.
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        int n = s.size();
        if(t.size() != n) return false;
        
        vector<int> diff(n, 0);
        vector<bool> used(k+1, false); //1-based
        vector<int> nextseq(26); //[1-25], (moves, seq)
        iota(nextseq.begin(), nextseq.end(), 0);
        for(int i = 0; i < n; ++i){
            diff[i] = t[i] - s[i];
            if(diff[i] == 0) continue;
            if(diff[i] < 0) diff[i] += 26;
            // cout << i << " th char, need " << diff[i] << " moves" << endl;
            if(diff[i] > k) return false;
            
            int seq = nextseq[diff[i]];
            // while(seq <= k && used[seq]){
            //     seq += 26;
            // }
            if(seq <= k){
                // cout << "we can shift this char in " << seq << " th move" << endl;
                used[seq] = true;
                nextseq[diff[i]] += 26;
            }else{
                //cannot find a move in sequence to place diff[i]
                // cout << "cannot find" << endl;
                return false;
            }
        }
        
        return true;
    }
};

//counter
//https://leetcode.com/problems/can-convert-string-in-k-moves/discuss/779903/JavaPython-3-O(n)-Count-the-shift-displacement-w-brief-explanation-and-analysis.
//Runtime: 172 ms, faster than 100.00% of C++ online submissions for Can Convert String in K Moves.
//Memory Usage: 18 MB, less than 33.33% of C++ online submissions for Can Convert String in K Moves.
//time: O(N), space: O(1)
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        int n = s.size();
        
        if(t.size() != n) return false;
        
        vector<int> counter(26, 0);
        
        for(int i = 0; i < n; ++i){
            int diff = t[i] - s[i];
            if(diff < 0) diff += 26;
            //no op
            if(diff == 0) continue;
            
            //diff + counter[diff]*26: how many moves we need
            if(k < diff + counter[diff]*26){
                return false;
            }
            
            ++counter[diff];
        }
        
        return true;
    }
};
