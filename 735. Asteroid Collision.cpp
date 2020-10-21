//stack
//Runtime: 1072 ms, faster than 5.51% of C++ online submissions for Asteroid Collision.
//Memory Usage: 21 MB, less than 95.21% of C++ online submissions for Asteroid Collision.
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> stk;
        
        bool changed = false;
        
        do{
            changed = false;
            for(int& cur : asteroids){
                if(!stk.empty() && stk.top() > 0 && cur < 0){
                    int prev = stk.top();
                    if(abs(prev) > abs(cur)){
                        //do nothing
                    }else if(abs(prev) == abs(cur)){
                        stk.pop();
                    }else{
                        //abs(prev) < abs(cur)
                        stk.pop();
                        stk.push(cur);
                    }
                }else{
                    stk.push(cur);
                }
            }

            if(stk.size() < asteroids.size()){
                changed = true;
            }
            
            asteroids.clear();

            while(!stk.empty()){
                asteroids.insert(asteroids.begin(), stk.top());
                stk.pop();
            }
        }while(changed);
        
        return asteroids;
    }
};

//official sol
//stack, keep going left until exploded
//Runtime: 20 ms, faster than 95.41% of C++ online submissions for Asteroid Collision.
//Memory Usage: 18.3 MB, less than 95.21% of C++ online submissions for Asteroid Collision.
//time: O(N), space: O(N)
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> stk;
        
        for(int& cur : asteroids){
            bool exploded = false;
            while(!stk.empty() && stk.top() > 0 && cur < 0){
                int prev = stk.top();
                if(abs(prev) > abs(cur)){
                    //do nothing
                    exploded = true;
                    break;
                }else if(abs(prev) == abs(cur)){
                    stk.pop();
                    exploded = true;
                    break;
                }else{
                    //abs(prev) < abs(cur)
                    stk.pop();
                    //cur keeps going left
                }
            }

            if(!exploded){
                stk.push(cur);
            }
        }

        asteroids.clear();

        while(!stk.empty()){
            asteroids.insert(asteroids.begin(), stk.top());
            stk.pop();
        }
        
        return asteroids;
    }
};

