
// HW2_N16074988_伍錫志_v1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "HW2_N16074988_伍錫志_v1.h"
#include "HW2_N16074988_伍錫志_v1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <opencv2/opencv.hpp> 
#include <opencv2/xfeatures2d/nonfree.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <fstream>
#include <Windows.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;  //包含cv命名空间
using namespace std;
using namespace cv::xfeatures2d;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void onMouse(int Event, int x, int y, int flags, void* param);
vector <Point2f> points_for_click;
vector <Point2f> points_for_click2;

vector<Point2f> trajectory;
void onMouse(int Event, int x, int y, int flags, void* param) {
	if (Event == CV_EVENT_LBUTTONDOWN) 
	{
		points_for_click.push_back(Point(x, y));
	}
	
}
void onMouse2(int Event, int x, int y, int flags, void* param) {
	if (Event == CV_EVENT_LBUTTONDOWN)
	{
		points_for_click2.push_back(Point(x, y));
		cout << "x=" << x << ", " << "y=" <<y<< endl;
	}

}

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHW2_N16074988_伍錫志_v1Dlg 對話方塊



CHW2_N16074988_伍錫志_v1Dlg::CHW2_N16074988_伍錫志_v1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HW2_N16074988__V1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW2_N16074988_伍錫志_v1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHW2_N16074988_伍錫志_v1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CHW2_N16074988_伍錫志_v1Dlg 訊息處理常式
void drawHistImg(const Mat &src, Mat &dst) {
	int histSize = 256;
	float histMaxValue = 0;
	for (int i = 0; i<histSize; i++) {
		float tempValue = src.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale = (0.9 * 256) / histMaxValue;
	for (int i = 0; i<histSize; i++) {
		int intensity = static_cast<int>(src.at<float>(i)*scale);
		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
	}
}


BOOL CHW2_N16074988_伍錫志_v1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

									// TODO: 在此加入額外的初始設定
	FILE * pNewStdin = nullptr;
	AllocConsole();
	freopen_s(&pNewStdin, "CONOUT$", "w", stdout);
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CHW2_N16074988_伍錫志_v1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CHW2_N16074988_伍錫志_v1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CHW2_N16074988_伍錫志_v1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton1()
{
	Mat img = imread("lena.png");
	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	// TODO: 在此加入控制項告知處理常式程式碼
}


// Keypoints
//https://blog.csdn.net/NNNNNNNNNNNNY/article/details/52182091
void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton2()
{
	Mat  img_1 = imread("Bird1.jpg");
	Mat img_2 = imread("Bird2.jpg");
	int minHessian = 5000;
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(5);
	vector<KeyPoint> keypoints_1, keypoints_2;

	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	Mat img_keypoints_1; Mat img_keypoints_2;
	//drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);

	cout << "number of keypoints_1: " << keypoints_1.size() << endl;

	for (int i = 0; i < keypoints_1.size(); i++) {
		cout << keypoints_1[i].pt.x << ", " << keypoints_1[i].pt.y << endl;
	}

	waitKey(0);

	return;
	// TODO: 在此加入控制項告知處理常式程式碼
}

// Match keypoints
void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton3()
{
	Mat  img_1 = imread("Bird1.jpg");
	Mat  img_2 = imread("Bird2.jpg");	
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(5);
	vector<KeyPoint> keypoints_1, keypoints_2;

	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	Mat img_keypoints_1; Mat img_keypoints_2;
	//drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	//drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);
	cout << "number of descriptors_1: " << descriptors_1.size() << endl;
	cout << "number of descriptors_2: " << descriptors_2.size() << endl;
	//-- Show detected (drawn) keypoints
//	imshow("Keypoints 1", img_keypoints_1);
//	imshow("Keypoints 2", img_keypoints_2);

	cout << "number of keypoints1: " << keypoints_1.size() << endl;
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	imshow("【match图】", img_matches);

	for (int i = 0; i < keypoints_1.size(); i++) {
		cout << keypoints_1[i].pt.x << ", " << keypoints_1[i].pt.y << endl;
	}

	waitKey(0);

	return;
	// TODO: 在此加入控制項告知處理常式程式碼
}

//1.3 Feature vector histogram 
void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton4()
{
	Mat  img_1 = imread("Bird1.jpg");
	
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	vector<KeyPoint> keypoints_1;
	keypoints_1.clear();
	keypoints_1.push_back(KeyPoint(179.96f, 114.0f, 15.0));
	cout << keypoints_1.size() << endl;
	/*keypoints_1[0].pt.x = ;
	keypoints_1[0].pt.y = ;*/
	Mat descriptors_1;
	f2d->compute(img_1, keypoints_1, descriptors_1);

	cout << "number of descriptors_1: " << descriptors_1.size() << endl;
	cout <<"descriptors="<< descriptors_1 << endl;

	

	cout << "rows" << descriptors_1.rows << endl;
	cout << "columns" << descriptors_1.cols << endl;
	cout << "high" << endl;
	
	

	for (int i = 0; i < descriptors_1.cols; i++)
	{
		int j = 0;
	//	descriptors_1.at<int>(j, i) = descriptors_1.at<int>(j, i) / 100000000;
		cout << descriptors_1.at<int>(j, i) << endl;
	}
	

	Mat histImage(200, 128 *5 , CV_8UC1, Scalar(255,255,255));
	

	for (int i = 0; i < descriptors_1.cols; i++)
	{
		int j = 0;
		line( histImage, Point(5*i, 200),Point(5*i, 200 -descriptors_1.at<float>(0, i)),Scalar(0,0,255),2.5);
		cout << Point(i, 0) << ", " << Point(i,descriptors_1.at<float>(0, i)) << endl;
	}

	
	//circle(histImage, Point(25, 50), 12, Scalar(255, 0, 0));
	imshow("Feature vector histogram", histImage);

	/*
	setMouseCallback("calcHist Demo", onMouse2, NULL);
	while (1)
	{
		if (points_for_click2.size() == 0)
		{
			imshow("calcHist Demo", histImage);
		}
		if (points_for_click2.size() > 0 && points_for_click2.size() < 7)
		{
			for (int hehe = 1; hehe <= points_for_click2.size(); hehe++)
			{
				//circle(frame, points_for_click[hehe - 1], 8, Scalar(0, 0, 255), -1);
				rectangle(histImage, points_for_click2[hehe - 1] - Point2f(5, 5), points_for_click2[hehe - 1] + Point2f(5, 5), Scalar(0, 0, 255), 1);

			}
			imshow("calcHist Demo", histImage);
		}
		if (cvWaitKey(33) == 27) {
			break;
		}

	}
	*/
	
	waitKey(0);

	
	// TODO: 在此加入控制項告知處理常式程式碼
}


void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton5()
{
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(50,100).dynamicCast<BackgroundSubtractor>();
	//Ptr<BackgroundSubtractor> bg_model;
	// Create empy input img, foreground and background image and foreground mask.
	Mat img, foregroundMask, backgroundImage, foregroundImg;
	VideoCapture cap("bgSub.mp4");
	if (!cap.isOpened()) {
		std::cout << "Cannot load video" << std::endl;
		return;
	}

	while (1) {
		cap.grab();
		cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
		//cap.read(img);
		if (img.empty())
			break;
		resize(img, img, Size(640, 480));
		//cout << img.size();
		if (foregroundMask.empty()) {
			foregroundMask.create(img.size(), img.type());
		}
		//bg_model->apply(img, foregroundMask, true ? -1 : 0);
		bg_model->apply(img, foregroundMask, -1);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);

		foregroundImg = Scalar::all(0);

		img.copyTo(foregroundImg, foregroundMask);
		bg_model->getBackgroundImage(backgroundImage);
		imshow("Original video", img);
		//imshow("foreground mask", foregroundMask);
		imshow("foreground video", foregroundImg);
		if (waitKey(1) == 27)
			break;
	}
	destroyAllWindows();
}


