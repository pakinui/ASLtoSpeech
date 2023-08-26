/**
 * @file ttsCall.cpp
 * @brief Contains the function for text-to-speech conversion using an external tool.
 *
 * This file contains the function for text-to-speech conversion using an external tool.
 */

#include "ttsCall.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>


/**
 * @brief Converts the given text to speech using an external tool.
 *
 * This function takes a text input, constructs a command using the input text,
 * and executes the command using an external text-to-speech tool. The resulting
 * audio is saved as "speech.wav" and can be played using PlaySound.
 *
 * @param text The input text to convert to speech. Currently the text is hardcoded.
 * @return Returns 0 if the text-to-speech process is completed successfully.
 */
bool tts(const std::string& text) {

    // Hard coded text for testing.
    std::string test1 = "Testing The Text to Speech";

    // Construct the command using the passed text
    std::string command = "tts --text \"" + test1 + "\" --model_name \"tts_models/en/ljspeech/glow-tts\" --out_path speech.wav";

    // Execute the command using system()
    int result = std::system(command.c_str());

    if (result == 0) {

        std::cout << "Text-to-speech completed successfully." << std::endl;

        //Play the generated audio (you might need to use a suitable audio player command)
        PlaySound(TEXT("speech.wav"), NULL, SND_FILENAME);

    } else {

        std::cerr << "Error occurred during text-to-speech." << std::endl;

    }

    // Always return success for this example
    return 0;
}
