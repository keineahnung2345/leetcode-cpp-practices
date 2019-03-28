/**
An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input: 
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: 
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected 
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
**/

//Runtime: 28 ms, faster than 98.25% of C++ online submissions for Flood Fill.
//Memory Usage: 10.5 MB, less than 98.44% of C++ online submissions for Flood Fill.
class Solution {
public:
    queue<pair<int, int>> q;
    vector<pair<int, int>> visited;
    
    bool isVisited(int r, int c){
        return find(visited.begin(), visited.end(), make_pair(r, c))!=visited.end();
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        q.push(make_pair(sr, sc));
        
        //BFS a graph
        while(!q.empty()){
            pair<int, int> p = q.front();
            q.pop();
            sr = p.first;
            sc = p.second;
            // cout << sr << " " << sc << endl;
            
            image[sr][sc] = newColor;
            visited.push_back(make_pair(sr, sc));
            
            if(sr > 0 && !isVisited(sr-1, sc) && image[sr-1][sc]==oldColor){
                q.push(make_pair(sr-1, sc));
            }
            if(sc > 0 && !isVisited(sr, sc-1) && image[sr][sc-1]==oldColor){
                q.push(make_pair(sr, sc-1));
            }
            if(sr < image.size()-1 && !isVisited(sr+1, sc) && image[sr+1][sc]==oldColor){
                q.push(make_pair(sr+1, sc));
            }
            if(sc < image[0].size()-1 && !isVisited(sr, sc+1) && image[sr][sc+1]==oldColor){
                q.push(make_pair(sr, sc+1));
            }
        }
        
        return image;
    }
};

/**
Approach #1: Depth-First Search [Accepted]
Intuition

We perform the algorithm explained in the problem description: paint the starting pixels, plus adjacent pixels of the same color, and so on.

Algorithm

Say color is the color of the starting pixel. Let's floodfill the starting pixel: we change the color of that pixel to the new color, then check the 4 neighboring pixels to make sure they are valid pixels of the same color, and of the valid ones, we floodfill those, and so on.

We can use a function dfs to perform a floodfill on a target pixel.
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the number of pixels in the image. We might process every pixel.

Space Complexity: O(N)O(N), the size of the implicit call stack when calling dfs.
**/

/**
class Solution {
public:
    int oc;
    int nc;
    
    void dfs(vector<vector<int>>& image, int r, int c){
        if(image[r][c] == oc){
            image[r][c] = nc;
            if(r > 0) dfs(image, r-1, c);
            if(c > 0) dfs(image, r, c-1);
            if(r < image.size()-1) dfs(image, r+1, c);
            if(c < image[0].size()-1) dfs(image, r, c+1);
        }
    }
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        oc = image[sr][sc];
        nc = newColor;
        
        if(oc != nc){
            dfs(image, sr, sc);
        }
        return image;
    }
};
**/

