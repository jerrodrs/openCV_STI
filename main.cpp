#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    char filename[1024];
    printf("Enter a filename (e.g. small.ogv): ");
    scanf("%s", filename);
    if (filename[0] == '\0')
    {
        fprintf(stderr, "Please select a file\n");
        return EXIT_FAILURE;
    }
    
    VideoCapture vc = VideoCapture(filename);
    int frameCount = vc.get(CV_CAP_PROP_FRAME_COUNT);
    int frameHeight = vc.get(CV_CAP_PROP_FRAME_HEIGHT );
    int frameWidth = vc.get(CV_CAP_PROP_FRAME_WIDTH );

    //current frame from video
    Mat image;

    //constructed STI frame for center columns
    Mat STI_image_cols(frameWidth, frameCount, CV_8UC3, Scalar::all(0));

    //constructed STI frame for center rows
    Mat STI_image_rows(frameHeight, frameCount, CV_8UC3, Scalar::all(0));

    // Create a window
    namedWindow("Display", WINDOW_NORMAL);

    while (true)
    {
        // Get the image from the video file
        vc.read(image);

        // Stop if there are no more frames in the video
        if (image.empty()) break;

        // Draw some colours on the image
        for (int col = 0; col < image.size().width; col++)
        for (int row = 16; row < 32; row++) {
            Vec3b bgrPixel = image.at<Vec3b>(row, col);
            if (col < image.size().width / 3)
                bgrPixel[0] = 255; // left third, blue
            else if (col < image.size().width * 2 / 3)
                bgrPixel[1] = 255; // middle third, green
            else
                bgrPixel[2] = 255; // right third, red
            image.at<Vec3b>(row, col) = bgrPixel;
        }

        // Display the image 
        imshow("Display", image);

        // Sleep for 30 milliseconds. Note: This function is the only method in 
        // HighGUI that can fetch and handle events,  so it needs to be called 
        // periodically for normal event processing unless HighGUI is used within 
        // an environment that takes care of event processing.
        int c = waitKey(30);

        // Quit if any key is pressed
        if (c != -1) break;
    }
}