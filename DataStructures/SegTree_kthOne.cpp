/*
 * Refer to Codeforces EDU Segment Tree part 2B.
 */


#include <bits/stdc++.h>
using namespace std ;

struct SegmentTree {
    SegmentTree *left, *right ;
    long long value ;
    int left_limit, right_limit ;

    SegmentTree() {}

    SegmentTree(vector<int>& a) {
        buildTree(a, 0, a.size()-1) ;
    }

    ~SegmentTree() {
        if (left)
            delete left ;
        if (right)
            delete right ;
    }

    void buildTree(vector<int>& a, int l, int r) {
        left_limit = l ;
        right_limit = r ;
        if (l == r) {
            value = a[l] ;
            left = right = nullptr ;
            return ;
        }

        int mid = (l + r + 1) / 2 ;
        left = new SegmentTree() ;
        left->buildTree(a, l, mid-1) ;
        right = new SegmentTree() ;
        right->buildTree(a, mid, r) ;
        this->value = left->value + right->value ;
    }

    long long kth_one(int k) {
        if (this->left_limit == this->right_limit && this->value == 1) {
            return this->left_limit ;
        }
        if (k < left->value) {
            //present in the left subtree.
            return left->kth_one(k) ;
        }
        k -= left->value ;
        return right->kth_one(k) ;
    }

    void update(int index) {
        if (left_limit == right_limit && left_limit == index) {
            this->value ^= 1 ;
            return ;
        }

        int mid = (this->left_limit + this->right_limit + 1) / 2;
        if (index < mid) {
            left->update(index) ;
        } else {
            right->update(index) ;
        }

        this->value = left->value + right->value ;
    }
};

int main() {
    int n, q ;
    cin >> n >> q ;

    vector<int> a(n) ;
    for (int& x : a) cin >> x ;

    SegmentTree st(a) ;
    while (q--) {
        int op, x ;
        cin >> op >> x ;

        if (op == 1) {
            st.update(x) ;
        } else {
            cout << st.kth_one(x) << '\n' ;
        }
    }
}
