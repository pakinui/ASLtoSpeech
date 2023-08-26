
#include <QtMultimedia/QVideoSink>
#include <QtMultimedia/qvideosink.h>
#include <QVideoSink>
#include <string>


class SharedObject {
public:
  SharedObject() {
    q_video_sink = new QVideoSink();
    int_value = 10;
    string_value = "Hello, world!";
  }

  QVideoSink* q_video_sink;
  int int_value;
  std::string string_value;
};

extern "C" {
  SharedObject* get_shared_object() {
    return new SharedObject();
  }
}
