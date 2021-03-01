#include <bits/stdc++.h>
using namespace std ;

struct FenwickTree {
	vector<long long> values ;
public:
	FenwickTree(int n) {
		int sz = 1 ;
		while (sz <= n) sz *= 2 ;
		values.assign(sz+1, 0LL) ;
	}

	FenwickTree(vector<int>& a) {
		int sz = 1 ;
		while (sz <= a.size()) sz *= 2 ;
		values.assign(sz+1, 0) ;

		for (int i = 0; i < a.size(); ++i) {
			values[i+1] = a[i] ;
		}

		for (int i = 1; i <= a.size(); ++i) {
			values[i + LSB(i)] += values[i] ;
		}
	}

	//this function returns the position of first occurence of
	// the bit 1 from the left. It actually returns 2^i.
	inline int LSB(int x) {
		return x & -x ;
	}

	friend ostream& operator<<(ostream&, FenwickTree&) ;
	void add(int index, int value) ;
	long long range_sum(int index) ;
};

long long FenwickTree::range_sum(int index) {
	long long ans = 0 ;
	++index ;
	while (index > 0) {
		ans += values[index] ;
		index -= LSB(index) ;
	}
	return ans ;
}

void FenwickTree::add(int index, int value) {
	++index ;
	while (index < values.size()) {
		values[index] += value ;
		index += LSB(index) ;	
	}
}

ostream& operator<<(ostream& os, FenwickTree& ft) {
	for (int i = 1; i < ft.values.size(); ++i) {
		os << ft.values[i] << ", " ;
	}
	os << '\n' ;
}

int main() {
	int n, q ;
	cin >> n >> q ;

	vector<int> a(n) ;
	for (int& x : a) cin >> x ;

	FenwickTree ft(a) ;

	while (q--) {
		int op, l, r ;
		cin >> op >> l >> r ;
		if (op == 1) {
			ft.add(l, -a[l]) ;
			a[l] = r ;
			ft.add(l, a[l]) ;
		} else {
			long long left = ft.range_sum(l-1) ;
			long long right = ft.range_sum(r-1) ;

			cout << (right - left) << '\n' ;
		}
	}
}
