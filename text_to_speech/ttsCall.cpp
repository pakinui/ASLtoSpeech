#include <iostream>
#include <cstdlib>

int main() {
    std::string text = "The quick brown fox jumps over the lazy dog.";

    // Construct the command
    std::string command = "tts --text \"" + text + "\" --model_name \"tts_models/en/ljspeech/glow-tts\" --out_path speech.wav";

    // Execute the command using system()
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Text-to-speech completed successfully." << std::endl;

        // Play the generated audio (you might need to use a suitable audio player command)
        std::string playCommand = "play speech.wav"; // Update with your audio player command
        int playResult = std::system(playCommand.c_str());

        if (playResult != 0) {
            std::cerr << "Error occurred while playing audio." << std::endl;
        }
    } else {
        std::cerr << "Error occurred during text-to-speech." << std::endl;
    }

    return 0;
}