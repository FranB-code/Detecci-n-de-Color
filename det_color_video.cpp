#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    // Abrir la cámara (0 = cámara por defecto)
    cv::VideoCapture camara(1);
    if (!camara.isOpened()) {
        std::cerr << "No se pudo abrir la cámara." << std::endl;
        return -1;
    }

    std::cout<<"Pulsa q para salir del video"<<std::endl;

    while (true) {
        cv::Mat frame;
        camara >> frame;  // capturar frame
        if (frame.empty()) break;

        // Convertir a HSV
        cv::Mat frameHSV;
        cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);

        // Definir el rango de color VERDE en HSV
        cv::Scalar verdeBajo(35, 50, 50);
        cv::Scalar verdeAlto(85, 255, 255);
        cv::Mat mascaraVerde;
        cv::inRange(frameHSV, verdeBajo, verdeAlto, mascaraVerde);

        // Encontrar contornos
        std::vector<std::vector<cv::Point>> contornos;
        cv::findContours(mascaraVerde, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contorno : contornos) {
            if (cv::contourArea(contorno) > 500) {
                cv::Rect rect = cv::boundingRect(contorno);
                cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);  // dibujar rectángulo verde
            }
        }

        // Mostrar resultados
        cv::imshow("Detección de Verde", frame);

        

        // Salir si se presiona 'q'
        if (cv::waitKey(1) == 'q') break;
    }

    camara.release();
    cv::destroyAllWindows();
    return 0;
}
