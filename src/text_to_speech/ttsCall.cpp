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

std::string currentString = ""; ///< The placeholder string that will be used in TTS.

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
bool TextToSpeech::tts(const std::string& text) {

    // Hard coded text for testing.
    std::string test1 = "Testing The Text to Speech Oh Please Work";
    currentString = text;

    // Construct the command using the passed text
    std::string command = "espeak-ng \"" + text + "\"";

    STARTUPINFOA startupInfo = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION processInfo;

    if (CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW | DETACHED_PROCESS, NULL, NULL, &startupInfo, &processInfo)) {
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
        return true;
    } else {
        // Handle error
        return false;
    }

    // Always return success for this example
    return 0;
}

/**
 * @brief Returns the current string that is being converted to speech.
 *
 * This function is used to return the current string that is going to be converted to speech.
 *
 * @return Returns the current string that is being converted to speech.
 */
std::string TextToSpeech::getString(){
    return currentString;
}