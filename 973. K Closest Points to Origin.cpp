/**
We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)
**/

//Runtime: 252 ms, faster than 89.47% of C++ online submissions for K Closest Points to Origin.
//Memory Usage: 47.6 MB, less than 56.00% of C++ online submissions for K Closest Points to Origin.

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
