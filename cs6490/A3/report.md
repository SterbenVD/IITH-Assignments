---
title: CS6490 Assignment 3
author:
  - Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1.5cm
documentclass: extarticle
fontsize: 12pt
header-includes:
  - \usepackage{setspace}
  - \onehalfspacing
---

# Table of Contents

- [Table of Contents](#table-of-contents)
- [Learning](#learning)
- [Installation and Setup](#installation-and-setup)
  - [Inference](#inference)
  - [Training](#training)
- [Issues I faced](#issues-i-faced)
  - [Setup with the Board](#setup-with-the-board)
  - [When using Fedora](#when-using-fedora)
  - [When using Ubuntu:](#when-using-ubuntu)

# Learning

I learnt about:

- STM32CubeIDE and the TinyEngine project.
- Interacting with the STM32 board using the IDE.
- Running the inference and training examples on the board.

The IDE was easy to use and the examples were well documented.

# Installation and Setup

1. Downloaded the [IDE](https://www.st.com/en/development-tools/stm32cubeide.html) from the official website and installed it.
2. Cloned the [repository](https://github.com/mit-han-lab/tinyengine) from the official github page.
3. Installed the required dependencies using conda and pip as mentioned in the README.md file.
4. Followed the instructions regarding the setup of the REPO.

\newpage

## Inference

1. Loaded the `inference` example project in the IDE
2. Built the project with the settings mentioned in the README.md file.
3. Ran the project on the board and observed the output on the monitor connected to the board.

![No face in photo](./images/1-no.jpeg){ width=300px }

![Face in photo](./images/1-de.jpeg){ width=300px }

\newpage

## Training

1. Loaded the `training` example project in the IDE
2. Built the project with the settings mentioned in the README.md file.
3. Ran the project on the board and observed the output on the monitor connected to the board.
4. Used `minicom` to send input to the board and observed the output on the monitor.

![Not recognized before training](./images/2-inf-ini.jpeg){ width=300px}

Initial state of the board before training

\newpage

![Training Class 0 (Not Recognized)](./images/2-train-0-in.jpeg){ width=300px }

Training the board with class 0 with the face in the photo first leads to incorrect recognition.

![Training Class 0 (Recognized)](./images/2-train-0-cor.jpeg){ width=300px }

Training the board with class 0 with the face in the photo again leads to correct recognition after training.

\newpage

![Training Class 1 (Not Recognized)](./images/2-train-1-in.jpeg){ width=300px }

Training the board with class 1 without the face in the photo first leads to incorrect recognition.

![Training Class 1 (Recognized)](./images/2-train-1-cor.jpeg){ width=300px }

Training the board with class 1 without the face in the photo again leads to correct recognition after training.

\newpage

# Issues I faced

## Setup with the Board

1. The pin configuration of the board was confusing at first and I messed up the configuration once, but after going through the documention, I was able to fix it.

## When using Fedora

1. On fedora, eclipse-swt was not installed by default, so i had to install it using `sudo dnf install eclipse-swt`.
2. On launching the IDE, it crashed because it was not able to load the swt library.
   1. On seeing the logs, i found that the IDE was trying to load the `libswt-pi4-gtk.so` library and `libswt-pi4-gtk-4934r6.so`, but this is not present in the system.
   2. I tried linking the `libswt-pi3` version of the respective library to the required name, but it did not work.
   3. I eventually gave up on this and tried running the STM32CubeIDE version 1.15 which is the latest version as of now instead of 1.5 which is the version mentioned in the README.md file and in the class. This worked and the IDE launched successfully.
3. The build failed with the error `Build might be incomplete` with 66 errors and 463 warnings on 1.15 version of the IDE.
   1. I guess this is because of the version mismatch with the version of the IDE, libraries and the project.
   2. I tried to fix the errors by changing the version of the libraries and the project, but it did not work.
4. I gave on this, and moved on to using Ubuntu 22.04 LTS on a friend's laptop for the assignment.

## When using Ubuntu:

1. In the first build, the workspace failed to import the default build settings mentioned in the README
   1. I had to import the settings manually.
   2. The debugger kept disconnecting on trying to run the DEMO and gave no output.
   3. I tried to fix this by changing the settings, but it did not work.
   4. I eventually gave up on this, redid the setup and tried running the DEMO again, and then it worked.
   5. I guess i might have missed some settings in the first build.
2. In the `training` example, initially I was not able to send input to the board using the terminal.
   1. I fixed this by using `minicom` and setting the baud rate to 115200.
   2. `minicom` did not show the inputs on the terminal, but the board was able to receive the inputs and give the output.
