struct LCA {
  //Pass in the adjecency vector as the input to the constructor
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

    arr_sz = 4 * int(euler_tour.size()) + 5;
    arr = new Node[arr_sz];
    build_seg_tree(1, 0, int(euler_tour.size()) - 1);
  }

  ~LCA() {
    delete[] arr;
  }

  int find(int u, int v) {
    int fo_u = first_occurence[u];
    int fo_v = first_occurence[v];

    pair<int, int> p = query_seg_tree(1, min(fo_u, fo_v), max(fo_u, fo_v));
    return p.second;
  }
private:
  void build_seg_tree(int i, int left, int right) {
    arr[i].left_limit = left;
    arr[i].right_limit = right;
    if (left == right) {
      arr[i].min_value = entry_time[euler_tour[left]];
      arr[i].node_value = euler_tour[left];
      return;
    }

    int mid = (left + right) / 2;
    int l_idx = i * 2, r_idx = i * 2 + 1;
    build_seg_tree(l_idx, left, mid);
    build_seg_tree(r_idx, mid + 1, right);

    if (arr[l_idx].min_value < arr[r_idx].min_value) {
      arr[i].min_value = arr[l_idx].min_value;
      arr[i].node_value = arr[l_idx].node_value;
    } else {
      arr[i].min_value = arr[r_idx].min_value;
      arr[i].node_value = arr[r_idx].node_value;
    }
  }

  pair<int, int> query_seg_tree(int i, int left, int right) {
    if (arr[i].left_limit > right || arr[i].right_limit < left) {
      //totally outside
      return make_pair(int(1e9), -1);
    }
    if (left <= arr[i].left_limit && arr[i].right_limit <= right) {
      //totally inside
      return make_pair(arr[i].min_value, arr[i].node_value);
    }

    pair<int, int> l = query_seg_tree(i * 2, left, right);
    pair<int, int> r = query_seg_tree(i * 2 + 1, left, right);

    if (l.first < r.first) {
      return l;
    } else {
      return r;
    }
  }

  vector<int> euler_tour;
  vector<int> entry_time;
  vector<int> first_occurence;
  
  struct Node {
    int left_limit, right_limit;
    int min_value;
    int node_value;
  };

  Node* arr;

  int n_nodes;
  int arr_sz;
};
