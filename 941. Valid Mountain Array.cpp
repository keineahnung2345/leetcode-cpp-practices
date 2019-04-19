//One Pass
//time: O(n), space: O(1)
//Runtime: 36 ms, faster than 80.51% of C++ online submissions for Valid Mountain Array.
//Memory Usage: 10.4 MB, less than 100.00% of C++ online submissions for Valid Mountain Array.

class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        if(A.size() < 3) return false;
        int i = 1;
        while(i < A.size() && A[i] > A[i-1]){
            i++;
        }
        //i == 1 means A[1] <= A[0]
        //while loop terminate because the array has been scanned
        if(i == 1 || i == A.size()) return false;
        
        while(i < A.size() && A[i] < A[i-1]){
            i++;
        }
        //while loop terminate because the array has been scanned
        if(i == A.size()) return true;
        //while loop terminate because A[i] < A[i-1] not holds
        return false;
    }
};
