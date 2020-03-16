//Runtime: 28 ms, faster than 61.61% of C++ online submissions for Push Dominoes.
//Memory Usage: 14.6 MB, less than 25.00% of C++ online submissions for Push Dominoes.

class Solution {
public:
    string pushDominoes(string dominoes) {
        int N = dominoes.size();
        //record the distance to left or right force
        vector<int> left(N, INT_MAX), right(N, INT_MAX);
        
        int last = -1;
        for(int i = 0; i < N; i++){
            switch(dominoes[i]){
                case 'R':
                    last = i;
                    break;
                case '.':
                    if(last != -1) right[i] = i - last;
                    break;
                case 'L':
                    last = -1;
                    break;
            }
            // cout << right[i];
        }
        // cout << endl;
        
        last = -1;
        for(int i = N-1; i >= 0; i--){
            switch(dominoes[i]){
                case 'L':
                    last = i;
                    break;
                case '.':
                    if(last != -1) left[i] = last - i;
                    break;
                case 'R':
                    last = -1;
                    break;
            }
            // cout << left[i];
        }
        // cout << endl;
        
        for(int i = 0; i < N; i++){
            if(dominoes[i] == '.'){
                //the smaller the stronger
                if(left[i] < right[i]){
                    dominoes[i] = 'L';
                }else if(left[i] > right[i]){
                    dominoes[i] = 'R';
                }
            }
        }
        
        return dominoes;
    }
};

//Two pointer
//https://leetcode.com/problems/push-dominoes/discuss/132332/C%2B%2BJavaPython-Two-Pointers
//Runtime: 32 ms, faster than 40.77% of C++ online submissions for Push Dominoes.
//Memory Usage: 13.1 MB, less than 25.00% of C++ online submissions for Push Dominoes.
class Solution {
public:
    string pushDominoes(string dominoes) {
        dominoes = 'L' + dominoes + 'R';
        // cout << dominoes << endl;
        string res = "";
        for (int slow = 0, fast = 1; fast < dominoes.length(); fast++) {
            if (dominoes[fast] == '.') continue;
            //we've found a interval('R......R', 'R......L', 'L......R' or 'L......R')
            int middle = fast - slow - 1;
            
            //deal with slow(left bound)
            //slow == 0 is padding
            if (slow > 0){
                res += dominoes[slow];
            }
            
            //deal with middle(between left and right bound)
            if (dominoes[slow] == dominoes[fast]){
                //'R......R' => 'RRRRRRRR'
                //'L......L' => 'LLLLLLLL'
                res += string(middle, dominoes[slow]);
            }else if (dominoes[slow] == 'L' && dominoes[fast] == 'R'){
                //'L......R' => 'L......R'
                res += string(middle, '.');
            }else{
                //'R......L' => 'RRRRLLLL' or 'RRRR.LLLL'
                res += string(middle / 2, 'R') + string(middle % 2,'.') + string(middle / 2, 'L');
            }
            
            //don't need to deal with right bound because the rightmost char is padding
            // cout << slow << " " << fast << " " << middle << " " << res << endl;
            slow = fast;
        }
        return res;
    }
};
