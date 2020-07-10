//#include "pch.h"
#include<fstream>
#include<sstream>
#include<iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
/*
 * Write with Ramin Shirali
 * Programming in cpp with opencv library
 * Date released 20/04/1399
 */
using namespace std;
using namespace cv;


int main(int argc, char** argv)
{

    CV_UNUSED(argc);
    CV_UNUSED(argv);

    Mat image,gray,blueGray,thresh,close;

    vector<vector<Point> > contoure;

    double t = getTickCount();// برای محاسبه زمان پردازش

    image = imread("C:\\Users\\YaHosein\\Desktop\\example\\qt\\exOpencv\\gray_image.png");//خواندن تصویر

    if(image.empty())return 1;

    resize(image,image,Size(image.cols*0.75,image.rows*0.75),0,0,INTER_CUBIC);// تغییر اندازه تصویر

    imshow("Orginal",image);

    cvtColor(image,gray,COLOR_BGR2GRAY); // تبدیل عکس رنگی به خاکستری

    imshow("Gray",gray);

    GaussianBlur(gray,blueGray,Size(15,15),0);// حذف نویزهای فرکانس بالا

    imshow("Blue Gray",blueGray);

    threshold(gray,thresh,50,255,THRESH_BINARY_INV);//آستانه گیری و تبدیل تصویر به مقادیر باینری

    imshow("threshold",thresh);

    morphologyEx(thresh,close,MORPH_CLOSE,Mat(),Point(-1,-1),4);// پر کردن سکه ها

    imshow("Closeing Image",close);

    findContours(close , contoure,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE); // پیدا کردن کاممپوننت ها متصل بهم در تصویر

    vector<vector<Point> >::iterator it = contoure.begin(); // ایجاد حلقه برای بدست آوردن سکه ها و گرفتن موقعیت آنها

    while (it != contoure.end()) {

        RotatedRect rotatedRect = fitEllipse(*it);// بدست آوردن ابعاد ،سایز ،و نقطه مرکز کامپوننت ها

        Rect rect = boundingRect(*it); // گرفتن موقعیت اضلاع آنها

        rectangle(image,rect,Scalar(255,255,255),2);//کشیدن مربع دورتادور کامپوننت ها

        ellipse(image,rotatedRect,Scalar(0,255,0),2);// کشیدن منحنی بوسیله ابعاد نقطه مرکزی و مقدار چرخش آن

        putText(image,to_string(distance(contoure.begin(),it)+1),rotatedRect.center,FONT_HERSHEY_SIMPLEX,0.5,Scalar(100,200,150),2);// نشان دادن تعداد کامپوننت ها

        ++it;

    }
    imshow("result Image",image);
    cout <<  (getTickCount()-t) / getTickFrequency()<< " mSec"<<endl;// نشان دادن زمان پردازش به میلی ثانیه
    waitKey(0);
}
