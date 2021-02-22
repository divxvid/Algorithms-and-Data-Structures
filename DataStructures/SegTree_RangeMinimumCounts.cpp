#include <bits/stdc++.h>
using namespace std ;

struct SegmentTree {
    SegmentTree* left ;
	SegmentTree* right ;
    long long value ;
	int count ; 
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
			count = 1 ;
            return ;
        }

        int mid = (l + r + 1) / 2 ;
        left = new SegmentTree() ;
        left->buildTree(a, l, mid-1) ;
        right = new SegmentTree() ;
        right->buildTree(a, mid, r) ;
        this->value = min(left->value, right->value) ;
		this->count = 0 ;
		if (this->value == left->value)
			this->count += left->count ;
		if (this->value == right->value)
			this->count += right->count ;
    }

	pair<long long, int> range_min(int l, int r) {
		if (this->left_limit > r || this->right_limit < l) {
			// this node is out of bound
			return {INT_MAX, 0} ; // TODO: change for other utilities
		}

		if (this->left_limit >= l && this->right_limit <= r) {
			//this node lies completely inside the interval
			return {this->value, this->count} ;
		}

		pair<long long, int> l_ret =  left->range_min(l, r) ;
		pair<long long, int> r_ret =  right->range_min(l, r) ;

		if (l_ret.first < r_ret.first) {
			return l_ret ;
		} else if(r_ret.first < l_ret.first) {
			return r_ret ;
		} else {
			return {l_ret.first, l_ret.second + r_ret.second} ;
		}
	}

	void update(int index, int value) {
		if (left_limit == right_limit && left_limit == index) {
			this->value = value ;
			this->count = 1 ;
			return ;
		}

		int mid = (this->left_limit + this->right_limit + 1) / 2;
		if (index < mid) {
			left->update(index, value) ;
		} else {
			right->update(index, value) ;
		}

        this->value = min(left->value, right->value) ;
		this->count = 0 ;
		if (this->value == left->value)
			this->count += left->count ;
		if (this->value == right->value)
			this->count += right->count ;
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
		cin >> op >> l >> r ;

		if (op == 1) {
			st.update(l, r) ;
		} else {
			pair<long long, int> ret = st.range_min(l, r-1) ;
			cout << ret.first << ' ' << ret.second << '\n' ;
		}
	}
}
