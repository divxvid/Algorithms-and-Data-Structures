#include <bits/stdc++.h>
using namespace std ;

template <typename T>
struct SparseTable {
	int size ;
	int rows ;
	T** table ;
	int* log ;

	SparseTable(vector<T>& a) {
		size = a.size() ;
		rows = 0 ;
		while ((1 << rows) < size) ++rows ;
		
		table = new T*[rows] ;
		table[0] = new T[size] ; //first row

		for (int i = 0; i < size; ++i) {
			table[0][i] = a[i] ;
		}

		int last_size = size ;
		for (int i = 1; i < rows; ++i) {
			const int skip = (1 << (i-1)) ;
			table[i] = new T[size] ;
			for (int j = 0; j+skip < last_size; ++j) {
				table[i][j] = min(table[i-1][j], table[i-1][j+skip]) ; // CHANGE HERE FOR OTHERS
			}
			last_size = size - skip ;
		}

		//precomputing the floor(log) value
		log = new int[size+5] ;
		log[1] = 0 ;
		for (int i = 2; i <= size; ++i) {
			log[i] = log[i/2] + 1 ;
		}
	}

	~SparseTable() {
		for (int i = 0; i < rows; ++i)
			delete[] table[i] ;
		delete[] table ;
		delete[] log ;
	}

	void show() {
		int last_size = size ;
		for (int i = 0; i < rows; ++i) {
			int skip = (i == 0 ? 0 : (1 << (i-1))) ;
			for (int j = 0; j+skip < last_size; ++j) {
				cout << table[i][j] << ' ' ;	
			}
			cout << '\n' ;
			last_size = size - skip ;
		}
	}

	//Note : INCLUSIVE RANGE
	T query(int L, int R) {
		int seg_len = R - L + 1 ;
		int row_idx = log[seg_len] ;
		return min(table[row_idx][L], table[row_idx][L+seg_len-row_idx-1]);
	}
};

int main() {
	vector<int> a = {1, 5, 7, 2, 6, 6, 3, 1, 5, 4, 12, 6, 4} ;
	SparseTable<int> st(a) ;

	st.show() ;

	cout << st.query(0, 3) << '\n' ;
	cout << st.query(1, 3) << '\n' ;
	cout << st.query(2, 7) << '\n' ;
	cout << st.query(4, 10) << '\n' ;
}
