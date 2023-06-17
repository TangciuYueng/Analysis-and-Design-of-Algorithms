### 变治法
#### two stages
- 变：把问题的**实例**变得更容易
- 治：对实例进行求解
#### 变的分类
- instance simplification**(实例化简)**
to a **simple/more convenient** instance of the **same problem**
- representation change**(改变表现)**
to a **different representation** of the same instance
- problem reduction**(问题化简)**
to a **different problem** for which an algorithm is already available
#### example 
##### instance simplification实例化简
  - 找数组中是否又**重复数字**
  数组**预排序**，顺序变了就算实例变化了
  - 找数组中出现**次数最大的**
  也是排序，变量记录当前最大出现次数与数字
  - **查找**，一般查找$\theta(n)$，但排序就已经$\theta(n\log(n))$，因此多次查找才**有可能**更快
  - Gaussian Elimination**高斯消去**
  利用**矩阵初等变换解方程**，化为上三角，每轮把该列下面都消为0
  两点考虑
    - if $A[i, i] = 0$ then 找其他行交换
    - if $A[i, i]$ is so small 找该列中最大的行交换->保证比例因子的绝对值不会大于一
  时间复杂度$O(n^3) + O(n^2) = O(n^3)$
  - **多次找到最大/最小**->构建堆
    - 父母优势
    - 基本完备
    - 过程
      - 对现有数组构造：从最后一个父节点向下调整
      - 插入：插入到最后，不断上浮
      - 删除：堆顶和最后一个交换，删除后，从堆顶向下调整
##### representation change改变表现
  - **Horner's Rule** for Polynomial Evaluation
  $p(x) = (...(a_nx+a_{n+1})x + ...)x + a_0$
  eg. $p(x) = 2x^4 - x^3 + 3x^2 + x - 5 \\
    = x(x(x(2x - 1) + 3) + 1) - 5$
  ```
  algorithm Horner(P[0..n], x)
    p <- P[n]
    for i <- n - 1 downto 0 do
      p <- x * p + P[i]
    return p
  ```
##### problem reduction问题化简->把一个复杂的几何问题...化简为简单的代数问题、把一个复杂的过河问题化简为状态图连线问题
  - 判断点c在不在ab的连线上 -> 坐标构成的行列式是否等于零
  - 线性规划问题，一堆复杂的条件->一个个不等式组
    - Simplex method: worst-case efficiency is to be exponential
    - Ellipsoid algorithm: polynomial time
    - Interior-point methods: polynomial time
    - Karmarkar’s algorithm: polynomial worst-case efficiency
  - 零一背包(离散背包)
    数学模型
      - Maximize $\sum^{n}_{i=1}v_ix_i$
      - subject to $\sum^{n}_{i=1}w_ix_i \le W$
      - $x_i \in \{0, 1\}$
  - 连续背包(小数背包)：一个物品可以切成0-1的任意小部分->线性规划问题
    数学模型
      - Maximize $\sum^{n}_{i=1}v_ix_i$
      - subject to $\sum^{n}_{i=1}w_ix_i \le W$
      - $0 \le x_i \le 1$
  - 过河问题->状态图