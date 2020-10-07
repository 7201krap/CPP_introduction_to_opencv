## OpenCV_Intruder_dectection <침입자 검출 시스템>

### How to set up the environment to run this:

### How does this program works:

1. Get a webcam video. (This is can be changed to an another camera such as a CCTV. You can do this by changing parameter in 'VideoCapture') 

2. It detects an intruder by comparing the previous frame and the current frame. Therefore, clone the current frame to the old frame (previous frame)

3. Make both frame as a binary image therefore reduces the computational complexity as well as easier to detect blobs.

4. By some environmental effects, the background of the frame would be changed such as direction of sunlight. Also, some objects in the previous frame could be removed such as trash bin. Therefore, it is necessary to gradually update from the previous frame to the current frame. This is implemented by 'addWeighted' 

5. Calculate | previous frame - current frame | by using 'absdiff'

6. Before this program detects the intruder, noise removal is essential. Therefore it thresholds minor noises. The threshold parameter is 'TH1' and the parameter should be changed depending on the circumstances.

7. Use a morphology method (MORPH_OPEN : erosion -> dilation) to reduce some noises. I'm not sure how to use this in proper way.
Refer to the following link about morphology: https://www.mathworks.com/help/images/morphological-dilation-and-erosion.html
8. Draw contours by using 'findContours' and absdiffed frame.

9. An area of the rectangle generated by drawing contours is calculated because we don't want to detect small changes. The program won't draw a rectangle if the rectangle is smaller than the threshold value. The threshold of this parameter is 'TH_AREA'. The parameter should be changed depending on the circumstances.

9_1. Instead of using the area of the rectangle, size of the rectangle (width and height) could be used. I have commented this section.

10. It saves the images of the intruder in your folder(hardisk). It auotomatically generates a jpg image. The format of the file name is 'year month day hour min sec'


