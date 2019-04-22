//TLE
struct Node{
    long long cur;
    long long move;
    Node(){};
    Node(long long c, long long m){
        cur = c;
        move = m;
    };
};

class Solution {
public:
    int reachNumber(int target) {
        queue<Node> q;
        q.push(Node((long long)0, (long long)1));
        Node n;
            
        while(!q.empty()){
            n = q.front();
            q.pop();
            
            if(n.cur == target){
                //moves taken
                return n.move-1;
            }
            
            q.push(Node(n.cur+n.move, n.move+1));
            q.push(Node(n.cur-n.move, n.move+1));
        }
        
        return -1;
    }
};

//solution
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Reach a Number.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Reach a Number.
//time: O(sqrt(target)), the iteration count of while loop, (1+2+...+move) = (1+move)*move/2 >= target
//the while loop execute O(move) times, equal to O(log(target)) times
//space: O(1)

class Solution {
public:
    int reachNumber(int target) {
        target = abs(target);
        int sum = 0, move = 1;
        while(sum < target){
            sum += move;
            move++;
        }
        move--;
        int delta = sum - target;
        //if delta is even, we can make one move negative so the sum will be target
        if(delta % 2 == 0) return move;
        //if delta is odd
        // we go one more step: move+1(odd), now delta become even
        // if move+1 is even, we need to go move+2 steps
        return move + 1 + move%2;
    }
};
