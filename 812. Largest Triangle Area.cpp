//Runtime: 152 ms, faster than 5.31% of C++ online submissions for Largest Triangle Area.
//Memory Usage: 56.1 MB, less than 50.00% of C++ online submissions for Largest Triangle Area.
class Solution {
public:
    void combinationUtil(std::vector<int>& arr, std::vector<int>& combination, std::vector<std::vector<int>>& combinations, int start, int end, int index, int r) { 
        if (index == r) { 
            combinations.push_back(combination);
            return;
        }

        //r - index : number of remaining cells in "combination" to be filled
        //end - i + 1 : the size of remaining cells in "arr"
        //stop when we don't have enough elements to fill the remaining part of "combination"
        for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
            combination[index] = arr[i];
            combinationUtil(arr, combination, combinations, i+1, end, index+1, r);
        } 
    } 

    void getCombinations(std::vector<int>& arr, std::vector<std::vector<int>>& combinations, int n, int r) {
        std::vector<int> combination(r);
        combinationUtil(arr, combination, combinations, 0, n-1, 0, r); 
    } 
    
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size(), r = 3;
        vector<int> indices(n);
        vector<vector<int>> combs;
        //min of double(negative)
        double max_area = std::numeric_limits<double>::lowest();
        
        iota(indices.begin(), indices.end(), 0);
        
        getCombinations(indices, combs, n, r);
        // cout << "n: " << n << ", " << combs.size() << endl;
        
        for(vector<int>& comb : combs){
            // cout << comb[0] << ", " << comb[1] << ", " << comb[2] << endl;
            int curx = points[comb[0]][0];
            vector<int> p0 = points[comb[0]];
            vector<int> p1 = points[comb[1]];
            vector<int> p2 = points[comb[2]];
            
            //x coordinates are same
            if((p0[0] == p1[0]) && (p1[0] == p2[0])){
                continue;
            }
            //on same line
            //(y1-y0)/(x1-x0) == (y2-y1)/(x2-x1)
            //(y1-y0)*(x2-x1) == (y2-y1)*(x1-x0)
            if((p1[1] - p0[1]) * (p2[0] - p1[0]) == 
              (p2[1] - p1[1]) * (p1[0] - p0[0])){
                continue;
            }
            
            //calculate area using Heron's formula
            double a = sqrt(pow(p1[0] - p0[0], 2) + pow(p1[1] - p0[1], 2));
            double b = sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
            double c = sqrt(pow(p2[0] - p0[0], 2) + pow(p2[1] - p0[1], 2));
            double s = (a + b + c)/2;
            double area = sqrt(s * (s - a) * (s - b) * (s - c));
            max_area = max(max_area, area);
        }
        
        return max_area;
    }
};
