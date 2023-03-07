#include <numeric>
#include <vector>

struct DSU {
  std::vector<int> parent;
  std::vector<int> size;

  DSU(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
  int Root(int x) { return parent[x] == x ? x : parent[x] = Root(parent[x]); }
  void Merge(int x, int y) {
    x = Root(x);
    y = Root(y);
    if (x == y) return;
    if (size[x] < size[y]) std::swap(x, y);
    parent[y] = x;
    size[x] += size[y];
  }
};