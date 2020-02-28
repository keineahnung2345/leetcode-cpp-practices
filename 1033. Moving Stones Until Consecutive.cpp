//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Moving Stones Until Consecutive.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Moving Stones Until Consecutive.

class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        vector<int> v = {a, b, c};
        int least, most;
        sort(v.begin(), v.end());
        
        //move the two stones at endpoint one position by one position
        most = (v[1]-v[0]-1) + (v[2]-v[1]-1);
        if(most == 0){
            //three stones are already consecutive
            least = 0;
        }else{
            //for [1,5,8]:
            //move 8 -> [1,2,5]
            //move 5 -> [1,2,3]
            least = min(v[1]-v[0]-1, v[2]-v[1]-1);
            //if there are two consecutive stones, we only need to move the other stone to the next of them, so one move is enough
            //if there are two stones with one empty position inside, we only need to put the other stone into that empty position, so one move is enough
            //if there are no consecutive stones, we can do one move to make two stones consecutive
            least = (least <= 1) ? 1 : 2;
        }
        
        return {least, most};
    }
};
