#include "Cabecera.h"
int hMin = 0, sMin = 0, vMin = 0;
int hMax = 180, sMax = 255, vMax = 255;

Vec3b pixel;
int pixelGris;

Mat frame;
Mat frame2;
Mat frameFiltro;
Mat frameHSV;
Mat frameGris;

void eventoTrackbar(int v, void *p) {
	cout << "Cambio Trackbar" << endl;
}

void eventoRaton(int evento, int x, int y, int flags, void*p) {
	if (evento == EVENT_LBUTTONDOWN) {
		cout << "Clic boton izquierdo x=" << x << " y=" << y << endl;
	}
	else if (evento == EVENT_RBUTTONDOWN) {
		cout << "Clic boton derecho x=" << x << " y=" << y << endl;
		//pixel = frameFiltro.at<Vec3b>(y, x);
		pixel = frame.at<Vec3b>(y, x);
		//pixel = frameHSV.at<Vec3b>(y, x);
		//pixelGris = frameGris.at<uchar>(y, x);
		//cout << "Color: " << pixelGris << endl;
		cout << "Color: " << pixel << endl;
	}
	else if (evento == EVENT_MBUTTONDOWN) {
		cout << "Clic boton medio x=" << x << " y=" << y << endl;
	}
}

int main(){

	string nombreVideo = "videocorto.mp4";
	Mat imagenFondo = imread("catedral.jpg");
	Mat imagenFondoFinal = imread("catedral.jpg");
	VideoCapture video(nombreVideo);
	resize(imagenFondo, imagenFondo, Size(640, 480));
	resize(imagenFondoFinal,imagenFondoFinal, Size(640,480));

	int ratio = 3;
	int minimo = 50;

	Mat estructura = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	if (video.isOpened()) {

		namedWindow("Video", WINDOW_AUTOSIZE);
		//namedWindow("Filtro", WINDOW_AUTOSIZE);
		//namedWindow("Gris", WINDOW_AUTOSIZE);
		namedWindow("Imagen Binaria", WINDOW_AUTOSIZE);
		namedWindow("Mascara INV", WINDOW_AUTOSIZE);
		namedWindow("BG", WINDOW_AUTOSIZE);
		namedWindow("FG", WINDOW_AUTOSIZE);
		namedWindow("SUMA", WINDOW_AUTOSIZE);

		setMouseCallback("Video", eventoRaton, NULL);

		Mat imagenBinaria;
		Mat mascara;
		Mat mascaraInv;
		Mat bg;
		Mat fg;
		Mat suma;

		Mat roi = imagenFondo(Rect(0, 0, frame.cols, frame.rows));

		

		while (3 == 3) {

			video >> frame;
			
			
		
			if (frame.rows > 0 && frame.cols > 0) {
				resize(frame, frame, Size(640, 480));
				cvtColor(frame, frameHSV, COLOR_BGR2HSV);

				/*
				//cvtColor(frame, frameGris, COLOR_BGR2GRAY);

				//Filtros
				//GaussianBlur(frame, frameFiltro, Size(9, 9), 5); //Gaussian
				//medianBlur(frame, frameFiltro, 5);
				/*
				//Canny(frame, frameFiltro, minimo, minimo*ratio, 3);
				//Laplacian(frame, frameFiltro, CV_8UC1, 3);
				//inRange(frameFiltro, Vec3b(5, 5, 5), Vec3b(255, 255, 255), mascara);
				//inRange(frameFiltro, 255, 255, mascara);
				bitwise_not(mascara, mascaraInv);
				roi = imagenFondo(Rect(0, 0, frame.cols, frame.rows));
				bitwise_and(roi, roi, bg, mascaraInv);
				bitwise_and(frameFiltro, frameFiltro, fg, mascara);

				add(bg, fg, suma);

				suma.copyTo(imagenFondoFinal(Rect(0, 0, suma.cols, suma.rows)));
				*/
				/*
				//Operaciones morfológicas
				//erode(frame, frameFiltro, estructura);
				//dilate(frame, frameFiltro, estructura);

				
				//inRange(frameFiltro, Vec3b(pixel[0], pixel[1], pixel[2]), Vec3b(pixel[0]+(65-pixel[0]), pixel[1]+(255-pixel[1]), pixel[2]+(255-pixel[2])), mascara);//RGB
				
				//inRange(frameHSV, Vec3b(45, 100, 20), Vec3b(70, 255, 255), mascara);
				//inRange(frameHSV, Vec3b(pixel[0]+(45-pixel[0]), pixel[1]+(100-pixel[1]), pixel[2]+(20-pixel[2])), Vec3b(pixel[0] + (70 - pixel[0]), pixel[1] + (255 - pixel[1]), pixel[2] + (255 - pixel[2])), mascara);//HSV
				//inRange(frameHSV, Vec3b(pixel[0] + (118 - pixel[0]), pixel[1] + (100 - pixel[1]), pixel[2] + (20 - pixel[2])), Vec3b(pixel[0] + (255- pixel[0]), pixel[1] + (255 - pixel[1]), pixel[2] + (255 - pixel[2])), mascara);//HSV
				//inRange(frameGris, pixelGris-10, pixelGris+10, mascara);
				*/

				//cout << pixel << endl;
				inRange(frameHSV, Vec3b(pixel[0]+(45-pixel[0]), pixel[1]+(100-pixel[1]), pixel[2]+(20-pixel[2])), Vec3b(pixel[0] + (60 - pixel[0]), pixel[1] + (255 - pixel[1]), pixel[2] + (255 - pixel[2])), mascara);//HSV
				//inRange(frame, Vec3b(pixel[0], pixel[1], pixel[2]), Vec3b(pixel[0]+(255-pixel[0]), pixel[1]+(100-pixel[1]), pixel[2]+(100-pixel[2])), mascara);//RGB
				mascaraInv = mascara.clone();
				bitwise_not(mascara, mascara);

				roi = imagenFondo(Rect(0, 0, frame.cols, frame.rows));
				
				bitwise_and(roi, roi, bg, mascaraInv);
				bitwise_and(frame, frame, fg, mascara);

				add(bg, fg, suma);
				
				suma.copyTo(imagenFondoFinal(Rect(0, 0, suma.cols, suma.rows)));
				
				imshow("Video", frame);//Video
				//imshow("Gris", frameGris);//Gris
				imshow("HSV", frameHSV);//Mascara
				//imshow("Filtro", frameFiltro);//Filtro
				imshow("Imagen Binaria", mascara);//Mascara
				imshow("Mascara INV", mascaraInv);//Mascara
				
				imshow("SUMA", imagenFondoFinal);
				imshow("BG", bg);
				imshow("FG", fg);
				
				fg= Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
				bg = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
				
			}
			if (waitKey(23) == 27)
				break;
		}
	}
}
