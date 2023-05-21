from math import exp
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# 学习率
learning_rate = 0.001
# 结束阈值
threshold = 1e-10
# 迭代次数
n = 100

# 函数
def fun(x1, x2):
    res = exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) + exp(-x1 - 0.1)
    dx1 = exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) - exp(-x1 - 0.1)
    dx2 = 3 * exp(x1 + 3 * x2 - 0.1) - 3 * exp(x1 - 3 * x2 - 0.1)
    return res, dx1, dx2


if __name__ == '__main__':
    x1, x2 = 0, 0
    y_old, dx1, dx2 = fun(x1, x2)

    for i in range(n):
        x1 -= learning_rate * dx1
        x2 -= learning_rate * dx2

        y_res, dx1, dx2 = fun(x1, x2)
        print('第%d轮, x1 = %f, x2 = %f' % (i, x1, x2))

        if abs(y_old - y_res) < threshold:
            break

    print('x1 = {0} x2 = {1}\nf = {2}'.format(x1, x2, y_res))
