#Deteccion de colores en un video
import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(cap.isOpened()):
    ret, img = cap.read() #esta vez usamos 'img' en lugar de 'frame'

    if (ret == True):
        #convertimos a hsv
        img_hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

        #definimos los rangos del color que queremos detectar y buscamos en la iage
        azul_bajo = np.array([100,50,50],np.uint8)
        azul_alto = np.array([130,255,255],np.uint8)
        mascara = cv2.inRange(img_hsv,azul_bajo,azul_alto)

        #ahora buscamos los contornos 

        contornos,_ = cv2.findContours(mascara,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

        for c in contornos:
            area = cv2.contourArea(c)
            if (area>1000):
                
                x,y,w,h = cv2.boundingRect(c)
                cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
                cv2.putText(img,str(area),(x,y-5),cv2.FONT_HERSHEY_SIMPLEX,0.5,(255,0,0),4)
        
        
        cv2.imshow('Video binarizado',mascara)
        cv2.imshow('Video de entrada',img)

        if(cv2.waitKey(1) & 0xFF == ord('q')):
            break
    else:
        break

cap.release()
cv2.destroyAllWindows()
