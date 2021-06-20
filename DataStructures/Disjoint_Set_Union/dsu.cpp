struct DSU {
    int sz ;
    vector<int> parent ;
    vector<long long> weight ;

    DSU(int n) {
        sz = n+1 ;
        parent.resize(sz, -1) ;
        weight.resize(sz, 1) ;

        iota(parent.begin(), parent.end(), 0) ;
    }

    int get_parent(int i) {
        while (parent[i] != i) {
            i = parent[i] ;
        }
        return i ;
    }

    bool find(int a, int b) {
        return get_parent(a) == get_parent(b) ;
    }

    void union_(int a, int b) {
        int _pa = get_parent(a) ;
        int _pb = get_parent(b) ;

        if (_pa == _pb) return ;
        if (weight[_pa] >= weight[_pb]) {
            parent[_pb] = _pa ;
            weight[_pa] += weight[_pb] ;
        } else {
            parent[_pa] = _pb ;
            weight[_pb] += weight[_pa] ;
        }
    }
};
