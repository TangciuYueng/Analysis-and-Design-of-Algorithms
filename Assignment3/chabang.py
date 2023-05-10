import sys
NEI = []
NEI.append([-1, -1, 2, 1, -1, -1])
NEI.append([0, 2, 4, 3, -1, -1])
NEI.append([-1, -1, 5, 4, 1, 0])
NEI.append([1, 4, 7, 6, -1, -1])
NEI.append([2, 5, 8, 7, 3, 1])
NEI.append([-1, -1, 9, 8, 4, 2])
NEI.append([3, 7, 11, 10, -1, -1])
NEI.append([4, 8 ,12, 11, 6, 3])
NEI.append([5, 9, 13, 12, 7, 4])
NEI.append([-1, -1, 14, 13, 8, 5])
NEI.append([6, 11, -1, -1, -1, -1])
NEI.append([7, 12, -1, -1, 10, 6])
NEI.append([8, 13, -1, -1, 11, 7])
NEI.append([9, 14, -1, -1, 12, 8])
NEI.append([-1, -1, -1, -1, 13, 9])


NEINEI = []
NEINEI.append([-1, -1, 5, 3, -1, -1])
NEINEI.append([-1, -1, 8, 6, -1, -1])
NEINEI.append([-1, -1, 9, 7, -1, -1])
NEINEI.append([0, 5, 12, 10, -1, -1])
NEINEI.append([-1, -1, 13, 11, -1, -1])
NEINEI.append([-1, -1, 14, 12, 3, 0])
NEINEI.append([1, 8, -1, -1, -1, -1])
NEINEI.append([2, 9, -1, -1, -1, -1])
NEINEI.append([-1, -1, -1, -1, 6, 1])
NEINEI.append([-1, -1, -1, -1, 7, 2])
NEINEI.append([3, 12, -1, -1, -1, -1])
NEINEI.append([4, 13, -1, -1, -1, -1])
NEINEI.append([5, 14, -1, -1, 10, 3])
NEINEI.append([-1, -1, -1, -1, 11, 4])
NEINEI.append([-1, -1, -1, -1, 12, 5])

board = [True] * 15
board[12] = False
ans = []

def func(count):
    # 步数超过13
    if count > 13:
        return
    # 只剩一个

    # num = 0
    # idx = -1
    # for i, x in enumerate(board):
    #     if x:
    #         num += 1
    #         idx = i
    # if num  == 1 and idx == 12:
    #     print("success")
    #     print(ans)
    #     sys.exit()
    #     return

    if board.count(True) == 1: 
        print("success")
        print(ans)
        sys.exit()
        return
    print(count, board.count(False))
    # 遍历整个棋盘
    for idx, x in enumerate(board):
        # 空的
        if x == False:
            # 遍历六个方向
            for i in range(6):
                # 有邻居的邻居且有邻居并且都有棒
                if NEINEI[idx][i] != -1 and NEI[idx][i] != 1 and board[NEINEI[idx][i]] == True and board[NEI[idx][i]] == True:
                    board[NEINEI[idx][i]] = False
                    board[NEI[idx][i]] = False
                    board[idx] = True
                    # 记录当前棋盘状态
                    ans.append(board[0:15])

                    func(count + 1)
                    # 退出当前棋盘状态
                    ans.pop()
                    # 回溯
                    board[NEINEI[idx][i]] = True
                    board[NEI[idx][i]] = True
                    board[idx] = False


func(0)
