//Runtime: 20 ms, faster than 91.05% of C++ online submissions for Can Place Flowers.
//Memory Usage: 10.9 MB, less than 86.42% of C++ online submissions for Can Place Flowers.
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        vector<int> planted;
        for(int i = 0; i < flowerbed.size(); i++){
            if(flowerbed[i] == 1) planted.push_back(i);
        }
        
        //when the first flower locates at x >= 2, we can plant flower(s) at left
        planted.insert(planted.begin(), -2);
        //when the last flower locates at x <= n-3, we can plant flower(s) at right
        planted.push_back(flowerbed.size()+1);
        
        int count = 0;
        // if(planted[0] >= 2) count += planted[i]/2;
        // if(flowerbed.size()-1-planted.back() >= 2) count += (flowerbed.size()-1-planted.back())/2;
         
        for(int i = 1; i < planted.size(); i++){
            if(planted[i] - planted[i-1] >= 4){
                count += ((planted[i] - planted[i-1])/2-1);
            }
            if(count >= n) return true;
        }
        
        return false;
    }
};

//single scan & optimized
//Runtime: 20 ms, faster than 91.12% of C++ online submissions for Can Place Flowers.
//Memory Usage: 10.1 MB, less than 100.00% of C++ online submissions for Can Place Flowers.
//time: O(n), space: O(1)
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        for(int i = 0; i < flowerbed.size(); i++){
            if(flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) && (i == flowerbed.size()-1 || flowerbed[i+1] ==0)) {
                //case 1: i == 0 && i == flowerbed.size()-1(length 1, empty flowerbed)
                //case 2: i == 0 && flowerbed[i+1] == 0(0th and 1st places are empty)
                //case 3: flowerbed[i-1] == 0 && i == flowerbed.size()-1(last and 2nd last places are empty)
                //case 4: flowerbed[i-1] == 0 && flowerbed[i+1] == 0(middle empty place)
                flowerbed[i] = 1;
                count ++;
            }
            if(count >= n) return true;
        }
        return count >= n;
    }
};
