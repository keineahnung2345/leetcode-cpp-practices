class Solution {
public:
    vector<string> tokens;
    vector<string> ones;
    vector<string> tens;
    vector<string> teens;
    
    template <typename Iter>
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        result.precision(2); //for floating point
        if (begin != end)
            result << *begin++;
        while (begin != end)
            //std::fixed : for floating point
            result << std::fixed << separator << *begin++;
        return result.str();
    }
    
    void numberToWords(int num, int exp) {
        //to solve 1000000
        if(num == 0 && exp > 0) return;
        
        if(num >= 100){
            tokens.push_back(ones[num/100]);
            tokens.push_back("Hundred");
            num %= 100;
        }
        
        if(num >= 11 && num <= 19){
            tokens.push_back(teens[num-11]);
            num = 0;
        }
        
        if(num >= 10){
            tokens.push_back(tens[num/10-1]);
            num %= 10;
        }
        
        if(num > 0){
            tokens.push_back(ones[num]);
        }else if(tokens.empty() && num == 0 && exp == 0){
            //add "Zero" only when there is no previous digits
            tokens.push_back(ones[0]);
        }
        
        if(!tokens.empty()){
            if(exp == 3){
                tokens.push_back("Thousand");
            }else if(exp == 6){
                tokens.push_back("Million");
            }else if(exp == 9){
                tokens.push_back("Billion");
            }
        }
    };
    
    string numberToWords(int num) {
        ones = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        tens = {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        teens = {"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        
        for(int exp = 9; exp >= 0; exp -= 3){
            // cout << "num: " << num << endl;
            numberToWords(num/pow(10,exp), exp);
            num %= (int)pow(10, exp);
        }
        
        return join(tokens.begin(), tokens.end(), " ");
    }
};
