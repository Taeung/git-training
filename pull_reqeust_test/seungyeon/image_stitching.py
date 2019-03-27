#USAGE
#python image_stitching.py --images images/scottsdale --output output.png --crop 1

from imutils import paths
import numpy as np
import argparse
import imutils
import cv2

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--images", type=str, required=True, help="stitch할 input 디렉토리 경로")
ap.add_argument("-o", "--output", type=str, required=True, help="output image 만들 경로")
ap.add_argument("-c", "--crop", type=int, default=0, help="보기 좋게 자를지 말지")
args = vars(ap.parse_args())

#이미지를 경로로 받아오고 초기의 작업
print("[INFO] loading images...")
imagePaths = sorted(list(paths.list_images(args["images"])))
images = []

#이미지를 받아와서 images배열에 저장
for imagePath in imagePaths:
    image = cv2.imread(imagePath)
    images.append(image)

print("[INFO] stitching images...")
#stitch를 하기 위한 환경설정
stitcher = cv2.createStitcher() if imutils.is_cv3() else cv2.Stitcher_create()
(status, stitched) = stitcher.stitch(images)# stitch를 시도하는 함수

#만약 status가 0이면 성공적으로 image 처리 한 것이다.
if status == 0:
    if args["crop"] > 0:
        print("[INFO] cropping...")
        #기존 사진의 경계의 여백을 늘력준다.
        stitched = cv2.copyMakeBorder(stitched, 10, 10, 10, 10, cv2.BORDER_CONSTANT, (0, 0, 0))
        #기존 사진의 색깔을 gray로 바꾼다.
        gray = cv2.cvtColor(stitched, cv2.COLOR_BGR2GRAY)
        #반전 시킨다.+grayscale된 이미지를 이분화 한다. ex) 흰검으로
        thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY)[1]

        cv2.imshow("stitched", thresh)
        cv2.waitKey(0)