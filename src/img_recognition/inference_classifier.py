## @file inference_classifier.py
#  @brief Contains further implementation of the PythonTest class for sign language detection.
#
# This file is used in the prediction of the sign language character from the frames.
# It is used to detect the hand landmarks and predict the sign language character from the trained model.
# It is also used to draw the rectangle around the hand and display the predicted sign language character.

import pickle
import cv2
import mediapipe as mp
import numpy as np

## Load the trained sign-lange detection model.
model_dict = pickle.load(open('./ASL_model.p', 'rb'))
## Declare variable model.
model = model_dict['model']

## capture is a variable that is used to capture the video
cap = cv2.VideoCapture(0)

## Declare variable mp_hands from Mediapipe module.
mp_hands = mp.solutions.hands
## Declare variable mp_drawing from Mediapipe module.
mp_drawing = mp.solutions.drawing_utils
## Declare variable mp_drawing_styles from Mediapipe module.
mp_drawing_styles = mp.solutions.drawing_styles

## Declare variable hands. It is used to detect hands.
hands = mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

## fourcc is used to create a video writer object for writing video files, specifying the codec for video compression.
fourcc = cv2.VideoWriter_fourcc(*'XVID')
## out is a variable used to create a VideoWriter object for writing video frames to a video file with specified settings. 
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))

while True:

    ## Declare variable data_aux as a list.
    data_aux = []
    ## Declare variable x_ as a list.
    x_ = []
    ## Declare variable y_ as a list.
    y_ = []

    ## ret and frame are used to read the capture.
    ret, frame = cap.read()

    ## H, W, _ are used to get the height and width of the frame.
    H, W, _ = frame.shape

    ## frame is a variable used to flip the frame.
    frame = cv2.flip(frame, 1)
    ## frame_rgb is a variable used to convert the frame from BGR to RGB.
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    ## results is a variable to process the frame of the hands.
    results = hands.process(frame_rgb)
    if results.multi_hand_landmarks:

        ## num_detected_hands is a variable equal the length of the results.multi_hand_landmarks, meaning the number of hands detected.
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
                ## Declare variable x for hand_landmarks.
                x = hand_landmarks.landmark[i].x
                ## Declare variable y for hand_landmarks.
                y = hand_landmarks.landmark[i].y

                x_.append(x)
                y_.append(y)

            for i in range(len(hand_landmarks.landmark)):
                ## Declare variable x for hand_landmarks.
                x = hand_landmarks.landmark[i].x
                ## Declare variable y for hand_landmarks.
                y = hand_landmarks.landmark[i].y
                data_aux.append(x - min(x_))
                data_aux.append(y - min(y_))

        if num_detected_hands == 1:
            # If only one hand is detected, duplicate the data_aux
            data_aux += data_aux

        ## x1 is set to the minimum int value of x_ multiplied by the width of the frame, minus 10.
        x1 = int(min(x_) * W) - 10
        ## y1 is set to the minimum int value of y_ multiplied by the height of the frame, minus 10.
        y1 = int(min(y_) * H) - 10

        ## x2 is set to the maximum int value of x_ multiplied by the width of the frame, minus 10.
        x2 = int(max(x_) * W) - 10
        ## y2 is set to the maximum int value of y_ multiplied by the height of the frame, minus 10.
        y2 = int(max(y_) * H) - 10

        ## prediction is set to the prediction of the model on a set of input data (data_aux).
        prediction = model.predict([np.asarray(data_aux)])
        ## predicted_class_label is set to the first element in the list of prediction.
        predicted_class_label = prediction[0]

        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)
        cv2.putText(frame, predicted_class_label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3,
                    cv2.LINE_AA)

    out.write(frame)

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
out.release()
cv2.destroyAllWindows()

