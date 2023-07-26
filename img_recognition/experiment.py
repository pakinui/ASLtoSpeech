#@title Imports and function definitions

# For running inference on the TF-Hub module.
import tensorflow as tf
import asyncio
from asgiref.sync import sync_to_async

import tensorflow_hub as hub


# For downloading the image.
import matplotlib.pyplot as plt
import os
import cv2
import tempfile
from six.moves.urllib.request import urlopen
from six import BytesIO

# For drawing onto the image.
import numpy as np
from PIL import Image
from PIL import ImageColor
from PIL import ImageDraw
from PIL import ImageFont
from PIL import ImageOps

# For measuring the inference time.
import time

# Print Tensorflow version

# Check available GPU devices.
print("The following GPU devices are available: %s" % tf.test.gpu_device_name())
save_name = os.path.join('saved', 'sign_lang_experiment')
net_save_name = save_name + '_cnn_sign_lang.h5'
model = tf.keras.models.load_model(net_save_name)
save_name = os.path.join('saved')
detector = tf.saved_model.load(save_name).signatures['default']


def display_image(image):
  fig = plt.figure(figsize=(20, 15))
  plt.grid(False)
  plt.imshow(image)
  plt.show()


def download_and_resize_image(img, new_width=256, new_height=256,
                              display=False):
  # _, filename = tempfile.mkstemp(suffix=".jpg")
  # response = urlopen(url)
  # image_data = response.read()
  # image_data = BytesIO(image_data)
  pil_image = Image.open(img)
  pil_image = ImageOps.fit(pil_image, (new_width, new_height), Image.LANCZOS)
  pil_image_rgb = pil_image.convert("RGB")
  # pil_image_rgb.save(filename, format="JPEG", quality=90)
  # print("Image downloaded to %s." % filename)
  if display:
    display_image(pil_image)
  return pil_image_rgb

class_names = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y']

def draw_bounding_box_on_image(image,
                               ymin,
                               xmin,
                               ymax,
                               xmax,
                               color,
                               font,
                               thickness=4,
                               display_str_list=()):
  """Adds a bounding box to an image."""
  draw = ImageDraw.Draw(image)
  im_width, im_height = image.size
  (left, right, top, bottom) = (xmin * im_width, xmax * im_width,
                                ymin * im_height, ymax * im_height)
  # Calculate the adjustments to make the box bigger
  width_adjustment = (right - left) * (1.2 - 1) / 2
  height_adjustment = (bottom - top) * (1.5 - 1) / 2

  # Adjust the bounding box coordinates to make it bigger
  left -= width_adjustment
  right += width_adjustment
  top -= height_adjustment

  draw.line([(left, top), (left, bottom), (right, bottom), (right, top),
             (left, top)],
            width=thickness,
            fill=color)

  croped_img = image.crop((left, top, right, bottom))
  croped_img = croped_img.resize((28, 28))
  croped_img = croped_img.convert("L")
  # Convert the PIL.Image.Image to a NumPy array
  numpy_array = np.array(croped_img)

  # Normalize the array (optional, depending on your model requirements)
  normalized_array = numpy_array / 255.0

  # Reshape the array if needed (depends on your model input shape)
  reshaped_array = normalized_array.reshape(1, 28, 28, 1)
  predictions = model.predict(reshaped_array)
  time.sleep(2)

  # Get the predicted class index (highest probability)
  predicted_class_index = np.argmax(predictions, axis=1)

  # Get the class label from the sign language labels
  predicted_label = class_names[predicted_class_index[0]]

  # Get the predicted probability
  predicted_probability = predictions[0][predicted_class_index]

  text = f"Prediction: {predicted_label} ({predicted_probability.item():.2f})"

  draw.text((10,10),
            text,
            fill="black",
            font=font)

  # If the total height of the display strings added to the top of the bounding
  # box exceeds the top of the image, stack the strings below the bounding box
  # instead of above.
  display_str_heights = [font.getbbox(ds)[3] for ds in display_str_list]
  # Each display_str has a top and bottom margin of 0.05x.
  total_display_str_height = (1 + 2 * 0.05) * sum(display_str_heights)

  if top > total_display_str_height:
    text_bottom = top
  else:
    text_bottom = top + total_display_str_height
  # Reverse list and print from bottom to top.
  for display_str in display_str_list[::-1]:
    bbox = font.getbbox(display_str)
    text_width, text_height = bbox[2], bbox[3]
    margin = np.ceil(0.05 * text_height)
    draw.rectangle([(left, text_bottom - text_height - 2 * margin),
                    (left + text_width, text_bottom)],
                   fill=color)
    draw.text((left + margin, text_bottom - text_height - margin),
              display_str,
              fill="black",
              font=font)
    text_bottom -= text_height - 2 * margin

    return predictions

