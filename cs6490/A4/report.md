---
title: CS6490 Assignment 4
author:
  - Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1.5cm
documentclass: extarticle
fontsize: 14pt
header-includes:
  - \usepackage{setspace}
  - \onehalfspacing
---

# Table of Contents

- [Table of Contents](#table-of-contents)
- [Assignment Details](#assignment-details)
  - [Steps I followed](#steps-i-followed)
  - [Learnings](#learnings)
  - [Photos](#photos)
- [Issues I faced](#issues-i-faced)
  - [Issues with Fedora](#issues-with-fedora)
  - [Issues with the board](#issues-with-the-board)
  - [Issues with the tinyML Repo](#issues-with-the-tinyml-repo)

\newpage

# Assignment Details

## Steps I followed

1) Obtained name of models from `mcunet/mcunet/models_zoo.py`
2) Substituted the model name in `/examples/vww.py` and ran the code
3) Navigate to the `tutorial/TinyEngine_vww_tutorial/src` directory
4) Change the image resolution in `main.cpp` to the required value for each model
5) Change the lcd output in `lcd.cpp` as required
6) Run the code and obtain the output

## Learnings

Similar to the previous assignment, I was able to learn more about the hardware, and the software that runs on the hardware. 
I was able to understand the working of the code and how the code interacts with the hardware.  

Scripting was also a major part of this assignment. I had to write scripts to generate various configs in order to ease out the process of running the code.

Also, the fact that the device can hold only a limited amount of memory(around 1MB) and yet can run complex models is quite fascinating.

\newpage

## Photos

Below are the images of the output of the code for the models `mcunet-vww0` 

![Actor: Robert Downey Jr](./images/0.jpeg){ width=300px }

![Character in Film: Iron Man](./images/1.jpeg){ width=300px }

\newpage

Below are the images of the output of the code for the models `mcunet-in1`

![Black Screen due to my coding skills](./images/2.jpeg){ width=300px }

![Image Net Prediction with correct screen](./images/3.jpeg){ width=300px }

For the imagenet model, the screen output was not as expected. The screen showed with the correct output but the image kepts blinking(alternating with a black screen) and the output was not stable. I was able to capture the alternating output in one of the frames. Showed both frames for reference.

\newpage

# Issues I faced

## Issues with Fedora

As on the previous assignment I faced issues with fedora, I decided to not install Ubuntu, instead I used distrobox(an container creating application that uses docker/podman) to create a container with Ubuntu 22.04 and installed the required packages. I faced the following issues while setting up the environment:

After installing the required packages, I tried to run the code but it was not able to find the board. On closer inspection I found that the board was not being detected by the container as it did not have the required permissions. I had to create the container with the `--root` flag to give the container root access to the host machine. This fixed the issue and I was able to run the code on the board.

## Issues with the board

After repeated use with the board, the connection between the board and the camera was not stable. On shaking the board or the camera, the connection would be lost and the board would freeze and I would have to restart the board. The issue kept repeating and I was not able to find a solution to this issue.

## Issues with the tinyML Repo

I faced issues with the patch based inference code in the tinyML repo. It was not able to correctly infer output as expected. Thus, I ignored the patch based inference code and have only given the results for the non-patch based inference code.

Also, when editing the code in the `tutorial/TinyEngine_vww_tutorial/src` directory, I had issues with `lcd.cpp` file. The changes I made to the file kept bugging the screen of the board. The issue is also mentioned above in the Imagenet section of output.