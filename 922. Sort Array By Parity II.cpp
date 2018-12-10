/**
Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.

Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.

You may return any answer array that satisfies this condition.

 

Example 1:

Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
 

Note:

2 <= A.length <= 20000
A.length % 2 == 0
0 <= A[i] <= 1000
**/

//Your runtime beats 28.06 % of cpp submissions.
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int evenix = 0;
        int oddix = 1;
        //use evenix to scan the even part of A, oddix to scan odd part of A
        while(evenix<A.size() && oddix<A.size()){
            if(A[evenix]%2==1 && A[oddix]%2==0){
                //swap
                int tmp = A[evenix];
                A[evenix] = A[oddix];
                A[oddix] = tmp;
                evenix+=2;
                oddix+=2;
            }
            if(A[evenix]%2==0){
                evenix+=2;
            }
            if(A[oddix]%2==1){
                oddix+=2;
            }
        }
        return A;
    }
};

/**
Solution
Approach 1: Two Pass
Intuition and Algorithm

Read all the even integers and put them into places ans[0], ans[2], ans[4], and so on.

Then, read all the odd integers and put them into places ans[1], ans[3], ans[5], etc.
**/

//Java
/**
class Solution {
    public int[] sortArrayByParityII(int[] A) {
        int N = A.length;
        int[] ans = new int[N];

        int t = 0;
        for (int x: A) if (x % 2 == 0) {
            ans[t] = x;
            t += 2;
        }

        t = 1;
        for (int x: A) if (x % 2 == 1) {
            ans[t] = x;
            t += 2;
        }

        return ans;
    }
}
**/

/**
Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(N). 
**/

/**
Approach 2: Read / Write Heads
Intuition

We are motivated (perhaps by the interviewer) to pursue a solution where we modify the original array A in place.

First, it is enough to put all even elements in the correct place, since all odd elements will be in the correct place too. So let's only focus on A[0], A[2], A[4], ...

Ideally, we would like to have some partition where everything to the left is already correct, and everything to the right is undecided.

Indeed, this idea works if we separate it into two slices even = A[0], A[2], A[4], ... and odd = A[1], A[3], A[5], .... Our invariant will be that everything less than i in the even slice is correct, and everything less than j in the odd slice is correct.

Algorithm

For each even i, let's make A[i] even. To do it, we will draft an element from the odd slice. We pass j through the odd slice until we find an even element, then swap. Our invariant is maintained, so the algorithm is correct.

**/

//Your runtime beats 22.25 % of cpp submissions.
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int evenix = 0;
        int oddix = 1;
        
        for(int evenix = 0; evenix < A.size(); evenix+=2){
            if(A[evenix]%2==1){
                while(A[oddix]%2==1)
                    oddix+=2;
                int tmp = A[evenix];
                A[evenix] = A[oddix];
                A[oddix] = tmp;
            }
        }
        return A;
    }
};

/**
Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(1). 
**/
