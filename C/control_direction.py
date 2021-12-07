from typing import Tuple
import numpy as np
import io
import picamera
import cv2

def control_direction:
    img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV) #imgをRGBからHSVに変換
    h = img_hsv[:, :, 0] #色相
    s = img_hsv[:, :, 1] #彩度
    v = img_hsv[:, :, 2] #明度

    mask = np.zeros(h.shape, dtype = np.uint8)
    mask[(s < 128)] = 255 #s < 128


    contours,_ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) #輪郭を抽出



    if (len(contours) != 0): #countoursの中身があるとき
        mContour = contours[0]
        maxArea = 0.0

        for contour in contours:
            area = cv2.contourArea(contour)
            if (area > maxArea): #area > maxAreaのとき
                maxArea = area #maxAreaをareaにする
                mContour = contour #mContorをcontourにする

        vx, vy, x0, y0 = cv2.fitLine(mContour, cv2.DIST_L2, 0, 0.01, 0.01) #

        #最小二乗法を用いる
        line_tend = vy / vx #傾き

        turn_speed = 1 / line_tend / 10 #逆数の10分の1の値を回転速度とする
        if (turn_speed < 0): #傾きが負の時（左旋回）
            tend = -1 #回転方向を示す変数tend
            turn_speed *= -1
        return tend turn_speed

        