//preprocessing
void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton6()
{
	points_for_click.clear();
	//Mat  img = imread("featureTracking.mp4");
	VideoCapture cap("featureTracking.mp4"); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
	{
		return;
	}

	/* Mat edges; */
	Mat frame;
	namedWindow("proprocessing", 1);
	double frnb(cap.get(CV_CAP_PROP_FRAME_COUNT));
	cout << "frame count = " << frnb << endl;
	cap.set(CV_CAP_PROP_POS_FRAMES, 1);
	bool success = cap.read(frame);
	if (!success) {
		cout << "Cannot read  frame " << endl;
	}
	imshow("proprocessing", frame);

	setMouseCallback("proprocessing", onMouse, NULL);

	while (true) 
	{	
		if (points_for_click.size() == 0)
		{
			imshow("proprocessing", frame);
		}
		if (points_for_click.size() > 0 && points_for_click.size() < 7)
		{
			for (int hehe = 1; hehe <= points_for_click.size(); hehe++)
			{
				//circle(frame, points_for_click[hehe - 1], 8, Scalar(0, 0, 255), -1);
				rectangle(frame, points_for_click[hehe - 1]-Point2f(5,5), points_for_click[hehe - 1]+Point2f(5,5), Scalar(0, 0, 255), 1);

			}
			imshow("proprocessing", frame);
		}
		if (points_for_click.size() ==7)
		{
			for (int hehe = 1; hehe <= points_for_click.size(); hehe++)
			{
				//circle(frame, points_for_click[hehe - 1], 8, Scalar(0, 0, 255), -1);
				rectangle(frame, points_for_click[hehe - 1] - Point2f(5, 5), points_for_click[hehe - 1] + Point2f(5, 5), Scalar(0, 0, 255), 1);

			}
			imshow("proprocessing", frame);

			cout << "7 points clicked" << endl;
			print(points_for_click);
			cout << endl;
			cout << points_for_click[0] << endl;
			break;
		}	
		if (cvWaitKey(33) == 27) {
			break;
		}
	}
	
	if (waitKey(0) == 27)
	{
		return;
	}	
	// TODO: 在此加入控制項告知處理常式程式碼
}

