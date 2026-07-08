#include <iostream>            // WAJIB: untuk std::cout dan std::cerr
#include <opencv2/opencv.hpp>
#include <time.h>
#include <chrono>
#include <ctime>


int main(int argc, char *argv[]) {
    cv::VideoCapture webcam(0);

    if (!webcam.isOpened()) {
        std::cerr << "Cannot open webcam" << std::endl;
        return 1;
    }



    cv::Mat prevFrame, prevGray;
    webcam.read(prevFrame);
    cv::cvtColor(prevFrame, prevGray, cv::COLOR_BGR2GRAY);

    while (true) {
        cv::Mat frame, gray;
        webcam.read(frame);
        if (frame.empty()) break;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::Mat flow;
        cv::calcOpticalFlowFarneback(prevGray, gray, flow,
            0.5, 3, 15, 3, 5, 1.2, 0);

        cv::Mat flowParts[2];
        cv::split(flow, flowParts);
        cv::Mat magnitude;
        cv::magnitude(flowParts[0], flowParts[1], magnitude);
        double avgMotion = cv::mean(magnitude)[0];

        std::cout << "avgMotion: " << avgMotion << std::endl;

        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // 2. Format the time into a string (e.g., 2026-07-27_09-48-52.jpg)
        std::stringstream ss;
        ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d_%H-%M-%S") << ".jpg";
        std::string filename = ss.str();

        // 3. Create a dummy image (replace this with your actual cv::Mat image)
        cv::Mat myImage = cv::Mat::zeros(480, 640, CV_8UC3);


        if (avgMotion > 1.0) {
            cv::imwrite(filename, frame);
            std::cout << "avgMotion: " << avgMotion << std::endl;
        }

        prevGray = gray.clone();
    }
    return 0;
}
