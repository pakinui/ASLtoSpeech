/**
 * @file ttsCall.h
 * @brief Contains the declaration of the text-to-speech function.
 *
 * This file contains the declaration of the text-to-speech function.
 */


#ifndef TTSCALL_H
#define TTSCALL_H

#include <string>

/**
 * @class TextToSpeech
 * @brief The TextToSpeech class represents the text-to-speech functionality.
 *
 * This class represents the text-to-speech functionality. It provides a function
 * to convert text to speech using an external tool.
 */
class TextToSpeech{
public:
    /**
     * @brief Converts the given text to speech using an external tool.
     *
     * This function takes a text input, constructs a command using the input text,
     * and executes the command using an external text-to-speech tool. The resulting
     * audio can be played using appropriate audio playback functions.
     *
     * @param text The input text to convert to speech.
     * @return Returns true if the text-to-speech process is completed successfully,
     *         false otherwise.
     */
    bool tts(const std::string& text);

    std::string getString();
    void setPitch(int s);
    void setSpeed(int s);
    void setVolume(int s);
    void setGender(int gender);

};



#endif // TTSCALL_H
