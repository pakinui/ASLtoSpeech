import io
import os
import sys
import time
import mediapipe as mp
import numpy as np
import pickle
import cv2
from PySide6.QtCore import Qt, QThread, Signal, Slot
from PySide6.QtGui import QAction, QImage, QKeySequence, QPixmap
from PySide6.QtWidgets import (QApplication, QComboBox, QGroupBox,
                               QHBoxLayout, QLabel, QMainWindow, QPushButton,
                               QSizePolicy, QVBoxLayout, QWidget)

from ctypes import *
import PySide6.QtMultimedia
from PySide6.QtMultimedia import QVideoSink
from PySide6.QtMultimedia import QVideoFrame
from io import BytesIO

class PythonVideoSink(PySide6.QtCore.QObject):
  def __init__(self, psink):
    self.psink = psink


  def videoFrame(self, psink):
    print("changed")

class PythonTest:


    def __init__(self):

        self.img_path = "../../resources/captures/output.jpg"

        self.model_dict = pickle.load(open('ASL_model.p', 'rb'))
        self.model =self.model_dict['model']

        # Create a Python object that will listen for the signal.
        #self.sink = QVideoSink()

        #self.psink = PythonVideoSink(self.sink)
        # Connect the signal to the Python object.
        #sink.imageAvailable.connect(sink.renderFrame)
        #self.sink.videoFrameChanged.connect(self.psink.videoFrame)

        self.cap = cv2.VideoCapture(0)



        self.mp_hands = mp.solutions.hands
        self.mp_drawing = mp.solutions.drawing_utils
        self.mp_drawing_styles = mp.solutions.drawing_styles

        self.hands = self.mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)


        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 20.0, (640, 480))


    #def overlay(frame):
    #    while True:
    def print_hello():
            print("Hello from Python module!")
            return "heyyyy"

    def overlay(self):
        #print("overlay")
         # Load the image from the captures folder



         frame = cv2.imread("../../resources/captures/output.jpg")

        #  frame1 = np.frombuffer(frame_data, dtype=np.uint8)
        #  frame1 = cv2.imdecode(frame1, cv2.IMREAD_COLOR)
#         cap = cv2.VideoCapture(0)
         data_aux = []
         x_ = []
         y_ = []

#        #  ret, frame = self.cap.read()
##         frame = cv2.imread('.\captures\1.jpg')
#        #  frame = frame1
         H, W, _ = frame.shape

         frame = cv2.flip(frame, 1)
         frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

         results = self.hands.process(frame_rgb)
         if results.multi_hand_landmarks:
             num_detected_hands = len(results.multi_hand_landmarks)

#             # for hand_landmarks in results.multi_hand_landmarks:
#             #     mp_drawing.draw_landmarks(
#             #         frame,  # image to draw
#             #         hand_landmarks,  # model output
#             #         mp_hands.HAND_CONNECTIONS,  # hand connections
#             #         mp_drawing_styles.get_default_hand_landmarks_style(),
#             #         mp_drawing_styles.get_default_hand_connections_style())

             for hand_landmarks in results.multi_hand_landmarks:
                 for i in range(len(hand_landmarks.landmark)):
                     x = hand_landmarks.landmark[i].x
                     y = hand_landmarks.landmark[i].y

                     x_.append(x)
                     y_.append(y)

                 for i in range(len(hand_landmarks.landmark)):
                     x = hand_landmarks.landmark[i].x
                     y = hand_landmarks.landmark[i].y
                     data_aux.append(x - min(x_))
                     data_aux.append(y - min(y_))

             if num_detected_hands == 1:
                 # If only one hand is detected, duplicate the data_aux
                 data_aux += data_aux

             x1 = int(min(x_) * W) - 10
             y1 = int(min(y_) * H) - 10

             x2 = int(max(x_) * W) - 10
             y2 = int(max(y_) * H) - 10

             prediction = self.model.predict([np.asarray(data_aux)])
             predicted_class_label = prediction[0]

             cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)
             cv2.putText(frame, predicted_class_label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3,
                         cv2.LINE_AA)

#         #self.out.write(frame)
#         #  output_path = './../resources/captures/2.jpg'
#         #  cv2.imwrite(output_path, frame)
#         #  return frame
#         # Save the modified image to a BytesIO object
#         # Create a QImage from the processed frame
#         # Get the frame format.
#         #video_frame_format = QVideoFrame.Format_BGR888

#         # Convert the frame to RGB.
#         #frame = frame.rgb()

#         # Overlay the text on the frame.
#         #cv2.putText(frame, text, (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 0), 3)

#         # Convert the frame to a QVideoFrame object.

#         # Create a QImage from the processed frame
#         # Save the edited frame as a .jpg file.
#         #image_path2 = "../../resources/captures/output2.jpg"

             cv2.imwrite("../../resources/captures/output2.jpg", frame)
    #         #cv2.imwrite(image_path2, frame)

             return str(predicted_class_label)

         return ""
         #return "hiiii"
        # cv2.imshow('frame', frame)
        # if cv2.waitKey(1) == ord('q'):
        #     break


    #cv2.destroyAllWindows()

    def overlayText():
        # Get the text to overlay.
        text = "This is some text."
        frame = cv2.imread('.\captures\1.jpg')
        frame = overlay(frame)
        print("reaachingng")
        sink.setVideoFrame(frame)

        # Return the frame with the text overlayed.
        return "String"

