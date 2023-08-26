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

class PythonVideoSink(PySide6.QtCore.QObject):
  def __init__(self, psink):
    self.psink = psink

    
  def videoFrame(self, psink):
    print("changed")


model_dict = pickle.load(open('ASL_model.p', 'rb'))
model = model_dict['model']

# Create a Python object that will listen for the signal.
sink = QVideoSink()

psink = PythonVideoSink(sink)
# Connect the signal to the Python object.
#sink.imageAvailable.connect(sink.renderFrame)
sink.videoFrameChanged.connect(psink.videoFrame)

cap = cv2.VideoCapture(0)

def print_hello():
    print("Hello from Python module!")

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles

hands = mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)


fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))

#def overlay(frame):
#    while True:
def overlay(frame):
    print("overlay")
    # data_aux = []
    # x_ = []
    # y_ = []

    # ret, frame = cap.read()
    # frame = cv2.imread('.\captures\1.jpg')

    # H, W, _ = frame.shape

    # frame = cv2.flip(frame, 1)
    # frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # results = hands.process(frame_rgb)
    # if results.multi_hand_landmarks:
    #     num_detected_hands = len(results.multi_hand_landmarks)

    #     # for hand_landmarks in results.multi_hand_landmarks:
    #     #     mp_drawing.draw_landmarks(
    #     #         frame,  # image to draw
    #     #         hand_landmarks,  # model output
    #     #         mp_hands.HAND_CONNECTIONS,  # hand connections
    #     #         mp_drawing_styles.get_default_hand_landmarks_style(),
    #     #         mp_drawing_styles.get_default_hand_connections_style())

    #     for hand_landmarks in results.multi_hand_landmarks:
    #         for i in range(len(hand_landmarks.landmark)):
    #             x = hand_landmarks.landmark[i].x
    #             y = hand_landmarks.landmark[i].y

    #             x_.append(x)
    #             y_.append(y)

    #         for i in range(len(hand_landmarks.landmark)):
    #             x = hand_landmarks.landmark[i].x
    #             y = hand_landmarks.landmark[i].y
    #             data_aux.append(x - min(x_))
    #             data_aux.append(y - min(y_))

    #     if num_detected_hands == 1:
    #         # If only one hand is detected, duplicate the data_aux
    #         data_aux += data_aux

    #     x1 = int(min(x_) * W) - 10
    #     y1 = int(min(y_) * H) - 10

    #     x2 = int(max(x_) * W) - 10
    #     y2 = int(max(y_) * H) - 10

    #     prediction = model.predict([np.asarray(data_aux)])
    #     predicted_class_label = prediction[0]

    #     cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)
    #     cv2.putText(frame, predicted_class_label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3,
    #                 cv2.LINE_AA)

    # out.write(frame)
    return frame
    # cv2.imshow('frame', frame)
    # if cv2.waitKey(1) == ord('q'):
    #     break

#cap.release()
#out.release()
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

