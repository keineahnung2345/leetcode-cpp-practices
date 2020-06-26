//Runtime Error: stack-overflow on address
//20 / 41 test cases passed.
class Solution {
public:
    vector<int> serveAs;
    unordered_map<string, vector<double>> memo;
    
    vector<double> soupServings(int NA, int NB){
        /*
        prob[0]: A will be empty first
        prob[1]: A and B become empty at the same time
        */
        string key = to_string(NA) + "_" + to_string(NB);
        if(memo.find(key) != memo.end()){
            return memo[key];
        }
        
        vector<double> prob(2);
        
        for(int serveA : serveAs){
            int serveB = 100 - serveA;
            if(NA <= serveA && NB <= serveB){
                prob[1] += 0.25;
            }else if(NA <= serveA){
                prob[0] += 0.25;
            }else if(NB <= serveB){
                //pass
            }else{
                vector<double> subprob = soupServings(NA-serveA, NB-serveB);
                prob[0] += 0.25 * subprob[0];
                prob[1] += 0.25 * subprob[1];
            }
        }
        
        return memo[key] = prob;
    };
    
    double soupServings(int N) {
        serveAs = {100, 75, 50, 25};
        vector<double> prob = soupServings(N, N);
        return prob[0] + prob[1] * 0.5;
    }
};

//return 1 when N >= 4800
/*
Answers within 10^-5 of the true value will be accepted as correct.
When N = 4800, the result = 0.999994994426
*/
//https://leetcode.com/problems/soup-servings/discuss/121711/C%2B%2BJavaPython-When-N-greater-4800-just-return-1
//Runtime: 32 ms, faster than 15.42% of C++ online submissions for Soup Servings.
//Memory Usage: 8.9 MB, less than 41.48% of C++ online submissions for Soup Servings.
class Solution {
public:
    vector<int> serveAs;
    unordered_map<string, vector<double>> memo;
    
    vector<double> soupServings(int NA, int NB){
        /*
        prob[0]: A will be empty first
        prob[1]: A and B become empty at the same time
        */
        if(NA >= 4800) return {1.0, 0.0};
        string key = to_string(NA) + "_" + to_string(NB);
        if(memo.find(key) != memo.end()){
            return memo[key];
        }
        
        vector<double> prob(2);
        
        for(int serveA : serveAs){
            int serveB = 100 - serveA;
            if(NA <= serveA && NB <= serveB){
                prob[1] += 0.25;
            }else if(NA <= serveA){
                prob[0] += 0.25;
            }else if(NB <= serveB){
                //pass
            }else{
                vector<double> subprob = soupServings(NA-serveA, NB-serveB);
                prob[0] += 0.25 * subprob[0];
                prob[1] += 0.25 * subprob[1];
            }
        }
        
        return memo[key] = prob;
    };
    
    double soupServings(int N) {
        serveAs = {100, 75, 50, 25};
        vector<double> prob = soupServings(N, N);
        return prob[0] + prob[1] * 0.5;
    }
};
