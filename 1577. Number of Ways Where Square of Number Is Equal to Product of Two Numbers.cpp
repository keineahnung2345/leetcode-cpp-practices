//Two pointer
//note: if without sorting and using two pointer technique, the O(N^3) algorithm gives TLE
//Runtime: 56 ms, faster than 100.00% of C++ online submissions for Number of Ways Where Square of Number Is Equal to Product of Two Numbers.
//Memory Usage: 11.6 MB, less than 100.00% of C++ online submissions for Number of Ways Where Square of Number Is Equal to Product of Two Numbers.
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int ans = 0;
        
        map<int, int> counter1, counter2;
        
        for(int i = 0; i < n1; ++i){
            ++counter1[nums1[i]];
        }
        
        for(int j = 0; j < n2; ++j){
            ++counter2[nums2[j]];
        }
        
        for(auto it1 = counter1.begin(); it1 != counter1.end(); ++it1){
            long long a = it1->first;
            long long acount = it1->second;
            auto it2 = counter2.begin();
            auto it3 = counter2.rbegin();
            for(; it2 != counter2.end() && it3 != counter2.rend(); ){
                long long b = it2->first;
                long long bcount = it2->second;
                long long c = it3->first;
                long long ccount = it3->second;
                if(c < b) break;
                
                // cout << a << ", " << b << ", " << c << endl;
                
                if(a*a > b*c){
                    ++it2;
                }else if(a*a < b*c){
                    ++it3;
                }else if(a*a == b*c){
                    if(b == c){
                        ans += acount * (bcount * (bcount-1) >> 1);
                    }else{
                        ans += acount * bcount * ccount;
                    }
                    // cout << "ans: " << ans << endl;
                    // break;
                    ++it2;
                    ++it3;
                }
            }
        }
        
        swap(counter1, counter2);
        for(auto it1 = counter1.begin(); it1 != counter1.end(); ++it1){
            long long a = it1->first;
            long long acount = it1->second;
            auto it2 = counter2.begin();
            auto it3 = counter2.rbegin();
            for(; it2 != counter2.end() && it3 != counter2.rend(); ){
                long long b = it2->first;
                long long bcount = it2->second;
                long long c = it3->first;
                long long ccount = it3->second;
                if(c < b) break;
                
                // cout << a << ", " << b << ", " << c << endl;
                
                if(a*a > b*c){
                    ++it2;
                }else if(a*a < b*c){
                    ++it3;
                }else if(a*a == b*c){
                    if(b == c){
                        ans += acount * (bcount * (bcount-1) >> 1);
                    }else{
                        ans += acount * bcount * ccount;
                    }
                    // cout << "ans: " << ans << endl;
                    ++it2;
                    ++it3;
                }
            }
        }
        
        return ans;
    }
};
