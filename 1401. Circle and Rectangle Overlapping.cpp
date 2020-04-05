//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Circle and Rectangle Overlapping.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Circle and Rectangle Overlapping.
class Solution {
public:
    bool inCircle(double radius, double x_center, double y_center, double x, double y){
        return (x-x_center)*(x-x_center) + (y-y_center)*(y-y_center) <= radius*radius;
    };
    
    bool inSquare(int x1, int y1, int x2, int y2, int x, int y){
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) return true;
        return false;
    };
    
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        double delta = 1.0;
        for(int x = x1, y = y1; x <= x2; x += delta){
            if(inCircle(radius, x_center, y_center, x, y)){
                return true;
            }
        }
        for(int x = x1, y = y2; x <= x2; x += delta){
            if(inCircle(radius, x_center, y_center, x, y)){
                return true;
            }
        }
        for(int x = x1, y = y1; y <= y2; y += delta){
            if(inCircle(radius, x_center, y_center, x, y)){
                return true;
            }
        }
        for(int x = x2, y = y1; y <= y2; y += delta){
            if(inCircle(radius, x_center, y_center, x, y)){
                return true;
            }
        }
        
        if(inSquare(x1, y1, x2, y2, x_center, y_center)) return true;
        if(inSquare(x1, y1, x2, y2, x_center-radius, y_center)) return true;
        if(inSquare(x1, y1, x2, y2, x_center+radius, y_center)) return true;
        if(inSquare(x1, y1, x2, y2, x_center, y_center-radius)) return true;
        if(inSquare(x1, y1, x2, y2, x_center, y_center+radius)) return true;
        
        return false;
    }
};

//Find point in rectangle closest to circle first
//https://leetcode.com/problems/circle-and-rectangle-overlapping/discuss/563441/JAVA-compare-distance-between-radius-and-closest-point-on-rectangle-to-circle
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Circle and Rectangle Overlapping.
//Memory Usage: 6 MB, less than 100.00% of C++ online submissions for Circle and Rectangle Overlapping.
class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        int x_closest = (x_center < x1) ? x1 : (x_center > x2) ? x2 : x_center;
        int y_closest = (y_center < y1) ? y1 : (y_center > y2) ? y2 : y_center;
        
        int dist_squared = (x_center-x_closest)*(x_center-x_closest) + 
            (y_center-y_closest)*(y_center-y_closest);
        
        return dist_squared <= radius * radius;
    }
};
