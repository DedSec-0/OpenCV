//! [includes]
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

#include <iostream>
#include <string>

//! [namespace]
using namespace cv;
using namespace std;

// ![Functions]
void loadImage(string imageName, int**&img, int &width, int&height);
void blur(int** img, int width, int height);
void crop(int** img, int &width, int &height);
void addborder(int** img, int width, int height);
void zoom(int** img, int width, int height);
void removeColor(int** img, int width, int height);
void drawSquare(int** img, int width, int height);
void drawCircle(int** img, int width, int height);
void findSquare(int** img, int width, int height);
void Brightness(int** img, int width, int height);
void SquaredBlur(int** img);
void Mosaic(int** img, int width, int height);
void displayFrame(int**img, int width, int height, string winName);
void displayImage(int**img, int width, int height, string winName);
void saveImage(string imageName, int** image, int width, int height);

void GetAvg(int** img, int row, int column, int & Avg);
void PlaceBorder(int** &img, int width, int height, int Color);
bool Square(int** img, int Area, int width, int height, int Limit1, int Limit2);

int main(int argc, char** argv)
{
	//! [wait]
	int **img = NULL;
	int width = 500;
	int height = 500;
	int Option = 0;

	cout << "**************************** Welcome to Image Editor ***************************" << endl;
	cout << "Enter any of the option number to perform on image from below or 0 to quit" << endl << endl;
	cout << "1. Load Image" << endl << "2. Blur Image" << endl << "3. Crop Image" << endl << "4. Add a border in a Image" << endl << "5. Zoom Image" << endl;
	cout << "6. Remove Certain Color from Image" << endl << "7. Draw Hollow Square on image" << endl << "8. Draw Hollow Circle on image" << endl;
	cout << "9. Find Square in Image" << endl << "10. Adjust Brightness in Image" << endl << "11. Blur certain points in image in Square" << endl;
	cout << "12. Make an image Mosaic" << endl << "13. Display Image" << endl << "14. Display Frame" << endl << "15. Save Image" << endl << "16. Load Saved Image" << endl << "Write Option Number: ";
	cin >> Option;
	//blur(image, width, height);

	while (Option != 0)
	{
		switch (Option)
		{
		case 1:
			loadImage("goat.jpg", img, width, height);
			break;
		case 2:
			blur(img, width, height);
			break;
		case 3:
			crop(img, width, height);
			break;
		case 4:
			addborder(img, width, height);
			break;
		case 5:
			zoom(img, width, height);
			break;
		case 6:
			removeColor(img, width, height);
			break;
		case 7:
			drawSquare(img, width, height);
			break;
		case 8:
			drawCircle(img, width, height);
			break;
		case 9:
			findSquare(img, width, height);
			break;
		case 10:
			Brightness(img, width, height);
			break;
		case 11:
			SquaredBlur(img);
			break;
		case 12:
			Mosaic(img, width, height);
			break;
		case 13:
			displayImage(img, width, height, "First Image");
			break;
		case 14:
			displayFrame(img, width, height, "First Image");
			break;
		case 15:
			saveImage("goat2.bmp", img, width, height);
			break;
		case 16:
			loadImage("goat2.bmp", img, width, height);
			break;
		default:
			cout << "Wrong Input!!!!...... Try Again!";
			break;
		}

		cout << "Select Another Option or 0 to quit: ";
		cin >> Option;
	}
	cvDestroyAllWindows();
	
	return 0;
}

void loadImage(string imageName, int**&img, int &width, int&height)
{
	//! [load]
	string imgName = "data/" + imageName;
	Mat image;
	//! [mat]

	//! [imread]
	image = imread(imgName.c_str(), IMREAD_COLOR); // Read the file
												   //! [imread]
	cout << "Image is Loaded Successfully. . ." << endl;
	cout << "Image Name: " << imgName << endl;

	Mat frame;
	//image.copyTo(frame);
	cvtColor(image, frame, COLOR_BGR2GRAY);


	//! [window]
	cout << "Dimensions: " << frame.rows << "*" << frame.cols << endl;
	width = frame.cols;
	height = frame.rows;
	img = new int*[height];

	for (int i = 0; i < height; i++)
		img[i] = new int[width];

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{

			img[i][j] = frame.at<uchar>(i, j);
		}
	}
}

