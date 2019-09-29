namespace {

using LL = long long;

struct LinearBasis {
  // MAXL=基中每一个向量的维度,一般是32 or 64
  // 因为基的向量个数 <= 每一个向量的维度
  // 所以数组a的size=MAXL就足够了
  // a[i]表示第i个列向量，从上到下为2进制的低到高
  // 逆序枚举的话，最终a是一个上三角形矩阵：
  // 1.可能有些列全为0(即a[i] = 0)
  // 2.若a[i]!=0,a[i]的第i位一定是1,[1,i-1]位可能有1,[i+1,MAXL-1]位全为0
  // 3.若a[i]的第i位为1,则a[i+1, MAXL-1]的第i位全为0
  static const int MAXL = 64;
  LL a[MAXL];

  LinearBasis() {
    for (int i = 0; i < MAXL; ++i) a[i] = 0;
  }

  void Add(LL vec) {
    // 一般逆序枚举vec的二进制位，根据需要顺序/逆序枚举
    for (int j = MAXL - 1; j >= 0 && vec > 0; --j) {
      if (((vec >> j) & 1) == 0) continue;
      if (a[j] > 0) {
        vec ^= a[j];  // a[j]!=0,就用a[j]消去t的第j位的1
        continue;
      }
      // 此时vec的第j位!=0 && a[j] = 0
      // 用a[0,j-1]消去vec的第[0,j-1]位的1
      // 如果a[k]=0,vec的第k位可以为1
      for (int k = 0; k < j; ++k) {
        if ((vec >> k) & 1) vec ^= a[k];
      }
      // 用vec消去a[j+1, MAXL-1]的第j位的1
      for (int k = j + 1; k < MAXL; ++k) {
        if ((a[k] >> j) & 1) a[k] ^= vec;
      }
      a[j] = vec;
      break;
    }    
  }

  void Build(LL *vec_array, int len) {
    for (int i = 0; i < len; ++i) Add(vec_array[i]);
  }

  void Merge(const LinearBasis &another) {
    for (int i = 0; i < MAXL; ++i) Add(another.a[i]);
  }
};

}  // End namespace
