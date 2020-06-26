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

//conversion
//Runtime: 8 ms, faster than 52.57% of C++ online submissions for Soup Servings.
//Memory Usage: 14.5 MB, less than 13.63% of C++ online submissions for Soup Servings.
class Solution {
public:
    vector<vector<double>> memo;
    
    double f(int NA, int NB){
        if(NA <= 0 && NB <= 0) return 0.5;
        if(NA <= 0) return 1.0;
        if(NB <= 0) return 0.0;
        if(memo[NA][NB] > 0) return memo[NA][NB];
        return memo[NA][NB] = 0.25*(f(NA-4,NB)+f(NA-3,NB-1)+f(NA-2,NB-2)+f(NA-1,NB-3));
    };
    
    double soupServings(int N) {
        if(N > 4800) return 1.0;
        memo = vector<vector<double>>(200, vector<double>(200));
        //conversion from 25's multiple to the number of spoons
        return f(ceil((double)N/25), ceil((double)N/25));
    }
};

//conversion, using array
//https://leetcode.com/problems/soup-servings/discuss/121711/C%2B%2BJavaPython-When-N-greater-4800-just-return-1
//Runtime: 4 ms, faster than 69.96% of C++ online submissions for Soup Servings.
//Memory Usage: 6.2 MB, less than 95.45% of C++ online submissions for Soup Servings.
class Solution {
public:
    double memo[200][200];
    
    double f(int NA, int NB){
        if(NA <= 0 && NB <= 0) return 0.5;
        if(NA <= 0) return 1.0;
        if(NB <= 0) return 0.0;
        if(memo[NA][NB] > 0) return memo[NA][NB];
        return memo[NA][NB] = 0.25*(f(NA-4,NB)+f(NA-3,NB-1)+f(NA-2,NB-2)+f(NA-1,NB-3));
    };
    
    double soupServings(int N) {
        if(N > 4800) return 1.0;
        //conversion from 25's multiple to the number of spoons
        return f(ceil((double)N/25), ceil((double)N/25));
    }
};
