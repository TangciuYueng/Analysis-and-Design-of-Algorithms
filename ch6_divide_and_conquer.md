### 分治法
- 分成**相同类型**的**独立**的规模均衡的子问题，直到不能再分为止，再将子问题合并(主要的)
- *注意子问题规模不一定都相等*，只是**均衡**
- 步骤
  - Divide 
  - Conquer
  - Combine
- 递推关系
    - $T(n) = \alpha \times T(n / \beta) + f(n)$
    - $f(n)$为combine的消耗
    - $\alpha$ 为需要解决的子问题的个数
    - $\beta$ 为一次分成多少个子问题
    - Master Theorem: if $f(n) \in \Theta(n^{d}) \And d \gt 0$
        $ T(n)=\begin{cases}
                \ \Theta(n^{d})  \quad if \quad a \lt \beta^{d} \\
                \ \Theta(n^{d}\log{n}) \quad if \quad a = \beta^{d} \\
                \ \Theta(n^{\log_{\beta}{\alpha}}) \quad if \quad a \gt \beta^{d}
                \end{cases}
        $
        - 需要注意的是求出来的是增长阶数
        - 具体的还要初始条件
- 例子
    - **MergeSort**
    - **BinarySort**
    - **QuickSort**
    - **Multiplication of Large Integers**
      - $X \times Y$ X Y 都是n位?
      - $X = A \times 10^{n / 2} + B, Y = C\times 10^{n / 2} + D$
      - $X \times Y \\
      = A \times C \times 10^n + (A \times D + B \times C) \times 10^{n / 2} + B \times D \\
      = A \times C \times 10^n + [(A + B) \times (C + D) - A \times C - B \times D] \times 10^{n / 2} + B \times D
      $
      - M(n) = 3M(n / 2) 三次n/2的数字乘法
        - A * C
        - B * D
        - (A + B) * (C + D)
      - $M(n) = 3M(n/2) \in O(n^{log_2{3}})$
    - **Strassen's Matrix Multiplication**
        $   \begin{bmatrix}
            C_{11} & C_{12} \\
            C_{21} & C_{22} 
            \end{bmatrix}=
            \begin{bmatrix}
            A_{11} & A_{12} \\
            A_{21} & A_{22}
            \end{bmatrix} 
            \begin{bmatrix}
            B_{11} & B_{12} \\
            B_{21} & B_{22}
            \end{bmatrix}=
            \begin{bmatrix}
            M_5 + M_4 - M_2 + M_6 & M_1 + M_2 \\
            M_3 + M_4 & M_5 + M_1 - M_3 - M_7
            \end{bmatrix}
        $
        其中
        $
            M_1 = A_{11}(B_{12} - B_{22}) \\
            M_2 = (A_{11} + A_{12})B_{22} \\
            M_3 = (A_{21} + A{22})B_{11} \\
            M_4 = A_{22}(B_{21} - B_{11}) \\
            M_5 = (A_{11} + A_{22})(B_{11} + B_{22})
            M_6 = (A_{12} - A_{22})(B_{21} + B_{22})
            M_7 = (A_{11} - A_{21})(B_{11} + B_{12})
        $
        $M(n) = 7M(n/2) \in n^{log_2{7}}$
- 思考题
    - 给定2个大整数u和v，分别有m位和n位数字，且m<=n。用通常的乘法求uv的值需要O(mn)时间。当m比n小得多时，试设计一个算法，在上述情况下用$O(nm^{log^{3/2}})$时间求出uv值。
    - 将v分解位n / m段，每段为m位，然后进行n / m次m位乘法，故时间复杂度位$O(\frac{n}{m}  \times m^{log{3}})$