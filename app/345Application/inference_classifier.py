import os
import mediapipe as mp
import numpy as np
import pickle
import cv2


model_dict = pickle.load(open('ASL_model.p', 'rb'))
model = model_dict['model']

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles

hands = mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

print("hello")
def overlay(frame_data):
    print("hi")
    flat_array = bytearray(frame_data)
    height = 720
    width = 1280
    frame_np = np.frombuffer(flat_array, dtype=np.uint8).reshape(height, width, 3)
    data_aux = []
    x_ = []
    y_ = []

    frame = cv2.flip(frame_np, 1)
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    print("did it work?")
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

        return predicted_class_label
    else:
        return "N/A"

