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

//https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/discuss/252242/JavaC%2B%2BPython-Different-Ideas
//Runtime: 128 ms, faster than 42.29% of C++ online submissions for Minimum Domino Rotations For Equal Row.
//Memory Usage: 17.1 MB, less than 100.00% of C++ online submissions for Minimum Domino Rotations For Equal Row.
//time: O(N), space: O(N)
class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int N = A.size();
        vector<int> countA(7, 0), countB(7, 0), same(7, 0);
        for(int i = 0; i < N; i++){
            countA[A[i]]++;
            countB[B[i]]++;
            if(A[i] == B[i]) same[A[i]]++;
        }
        
        int ans = -1;
        for(int i = 1; i <= 6; i++){
            /*
            countA[i] + countB[i] - same[i]: i can fill how many position,
            this value will always <= N
            */
            if(countA[i] + countB[i] - same[i] == N){
                /*
                if countA[i] > countB[i],
                we flip N - countA[i] times so that 
                row A will be all i
                */
                ans = N - max(countA[i], countB[i]);
                /*
                we can break the loop immediately because when there are 2 "i"
                (say x and y) meets the condition 
                "countA[i] + countB[i] - same[i] == N", 
                same[x] and same[y] will be 0, 
                and countA[x] will equal countB[y], 
                countA[y] will equal countB[x],
                so max(countA[i], countB[i]) and so ans will be the same
                */
                break;
            }
            // cout << i << " " << countA[i] << " " << countB[i] << " " << same[i] << " " << ans << endl;
        }
        
        return ans;
    }
};
