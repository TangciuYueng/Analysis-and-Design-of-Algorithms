ans = [[True, True, True, True, True, False, True, True, False, True, True, True, True, True, True], [True, True, True, True, True, True, True, True, False, False, True, True, True, True, False], [True, True, True, True, True, True, False, 
False, True, False, True, True, True, True, False], [True, False, True, False, True, True, True, False, True, False, 
True, True, True, True, False], [True, False, True, True, False, False, True, False, True, False, True, True, True, True, False], [True, True, True, False, False, False, False, False, True, False, True, True, True, True, False], [True, True, True, False, True, False, False, False, False, False, True, True, True, False, False], [False, True, False, False, True, True, False, False, False, False, True, True, True, False, False], [False, False, False, False, False, True, False, False, True, False, True, True, True, False, False], [False, False, False, False, False, True, False, False, True, False, True, False, False, True, False], [False, False, False, False, False, False, False, False, False, False, True, False, True, True, False], [False, False, False, False, False, False, False, False, False, False, True, True, False, False, False], [False, False, False, False, False, False, False, False, False, False, False, False, True, False, False]]


print('first')
for board in ans:
    for i in range(len(board)):
        if i == 0:
            print(' ' * 4 + str(1 if board[i] else 0))
        elif i == 1:
            print(' ' * 3 + str(1 if board[i] else 0) + ' ' + str(1 if board[i + 1] else 0))
        elif i == 3:
            print(' ' * 2 + str(1 if board[i] else 0) + ' ' + str(1 if board[i + 1] else 0) + ' ' + str(1 if board[i + 2] else 0))
        elif i == 6:
            print(' ' * 1 + str(1 if board[i] else 0) + ' ' + str(1 if board[i + 1] else 0) + ' ' + str(1 if board[i + 2] else 0) + ' ' + str(1 if board[i + 3] else 0))
        elif i == 10:
            print(str(1 if board[i] else 0) + ' ' + str(1 if board[i + 1] else 0) + ' ' + str(1 if board[i + 2] else 0) + ' ' + str(1 if board[i + 3] else 0) + ' ' + str(1 if board[i + 4] else 0))
