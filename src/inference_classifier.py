## @file inference_classifier.py
#  @brief Contains the implementation of the PythonTest class for sign language detection.
#
#  This file contains the implementation of the PythonTest class, which provides functionalities
#  for webcam-based sign language detection using the MediaPipe library and a trained model.

import mediapipe as mp
import numpy as np
import pickle
import cv2

## @brief A class representing sign language detection using webcam and trained model.
#
#  This class provides functionalities for webcam-based sign language detection
#  using the MediaPipe library for hand tracking and a trained model for sign
#  language recognition.
class PythonTest:
    ## @brief Initialize the PythonTest class.
    #
    #  This constructor initializes the necessary components for sign language detection.
    def __init__(self):

        ## Declear the current frame of the webcam.
        self.img_path = "../../resources/captures/output.jpg"

        ## Load the trained sign-lange detection model.
        self.model_dict = pickle.load(open('ASL_model.p', 'rb'))
        ## Declare variable model.
        self.model =self.model_dict['model']

        ## Declare opencv.
        self.cap = cv2.VideoCapture(0)

        ## Declare variable mp_hands from Mediapipe module.
        self.mp_hands = mp.solutions.hands
        ## Declare variable mp_drawing from Mediapipe module.
        self.mp_drawing = mp.solutions.drawing_utils
        ## Declare variable mp_drawing_styles from Mediapipe module.
        self.mp_drawing_styles = mp.solutions.drawing_styles

        ## Declare variable hands.
        self.hands = self.mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

        ## Setting opencv.
        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')
        ## Setting opencv.
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 20.0, (640, 480))

    ## @brief Perform sign language identification on a frame.
    #
    #  This method performs sign language identification on a given frame using hand
    #  landmarks and a trained model.
    #
    #  @return The predicted sign language character.
    def sign_identifier(self):

        frame = cv2.imread("../../resources/captures/output.jpg")

        ## Declare variable data_aux.
        data_aux = []
        x_ = []
        y_ = []

        H, W, _ = frame.shape

        ## Modify the cv to be fliped % set frame rgb.
#        frame = cv2.flip(frame, 1)
        ## Convert the frame to rgb.
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        ## Declare variable of the hand which has been detected on the frame.
        results = self.hands.process(frame_rgb)

        # If statement to place landmarks of fingers(if the hand was detected)
        if results.multi_hand_landmarks:
            ## Declare variable num_detected_hands.
            num_detected_hands = len(results.multi_hand_landmarks)

            for hand_landmarks in results.multi_hand_landmarks:
                for _, landmark in enumerate(hand_landmarks.landmark):
                    ## Declare variable x for hand_landmarks.
                    x = landmark.x
                    ## Declare variable y for hand_landmarks.
                    y = landmark.y

                    x_.append(x)
                    y_.append(y)

                for _, landmark in enumerate(hand_landmarks.landmark):
                    x = landmark.x
                    y = landmark.y
                    data_aux.append(x - min(x_))
                    data_aux.append(y - min(y_))

            # If only one hand is detected, duplicate the data_aux
            if num_detected_hands == 1:
                data_aux += data_aux

            ## Declare variable x1.
            x1 = int(min(x_) * W) - 10
            ## Declare variable y1.
            y1 = int(min(y_) * H) - 10

            ## Declare variable x2.
            x2 = int(max(x_) * W) - 10
            ## Declare variable y2.
            y2 = int(max(y_) * H) - 10

            ## Run the trained model according to the placements of the landmarks
            prediction = self.model.predict([np.asarray(data_aux)])

            ## Declare label of the prediction.
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

