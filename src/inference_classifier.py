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

        self.cap = cv2.VideoCapture(0)

        self.mp_hands = mp.solutions.hands
        self.mp_drawing = mp.solutions.drawing_utils
        self.mp_drawing_styles = mp.solutions.drawing_styles

        self.hands = self.mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)


        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 20.0, (640, 480))


    def print_hello():
            print("Hello from Python module!")
            return "heyyyy"

    def sign_identifier(self):

         frame = cv2.imread("../../resources/captures/output.jpg")

         data_aux = []
         x_ = []
         y_ = []

         H, W, _ = frame.shape

         frame = cv2.flip(frame, 1)
         frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

         results = self.hands.process(frame_rgb)
         if results.multi_hand_landmarks:
             num_detected_hands = len(results.multi_hand_landmarks)

             # for hand_landmarks in results.multi_hand_landmarks:
             #     mp_drawing.draw_landmarks(
             #         frame,  # image to draw
             #         hand_landmarks,  # model output
             #         mp_hands.HAND_CONNECTIONS,  # hand connections
             #         mp_drawing_styles.get_default_hand_landmarks_style(),
             #         mp_drawing_styles.get_default_hand_connections_style())

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

             cv2.imwrite("../../resources/captures/output2.jpg", frame)

             return str(predicted_class_label) # return predicted character of sign

         return "" # return empty string if there is no hand detected

    #cv2.destroyAllWindows()

