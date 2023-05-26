from math import exp
import matplotlib.pyplot as plt
import numpy as np

# 学习率
learning_rate = 0.001
# 结束阈值
threshold = 1e-10
# 迭代次数
n = 1000

# 函数
# 返回函数计算结果和求偏导结果
def fun(x1, x2):
    res = exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) + exp(-x1 - 0.1)
    dx1 = exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) - exp(-x1 - 0.1)
    dx2 = 3 * exp(x1 + 3 * x2 - 0.1) - 3 * exp(x1 - 3 * x2 - 0.1)
    return res, dx1, dx2


if __name__ == '__main__':
    x1, x2 = 0, 0
    y_old, dx1, dx2 = fun(x1, x2)
    # n此迭代
    for i in range(n):
        x1 -= learning_rate * dx1
        x2 -= learning_rate * dx2
        # 得到新计算值
        y_res, dx1, dx2 = fun(x1, x2)
        # print('第%d轮, x1 = %f, x2 = %f' % (i, x1, x2))
        # 变化不大跳出循环
        if abs(y_old - y_res) < threshold:
            break
        # 更新y_old
        y_old = y_res

    print('x1*= {:.10f} x2*= {:.10f}\nf*= {:.10f}'.format(x1, x2, y_res))
