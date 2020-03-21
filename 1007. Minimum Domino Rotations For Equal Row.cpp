//WA
//78 / 84 test cases passed.
class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int aValue = A[0], bValue = B[0];
        int N = A.size();
        int aSwap = 0, bSwap = 0;
        
        for(int i = 1; i < N; i++){
            if(A[i] == aValue){
                continue;
            }else if(B[i] == aValue){
                aSwap++;
            }else{
                //cannot swap so that A is filled with aValue
                aSwap = INT_MAX;
                break;
            }
        }
        
        for(int i = 1; i < N; i++){
            if(B[i] == bValue){
                continue;
            }else if(A[i] == bValue){
                bSwap++;
            }else{
                bSwap = INT_MAX;
                break;
            }
        }
        
        cout << aSwap << " " << bSwap << endl;
        if(aSwap == INT_MAX && bSwap == INT_MAX) return -1;
        return min(aSwap, bSwap);
    }
};
