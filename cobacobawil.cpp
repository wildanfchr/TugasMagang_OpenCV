#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture vid("ball2.mp4");
    Mat gambar, thresh, gambar_ukur, gambar_hsv;

    int L_H = 0;
    int U_H = 68;
    int L_S = 9;
    int U_S = 246;
    int L_V = 241;
    int U_V = 255;

    namedWindow("threshold", WINDOW_AUTOSIZE);

    createTrackbar("L_H", "threshold", &L_H, 179);
    createTrackbar("U_H", "threshold", &U_H, 179);
    createTrackbar("L_S", "threshold", &L_S, 255);
    createTrackbar("U_S", "threshold", &U_S, 255);
    createTrackbar("L_V", "threshold", &L_V, 255);
    createTrackbar("U_V", "threshold", &U_V, 255);
        
    while(true){
        vid.read(gambar);
        resize(gambar, gambar_ukur, Size(), 0.5, 0.5);
        cvtColor(gambar_ukur, gambar_hsv, COLOR_BGR2HSV);
        
        inRange(gambar_hsv, Scalar(L_H, L_S, L_V), Scalar(U_H, U_S, U_V), thresh);

        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_TREE, CHAIN_APPROX_NONE);
    
    for(int i=0; i<contours.size(); i++)
    {
        vector<Point>contours_new;
        Point2f center;
        float radius;
        contours_new = contours [i];
        minEnclosingCircle(contours_new, center, radius);

        if (radius>30 && radius<78)
        {
            circle(gambar_ukur, center, radius, Scalar(255, 0, 0), 3);
            printf("x: %2f y: %2f rad: %f\n\n", center.x, center.y, radius);
        }
    }
    imshow ("YNTKTS", gambar_ukur);
    imshow ("YNTKTS_2", thresh);
    
    if ( (char)27 == (char) waitKey(150) )
    break;
    }
    return 0;
}