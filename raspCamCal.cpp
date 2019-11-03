#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    vector<vector<cv::Point2f>> image_points;
    vector<vector<cv::Point3f>> object_points;
    char* path = "/Users/aspirin/Documents/git_repo/VisCal/PatternPicture/test_img";
    string path_full;
    int board_w = 4;
    int board_h = 11;
    int board_n = board_w * board_h;
    cv::Size image_size;

    for(int i=0;i<9;i++){
        path_full = string(path)+to_string(i)+string(".jpg");
        cout<<path_full<<endl;    
        cv::Mat img = cv::imread(path_full);
        image_size = img.size();
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        vector<cv::Point2f> corners; 
        bool found = cv::findCirclesGrid(img, cv::Size(board_w,board_h),corners, cv::CALIB_CB_ASYMMETRIC_GRID);
        if(found){
            cv::drawChessboardCorners(img, cv::Size(board_w,board_h),corners,found);
            image_points.push_back(corners);
            object_points.push_back(vector<cv::Point3f>());
            vector<cv::Point3f>& opt = object_points.back();
            opt.resize(board_n);
            for(int j=0; j<board_n; j++){
                opt[j]=cv::Point3f(j/board_w, (j%board_w)*2+((j/board_w)%2), 0.f);
            }
            cv::imshow("show",img);
            cv::waitKey();
        }
        cout<<"found="<<found<<endl;
    }

   /*Start Calibration*/
    cv::Mat intrinsic_matrix, distortion_coeffs;
    double error = cv::calibrateCamera(object_points, image_points, image_size, intrinsic_matrix, distortion_coeffs, cv::noArray(), cv::noArray());
    cout<<"error ="<< error<<endl;
    cout<<"Intrinsic Matrix="<<intrinsic_matrix<<endl;
    cout<<"Image Size:"<<image_size<<endl;
    cout<<"Distortion Matrix:"<<distortion_coeffs<<endl;
    return 0;
}
