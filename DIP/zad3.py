import cv2 as cv
import numpy as np

# hue [0, 179]
# saturation [0, 255]
# value [0, 255]
### o (e, e, e) (d, d, d, d) (t) (ddddddddddd)
'''
e
e
e
d
d
d
d
d
d
d
d
d
d
d
d
d
d
t
d
d
d
d
d
d
'''
###
'''
e
e
e
d
d
d
d
d
d
d
d
t
d
d
d
d
d
d
d
d
'''
cv.namedWindow("work", cv.WINDOW_NORMAL)
cv.resizeWindow("work", 1400, 900)
cv.namedWindow("work_previous_step", cv.WINDOW_NORMAL)
cv.resizeWindow("work_previous_step", 1400, 900)
'''
cv.namedWindow("output", cv.WINDOW_NORMAL)
cv.resizeWindow("output", 1400, 900)

cv.namedWindow("bgr", cv.WINDOW_NORMAL)
cv.resizeWindow("bgr", 1400, 900)
cv.namedWindow("hsv_enhance", cv.WINDOW_NORMAL)
cv.resizeWindow("hsv_enhance", 1400, 900)
cv.namedWindow("binary", cv.WINDOW_NORMAL)
cv.resizeWindow("binary", 1400, 900)
cv.namedWindow("edges", cv.WINDOW_NORMAL)
cv.resizeWindow("edges", 1400, 900)
# Read image
bgr = cv.imread("/home/kacper/Documents/LaTex/DIP/DIPz1Photo.jpg")
hsv = cv.cvtColor(bgr, cv.COLOR_BGR2HSV) # konwersja
hsv_s = np.copy(hsv)
(h, s, v) = cv.split(hsv_s)
for i in range(len(s)):
    for j in range(len(s[i])):
        if s[i][j] > (255 * 0.9):
            s[i][j] = 255
        else:
            s[i][j] = max(0, (5.0 / 4.0) * s[i][j] - (0.15*255))

binary = cv.adaptiveThreshold(v, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 151, 5)
hsv_s = cv.merge((h, s, v))

'''
# displaying output
#hsv_s = cv.cvtColor(hsv_s, cv.COLOR_HSV2BGR)
#cv.imwrite("hsv_s.jpg", hsv_s) to save


####
#   DRUGA CZĘŚĆ ZASTOSOWANIE MORFOLOGICZNYCH OPERACJI
####

hsv_s = cv.imread("hsv_enhance.jpg")
gray = cv.imread("value_gray.jpg", cv.COLOR_BGR2GRAY)
binary = cv.adaptiveThreshold(gray, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 97, 10)

kernel = cv.getStructuringElement(cv.MORPH_CROSS, (3, 3))
start = np.copy(binary)
img_output = start
# Create an empty output image to hold values
#thin = np.zeros(binary.shape, dtype='uint8')
#img = img_output
#img_output = cv.morphologyEx(start, cv.MORPH_OPEN, kernel)
# Loop until erosion leads to an empty set
'''
while cv.countNonZero(img_output) != 0:
    # Erosion
    erode = cv.erode(img_output, kernel)
    # Opening on eroded image
    opening = cv.morphologyEx(erode, cv.MORPH_OPEN, kernel)
    # Subtract these two
    subset = erode - opening
    # Union of all previous sets
    thin = cv.bitwise_or(subset, thin)
    # Set the eroded image for next iteration
    img_output = erode.copy()

cv.imshow('work', img)
cv.imshow('output', thin)
cv.waitKey(0)

'''

#img_output = cv.erode(img_output, kernel, 9)
#img_output = cv.morphologyEx(start, cv.MORPH_CLOSE, kernel)
#img_output = cv.erode(img_output, kernel, 14)
#img_output = cv.bitwise_not(img_output)
#img_output = cv.dilate(img_output, kernel, 4)
#l = img_output
#img_output = cv.morphologyEx(img_output, cv.MORPH_GRADIENT, kernel)
#img_output = cv.dilate(img_output, kernel, 4)
#img_output = img_output - l
#img_output = cv.morphologyEx(start, cv.MORPH_CLOSE, kernel)
#img_output = cv.dilate(img_output, kernel, 10)
#img_output = cv.bitwise_xor(img_output, start)
#img_output = cv.bitwise_not(img_output)
#img_output = cv.bitwise_and(img_output, start)

