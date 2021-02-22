/*
 * Refer to Codeforces EDU Segment Tree part 2A.
 */


#include <bits/stdc++.h>
using namespace std ;

struct SegmentTree {

	SegmentTree *left, *right ;
    long long max_segment_sum ;
	long long total_segment_sum ;
	long long max_prefix_sum ;
	long long max_suffix_sum ;

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

	void recalculate_values() {
		this->max_segment_sum = max({left->max_segment_sum,
				right->max_segment_sum,
				left->max_suffix_sum + right->max_prefix_sum}) ;

		this->max_prefix_sum = max(left->max_prefix_sum, left->total_segment_sum + right->max_prefix_sum);
		this->max_suffix_sum = max(right->max_suffix_sum, right->total_segment_sum + left->max_suffix_sum);
		this->total_segment_sum = left->total_segment_sum + right->total_segment_sum ;
	}

	void assign_value(int value) {
		this->max_segment_sum = value ;
		this->max_prefix_sum = value ;
		this->max_suffix_sum = value ;
		this->total_segment_sum = value ;
	}

    void buildTree(vector<int>& a, int l, int r) {
		left_limit = l ;
		right_limit = r ;
        if (l == r) {
			this->assign_value(a[l]) ;
            left = right = nullptr ;
            return ;
        }

        int mid = (l + r + 1) / 2 ;
        left = new SegmentTree() ;
        left->buildTree(a, l, mid-1) ;
        right = new SegmentTree() ;
        right->buildTree(a, mid, r) ;

		this->recalculate_values() ;
    }

	long long maximal_sum_subsegment() {
		return max(0LL, this->max_segment_sum) ;
	}

	void update(int index, int value) {
		if (left_limit == right_limit && left_limit == index) {
			this->assign_value(value) ;
			return ;
		}

		int mid = (this->left_limit + this->right_limit + 1) / 2;
		if (index < mid) {
			left->update(index, value) ;
		} else {
			right->update(index, value) ;
		}

		this->recalculate_values() ;
	}
};

int main() {
	int n, q ;
	cin >> n >> q ;

	vector<int> a(n) ;
	for (int& x : a) cin >> x ;

	SegmentTree st(a) ;
	
	cout << st.maximal_sum_subsegment() << '\n' ;
	while (q--) {
		int i, v ;
		cin >> i >> v ;

		st.update(i, v) ;
		cout << st.maximal_sum_subsegment() << '\n' ;
	}
}
