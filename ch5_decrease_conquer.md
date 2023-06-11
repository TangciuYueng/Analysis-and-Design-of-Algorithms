### 减治法(DECREASE & CONQUER)
利用一个问题**给定实例的解**和**同样问题较小实例的解**之间的某种关系
自底向上-非递归
自顶向下-递归
- **减常数***Decrease by a constant
    - *减一的思想*，想解决`n`规模的，先解决`n - 1`规模的
    - 时间效率分析
      $T(n) = T(n - 1) + f(n) \\
            = T(n - 2) + f(n - 1) + f(n) \\
            = T(0) + \sum_{j = 1}^{n}f(j)
    $
    - **求n个a相乘**
      - $a^n = a * a^{n - 1}$
    - **插入排序**
      - 先求`n - 1`，再加上`1`
      - 最好$C(n) = n - 1$
      - 最坏$C(n) = n(n - 1) / 2$
      - 平均$C_{avg}(n) \approx n^2 / 4 \in \Theta(n^2)$
    - **拓扑排序**
      - dfs
        - 按照出栈的逆序作为拓扑排序，要出栈的时候就是死点
        - 为什么不能拿进栈顺序当作拓扑排序的顺序
        - 因为
      - Source Removal method源(入度为零 减治法)删除法，拓扑排序
        - 先求`1`，再求`n - 1`
      - 应用
        - 程序编译中的指令调度
        - 电子表格单元格的公式求值顺序
        - 解决链接器中的符号以来问题
- **减常因子**Decrease by a constant factor
    - 时间效率分析
      - 递推方程
      $T(n) = T(n / b) + f(n) b > 1$
      $T(b^k) = T(b^{k - 1}) + f(b^k) \\
                = T(1) + \sum^{k}_{j = 1} f(b^j)$
    - **Binary Search**
      ```
      algorithm BinarySearch(A[0..n-1], K)
        while l <= r do
          m <- [(l+r)/2]
          if k = A[m] return m
          else if K < A[m] r <- m - 1
          else l <- m + 1
      ```
      - Basic operation: key comparison
      - Worst case
        - 递推方程: $C_{worst}(n) = C_{worst}(\lceil n / 2 \rceil) + 1$
        - 初始值: $C_{worst}(1) = 1$
      - Best case
        - $C_{bast}(n) = 1$一次就找到了
      - Average case
        - 利用平衡二叉搜索树
        - $A(n) = \frac{1}{n} \sum_{i = 1}^{k}i*2^{i - 1} \approx \log(n + 1) - 1 $
    - **Fake-Coin Problem**
      - n枚硬币中找出一个重量较轻的假币
      - 分两堆硬币
      - 分三堆硬币
    - $
    a^n =   \begin{cases}
            \ {(a^{n/2})}^2 :n正偶数\\
            \ {(a^{n/2})}^2 * a :n正奇数 \\
            \ a :n == 1
            \end{cases}
    $
    - **Russian Peasant Multiplication**
      - 将乘法运算转换为移位运算和加减运算
      - $
          n * m = \begin{cases}
                  \ \frac{n}{2} * 2m : n偶数\\
                  \ \frac{n - 1}{2} * 2m + m : n奇数\\
                  \end{cases}
        $
- **减可变规模**Variable size decrease
    - $gcd(m, n) = gcd(n, m \mod n)$