####
#img_output = cv.erode(img_output2, kernel, 1)
#img_output = img_output2 - img_output
#img_output = cv.dilate(img_output, kernel, 1)

#cv.imshow("output", img_output)
#cv.waitKey(0)

# displaying output
#cv.imshow("bgr", bgr)
#hsv_s = cv.cvtColor(hsv_s, cv.COLOR_HSV2BGR)
##cv.imshow("hsv_enhance", hsv_s)
#cv.imshow("binary", binary)
#cv.imshow("edges", edges)#
#cv.waitKey(0)
''' # Set proper saturation
hsv_s = np.copy(hsv)
h, s, v = cv.split(hsv_s)
for line in s:
    for i, item in enumerate(line):
        if item > (255 * 0.9):
            line[i] = 255
        else:
            line[i] = max(0, 5.0/4.0 * line[i] - 0.15)

#h, s, v = cv.split(hsv_s)
#hsv_s = cv.cvtColor(hsv_s, cv.COLOR_BGR2HSV)
#hsv_s = cv.imread("/home/kacper/Documents/LaTex/DIP/hsv_s.jpg")  # Read image # za  pierwszym razem to zakomentowac
#v = cv.imread("/home/kacper/Documents/LaTex/DIP/gray.jpg")  # Read image # za  pierwszym razem to zakomentowac
#v = cv.cvtColor(v, cv.COLOR_BGR2GRAY)  # conversion from bgr to hsv # za  pierwszym razem to zakomentowac
binary = cv.adaptiveThreshold(s, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 9, 5)
#hsv_s = cv.Canny(v,100,200)
cv.contourArea()
'''

instruction = "s - set kernel\nk - display kernel\ne - erode with current kernel\nd - dilate with current kernel\
    \no - opening operation\nc -closing operation\nb - one step back\nr - restart the work\nq - quit\n"
print(instruction)
pocket = np.copy(binary)
work = img_output
work_ps = np.copy(hsv_s)
#kernel = np.ones((3, 3),  dtype=np.uint8)
while True:
    cv.imshow("work", work)
    cv.imshow("work_previous_step", work_ps)
    cv.waitKey(0)
    cmd = input()
    if cmd == "q":
        print("quit")
        break
    elif cmd == "e":
        work_ps = work
        work = cv.erode(work, kernel, 1)
    elif cmd == "d":
        work_ps = work
        work = cv.dilate(work, kernel, 1)
    elif cmd == "o":
        work_ps = work
        work = cv.morphologyEx(work, cv.MORPH_OPEN, kernel)
    elif cmd == "c":
        work_ps = work
        work = cv.morphologyEx(work, cv.MORPH_CLOSE, kernel)
    elif cmd == "g":
        work_ps = work
        work = cv.morphologyEx(work, cv.MORPH_GRADIENT, kernel)
    elif cmd == "s":
        print("Give the size of kernel")
        size = int(input())
        kernel = np.ones((size, size),  dtype=np.uint8)
        for i in range(len(kernel)):
            for j in range(len(kernel[i])):
                print("k[", i, "][", j, "] = ")
                kernel[i][j] = int(input())
    elif cmd == "r":
        work_ps = hsv_s
        work = binary
    elif cmd == "b":
        work = work_ps
    elif cmd == "k":
        print(kernel)
    elif cmd == "p":
        pocket = np.copy(work)
    elif cmd == "t":
        im = np.copy(work)
        thin = np.zeros(binary.shape, dtype='uint8')
        while cv.countNonZero(im) != 0:
            # Erosion
            erode = cv.erode(im, kernel)
            # Opening on eroded image
            opening = cv.morphologyEx(erode, cv.MORPH_OPEN, kernel)
            # Subtract these two
            subset = erode - opening
            # Union of all previous sets
            thin = cv.bitwise_or(subset, thin)
            # Set the eroded image for next iteration
            im = erode.copy()
        work = thin
    else:
        print(instruction)

cv.destroyAllWindows()
