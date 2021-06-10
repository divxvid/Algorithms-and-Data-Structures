struct DSU {
    int sz ;
    int* parent ;
    long long* weight ;

    DSU(int n) {
        sz = n+1 ;
        parent = new int[sz] ;
        weight = new long long[sz] ;

        for (int i = 0; i < sz; ++i) {
            parent[i] = i ;
            weight[i] = 0 ;
        }
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

    ~DSU() {
        delete[] parent ;
        delete[] weight ;
    }
};
