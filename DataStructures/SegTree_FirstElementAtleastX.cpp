/*
 * Refer to Codeforces EDU Segment Tree part 2C and 2D
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
        this->value = max(left->value, right->value) ;
    }

    long long element_greater_than_x(int x, int lower_limit = 0) {
        if (this->value < x || this->right_limit < lower_limit)
            return -1 ;

        if (this->left_limit == this->right_limit) {
            return this->left_limit ;
        }

        long long res = left->element_greater_than_x(x, lower_limit) ;
        if (res != -1)
            return res ;
        return right->element_greater_than_x(x, lower_limit) ;
    }

    void update(int index, int value) {
        if (left_limit == right_limit && left_limit == index) {
            this->value = value ;
            return ;
        }

        int mid = (this->left_limit + this->right_limit + 1) / 2;
        if (index < mid) {
            left->update(index, value) ;
        } else {
            right->update(index, value) ;
        }

        this->value = max(left->value, right->value) ;
    }
};

int main() {
    int n, q ;
    cin >> n >> q ;

    vector<int> a(n) ;
    for (int& x : a) cin >> x ;

    SegmentTree st(a) ;
    while (q--) {
        int op, l, r ;
        cin >> op ;

        if (op == 1) {
            cin >> l >> r ;
            st.update(l, r) ;
        } else {
            //cin >> l ; // for 2C
            cin >> l >> r ;
            cout << st.element_greater_than_x(l, r) << '\n' ; //for 2D
            //cout << st.element_greater_than_x(l) << '\n' ; // for 2C
        }
    }
}
