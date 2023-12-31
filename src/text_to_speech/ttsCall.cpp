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
#include <QDebug>
#include <chrono>

std::string currentString = ""; ///< The placeholder string that will be used in TTS.
int pitch = 50;
int speed = 175;
int volume = 100;
std::string genderString = "";
std::string testString = "Do you like my new voice?";

bool TextToSpeech::tts(const std::string& text) {

    // Hard coded text for testing.
    //std::string test1 = "Testing The Text to Speech Oh Please Work"; COMMENTED OUT FOR STATIC ANALYSIS
    currentString = text;

    // Construct the command using the passed text
    //std::string command = "espeak-ng -v en \"" + text + "\" -w \"output.wav\" | start \"output.wav\"";
    std::string pitchStr = std::to_string(pitch);
    std::string speedStr = std::to_string(speed);
    std::string volumeStr = std::to_string(volume);

    std::string command = "espeak-ng -v en" + genderString + " -p " + pitchStr + " -s " + speedStr + " -a " + volumeStr + " \"" + currentString + "\" -w \"newoutput.wav\"";
    //safjsdj

    STARTUPINFOA startupInfo = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION processInfo;
    if (CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW | DETACHED_PROCESS, NULL, NULL, &startupInfo, &processInfo)) {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
        PlaySound(TEXT("newoutput.wav"), NULL, SND_FILENAME | SND_ASYNC);
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


void TextToSpeech::setPitch(int s){
    pitch = s;
    tts(testString);
}

void TextToSpeech::setSpeed(int s){
    speed = s;
    tts(testString);
}

void TextToSpeech::setVolume(int s){
    volume = s;
    tts(testString);
}

// after en
//+m1 for male
//+f2 for female
//0 == nothing
// -1 == male
// 1 == female
void TextToSpeech::setGender(int gender){
    if(gender == -1){
        genderString = "+m1";
    }else if(gender == 1){
        genderString = "+f2";
    }else{
        genderString = "";
    }
    tts(testString);
}
