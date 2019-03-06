/**
We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)
**/

//Runtime: 252 ms, faster than 89.47% of C++ online submissions for K Closest Points to Origin.
//Memory Usage: 47.6 MB, less than 56.00% of C++ online submissions for K Closest Points to Origin.

/**
Complexity Analysis

Time Complexity: O(N \log N)O(NlogN), where NN is the length of points.

Space Complexity: O(N)O(N). 
**/
class Solution {
public:
    template <typename T>
    vector<size_t> sort_indexes(const vector<T> &v) {

      // initialize original index locations
      vector<size_t> idx(v.size());
      iota(idx.begin(), idx.end(), 0);

      // sort indexes based on comparing values in v
      sort(idx.begin(), idx.end(),
           [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

      return idx;
    }
    
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<float> dist;
        vector<vector<int>> ans;
        
        for(vector<vector<int>>::iterator it=points.begin(); it<points.end(); it++) {
            vector<int> point = *it;
            dist.push_back(sqrt(pow(point[0], 2) + pow(point[1],2)));
        }
        
        vector<long unsigned int> sorted_indices = sort_indexes(dist);
        for(int i = 0; i < K; i++){
            int idx = sorted_indices[i];
            ans.push_back(points[idx]);
        }
        
        return ans;
    }
};

//Runtime: 236 ms, faster than 94.04% of C++ online submissions for K Closest Points to Origin.
//Memory Usage: 44.7 MB, less than 63.56% of C++ online submissions for K Closest Points to Origin.
/**
Approach 2: Divide and Conquer
Intuition
We want an algorithm faster than N \log NNlogN. 
Clearly, the only way to do this is to use the fact that the K elements returned can be in any order 
-- otherwise we would be sorting which is at least N \log NNlogN.

Say we choose some random element x = A[i] and split the array into two buckets: 
one bucket of all the elements less than x, 
and another bucket of all the elements greater than or equal to x. 
This is known as "quickselecting by a pivot x".

The idea is that if we quickselect by some pivot, 
on average in linear time we'll reduce the problem to a problem of half the size.

Algorithm

Let's do the work(i, j, K) of partially sorting the subarray 
(points[i], points[i+1], ..., points[j]) 
so that the smallest K elements of this subarray 
occur in the first K positions (i, i+1, ..., i+K-1).

First, we quickselect by a random pivot element from the subarray. 
To do this in place, we have two pointers i and j, 
and move these pointers to the elements that are in the wrong bucket 
-- then, we swap these elements.

After, we have two buckets [oi, i] and [i+1, oj], 
where (oi, oj) are the original (i, j) values when calling work(i, j, K). 
Say the first bucket has 10 items and the second bucket has 15 items.
If we were trying to partially sort say, K = 5 items, 
then we only need to partially sort the first bucket: work(oi, i, 5).
Otherwise, if we were trying to partially sort say, K = 17 items, 
then the first 10 items are already partially sorted, 
and we only need to partially sort the next 7 items: work(i+1, oj, 7).
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N) in average case complexity, where NN is the length of points.

Space Complexity: O(N)O(N). 
**/

/**
class Solution {
public:
    int dist(vector<vector<int>>& points, int i){
        return pow(points[i][0], 2) + pow(points[i][1], 2);
    }
    
    int partition(vector<vector<int>>& points, int i, int j){
        //Partition by pivot A[i], returning an index mid
        //such that A[i] <= A[mid] <= A[j] for i < mid < j.
        int oi = i;
        int pivot = dist(points, i);
        i += 1;

        while(true){
            while(i < j && dist(points, i) < pivot) i+=1;
            while(i <= j && dist(points, j) >= pivot) j-=1;
            if(i>=j) break;
            vector<int> tmp = points[i];
            points[i] = points[j];
            points[j] = tmp;
        }

        vector<int> tmp = points[oi];
        points[oi] = points[j];
        points[j] = tmp;
        return j;
    }

    
    void sort(vector<vector<int>> &points, int i, int j, int K){
        // Partially sorts A[i:j+1] so the first K elements are
        // the smallest K elements.
        if(i>=j) return;

        // Put random element as A[i] - this is the pivot
        srand(1);
        int k = rand()%(j-i) + i;
        vector<int> tmp = points[i];
        points[i] = points[k];
        points[k] = tmp;

        int mid = partition(points, i, j);
        //mid - i + 1 : the size of former partition
        if(K < mid - i + 1){
            sort(points, i, mid - 1, K);
        }else if(K > mid - i + 1){
            sort(points, mid + 1, j, K - (mid - i +1));
        }
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points, 0, points.size() - 1, K);
        vector<vector<int>> ans(points.begin(), points.begin() + K);
        return ans;
    }
    
};
**/
