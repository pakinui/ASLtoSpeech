# COSC345 Cool Group ASL to Speech App

An innovative application that bridges the communication gap between individuals using American Sign Language (ASL) and those who communicate through spoken language. The Sign Language to Speech App utilizes machine learning and text-to-speech technologies to seamlessly translate ASL gestures into spoken words.

<p align="center">
  <img src="ASL guidline.png" width="500" height= "800"/>
</p>
<p align="center">
  "Guideline for American Sign Language"
</p>


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
-   [User Documentation](#userdocumentation)
-   [Features](#features)
-   [Installation](#installation)
-   [Usage](#usage)

## About

Working together as a team, we've selected two distinct datasets to create a unique and impactful application: one that translates ASL gestures into text, and another that converts text into spoken language. This innovative combination allows us to facilitate communication across three different formats: ASL gestures, written text, and spoken words. Our primary objective is to create an inclusive environment for both the deaf and hard of hearing individuals, as well as those who may not be familiar with sign language.

## Guidelines
**Alpha:**
1.  Source code that builds :white_check_mark: (application with TTS)
2.  Version control (e.g. git) :white_check_mark:
3.  Continuous Integration :white_check_mark: (builds and runs application using GitHub Actions)
4.  Tests :white_check_mark:
5.  Coverage reports :white_check_mark:
6.  Static source code analysis :white_check_mark:
7.  Documentation :white_check_mark:
8.  Questionnaire :white_check_mark: (Can be accessed [here](https://forms.office.com/r/hqKygen2MY))

**Beta:**
1.  Source code that builds (on your computer in the lab in front of me) :white_check_mark:
2.  Full working CI pipeline (see Assignment 2’s requirements) :white_check_mark:
3.  Program that is nearly finished :white_check_mark:
4.  Through and extensive testing :white_check_mark:
5.  Increased coverage reports :white_check_mark:
6.  Fewer static analysis warnings (We have none! Thats pretty cool) :white_check_mark:
7.  More documentation :white_check_mark:

**Final Product:**
1.  Did you hit the deadline? :white_check_mark:
2.  Source code that builds in the lab :white_check_mark:
3.  Stable and Robust App :white_check_mark:
4.  Professionalism (look and feel) :white_check_mark:
5.  Professionalism (other aspects i.e. Sound, Text etc.) :white_check_mark:
6.  User Documentation :white_check_mark: (can be seen [here](#userdocumentation))
7.  User Testing :white_check_mark:
8.  Analysis of User feedback :white_check_mark: (Can be accessed [here](https://github.com/pakinui/cosc345/blob/main/PDFs/2nd_user_testing_review.pdf))

**Cool Points:**

We received zero marks for cool points from the <b>Alpha</b>.<br />
What we believe was cool from the <b>Alpha</b> that was not acknowledged:<br />
1.  GitHub integrated through using a webhook in Discord<br />
2.  Artifact generation<br />

A more detailed document with evidence can be found [here](https://github.com/pakinui/cosc345/blob/main/PDFs/PotentialAlphaCoolPoints.pdf)<br />

For the <b>Beta</b>, we believe the following could be considered for cool points:
1.  A retrospective, [here](https://github.com/pakinui/cosc345/blob/main/PDFs/retrospective%26actions.png), along with the follow up to it, [here](https://github.com/pakinui/cosc345/blob/main/PDFs/retrospective_follow_up.png)<br />
2.  An analysis on user testing [here](https://github.com/pakinui/cosc345/blob/main/PDFs/user_testing_review.pdf)<br />

For the <b>Final Product</b>, we discussed and confirmed that these should be counted for cool points:
1.  Laura has drawn an amazing ASL sign language guide for our application as seen at the top of the README. She also drew the logo for our app!
2.  Laura also performed the training of our AI model. The fact that we trained our own model for our app is extremely cool

## UserDocumentation

To use the app, we recommend that users first have a look at the ASL hand chart drawn by Laura Yoo, and practice doing a few of the hand symbols. The app can of course be used before doing this, however it can be somewhat hard to create legible sentences without any experience with American Sign Language.

Upon opening the app, you should be able to see yourself in the webcam frame. There is a box to the right that will have the letters signed added to it (after the bar under the cam is filled), and pressing translate speaks that sentence, as well as moves that sentence to the larger box above, displaying the history of what has been said. This is the default tab, however you can change to the "Hist" tab to see the history of chat in more depth, as well as a "Dict" tab to see the hand symbol to letter chart drawn by Laura.

When performing signs, you should see a green bar that fills at the bottom of the GUI. This indicates that a letter is being added to the translated sentence. When the green bar fills, the letter is added. You can tell what letter is going to be added as it is displayed on the screen, near the bottom of the webcam frame. This therefore allows more control of what is being added to the translated sentence. 

The app has ability to change the output voice, such that if you want to speak in a male or female voice, you have the ability to, as well as having the ability to change the pitch and the speed of the output voice. This can be accessed by opening the settings tab in the top left of the apps GUI. There is also a "Help" tab, in which there is in-app User Documentation.

That's all she wrote! Enjoy using the app, and if you have any questions or want to make a contribution, please get in touch!

## Features

**Essential Features:**

1.  **ASL to Speech:** Convert ASL gestures captured by the camera into text and then output them as spoken words. :white_check_mark:
2.  **Subtitles:** Display subtitles in distinct colors for both the ASL user and the person speaking. :white_check_mark:

**Potential/Along-the-line Features:**

1.  **Record Transcript:** Optional feature to save conversation transcripts as .txt files. 
2.  **Add Gestures:** Allow users to add custom gestures to expand the vocabulary of the app.
3.  **Change Voice:** Provide users with the flexibility to select and customize the synthesized voice.
4.  **Emotion Detector:** Utilize facial emotion recognition to infuse emotion into the generated speech.
5.  **Dictionary Mode:** Offer a comprehensive list of ASL gestures with an option to bookmark for future learning.
6.  **Speech to Text:** Enable voice recording for users and transform recorded speech into written text for interactive conversations.

## Installation

**Prerequisites:** <br />
Python 3.11.0<br />
QT 6.5.2<br />
QT MSVC 2019 64-bit<br />
QT Additional Library QT multimedia<br />
espeak-ng<br />

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
```
Open the CMakeLists.txt file in Ot6.5.2<br />
Insert '\cosc345\build' into the build directory between the parent directory and the build directory<br />
  i.e.(...\parent-directory\cosc345\build\build-cosc345...)<br />
Build and Run the Application in Release mode<br />
****

## Usage

Firstly, our ASL to Speech App will access the webcam from user's devices to detect the hand object.<br />
Once it is detected, it will then be put through our pre-trained American Sign Lanauge model to do the language detection.<br />
Those detected sign language symbols will be converted to text, and said text will be shown on the frame as a subtitle. <br />
The subtitle text will form sentences made out of Sign Lanauge Symbols displayed in the translate box, which can be converted to speech by pressing the 'Translate' button. <br />


## Codecov Coverage Graph
[![image](https://codecov.io/gh/pakinui/cosc345/graphs/sunburst.svg?token=GUFNGUO6M4.svg)](https://app.codecov.io/gh/pakinui/cosc345)
