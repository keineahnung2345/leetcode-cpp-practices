//adopted from https://leetcode.com/discuss/interview-question/124658/Design-a-URL-Shortener-(-TinyURL-)-System/
//Your runtime beats 99.35 % of cpp submissions.
class Solution {
public:
    map<string, int> longUrl2id;
    map<int, string> id2longUrl;
        
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        // Map to store 62 possible characters
        char map[] = "abcdefghijklmnopqrstuvwxyzABCDEF"
                     "GHIJKLMNOPQRSTUVWXYZ0123456789";
        
        string shorturl;
        int n;
        
        if(longUrl2id.find(longUrl)==longUrl2id.end()){
            n = longUrl2id.size();
            longUrl2id.insert(pair<string, int>(longUrl, n));
            id2longUrl.insert(pair<int, string>(n, longUrl));
        }else{
            n = longUrl2id[longUrl];
        }

        // Convert given integer id to a base 62 number
        while (n)
        {
            shorturl.push_back(map[n%62]);
            n = n/62;
        }

        // Reverse shortURL to complete base conversion
        reverse(shorturl.begin(), shorturl.end());

        return shorturl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int id = 0; // initialize result
  
        // A simple base conversion logic
        for (int i=0; i < shortUrl.length(); i++)
        {
            if ('a' <= shortUrl[i] && shortUrl[i] <= 'z')
              id = id*62 + shortUrl[i] - 'a';
            if ('A' <= shortUrl[i] && shortUrl[i] <= 'Z')
              id = id*62 + shortUrl[i] - 'A' + 26;
            if ('0' <= shortUrl[i] && shortUrl[i] <= '9')
              id = id*62 + shortUrl[i] - '0' + 52;
        }
        return id2longUrl[id];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
