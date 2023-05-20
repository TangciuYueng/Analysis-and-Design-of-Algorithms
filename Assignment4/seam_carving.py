import cv2
import numpy as np
import sys

class seam_carving:
    # 构造函数
    def __init__(self, filename):
        # initialize parameter
        self.filename = filename
        
        # read in image and store as np.float64 format
        self.in_image = cv2.imread(filename).astype(np.float64)
        self.in_height, self.in_width = self.in_image.shape[: 2]
        # 设置为原图的一般
        self.out_height = self.in_image.shape[0] // 2
        self.out_width = self.in_image.shape[1] // 2

        # keep tracking resulting image
        self.out_image = np.copy(self.in_image)

        # kernel for forward energy map calculation
        self.kernel_x = np.array([[0., 0., 0.], [-1., 0., 1.], [0., 0., 0.]], dtype=np.float64)
        self.kernel_y_left = np.array([[0., 0., 0.], [0., 0., 1.], [0., -1., 0.]], dtype=np.float64)
        self.kernel_y_right = np.array([[0., 0., 0.], [1., 0., 0.], [0., -1., 0.]], dtype=np.float64)

        # starting program
        self.start()

    def start(self):
        print(self.in_image.shape)
        
        self.seams_carving()

        self.save_picture(filename_out)
        
        print(self.out_image.shape)

    # 改变尺寸
    def seams_carving(self):
        # calculate number of rows and columns needed to be inserted or removed
        delta_row, delta_col = int(self.out_height - self.in_height), int(self.out_width - self.in_width)
        
        # 判断是要变大还是变小
        # remove column
        if delta_col < 0:
            self.seams_removal(delta_col * -1)
        # insert column
        # elif delta_col > 0:
        #     self.seams_insertion(delta_col)

        # 翻转变大or变小
        # remove row
        if delta_row < 0:
            self.out_image = self.rotate_image(self.out_image, 1)
            self.seams_removal(delta_row * -1)
            self.out_image = self.rotate_image(self.out_image, 0)
        # # insert row
        # elif delta_row > 0:
        #     self.out_image = self.rotate_image(self.out_image, 1)
        #     self.seams_insertion(delta_row)
        #     self.out_image = self.rotate_image(self.out_image, 0)

    # 缩小num_pixel像素
    def seams_removal(self, num_pixel):
        for _ in range(num_pixel):
            # 能量图
            energy_map = self.calc_energy_map()
            # 动态规划标记dp数组
            dp, path = self.cumulative_map_forward(energy_map)
            # 逆向找能量和最小的一条路
            seam_idx = self.find_seam(dp, path)
            # 删除能量和最小的路
            self.delete_seam(seam_idx)

     # 计算能量图
    def calc_energy_map(self):
        b, g, r = cv2.split(self.out_image)
        b_energy = np.absolute(cv2.Scharr(b, -1, 1, 0)) + np.absolute(cv2.Scharr(b, -1, 0, 1))
        g_energy = np.absolute(cv2.Scharr(g, -1, 1, 0)) + np.absolute(cv2.Scharr(g, -1, 0, 1))
        r_energy = np.absolute(cv2.Scharr(r, -1, 1, 0)) + np.absolute(cv2.Scharr(r, -1, 0, 1))
        return b_energy + g_energy + r_energy

    # 动态规划正向
    def cumulative_map_forward(self, energy_map):
        m, n = energy_map.shape
        dp = np.copy(energy_map)
        # 记录从哪来的，-1左上，0上，1右上
        path = np.zeros((m, n))
        # 从上到下
        for i in range(1, m):
            for j in range(n):
                # 第一列没有左上
                if j == 0:
                    # 取上
                    if energy_map[i - 1, j] < energy_map[i - 1, j + 1]:
                        path[i, j] = 0
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j]
                    # 取右上
                    else:
                        path[i, j] = 1
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j + 1]
                # 最后一列没有右上
                elif j == n - 1:
                    # 取左上
                    if energy_map[i - 1, j - 1] < energy_map[i - 1, j]:
                        path[i, j] = -1
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j - 1]
                    # 取上
                    else:
                        path[i, j] = 0
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j]
                # 中间的有三个来源方向
                else: 
                    # 取左上
                    if energy_map[i - 1, j - 1] < min(energy_map[i - 1, j], energy_map[i - 1, j + 1]):
                        path[i, j] = -1
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j - 1]
                    # 取上
                    elif energy_map[i - 1, j] < energy_map[i - 1, j + 1]:
                        path[i, j] = 0
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j]
                    # 取右上
                    else:
                        path[i, j] = 1
                        dp[i, j] = energy_map[i, j] + energy_map[i - 1, j + 1]
        return dp, path

    # 返回要找的线位于每行的第几列
    def find_seam(self, dp, path):
        m, n = dp.shape
        seam_idx = np.zeros((m, ), dtype=np.uint32)
        # 终点最小值对应的索引
        seam_idx[-1] = np.argmin(dp[-1])
        # 逆向寻找最小的路径
        for i in range(m - 2, -1, -1):
            j = seam_idx[i + 1]
            seam_idx[i] = j + path[i, j]

        return seam_idx        
            
    # 删除一条线的像素
    def delete_seam(self, seam_idx):
        m, n = self.out_image.shape[: 2]
        # 少一列
        ans = np.zeros((m, n - 1, 3))
        
        for i in range(m):
            j = seam_idx[i]
            ans[i, :, 0] = np.delete(self.out_image[i, :, 0], [j])
            ans[i, :, 1] = np.delete(self.out_image[i, :, 1], [j])
            ans[i, :, 2] = np.delete(self.out_image[i, :, 2], [j])
        
        self.out_image = np.copy(ans)

    def rotate_image(self, image, ccw):
        m, n, ch = image.shape
        output = np.zeros((n, m, ch))
        if ccw:
            image_flip = np.fliplr(image)
            for c in range(ch):
                for row in range(m):
                    output[:, row, c] = image_flip[row, :, c]
        else:
            for c in range(ch):
                for row in range(m):
                    output[:, m - 1 - row, c] = image[row, :, c]
        return output

    # 保存文件
    def save_picture(self, filename):
        cv2.imwrite(filename, self.out_image)

    
filename = 'E:\\xx\\algorithm_design_analysis\\Assignment4\\pict.png'
filename_out = 'E:\\xx\\algorithm_design_analysis\\Assignment4\\pict_resize.png'

obj = seam_carving(filename)