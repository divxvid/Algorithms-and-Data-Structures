#include <bits/stdc++.h>
using namespace std ;

struct RabinKarp {
    //ASSUMING ALL CHARS ARE LOWERCASE ENGLISH
    const char base_char = 'a' ; //change of digits or upper case
    const int MOD = int(1e9) + 7 ;
    const int PRIME = 17 ;

    int find_first(string text, string pattern) {
        const int n = text.length() ;
        const int m = pattern.length() ;

        if (m == 0)
        	return 0 ;

        long long text_hash = 0 ;
        long long pattern_hash = 0 ;
        long long P = 1 ;
        long long D = 1 ;

        for (int i = 0; i < m; ++i) {
            text_hash = (text_hash + (text[i]-base_char+1)*P) % MOD ;
            pattern_hash = (pattern_hash + (pattern[i]-base_char+1)*P) % MOD ;
            P = (P * PRIME) % MOD ;
        }

        //NOTE : IF YOU GET WA, do pattern check as well : pattern == text.substr(i, m)
        if (text_hash == pattern_hash) {
            return 0 ;
        }

        for (int i = 1; i+m <= n; ++i) {
            text_hash = (text_hash - (text[i-1]-base_char+1)*D) % MOD ;
            if (text_hash < 0) text_hash += MOD ;
            text_hash = (text_hash + (text[i+m-1]-base_char+1)*P) % MOD ;
            pattern_hash = (pattern_hash * PRIME) % MOD ;
            D = (D * PRIME) % MOD ;
            P = (P * PRIME) % MOD ;
            //NOTE : IF YOU GET WA, do pattern check as well : pattern == text.substr(i, m)
            if (text_hash == pattern_hash) {
                return i ;
            }
        }

        return -1 ;
	}

    vector<int> find_all(string text, string pattern) {
        const int n = text.length() ;
        const int m = pattern.length() ;

        if (m == 0)
            return {} ;

        long long text_hash = 0 ;
        long long pattern_hash = 0 ;
        long long P = 1 ;
        long long D = 1 ;

        for (int i = 0; i < m; ++i) {
            text_hash = (text_hash + (text[i]-base_char+1)*P) % MOD ;
            pattern_hash = (pattern_hash + (pattern[i]-base_char+1)*P) % MOD ;
            P = (P * PRIME) % MOD ;
        }

        vector<int> pos ;
        //NOTE : IF YOU GET WA, do pattern check as well : pattern == text.substr(i, m)
        if (text_hash == pattern_hash) {
            pos.push_back(0) ;
        }

        for (int i = 1; i+m <= n; ++i) {
            text_hash = (text_hash - (text[i-1]-base_char+1)*D) % MOD ;
            if (text_hash < 0) text_hash += MOD ;
            text_hash = (text_hash + (text[i+m-1]-base_char+1)*P) % MOD ;
            pattern_hash = (pattern_hash * PRIME) % MOD ;
            D = (D * PRIME) % MOD ;
            P = (P * PRIME) % MOD ;
            //NOTE : IF YOU GET WA, do pattern check as well : pattern == text.substr(i, m)
            if (text_hash == pattern_hash) {
                pos.push_back(i) ;
            }
        }

        return pos ;
    }
};

int main() {
    string s, t ;
    cin >> s >> t ;

    RabinKarp rk ;
    cout << rk.find_first(s, t) << '\n' ;
    vector<int> v = rk.find_all(s, t) ;
    for (int x : v)
        cout << x << '\n' ;

    return 0 ;
}