//video tracking
void CHW2_N16074988_伍錫志_v1Dlg::OnBnClickedButton7()
{
	trajectory.clear();

	VideoCapture cap("featureTracking.mp4"); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
	{
		return;
	}

	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);

	const int MAX_COUNT = 500;
	bool needToInit = false;
	bool nightMode = false;		
	

	if (!cap.isOpened())
	{
		cout << "Could not initialize capturing...\n";
		return ;
	}

	namedWindow("LK Demo", 1);

	Mat gray, prevGray, image, frame;
	vector<Point2f> new_points;

	while (1)
	{
		cap >> frame;
		if (frame.empty())
			break;

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		if (!points_for_click.empty())
		{
			vector<uchar> status;
			vector<float> err;
			if (prevGray.empty())
			{
				gray.copyTo(prevGray);
			}
			calcOpticalFlowPyrLK(prevGray, gray, points_for_click, new_points, status, err, winSize, 3, termcrit, 0, 0.001);			

			for ( int i  = 0; i < new_points.size(); i++)
			{
				trajectory.push_back((new_points[i]));
				circle(image, new_points[i], 3, Scalar(0, 255, 0), -1, 8);
			}
		}
		cout <<"trajectory.size()"<< trajectory.size() << endl;		
		for (int hehe = 1; hehe <= trajectory.size(); hehe++)
		{
			rectangle(image, trajectory[hehe - 1] - Point2f(5, 5), trajectory[hehe - 1] + Point2f(5, 5), Scalar(0, 0, 255), 1);
		}		
		imshow("LK Demo", image);
		waitKey(25);
		std::swap(new_points, points_for_click);
		cv::swap(gray,prevGray);
	}



	// TODO: 在此加入控制項告知處理常式程式碼
}
