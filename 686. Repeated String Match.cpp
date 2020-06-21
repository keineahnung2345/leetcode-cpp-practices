//failed
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
//         if(A.find(B) != string::npos){
//             /**
//             A: "aa"
//             B: "a"
//             **/
//             return 1;
//         }
//         int prev_s = 0, s = 0;
//         int count = 0;
        
//         while((s = B.find(A, prev_s)) != string::npos){
//             cout << "prev_s: " << prev_s << ", s: " << s << endl;
//             if(prev_s == 0){
//                 //the first occurent of A in B should at 0 ~ A.size()-1
//                 if(s >= A.size()) return -1;
//                 //B[0:s] should be a substring of A
//                 if(A.find(B.substr(0, s)) == string::npos){
//                     return -1;
//                 }else if(s != 0){
//                     count++;
//                 }
//                 count++;
//                 cout << "first" << endl;
//             // }else if(s + A.size()*2 > B.size()){
//             //     //last occurence
//             //     //the last part of B should be a substring of A
//             //     if(A.find(B.substr(s+A.size(), A.size())) == string::npos) return -1;
//             //     count++;
//             //     cout << "last" << endl;
//             }else{
//                 //middle occurence
//                 //the 's' should be the same as the guessed 'prev_s'
//                 if(prev_s != s) return -1;
//                 count++;
//                 // cout << "middle" << endl;
//             }
//             cout << "count: " << count << endl;
//             //update pointer
//             //guess that the next occurence of A is at (s + A.size())
//             prev_s = s + A.size();
//         }
        
//         cout << "prev_s: " << prev_s << ", s: " << s << endl;
//         if(prev_s == 0){
//             /**
//             A: "abcd"
//             B: "cda"
//             **/
//             //not found any A in B
//             cout << "prev_s== 0" << endl;
//             cout << A.substr(0, 1) << endl;
//             if((s = B.find(A.substr(0, 1))) != string::npos){
//                 cout << B.substr(s, A.size()) << endl;
//                 if(A.find(B.substr(s, A.size())) != string::npos){
//                     count++;
//                 }
//             }
            
//             string sub_B = (s != string::npos)?B.substr(0, s):B;
//             cout << sub_B << endl;
//             if(A.find(sub_B) != string::npos){
//                 count++;
//             }
            
//             return count;
//         }
//         //if the last occurence of A in B is intact, 
//         // then prev_s should be equal to B.size()
//         if(prev_s != B.size()){
//             // prev_s-1+A.size()
//             //last occurence
//             //the last part of B should be a substring of A
//             if(A.find(B.substr(prev_s, A.size())) == string::npos) return -1;
//             count++;
//             cout << "last" << endl;
//             cout << "count: " << count << endl;
//         }
        
        // int count = 1;
        // string dup_A = A;
        // while(dup_A.find(B) == string::npos && dup_A.size() <= B.size()*2){
        //     dup_A += A;
        //     count++;
        // }
        // if(dup_A.size() > B.size()*2) return -1;
        // return count;
    }
};

//Approach #1: Ad-Hoc [Accepted]
//Runtime: 16 ms, faster than 85.90% of C++ online submissions for Repeated String Match.
//Memory Usage: 9.1 MB, less than 82.08% of C++ online submissions for Repeated String Match.
//time: O(N * (M+N)), M, N is the length of A and B respectively. M+N is the length of dup_A. 
// We compare dup_A with B, so the time used is the product of their lengths.
//space: O(M+N), used by dup_A
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        string dup_A = A;
        for(; dup_A.size() < B.size(); dup_A += A){}
        if(dup_A.find(B) != string::npos) return dup_A.size()/A.size();
        dup_A += A;
        if(dup_A.find(B) != string::npos) return dup_A.size()/A.size();
        return -1;
    }
};

//Approach #2: Rabin-Karp (Rolling Hash) [Accepted]
//Runtime: 8 ms, faster than 97.22% of C++ online submissions for Repeated String Match.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Repeated String Match.
//time: O(M+N), space: O(1)
class Solution {
public:
    // To compute x^y under modulo m 
    int power(int x, unsigned int y, unsigned int m){ 
        if (y == 0) 
            return 1; 
        long long p = power(x, y/2, m) % m; 
        p = (p * p) % m; 

        return (y%2 == 0)? p : (x * p) % m; 
    };

    // Function to return gcd of a and b 
    int gcd(int a, int b){ 
        if (a == 0) 
            return b; 
        return gcd(b%a, a); 
    };

    // Function to find modular inverse of a under modulo m 
    // Assumption: m is prime 
    int modInverse(int a, int m){ 
        int g = gcd(a, m); 
        if (g != 1){
            return -1;
        }else{ 
            // If a and m are relatively prime, then modulo inverse 
            // is a^(m-2) mode m 
            return power(a, m-2, m);
        } 
    };
    
    bool check(int index, string A, string B){
        for(int i = 0; i < B.size(); i++) {
            if(A[(i+index) % A.size()] != B[i]){
                return false;
            }
        }
        return true;
    }
    int repeatedStringMatch(string A, string B) {
        /*
        the expanded A's length should be >= B's length
        A.size() * q = B.size() + A.size() -1,
        which is just larger than B.size(),
        because (B.size() + A.size() -1) - A.size() =
        B.size() - 1, this is smaller than B.size()
        */
        int q = (B.size() - 1)/A.size() + 1;
        //p: just a prime number
        int p = 113, MOD = 1000000007;
        int pInv = modInverse(p, MOD);
        
        /*
        hash(S) = p^0 * S[0] + p^1 * S[1] + ... + p^(n-1) * S[n-1]
        */
        long long bHash = 0, power = 1;
        for(int i = 0; i < B.size(); i++){
            bHash += power * int(B[i]);
            bHash %= MOD;
            power = (power * p) % MOD;
        }
        
        /*
        first expand string A to B.size()
        aHash: the hash of expanded string A
        */
        long long aHash = 0;
        power = 1;
        for(int i = 0; i < B.size(); i++){
            aHash += power * int(A[i % A.size()]);
            aHash %= MOD;
            power = (power * p) % MOD;
        }
        
        //now power = p^(n-1) % MOD
        
        if(aHash == bHash && check(0, A, B)) return q;
        power = (power * pInv) % MOD;
        //now power = p^(n-2) % MOD = p^(-1) % MOD(by Fermat's Little Theorem)
        
        for(int i = B.size(); i < (q + 1) * A.size(); i++){
            /*
            in each iteration, pop a char from front and append a char to tail
            the (string represented by aHash)'s size remains B.size()
            
            S: the expanded string A
            x: the char to be appended
            n: the size of the expanded string A, here it's B.size()
            p: the prime number
            hash(S[1:] + x) = [hash(S) - S[0]]/p + p^(n-1)*x
            */
            //-S[0]
            aHash -= int(A[(i - B.size()) % A.size()]);
            //divided by p
            aHash *= pInv;
            //power: p^(n-1)
            //A[i % A.size()]: the appended char
            aHash += power * int(A[i % A.size()]);
            aHash %= MOD;
            /*
            i - B.size() + 1: the first char in current string 
            represented by aHash is A[(i - B.size() + 1)%A.size()]
            */
            if(aHash == bHash && check(i - B.size() + 1, A, B)){
                return i < q * A.size() ? q : q+1;
            }
        }
        return -1;
    }
};
