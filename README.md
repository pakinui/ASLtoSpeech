# COSC345 Cool Group ASL to Speech App

An innovative application that bridges the communication gap between individuals using American Sign Language (ASL) and those who communicate through spoken language. The Sign Language to Speech App utilizes machine learning and text-to-speech technologies to seamlessly translate ASL gestures into spoken words.

## Badges
[![C/C++ CI](https://github.com/pakinui/cosc345/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/pakinui/cosc345/actions/workflows/c-cpp.yml)
[![GitHub Pages](https://github.com/pakinui/cosc345/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/pakinui/cosc345/actions/workflows/pages/pages-build-deployment)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/409b0d67499c4c9b8def12c695be78f9)](https://app.codacy.com/gh/pakinui/cosc345/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade) 
[![codecov](https://codecov.io/gh/pakinui/cosc345/graph/badge.svg?token=GUFNGUO6M4)](https://codecov.io/gh/pakinui/cosc345)
[![Documentation](https://codedocs.xyz/pakinui/cosc345.svg)](https://codedocs.xyz/pakinui/cosc345/)
# COSC345-Project

![image](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![image](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![image](https://img.shields.io/badge/VSCode-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)
![image](https://img.shields.io/badge/Codecov-F01F7A?style=for-the-badge&logo=Codecov&logoColor=white)
![image](https://img.shields.io/badge/Python-FFD43B?style=for-the-badge&logo=python&logoColor=blue)


## Table of Contents

-   [About](#about)
-   [Guidelines](#guidelines)
-   [Features](#features)
-   [Installation](#installation)
-   [Usage](#usage)
-   [Configuration](#configuration)

## About

Working together as a team, we've selected two distinct datasets to create a unique and impactful application: one that translates ASL gestures into text, and another that converts text into spoken language. This innovative combination allows us to facilitate communication across three different formats: ASL gestures, written text, and spoken words. Our primary objective is to create an inclusive environment for both the deaf and hard of hearing individuals, as well as those who may not be familiar with sign language.

## Guidelines
1.  Source code that builds ✅ (application with TTS)
2.  Version control (e.g. git) :white_check_mark:
3.  Continuous Integration ✅ (builds and runs application using GitHub Actions)
4.  Tests ✅ 
5.  Coverage reports ✅ 
6.  Static source code analysis :white_check_mark:
7.  Documentation :white_check_mark:
8.  Questionnaire :white_check_mark: (Can be accessed [here](https://forms.office.com/r/hqKygen2MY))
 
## Features

**Essential Features:**

1.  **ASL to Speech:** Convert ASL gestures captured by the camera into text and then output them as spoken words. :white_check_mark:
2.  **Subtitles:** Display subtitles in distinct colors for both the ASL user and the person speaking. :white_check_mark:

**Potential/Along-the-line Features:**

1.  **Record Transcript:** Optional feature to save conversation transcripts as .txt files. :x:
2.  **Add Gestures:** Allow users to add custom gestures to expand the vocabulary of the app. :x:
3.  **Change Voice:** Provide users with the flexibility to select and customize the synthesized voice. :question:
4.  **Emotion Detector:** Utilize facial emotion recognition to infuse emotion into the generated speech. :x:
5.  **Dictionary Mode:** Offer a comprehensive list of ASL gestures with an option to bookmark for future learning. :x:
6.  **Speech to Text:** Enable voice recording for users and transform recorded speech into written text for interactive conversations. :x:

## Installation

**Prerequisites:** <br />
Python 3.11.0<br />
QT 6.5.2<br />
QT MSVC 2019 64-bit<br />
QT Additional Library QT multimedia<br />

```bash
pip install python-dev-tools
choco install cmake
choco install opencv
choco install ninja
```
```bash
git clone https://github.com/pakinui/cosc345.git
cd cosc345
pip install -r requirements.txt
mkdir build
cd build
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build ./ --config Release
```

## Usage

Firstly, Our ASL to Speech App will access the webcam from user's devices to detect the hand object.<br />
Once it is detected, It will then be put through the pre-trained American Sign Lanauge model to do the language detection.<br />
Those detected sing languages will be converted to text and will be shown on the frame as a subtitle. <br />
These sentences made out of Sign Lanauges can be converted to speech by pressing the 'Translate' button. <br />

## Configuration

This configuarations will be the Potential/Along-the-line Features above and will work on them during Bata. 

## Codecov Coverage Graph
[![image](https://codecov.io/gh/pakinui/cosc345/graphs/sunburst.svg?token=GUFNGUO6M4.svg)](https://app.codecov.io/gh/pakinui/cosc345)
