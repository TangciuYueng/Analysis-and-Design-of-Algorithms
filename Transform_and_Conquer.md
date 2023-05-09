### 变治法
- 进行变化Transformation
  - instance simplification实例变化
    - 找数组中是否又重复数字
    数组预排序，顺序变了就算实例变化了
    - 找数组中出现次数最大的
    也是排序，变量记录当前最大出现次数与数字
    - 查找，一般查找$\theta(n)$，但排序就已经$\theta(n\log(n))$，因此多次查找才**有可能**更快
    - Gaussian Elimination高斯消去
    利用矩阵初等变换解方程，化为上三角，每轮把该列下面都消为0
        - if $A[i, i] = 0$ then 找其他行交换
        - if $A[i, i] is so small$ 找该列中最大的行交换
    - 多次找到最大/最小->构建堆
      - 父母优势
      - 基本完备
  - representation change改变表现
    - Horner's Rule for Polynomial Evaluation
    $p(x) = (...(a_nx+a_{n+1})x + ...)x + a_0$
  - problem reduction问题化简->把一个复杂的几何问题...化简为简单的代数问题、把一个复杂的过河问题化简为状态图连线问题
    - 判断点c在不在ab的连线上 -> 坐标构成的行列式是否等于零
    - 线性规划问题，一堆复杂的条件->一个个不等式组
    - 零一背包(离散背包)
    - 连续背包(小数背包)：一个物品可以切成0-1的任意小部分->线性规划问题
    - 过河问题->状态图