void blur(int** img, int width, int height)
{
	int Avg = 0;

	for (int i = 0; i < height - 4; i++)
	{
		for (int j = 0; j < width - 4; j++)
		{
			GetAvg(img, i, j, Avg);
			img[i][j] = Avg;
		}
	}

	cout << "Image Blurred Succesfully. . ." << endl;
}

void crop(int** img, int &width, int &height)
{
	int CropW1 = 0;
	int CropH1 = 0;
	int CropW2 = 0;
	int CropH2 = 0;
	int **temp = new int*[height];

	cout << "Enter the number of pixels you want to crop from top side and bottom side: ";
	cin >> CropH1 >> CropH2;
	cout << "Enter the number of pixels you want to crop from left side and right side: ";
	cin >> CropW1 >> CropW2;

	//Cropping Top side and left side
	for (int i = 0; i < height - CropH1; i++)
	{
		img[i] = img[i + CropH1];
		for (int j = 0; j < width - CropW1; j++)
		{
			img[i][j] = img[i][j + CropW1];
		}
	}
	height -= CropH1;
	width -= CropW1;

	//Cropping Top bottom side and right side
	for (int i = 0; i < height; i++)
		temp[i] = new int[width];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] =  img[i][j];
		}
	}
	height -= CropH2;
	width -= CropW2;
	img = new int*[height];

	for (int i = 0; i < height; i++)
		img[i] = new int[width];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img[i][j] = temp[i][j];
		}
	}
	delete[] temp;

	cout << "Image Cropped Succesfully. . ." << endl;
}

void addborder(int** img, int width, int height)
{
	char Border;
	int counter = 0;
	int ColorCode = 0;

	cout << "Select a border color" << endl << "1. B for black" << endl << "2. W for white" << endl << "3. G for Grey: " << endl << "4. D for Gradient: ";
	cin >> Border;

	switch (Border)
	{
	case 'B': case 'b':
		ColorCode = 0;
		PlaceBorder(img, width, height, ColorCode);
		cout << "Border Added Succesfully. . ." << endl;
		break;

	case 'W': case 'w':
		ColorCode = 255;
		PlaceBorder(img, width, height, ColorCode);
		cout << "Border Added Succesfully. . ." << endl;
		break;

	case 'G': case 'g':
		ColorCode = 128;
		PlaceBorder(img, width, height, ColorCode);
		cout << "Border Added Succesfully. . ." << endl;
		break;

	case 'D': case 'd':
		ColorCode = 1;
		PlaceBorder(img, width, height, ColorCode);
		cout << "Border Added Succesfully. . ." << endl;
		break;

	default:
		cout << "Wrong Color Entered!!!!...." << endl;
		break;
	}
}

void zoom(int** img, int width, int height)
{
	int **temp = new int*[height];
	int Zoom = 0;
	int ZoomH = 0;
	int ZoomW = 0;

	cout << "Enter 2 for 2x zoom, 4 for 4x zoom or 8 for 8x zoom: ";
	cin >> Zoom;

	ZoomH = height / Zoom;
	ZoomW = width / Zoom;
	for (int i = 0; i < height; i++)
		temp[i] = new int[width];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] = img[i][j];
		}
	}
	for (int i = 0; i < height - ZoomH; i++)
	{
		temp[i] = temp[i + ZoomH];
		for (int j = 0; j < width - ZoomW; j++)
		{
			temp[i][j] = temp[i][j + ZoomW];
		}
	}
	height -= ZoomW;
	width -= ZoomW;

	displayImage(img, width, height, "Zoomed Image");
	delete[] temp;
}

