/**
In a array A of size 2N, there are N+1 unique elements, and exactly one of these elements is repeated N times.

Return the element repeated N times.

 

Example 1:

Input: [1,2,3,3]
Output: 3
Example 2:

Input: [2,1,2,5,3,2]
Output: 2
Example 3:

Input: [5,1,5,2,5,3,5,4]
Output: 5
 

Note:

4 <= A.length <= 10000
0 <= A[i] < 10000
A.length is even
**/

//Runtime: 44 ms, faster than 50.05% of C++ online submissions for N-Repeated Element in Size 2N Array.
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        set<int> set;
        for(int i = 0; i<A.size(); i++){
            if(set.find(A[i])==set.end()){
                set.insert(A[i]);
            }else{
                return A[i];
            }
        }
    }
};

/**
Approach 1: Count
Intuition and Algorithm

Let's count the number of elements. We can use a HashMap or an array - here, we use a HashMap.

After, the element with a count larger than 1 must be the answer.

//Java
class Solution {
    public int repeatedNTimes(int[] A) {
        Map<Integer, Integer> count = new HashMap();
        for (int x: A) {
            count.put(x, count.getOrDefault(x, 0) + 1);
        }

        for (int k: count.keySet())
            if (count.get(k) > 1)
                return k;

        throw null;
    }
}

Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(N). 
**/

/**
Approach 2: Compare
Intuition and Algorithm

If we ever find a repeated element, it must be the answer. Let's call this answer the major element.

Consider all subarrays of length 4. There must be a major element in at least one such subarray.

This is because either:

There is a major element in a length 2 subarray, or;
Every length 2 subarray has exactly 1 major element, which means that a length 4 subarray that begins at a major element will have 2 major elements.
Thus, we only have to compare elements with their neighbors that are distance 1, 2, or 3 away.

//Runtime: 48 ms, faster than 35.71% of C++ online submissions for N-Repeated Element in Size 2N Array.
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        for(int k = 1; k <= 3; k++){
            for(int i = 0; i < A.size() - k; i++){
                if(A[i]==A[i+k]){
                    return A[i];
                }
            }
        }
    }
};

Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(1). 
**/
