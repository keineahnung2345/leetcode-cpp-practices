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
