struct LCA {
  LCA(vector<vector<int>>& G) {
    n_nodes = G.size();
    entry_time.resize(n_nodes);
    first_occurence.resize(n_nodes, -1);

    int timestamp = 0;
    auto tour = [&] (const auto& self, int node, int parent) -> void {
      euler_tour.push_back(node);
      entry_time[node] = timestamp++;
      for (int nn: G[node]) {
        if (nn == parent) {
          continue;
        }
        self(self, nn, node);
        ++timestamp;
        euler_tour.push_back(node);
      }
    };

    tour(tour, 1, -1);
    for (int i = 0; i < int(euler_tour.size()); ++i) {
      int e = euler_tour[i];
      if (first_occurence[e] != -1) continue;
      first_occurence[e] = i;
    }

    build_sparse_table();
  }


  int find(int u, int v) {
    int fo_u = first_occurence[u];
    int fo_v = first_occurence[v];

    return query_sparse_table(min(fo_u, fo_v), max(fo_u, fo_v));
  }

  private:
  void build_sparse_table() {
    int size = euler_tour.size();
    vector<pair<int, int>> layer0(size);
      for (int i = 0; i < size; ++i) {
      layer0[i] = make_pair(entry_time[euler_tour[i]], euler_tour[i]);
    }
    table.push_back(layer0); //layer 0 consist of the original vector
    for (int pow2 = 0, current_sz = size - (1 << pow2); current_sz > 0; ++pow2, current_sz -= (1 << pow2)) {
      int skip_length = (1 << pow2);

      vector<pair<int, int>> layer(current_sz);
      vector<pair<int, int>>& prev_layer = table.back();

      for (int i = 0; i < current_sz; ++i) {
        layer[i] = min(prev_layer[i], prev_layer[i + skip_length]);
      }

      table.push_back(layer); 
    }

    highest_pow2_layer.resize(size + 1);
    for (int start = 1, pow2 = 0; start <= size; ++pow2) {
      int limit = 1 << pow2;
      for (int off = 0; off < limit && (start + off) <= size; ++off) {
        highest_pow2_layer[start + off] = pow2;
      }
      start += limit;
    }
  }

  int query_sparse_table(int left, int right) {
    int seg_len = right - left + 1;
    int layer = highest_pow2_layer[seg_len];

    pair<int, int> first_segment = table[layer][left]; //from our example this would be [1, 8]
    pair<int, int> last_segment = table[layer][right - (1 << layer) + 1]; //from our example this would be [4, 11]

    return min(first_segment, last_segment).second;
  }

  vector<int> euler_tour;
  vector<int> entry_time;
  vector<int> first_occurence;

  vector<vector<pair<int, int>>> table;
  //used for the fast O(1) query function
  vector<int> highest_pow2_layer;
  int n_nodes;
};
