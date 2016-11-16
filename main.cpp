#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	/*
    char filename[1024];
    printf("Enter a filename (e.g. small.ogv): ");
    scanf("%s", filename);
    if (filename[0] == '\0')
    {
        fprintf(stderr, "Please select a file\n");
        return EXIT_FAILURE;
    }
    */
    VideoCapture vc = VideoCapture("samples/small_test.mp4");
    int frameCount = vc.get(CV_CAP_PROP_FRAME_COUNT);
    int frameHeight = vc.get(CV_CAP_PROP_FRAME_HEIGHT );
    int frameWidth = vc.get(CV_CAP_PROP_FRAME_WIDTH );

    //render out image
    Mat renderImage;

    //current frame from video
    Mat image;

    //constructed STI frame for center columns
    Mat STI_image_cols(frameHeight, frameCount, CV_8UC3, Scalar::all(0));

    //constructed STI frame for center rows
    Mat STI_image_rows(frameWidth, frameCount, CV_8UC3, Scalar::all(0));

    // Create a window
    namedWindow("PLAYER", WINDOW_NORMAL);
    namedWindow("STI_COL_DISPLAY", WINDOW_NORMAL);
    namedWindow("STI_ROW_DISPLAY", WINDOW_NORMAL);

    int offset = 100;

    moveWindow("PLAYER", offset, offset);
    moveWindow("STI_COL_DISPLAY", offset+frameWidth, offset);
    moveWindow("STI_ROW_DISPLAY", offset+frameWidth+frameWidth, offset);

    int centerColumn = frameWidth/2;
    int centerRow = frameHeight/2;

    int currentColumn = 0;

    while (true)
    {
        // Get the image from the video file
        vc.read(image);

        // Stop if there are no more frames in the video
        //if (image.empty()) break;
	    
	    if(!image.empty()){

	        if(currentColumn <= frameCount){
		        // Transfer center column to new image
		        for (int row = 0; row < image.size().height; row++) {
		            Vec3b bgrPixel = image.at<Vec3b>(row, centerColumn);
		            STI_image_cols.at<Vec3b>(row, currentColumn) = bgrPixel;
		        }
		        // Transfer center row to new image
		        for (int col = 0; col < image.size().width; col++) {
		            Vec3b bgrPixel = image.at<Vec3b>(centerRow, col);
		            STI_image_rows.at<Vec3b>(col, currentColumn) = bgrPixel;
		        }
		    }

		    currentColumn++;

	        // Display the image 
	        imshow("PLAYER", image);
	        imshow("STI_COL_DISPLAY", STI_image_cols);
	        imshow("STI_ROW_DISPLAY", STI_image_rows);
	    }

        // Sleep for 30 milliseconds. Note: This function is the only method in 
        // HighGUI that can fetch and handle events,  so it needs to be called 
        // periodically for normal event processing unless HighGUI is used within 
        // an environment that takes care of event processing.
        int c = waitKey(30);

        if(c == 32){
            vc.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
            STI_image_cols = Mat(frameHeight, frameCount, CV_8UC3, Scalar::all(0));
            STI_image_rows = Mat(frameWidth, frameCount, CV_8UC3, Scalar::all(0));
            currentColumn = 0;
            continue;
        }

        // Quit if any key is pressed
        if (c != -1) break;
    }
}