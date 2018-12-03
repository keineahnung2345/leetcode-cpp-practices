/**
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain, return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
**/

//Your runtime beats 52.46 % of cpp submissions.
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        //binary search
        int low = 0;
        int up = A.size()-1;
        int cur = A.size()/2;
        // cout << low << " " << up << " " << cur << endl;
        while(true){
        // cout << low << " " << up << " " << cur << endl;
            if(A[cur-1] < A[cur] && A[cur] < A[cur+1]){ //left side of mountain
                low = cur;
                cur = (cur+up)/2;
            }else if(A[cur-1] > A[cur] && A[cur] > A[cur+1]){ //right side
                up = cur;
                cur = (cur+low)/2;
            }else{
                return cur;
            }
        }
    }
};

/**
Approach 1: Linear Scan
Intuition and Algorithm

The mountain increases until it doesn't. The point at which it stops increasing is the peak.

//Java
class Solution {
    public int peakIndexInMountainArray(int[] A) {
        int i = 0;
        while (A[i] < A[i+1]) i++;
        return i;
    }
}

Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(1).

Approach 2: Binary Search
Intuition and Algorithm

The comparison A[i] < A[i+1] in a mountain array looks like [True, True, True, ..., True, False, False, ..., False]: 
1 or more boolean Trues, followed by 1 or more boolean False. 
For example, in the mountain array [1, 2, 3, 4, 1], the comparisons A[i] < A[i+1] would be True, True, True, False.

We can binary search over this array of comparisons, to find the largest index i such that A[i] < A[i+1]. 
For more on binary search, see the LeetCode explore topic here.

//Your runtime beats 52.46 % of cpp submissions.
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        //binary search
        int low = 0;
        int up = A.size()-1;
        while(low < up){
            int mi = (low+up)/2;
            if(A[mi] < A[mi+1]){
                low = mi+1;
            }else{
                up = mi;
            }
        }
        return low;
    }
};

Complexity Analysis

Time Complexity: O(logN), where N is the length of A.

Space Complexity: O(1).
**/