void removeColor(int** img, int width, int height)
{
	int Remove = 0;

	cout << "Enter 0 to remove Black color or 1 to remove White color or 2 to remove Grey Color: ";
	cin >> Remove;

	switch (Remove)
	{
	case 0:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (img[i][j] >= 0 && img[i][j] <= 30)
					img[i][j] = 128;
			}
		}
		break;

	case 1:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (img[i][j] >= 180 && img[i][j] <= 255)
					img[i][j] = 128;
			}
		}
		break;
	case 2:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (img[i][j] >= 87 && img[i][j] <= 162)
					img[i][j] = 255;
			}
		}
		break;

	default:
		cout << "Wrong Input!!!!.....";
		break;
	}

	cout << "Colored Removed Succesfully. . ." << endl;
	
}

void drawSquare(int** img, int width, int height)
{
	int Area = 0;
	int Color = 0;
	int CounterH = 0;
	int CounterW = 0;
	int j = 0;

	cout << "Enter the color of square" << endl << "0 for black" << endl << "128 for grey " << endl << "255 for white: ";
	cin >> Color;
	cout << "Enter the Area of square: ";
	cin >> Area;

	for (int i = height/2; CounterH < Area; i++, CounterH++)
	{
		j = width/2;
		if (!(CounterH > 0 && CounterH < Area-1))
		{
			for (; CounterW < Area; j++, CounterW++)
				img[i][j] = Color;
		}
		else
		{
			img[i][j] = Color;
			img[i][j + (Area-1)] = Color;
		}
		CounterW = 0;
	}

	cout << "Square Drawed Succesfully. . ." << endl;
}

void drawCircle(int** img, int width, int height)
{
	int Radius = 0;
	float Distance = 0;
	int Color = 0;
	int CounterH = 0;
	int CounterW = 0;

	cout << "Enter the color of Circle" << endl << "0 for black" << endl << "128 for grey " << endl << "255 for white: ";
	cin >> Color;
	cout << "Enter the Radius of Circle: ";
	cin >> Radius;

	for (int i = height / 2; CounterH <= 2 * Radius; i++, CounterH++)
	{
		for (int j = width / 2; CounterW <= 2 * Radius; j++, CounterW++)
		{
			Distance = sqrt((CounterH - Radius)*(CounterH - Radius) + (CounterW - Radius)*(CounterW - Radius));
			if ((Distance > Radius - 0.5 && Distance < Radius + 0.5))
			{
				img[i][j] = Color;
			}
		}
		CounterW = 0;
	}

	cout << "Circle Drawed Succesfully. . ." << endl;
}

void findSquare(int** img, int width, int height)
{
	int Area = 0;
	bool Found = 0;

	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 0; j < width - 1; j++)
		{
			Found = Square(img, Area, j, i, height, width);
			if (Found)
			{
				break;
			}
		}
		if (Found)
		{
			cout << "Square Found" << endl;
			break;
		}
	}

	if (!Found)
	{
		cout << "Square not Found" << endl;
	}
}

void Brightness(int** img, int width, int height)
{
	char Brightness = '\0';

	cout << "Enter + to increase brigtness and - to decrease brigness: ";
	cin >> Brightness;

	switch (Brightness)
	{
	case '+':
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (img[i][j] < 230)
				{
					img[i][j] = img[i][j] + 25;
				}
			}
		}
		break;

	case '-':
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (img[i][j] > 50)
				{
					img[i][j] = img[i][j] - 50;
				}
			}
		}
		break;

	default:
		break;
	}

	cout << "Brigtness Adjusted Succesfully. . ." << endl;
}

void SquaredBlur(int** img)
{
	int Area = 0;
	int x = 0;
	int y = 0;
	int Avg = 0;
	int CounterW = 0;
	int CounterH = 0;

	cout << "Enter the points you want to blur around: ";
	cin >> x >> y;
	cout << "Enter the Area of blur: ";
	cin >> Area;

	for (int i = x; CounterH < Area; i++, CounterH++)
	{
		CounterW = 0;
		for (int j = y; CounterW < Area; j++, CounterW++)
		{
			GetAvg(img, i, j, Avg);
			img[i][j] = Avg;
		}
	}

	cout << "Position Blurred Succesfully. . ." << endl;
}

