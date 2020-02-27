//Runtime: 4 ms, faster than 54.69% of C++ online submissions for Prime Arrangements.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for Prime Arrangements.
class Solution {
public:
    int modulo = pow(10, 9) + 7;
    
    set<int> primes = {2};
    
    long int factorial(int n){
        long int ans = 1;
        for(int i = n; i >= 1; i--){
            ans *= i;
            ans = ans % modulo;
        }
        return ans;
    }
    
    int numPrimeArrangements(int n) {
        for(int i = 3; i <= n; i++){
            bool isPrime = true;
            for(int prime : primes){
                if(i%prime == 0){
                    isPrime = false;
                    break;
                }
            }
            if(isPrime) primes.insert(i);
        }
        
        int pcount = primes.size(), npcount = n - pcount;
        // cout << pcount << ", " << npcount << endl;
        return (factorial(pcount) * factorial(npcount)) % modulo;
    }
};
