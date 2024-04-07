---
title: CS6490 Assignment 2
author:
  - Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1.5cm
documentclass: extarticle
fontsize: 12pt
header-includes:
  - \usepackage{setspace}
  - \onehalfspacing
---

# Installation and Setup

1. Downloaded the [IDE](https://www.st.com/en/development-tools/stm32cubeide.html) from the official website and installed it.
2. Cloned the [repository](https://github.com/mit-han-lab/tinyengine) from the official github page.
3. Installed the required dependencies using conda and pip as mentioned in the README.md file.
4. Followed the instructions regarding the setup of the REPO.
5. Imported the project into the IDE.
6.

# Issues I faced

When using fedora:

1. On fedora, eclipse-swt was not installed by default, so i had to install it using `sudo dnf install eclipse-swt`.
2. On launching the IDE, it crashed because it was not able to load the swt library.
   1. On seeing the logs, i found that the IDE was trying to load the `libswt-pi4-gtk.so` library and `libswt-pi4-gtk-4934r6.so`, but this is not present in the system.
   2. I tried linking the `libswt-pi3` version of the respective library to the required name, but it did not work.
   3. I eventually gave up on this and tried running the STM32CubeIDE version 1.15 which is the latest version as of now instead of 1.5 which is the version mentioned in the README.md file and the class. This worked and the IDE launched successfully.
3. The build failed with the error `Build might be incomplete` with 66 errors and 463 warnings.
   1. I guess this is because of the version mismatch with the version of the IDE, libraries and the project.
   2. I tried to fix the errors by changing the version of the libraries and the project, but it did not work.
4. I gave on this, and moved on to using Ubuntu 22.04 LTS on a friend's laptop for the assignment.

When using Ubuntu:

1. In the first build, the workspace failed to import the build settings mentioned in the README, so i had to import the settings manually.
2. The debugger kept disconnecting on trying to run the DEMO. I tried to fix this by changing the settings, but it did not work. I eventually gave up on this, redid the setup and tried running the DEMO again, and then it worked.
