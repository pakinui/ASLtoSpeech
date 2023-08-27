## @file webcam_pattern_detection.py
#  @brief Contains the implementation of the ASL detection application using webcam and trained model.
#
#This file contains the implementation of an American Sign Language (ASL) detection application
#using webcam capture, OpenCV for hand tracking, and a trained model for sign language recognition.


# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

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

## Load the trained sign language detection model
model_dict = pickle.load(open('ASL_model.p', 'rb'))
## Extract the trained model from the dictionary
model = model_dict['model']

## Declare variable mp_hands that is an instance of mp.solutions.hands.
mp_hands = mp.solutions.hands
## Declare variable mp_drawing that is an instance of mp.solutions.drawing_utils.
mp_drawing = mp.solutions.drawing_utils
## Declare variable mp_drawing_styles that is an instance of mp.solutions.drawing_styles.
mp_drawing_styles = mp.solutions.drawing_styles

## declare variable hands that is an instance of mp_hands.Hands.
hands = mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

## @brief Represents a thread for capturing and processing webcam frames.
#
#This class extends QThread to create a separate thread for capturing webcam frames,
#processing them using hand tracking and a trained model, and updating the display.
class Thread(QThread):

    
    updateFrame = Signal(QImage)

    ## @brief Initialize the Thread class.
    #
    #  This constructor initializes the thread and captures the webcam input.
    def __init__(self, parent=None):
        QThread.__init__(self, parent)
        self.status = True
        self.cap = True

    ## @brief Run the thread.
    #
    #  This method runs the thread and captures webcam frames, processes them using
    #  hand tracking and a trained model, and updates the display.
    def run(self):
        
        self.cap = cv2.VideoCapture(0)
        while self.status:
            data_aux = []
            x_ = []
            y_ = []

            ret, frame = self.cap.read()


            frame = cv2.flip(frame, 1)
            H, W, _ = frame.shape
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            results = hands.process(frame_rgb)
            if results.multi_hand_landmarks:
                num_detected_hands = len(results.multi_hand_landmarks)


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

                prediction = model.predict([np.asarray(data_aux)])
                predicted_class_label = prediction[0]

                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)
                cv2.putText(frame, predicted_class_label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3,
                            cv2.LINE_AA)

            color_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            h, w, ch = color_frame.shape
            img = QImage(color_frame.data, w, h, ch * w, QImage.Format_RGB888)
            scaled_img = img.scaled(640, 480, Qt.KeepAspectRatio)

            # Emit signal
            self.updateFrame.emit(scaled_img)
        sys.exit(-1)

## @brief Kill the thread.
#
#  This method kills the thread and releases the webcam capture.
def kill_thread():

    print("Finishing...")
    button2.setEnabled(False)
    button1.setEnabled(True)
    th.cap.release()
    cv2.destroyAllWindows()
    th.status = False
    th.terminate()
    # Give time for the thread to finish
    time.sleep(1)

## @brief Start the thread.
#
#  This method starts the thread and enables the stop button.
def start():

    print("Starting...")
    button2.setEnabled(True)
    button1.setEnabled(False)
    th.start()

## @brief Set the image.
#
#  This method sets the image to be displayed on the label.
def set_image(image):

    label.setPixmap(QPixmap.fromImage(image))

## Declare variable app that is an instance of QApplication.
app = QApplication(sys.argv)
## Declare variable window that is an instance of QMainWindow.
window = QMainWindow()
window.setWindowTitle("American Sign Language Detection")
window.setGeometry(0, 0, 650, 500)

## Main menu bar
menu = window.menuBar()
## menu_file adds the File option to the menu bar.
menu_file = menu.addMenu("File")
## Declare variable exit_action that is triggered when the user clicks on the Exit option.
exit_action = QAction("Exit", window, triggered=QApplication.quit)
menu_file.addAction(exit_action)

## menu_about adds the About option to the menu bar.
menu_about = menu.addMenu("&About")
## Declare variable about_action that is triggered when the user clicks on the About Qt option.
about_action = QAction("About Qt", window, shortcut=QKeySequence(QKeySequence.HelpContents), triggered=QApplication.aboutQt)
menu_about.addAction(about_action)

## Create a label for the display camera
label = QLabel(window)
label.setFixedSize(640, 480)

## Thread in charge of updating the image
th = Thread(window)
th.finished.connect(window.close)
th.updateFrame.connect(set_image)

# Model group (MAYBE USEFUL FOR PRESENTING TEXT)
#group_model = QGroupBox("Trained model")
#group_model.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
#model_layout = QHBoxLayout()

#combobox = QComboBox()
#for xml_file in os.listdir(cv2.data.haarcascades):
#    if xml_file.endswith(".xml"):
#        combobox.addItem(xml_file)

#model_layout.addWidget(QLabel("File:"), 10)
#model_layout.addWidget(combobox, 90)
#group_model.setLayout(model_layout)

## Buttons layout that contains the start and stop buttons.
buttons_layout = QHBoxLayout()
## Declare variable button1 that is an instance of QPushButton.
button1 = QPushButton("Start")
## Declare variable button2 that is an instance of QPushButton.
button2 = QPushButton("Stop/Close")
button1.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
button2.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
buttons_layout.addWidget(button2)
buttons_layout.addWidget(button1)

## Right layout that contains the model group and the buttons layout.
right_layout = QHBoxLayout()
#right_layout.addWidget(group_model, 1)
right_layout.addLayout(buttons_layout, 1)

## Main layout
layout = QVBoxLayout()
layout.addWidget(label)
layout.addLayout(right_layout)

## Central widget
widget = QWidget(window)
widget.setLayout(layout)
window.setCentralWidget(widget)

# Connections
button1.clicked.connect(start)
button2.clicked.connect(kill_thread)
button2.setEnabled(False)

window.show()
sys.exit(app.exec())
