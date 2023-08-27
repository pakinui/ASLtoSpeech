/**
 * @file shared_lib.cpp
 * @brief Contains the implementation of the SharedObject class and associated functions.
 *
 * This file contains the implementation of the SharedObject class, which represents
 * a shared object with integer and string values, as well as a QVideoSink for video handling.
 */
#include <QtMultimedia/QVideoSink>
#include <QtMultimedia/qvideosink.h>
#include <QVideoSink>
#include <string>

/**
 * @class SharedObject
 * @brief Represents a shared object with integer and string values, and a QVideoSink.
 *
 * The SharedObject class encapsulates an integer value, a string value, and a QVideoSink
 * instance. It provides methods to access and modify these values.
 */
class SharedObject {
public:
  /**
    * @brief Constructs a SharedObject with default values.
    *
    * This constructor initializes the QVideoSink, integer value, and string value.
    */
  SharedObject() {
    q_video_sink = new QVideoSink();
    int_value = 10;
    string_value = "Hello, world!";
  }

  QVideoSink* q_video_sink;
  int int_value;
  std::string string_value;
};


/**
 * @brief Get a new SharedObject instance.
 *
 * This function creates and returns a new SharedObject instance.
 *
 * @return A pointer to a newly created SharedObject instance.
 */
extern "C" {
  SharedObject* get_shared_object() {
    return new SharedObject();
  }
}
