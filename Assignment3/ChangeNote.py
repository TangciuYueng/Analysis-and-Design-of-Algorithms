# 面额种类
NOTE = [1, 3, 5]
# 需要兑换的零钱
target = 9

def func(NOTE, target):
    dp = [None] * (target + 1)
    # dp表建立，每个对应一个集合
    for i in range(target + 1):
        dp[i] = set()
    # 将list转为tuple才有hash，初始化
    dp[1].add(tuple([1, 0, 0]))
    dp[2].add(tuple([2, 0, 0]))
    dp[3].add(tuple([0, 1, 0]))
    dp[4].add(tuple([1, 1, 0]))
    dp[5].add(tuple([0, 0, 1]))

    for i in range(6, target + 1):
        # 一个很大的数
        minSum = 99999999
        # 得到最小组合
        for note in NOTE:
            for x in dp[i - note]:
                tempSum = sum(x)
                minSum = min(minSum, tempSum)

        # 通过最小组合，可能不止一个，找到新的组合
        for note in NOTE:
            for x in dp[i - note]:
                if minSum == sum(x):
                    temp = list(x)
                    temp[NOTE.index(note)] += 1
                    dp[i].add(tuple(temp))
        
    return dp[target]

print(func(NOTE, target))