def draw_boxes(image, boxes, class_names, scores):
  """Overlay labeled boxes on an image with formatted scores and label names."""
  colors = list(ImageColor.colormap.values())

  try:
    font = ImageFont.truetype("/usr/share/fonts/truetype/liberation/LiberationSansNarrow-Regular.ttf",
                              25)
  except IOError:
    font = ImageFont.truetype("./Roboto-Medium.ttf", 25)

  ymin, xmin, ymax, xmax = tuple(boxes)
  display_str = "{}: {}%".format(class_names.decode("ascii"),
                                 int(100 * scores))
  color = colors[hash(class_names) % len(colors)]
  image_pil = Image.fromarray(np.uint8(image)).convert("RGB")
  draw_bounding_box_on_image(
      image_pil,
      ymin,
      xmin,
      ymax,
      xmax,
      color,
      font,
  display_str_list=[display_str])
  np.copyto(image, np.array(image_pil))

  return image


video_capture = cv2.VideoCapture(0)


def load_img(path):
    img = tf.io.read_file(path)
    img = tf.image.decode_jpeg(img, channels=3)
    return img

def detected(coverted_img):
    result = detector(coverted_img)
    time.sleep(2)
    return result

def run_detector(img):
    start_time = time.time()

    # enable this line for image input
    img = tf.image.convert_image_dtype(img, tf.float32)[tf.newaxis, ...]
    result = detector(img)

    # result = detected(img)
    
    end_time = time.time()

    result = {key:value.numpy() for key,value in result.items()}
    print("Found %d objects." % len(result["detection_scores"]))
    print("Inference time: ", end_time-start_time)

    return result


# load image input
image = "./image1.jpg"
result = run_detector(load_img(image))
output_img = np.array(load_img(image))
hand_index = np.where(result["detection_class_entities"] == b'Human hand')
if hand_index[0].size != 0:
    output_img = draw_boxes(
        output_img, result["detection_boxes"][hand_index[0][0]],
        result["detection_class_entities"][hand_index[0][0]], result["detection_scores"][hand_index[0][0]])
display_image(output_img)

# load video input
# while True:
#     ret, frame = video_capture.read()
#     # Read a frame from the video capture
#     if not ret:
#         break
#
#     frame = cv2.flip(frame, 1)
#     # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#     normalised_frame = frame / 255.0 # Normalize pixel values to the range [0, 1]
#     # frame = tf.expand_dims(frame, axis=0)
#     # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#     # frame = np.expand_dims(frame, axis=0)
#     image_np = np.array(normalised_frame)
#     input_tensor = tf.convert_to_tensor(np.expand_dims(image_np, 0), dtype=tf.float32)
#     result = run_detector(input_tensor)
#
#     output_img = np.array(frame)
#     hand_index = np.where(result["detection_class_entities"] == b'Human hand')
#     if hand_index[0].size != 0:
#         output_img = draw_boxes(
#             output_img, result["detection_boxes"][hand_index[0][0]],
#             result["detection_class_entities"][hand_index[0][0]], result["detection_scores"][hand_index[0][0]])
#
#     # Display the output frame with predictions
#     cv2.imshow('Object Detection', output_img)
#     # cv2.imshow('Object Detection', cv2.resize(image_np_with_detections, (800, 600)))
#
#     # Exit the loop if the 'q' key is pressed
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break
#
#
# # Release video file when we're ready
# video_capture.release()
# cv2.destroyAllWindows()
