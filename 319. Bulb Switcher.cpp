//TLE
//31 / 35 test cases passed.
class Solution {
public:
    int bulbSwitch(int n) {
        if(n == 1) return 1;
        
        vector<bool> state(n, true);
        for(int t = 2; t <= n; t++){
            for(int i = t-1; i < n; i += t){
                // cout << state[i] << " " << (~state[i]) << " " << !state[i] << endl;
                //~: bitwise complement, !: not
                //~1 -> -2, !1 -> 0, so we should use "!" here
                state[i] = !state[i];
            }
        }
        
        // for(int i = 0; i < n; i++){
        //     cout << state[i] << " ";
        // }
        // cout << endl;
        
        return accumulate(state.begin(), state.end(), 0);
    }
};

//count divisor
//TLE
//30 / 35 test cases passed.
class Solution {
public:
    vector<int> divisorCount;
    
    int getDivisorCount(int n){
        if(divisorCount[n] == 0){
            int count = 0; //1
            double sqrt_n = sqrt(n);
            
            for(int i = 1; i <= sqrt_n; i++){
                if(n % i == 0){
                    if(i == sqrt_n) count++;
                    else count += 2;
                }
            }
            
            divisorCount[n] = count;
        }
        return divisorCount[n];
    };
    
    int bulbSwitch(int n) {
        //sum of divisor count from 1 to n
        divisorCount = vector<int>(n+1, 0);
        int ans = 0;
        
        for(int i = 1; i <= n; i++){
            int count = getDivisorCount(i);
            // cout << i << " " << count << endl;
            if(count % 2 == 1){
                ans++;
            }
        }
        
        return ans;
    }
};

//Count Divisors of n in O(n^1/3)
//TLE
//27 / 35 test cases passed.
//https://www.geeksforgeeks.org/count-divisors-n-on13/
class Solution {
public:
    vector<int> primes;
    vector<int> divisorCount;
    
    void sieveOfEratosthenes(int n, vector<int>& primes){
        vector<bool> isPrime = vector<bool>(n+1, true);
        // vector<bool> isPrimeSquare = vector<bool>((long long)n*n+1, false);
        
        //isPrime should be initialized as false
        //isPrimeSquare should be initialized as true
        isPrime[1] = false;
        
        //mark prime's multiples as non-prime
        for(int p = 2; p * p <= n; p++){
            if(isPrime[p]){
                //start from current prime's two times!
                for(int i = p*2; i <= n; i+=p){
                    isPrime[i] = false;
                }
            }
        }
        
        for(int p = 2; p <= n; p++){
            if(isPrime[p]){
                // cout << p << " ";
                // isPrimeSquare[p*p] = true;
                primes.push_back(p);
            }
        }
        // cout << endl;
    }
    
    int getDivisorCount(int n){
        if(n == 1) return 1;
        if(divisorCount[n] != 0) return divisorCount[n];
        
        int org_n = n;
        
        //split n into x*y
        
        int count = 1;
        /*
        counting factors of x
        if x = p^m + q^n, 
        then divisor count of x is (m+1)*(n+1)
        */
        for(int i = 0; pow(primes[i], 3) <= n; i++){
            int pow_i = 1;
            while(n % primes[i] == 0){
                n /= primes[i];
                pow_i++;
            }
            //now pow(primes[i], pow_i-1) becomes n
            
            count *= pow_i;
        }
        
        // cout << "n: " << org_n << ". x: " << org_n/n << ", y: " << n << endl;
        
        //counting factors of y
        
        if(find(primes.begin(), primes.end(), n) != primes.end()){
            //y is prime
            count *= 2;
        }else if(n/sqrt(n) == sqrt(n) && find(primes.begin(), primes.end(), sqrt(n)) != primes.end()){
            //y is a prime's square
            count *= 3;
        }else if(n != 1){
            //y is the product of two distinct prime numbers
            count *= 4;
        }
        
        divisorCount[n] = count;
        
        return count;
    };
    
    int bulbSwitch(int n) {
        //sum of divisor count from 1 to n
        divisorCount = vector<int>(n+1, 0);
        
        sieveOfEratosthenes(n, primes);
        
        int ans = 0;
        
        for(int i = 1; i <= n; i++){
            int count = getDivisorCount(i);
            // cout << i << " " << count << endl;
            if(count % 2 == 1){
                ans++;
            }
        }
        
        return ans;
    }
};
