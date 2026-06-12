#include <bits/stdc++.h>
using namespace std ;

struct SparseTable {
  int size;
  vector<vector<int>> table;

  //used for the fast O(1) query function
  vector<int> highest_pow2_layer;
  SparseTable(vector<int> v) {
    size = v.size();
    table.push_back(v); //layer 0 consist of the original vector
    for (int pow2 = 0, current_sz = size - (1 << pow2); current_sz > 0; ++pow2, current_sz -= (1 << pow2)) {
      int skip_length = (1 << pow2);

      vector<int> layer(current_sz);
      vector<int>& prev_layer = table.back();

      for (int i = 0; i < current_sz; ++i) {
        layer[i] = min(prev_layer[i], prev_layer[i + skip_length]);
      }

      table.push_back(layer); 
    }

    //pre-computing these values in O(N) for O(1) query function
    highest_pow2_layer.resize(size + 1);
    for (int start = 1, pow2 = 0; start <= size; ++pow2) {
      int limit = 1 << pow2;
      for (int off = 0; off < limit && (start + off) <= size; ++off) {
        highest_pow2_layer[start + off] = pow2;
      }
      start += limit;
    }
  }

  int query(int left, int right) {
    //we can make an interesting observation over the logn version that:
    //why don't we just use the greatest power of 2 for all the computation
    //
    //let's take logn example again:
    //lets say left = 1, right = 11 [inclusive]; seg_len = 11
    //highest power of 2 in 11 (0b1011) is 8, so we will use segments of length 8 only
    //so we will operate of layer 3 i.e. table[3].
    //so our query range becomes: [1, 8]; [2, 9]; [3, 10]; [4, 11];
    //
    //Now comes the interesting part:
    //since we know that the largest power of 2 is 8 in this case, we don't need any
    //intermediate segments i.e. [2, 9] and [3, 10] because first ([1, 8]) and
    //last([4, 11]) ranges cover the intermediate segments.
    //
    //1 2 3 4 5 6 7 8 9
    //  2 3 4 5 6 7 8 9 10
    //    3 4 5 6 7 8 9 10 11
    //      4 5 6 7 8 9 10 11 12
    //
    //Proof that it will work:
    //The only time first and last segment won't cover the intermediates is when
    //the both the segments are disjoint and there is an element between the two segments
    //1 2 3 4 5 6 7 8 9
    //                    11 12 ....
    //
    //This will never happen because now the overall query segment length would be
    //8 + 1 + 8 = 17, so now the highest power of 2 becomes 16 and we move to layer 4.

    int seg_len = right - left + 1;
    int layer = highest_pow2_layer[seg_len];

    int first_segment = table[layer][left]; //from our example this would be [1, 8]
    int last_segment = table[layer][right - (1 << layer) + 1]; //from our example this would be [4, 11]

    return min(first_segment, last_segment);
  }

  int query_logn(int left, int right) {
    int seg_len = right - left + 1;

    //basically we just disect the segment length into powers of 2
    //for example: seg_len = 11 == 0b1011
    //lets say left = 1, right = 11 [inclusive]
    //so we will get segments of size 1, 2 and 8 (0b1011)
    //that will result in: [1, 1]; [2, 3]; [4, 11]
    //we need to find the min of all these
    int overall_min = INT_MAX;
    int seg_start = left;
    for (int pow2 = 0; (1 << pow2) <= seg_len; ++pow2) {
      if ((seg_len & (1 << pow2)) != 0) {
        //checking if the bit is on/off
        overall_min = min(overall_min, table[pow2][seg_start]);
        seg_start += (1 << pow2);
      }
    }

    return overall_min;
  }

  void show() {
    for (int layer = 0; layer < int(table.size()); ++layer) {
      cout << "Layer " << layer << " Segment Size = " << (1 << layer) << " : [";
      for (int x: table[layer]) {
        cout << x << ", ";
      }
      cout << "]\n";
    }
  }
};

int main() {
	vector<int> a = {1, 5, 7, 2, 6, 6, 3, 1, 5, 4, 12, 6, 4} ;
	SparseTable st(a) ;

	st.show() ;

  cout << "Log n: " << endl;
	cout << st.query_logn(0, 3) << '\n' ;
	cout << st.query_logn(1, 3) << '\n' ;
	cout << st.query_logn(2, 7) << '\n' ;
	cout << st.query_logn(4, 10) << '\n' ;

  cout << "O(1): " << endl;
	cout << st.query_logn(0, 3) << '\n' ;
	cout << st.query_logn(1, 3) << '\n' ;
	cout << st.query_logn(2, 7) << '\n' ;
	cout << st.query_logn(4, 10) << '\n' ;
  return 0;
}
