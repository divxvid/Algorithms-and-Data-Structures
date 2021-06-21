#include <bits/stdc++.h>
using namespace std ;

struct SuffixArray {
    string s ;
    int size ;
    vector<int> ranks ;
    vector<int> suffix_array ;
    SuffixArray(string other) {
        s = other ;
        s.push_back('$') ; //a sentinel character that has ascii value lower than any other string
        size = s.length() ;
        ranks.resize(size) ;
        suffix_array.resize(size) ;
        build_ranks() ;
        for (int i = 0; i < size; ++i) {
            suffix_array[ranks[i]] = i ;
        }
    }
    
    void build_ranks() {
        //initial calculation for the base case i.e. substrings of length 1.
        vector<pair<char, int>> substrs ;
        for (int i = 0; i < size; ++i) {
            substrs.emplace_back(s[i], i) ;
        }
        sort(substrs.begin(), substrs.end()) ;
        
        // Assigning ranks now
        int rnk = 0 ;
        ranks[substrs[0].second] = rnk ;
        for (int i = 1; i < size; ++i) {
            if (substrs[i].first == substrs[i-1].first) {
                ranks[substrs[i].second] = rnk ;
            } else {
                ++rnk ;
                ranks[substrs[i].second] = rnk ;
            }
        }

        for (int jump = 1; jump < size; jump *= 2) {
            vector<pair<pair<int, int>, int>> rank_values ;
            for (int start = 0; start < size; ++start) {
                int fst = start ;
                int snd = (start + jump) % size ;
                rank_values.emplace_back(make_pair(ranks[fst], ranks[snd]), start) ;
            }

            //sorting these rank_values !
            sort(rank_values.begin(), rank_values.end()) ;

            //reassigning ranks
            int rnk = 0 ;
            ranks[rank_values[0].second] = rnk ;
            for (int i = 1; i < size; ++i) {
                if (rank_values[i].first != rank_values[i-1].first) {
                    ++rnk ;
                }
                ranks[rank_values[i].second] = rnk ;
            }
        }
    }
} ;

int main() {
    string s ;
    cin >> s ;

    SuffixArray sa(s) ;

    for (int x : sa.suffix_array)
        cout << x << ' ' ;
    cout << '\n' ;
}
