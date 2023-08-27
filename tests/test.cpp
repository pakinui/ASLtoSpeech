#include "../src/text_to_speech/ttsCall.h"
#include "catch_amalgamated.cpp"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>

// Link against the Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

// uint32_t factorial( uint32_t number ) {
//     return number <= 1 ? number : factorial(number-1) * number;
// }

// TEST_CASE( "Factorials are computed", "[factorial]" ) {
//     REQUIRE( factorial( 1) == 1 );
//     REQUIRE( factorial( 2) == 2 );
// }

TEST_CASE( "speech.wav file created", "[file_check]" ) {
    tts("test");

    std::string filePath = "speech.wav";

    DWORD fileAttributes = GetFileAttributesA(filePath.c_str());
    if (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        REQUIRE(true);
    } else {
        REQUIRE(false);
    }
}