void Mosaic(int** img, int width, int height)
{
	int Avg = 0;

	for (int i = 0; i < height - 4; i += 2)
	{
		for (int j = 0; j < width - 4; j += 2)
		{
			GetAvg(img, i, j, Avg);
			img[i][j] = Avg;
		}
	}

	cout << "Image Mosaiced Succesfully. . ." << endl;
}

void displayImage(int**img, int width, int height, string winName)
{
	Mat frame = Mat(height, width, CV_8U);

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{

			frame.at<uchar>(i, j) = img[i][j];
		}
	}


	namedWindow(winName, WINDOW_AUTOSIZE); // Create a window for display.
										   //! [window]

										   //! [imshow]
	imshow(winName, frame);                // Show our image inside it.
										   //Sleep(1);	
										   //! [imshow]
	cout << "Image Displayed Succesfully. . ." << endl;
	waitKey(0); // Wait for a keystroke in the window

}

void displayFrame(int**img, int width, int height, string winName)
{
	Mat frame = Mat(height, width, CV_8U);

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{

			frame.at<uchar>(i, j) = img[i][j];


		}
	}


	namedWindow(winName, WINDOW_AUTOSIZE); // Create a window for display.
										   //! [window]

										   //! [imshow]
	imshow(winName, frame);                // Show our image inside it.
										   //Sleep(1);	
										   //! [imshow]

	waitKey(1); // Wait for a keystroke in the window
	cout << "Frame Displayed Succesfully . . .";
}

void saveImage(string imageName, int** image, int width, int height)
{

	Mat frame = Mat(height, width, CV_8U);

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{

			frame.at<uchar>(i, j) = image[i][j];


		}
	}

	string imgName = "data/" + imageName;

	imwrite(imgName, frame);

	cout << "Image in BMP format saved Succesfully. . ." << endl;
}

void GetAvg(int** img, int row, int column, int & Avg)
{
	int Sum = 0;

	for (int i = row; i < row + 4; i++)
	{
		for (int j = column; j < column + 4; j++)
		{
			Sum += img[i][j];
		}
	}

	Avg = Sum / 16;
}

void PlaceBorder(int** &img, int width, int height, int Color)
{
	int counter = 0;
	const int BorderWidth = 7;
	int Gradient = Color;

	for (int i = 0; i < BorderWidth; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img[i][j] = Color;
		}
		if (Gradient == 1)
		{
			Color += 39;
		}
	}
	for (int i = height - 1; counter < BorderWidth; i--, counter++)
	{
		for (int j = 0; j < width; j++)
		{
			img[i][j] = Color;
		}
		if (Gradient == 1)
		{
			Color += 40;
		}
	}
	for (int i = 0; i < BorderWidth; i++)
	{
		for (int j = 0; j < height; j++)
		{
			img[j][i] = Color;
		}
		if (Gradient == 1)
		{
			Color += 40;
		}
	}
	counter = 0;
	for (int i = width - 1; counter < BorderWidth; i--, counter++)
	{
		for (int j = 0; j < height; j++)
		{
			img[j][i] = Color;
		}
		if (Gradient == 1)
		{
			Color += 40;
		}
	}
}

bool Square(int** img, int Area, int width, int height, int Limit1, int Limit2)
{
	int Length1 = 0;
	int Length2 = 0;
	int Length3 = 0;
	int Length4 = 0;
	int i = 0;
	int j = 0;

	i = height;
	j = width;
	while (img[i][j] == img[i][j + 1] && j < Limit2 - 2)
	{
		Length1++;
		j++;
	}

	while (img[i][j] == img[i + 1][j] && i < Limit1 - 2)
	{
		Length4++;
		i++;
	}

	i = height;
	j = width;
	while (img[i][j] == img[i + 1][j] && i < Limit1 - 2)
	{
		Length3++;
		i++;
	}

	while (img[i][j] == img[i][j + 1] && j < Limit2 - 2)
	{
		Length2++;
		j++;
	}

	if (Length1 >= 10 && Length2 >= 10 && Length3 >= 10 && Length4 >= 10)
	{
		if (Length1 == Length2 && Length2 == Length3 && Length3 == Length4)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}