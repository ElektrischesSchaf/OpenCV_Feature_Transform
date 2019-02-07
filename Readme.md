# Program UI
![Menu](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/menu.png)
![SIFT](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/SIFT.png)
![02](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/02.png)
![03](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/03.png)
![preprocessing](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/pre.png)
![click](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/click.png)
![track](https://github.com/ElektrischesSchaf/OpenCV_Feature_Transform/blob/master/Screenshots/track.png)  

# How to include SIFT libraries
1.	Download opencv-3.4.2 https://github.com/opencv/opencv/releases/download/3.4.2/opencv-3.4.2-vc14_vc15.exe  
2.	Download open_contrib-3.4.2.zip https://github.com/opencv/opencv_contrib/archive/3.4.2.zip  
3.	Download Cmake (version doesn’t matter) cmake-3.13.0-rc3-win64-x64.msi  
https://cmake.org/files/v3.13/cmake-3.13.0-rc3-win64-x64.msi  
4.	Move thye opencv and open_contrib-3.4.2 files to C:/  
5.	Open Cmake (Cmake-gui)  
6.	Under Where is the source code type: C:/opencv/sources  
7.	Create a folder in C:/opencv_with_contrib  
8.	Under where to buil binary files type: C:/opencv_with_contrib  
9.	Click configure and select Visual Studio version (VS 14 15)  
10.	Select native…  
11.	Search for OPENCV_EXTRA_MODULES_PATH and under value write C:/opencv_contrib-3.4.2/modules  
12.	Click configure again  
13.	Click generate  
14.	Go to you newly created folder opencv_with_contrib  
15.	Run the Opencv.sln (visual studio solution)  
16.	Under the Opencv project look for CmakeTargets  
17.	For Release and Debug with x64 do the following  
i.	Build ALL_BUILD  
ii.	Build INSTALL  
18.	Control Panel -> System and Saftey -> System -> Advanced System Setting -> Environmental Variables  
19.	System Variables -> Pick Path and click edit -> Add C:\opencv\build\x64\vc14\bin; C:\opencv_with_contrib\install\x64\vc14\bin  
20.	Start Visual Studio 2015 and pen project properties  
21.	For Release and Debug with x64 do the following:  
i.	C/C++ -> Additional include directories ->  
Add  C:\opencv_with_contrib\install\include; C:\opencv\build\include  
ii.	Linker -> General -> Other library directories ->  
Add  C:\opencv_with_contrib\install\x64\vc14\lib; C:\opencv\build\x64\vc14\lib  
iii.	Linker -> Input -> Other dependencies ->  
Add  opencv_world342.lib; opencv_xfeatures2d342.lib (Release)  
opencv_xfeatures2d342.lib  
opencv_videoio342.lib  
opencv_core342.lib  
opencv_flann342.lib  
opencv_features2d342.lib  
opencv_highgui342.lib  
opencv_imgproc342.lib  
opencv_imgcodecs342.lib  
opencv_video342.lib  
Add  opencv_world342d.lib; opencv_xfeatures2d342d.lib (Debug)  
opencv_xfeatures2d342d.lib  
opencv_videoio342d.lib  
opencv_core342d.lib  
opencv_flann342d.lib  
opencv_features2d342d.lib  
opencv_highgui342d.lib  
opencv_imgproc342d.lib  
opencv_imgcodecs342d.lib  
opencv_video342d.lib  
  
22.	Include Headers:  
#include <iostream>  
#include <opencv2/opencv.hpp>   
#include <opencv2/xfeatures2d/nonfree.hpp>  
using namespace cv;   
using namespace std;  
