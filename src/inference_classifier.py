"""
@file inference_classifier.py
@brief Contains the implementation of the PythonTest class for sign language detection.

This file contains the implementation of the PythonTest class, which provides functionalities
for webcam-based sign language detection using the MediaPipe library and a trained model.
"""
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
  """
  @brief A class representing a video sink for Python video processing.

  This class is used as a video sink for Python video processing.
  It takes a PySide6 video frame and performs processing on it.

  @param psink The PySide6 video sink to use.
  """
  def __init__(self, psink):
    self.psink = psink


  def videoFrame(self, psink):
    """
    @brief Process a video frame.

    This method is called when a new video frame is available.
    It performs processing on the frame and passes it to the
    associated PySide6 video sink.

    @param psink The PySide6 video sink containing the frame.
    """
    print("changed")

# Class to collect necessary modules to execute sign-langue detection on frame(=image)
class PythonTest:
    """
    @brief A class representing sign language detection using webcam and trained model.

    This class provides functionalities for webcam-based sign language detection
    using the MediaPipe library for hand tracking and a trained model for sign
    language recognition.
    """

    def __init__(self):
        """
        @brief Initialize the PythonTest class.

        This constructor initializes the necessary components for sign language detection.
        """
      # Declear the current frame of the webcam
        self.img_path = "../../resources/captures/output.jpg"

        """Load the trained sign-lange detection model."""
        self.model_dict = pickle.load(open('ASL_model.p', 'rb'))
        """Declare variable model."""
        self.model =self.model_dict['model']

        """Declare opencv."""
        self.cap = cv2.VideoCapture(0)

      # Declare necessary functionalities from Mediapipe module
        """Declare variable mp_hands from Mediapipe module."""
        self.mp_hands = mp.solutions.hands
        """Declare variable mp_drawing from Mediapipe module."""
        self.mp_drawing = mp.solutions.drawing_utils
        """Declare variable mp_drawing_styles from Mediapipe module."""
        self.mp_drawing_styles = mp.solutions.drawing_styles

        """Declare variable hands."""
        self.hands = self.mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

        """Setting opencv.""" 
        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 20.0, (640, 480))

    # Testing method
    def print_hello():
            print("Hello from Python module!")
            return "heyyyy"
    
    # Sign-language detection method
    def sign_identifier(self):
         """
        @brief Perform sign language identification on a frame.

        This method performs sign language identification on a given frame using hand
        landmarks and a trained model.

        @return The predicted sign language character.
        """

         frame = cv2.imread("../../resources/captures/output.jpg")
        
         """Declare variable data_aux."""
         data_aux = []
         x_ = []
         y_ = []

         H, W, _ = frame.shape

         """Modify the cv to be fliped % set frame rgb."""
         frame = cv2.flip(frame, 1)
         """Convert the frame to rgb."""
         frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

         """Declare variable of the hand which has been detected on the frame."""
         results = self.hands.process(frame_rgb)

        # If statement to place landmarks of fingers(if the hand was detected)
         if results.multi_hand_landmarks:
             """Declare variable num_detected_hands."""
             num_detected_hands = len(results.multi_hand_landmarks)

             for hand_landmarks in results.multi_hand_landmarks:
                 for i in range(len(hand_landmarks.landmark)):
                     """Declare variable x for hand_landmarks."""
                     x = hand_landmarks.landmark[i].x
                     """Declare variable y for hand_landmarks."""
                     y = hand_landmarks.landmark[i].y

                     x_.append(x)
                     y_.append(y)

                 for i in range(len(hand_landmarks.landmark)):
                     x = hand_landmarks.landmark[i].x
                     y = hand_landmarks.landmark[i].y
                     data_aux.append(x - min(x_))
                     data_aux.append(y - min(y_))

             # If only one hand is detected, duplicate the data_aux
             if num_detected_hands == 1:
                 data_aux += data_aux

             """Declare variable x1."""
             x1 = int(min(x_) * W) - 10
             """Declare variable y1."""
             y1 = int(min(y_) * H) - 10
             
             """Declare variable x2."""
             x2 = int(max(x_) * W) - 10
             """Declare variable y2."""
             y2 = int(max(y_) * H) - 10

             """Run the trained model according to the placements of the landmarks"""
             prediction = self.model.predict([np.asarray(data_aux)])

             """Declare label of the prediction."""
             predicted_class_label = prediction[0]

             # Draw rectangle on the detected hand of the frame
             cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)

             # Write the text of the detected sign language on the frame
             cv2.putText(frame, predicted_class_label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3,
                         cv2.LINE_AA)

             # Save the frame(=image) back to its directory
             cv2.imwrite("../../resources/captures/output2.jpg", frame)

             return str(predicted_class_label) # return predicted character of sign

         return "" # return empty string if there is no hand detected

    #cv2.destroyAllWindows()

