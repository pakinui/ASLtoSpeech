#include "ttsCall.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
bool tts(const std::string& text) {
    std::string test1 = "Testing The Text to Speech";
    // Construct the command using the passed text
    std::string command = "tts --text \"" + test1 + "\" --model_name \"tts_models/en/ljspeech/glow-tts\" --out_path speech.wav";

    // Execute the command using system()
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Text-to-speech completed successfully." << std::endl;

//        //Play the generated audio (you might need to use a suitable audio player command)
//        std::string playCommand = "start speech.wav"; // Update with your audio player command
//        int playResult = std::system(playCommand.c_str());

        PlaySound(TEXT("speech.wav"), NULL, SND_FILENAME);

//        if (playResult != 0) {
//            std::cerr << "Error occurred while playing audio." << std::endl;
//        }
    } else {
        std::cerr << "Error occurred during text-to-speech." << std::endl;
    }

    return 0;
}
