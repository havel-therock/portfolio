import cv2 as cv
import numpy as np


def thinning(work):
    img = np.copy(work)
    # thin = empty output image to hold values
    thin = np.zeros(binary.shape, dtype='uint8')
    while cv.countNonZero(img) != 0:
        # Erosion
        erode = cv.erode(img, kernel)
        # Opening on eroded image
        opening = cv.morphologyEx(erode, cv.MORPH_OPEN, kernel)
        # Subtract these two
        subset = erode - opening
        # Union of all previous sets
        thin = cv.bitwise_or(subset, thin)
        # Set the eroded image for next iteration
        img = erode.copy()
    # after while thin is the thinning effect
    return thin


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
cv.namedWindow("bgr", cv.WINDOW_NORMAL)
cv.resizeWindow("bgr", 1400, 900)
cv.namedWindow("hsv_enhance", cv.WINDOW_NORMAL)
cv.resizeWindow("hsv_enhance", 1400, 900)
cv.namedWindow("binary", cv.WINDOW_NORMAL)
cv.resizeWindow("binary", 1400, 900)
cv.namedWindow("edges", cv.WINDOW_NORMAL)
cv.resizeWindow("edges", 1400, 900)

# Read image
bgr = cv.imread("DIPz1Photo.jpg")
# Conversion to HSV
hsv = cv.cvtColor(bgr, cv.COLOR_BGR2HSV)
hsv_s = np.copy(hsv)
(h, s, v) = cv.split(hsv_s)
# enhance saturation
for i in range(len(s)):
    for j in range(len(s[i])):
        if s[i][j] > (255 * 0.9):
            s[i][j] = 255
        else:
            s[i][j] = max(0, (5.0 / 4.0) * s[i][j] - (0.15*255))

binary = cv.adaptiveThreshold(v, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 151, 5)
# merge for display purpose
hsv_s = cv.merge((h, s, v))

####
#   DRUGA CZĘŚĆ ZASTOSOWANIE MORFOLOGICZNYCH OPERACJI
####

# binary = cv.adaptiveThreshold(gray, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 97, 10)

# Set kernel
kernel = cv.getStructuringElement(cv.MORPH_CROSS, (3, 3))
img_output = np.copy(binary)
# Erosion for noise reduction
img_output = cv.erode(img_output, kernel, 1)
img_output = cv.erode(img_output, kernel, 1)
img_output = cv.erode(img_output, kernel, 1)
# Dilatation for edges connection and their thickness
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
# Thinning
img_output = thinning(img_output)
# Dilatation for fully connected edges
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)
img_output = cv.dilate(img_output, kernel, 1)

edges = img_output

# displaying output
cv.imshow("bgr", bgr)
# conversion for displaying purpose
hsv_s = cv.cvtColor(hsv_s, cv.COLOR_HSV2BGR)
#cv.imwrite("hsv_enhance.jpg", hsv_s)
#cv.imwrite("binary.jpg", binary)
#cv.imwrite("edges.jpg", edges)

cv.imshow("hsv_enhance", hsv_s)
cv.imshow("binary", binary)
cv.imshow("edges", edges)

cv.waitKey(0)
cv.destroyAllWindows()
