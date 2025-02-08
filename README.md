[![EN](https://user-images.githubusercontent.com/9499881/33184537-7be87e86-d096-11e7-89bb-f3286f752bc6.png)](https://github.com/r57zone/JoyAdvance/) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/r57zone/JoyAdvance/blob/master/README.RU.md)
← Choose language | Выберите язык

# JoyAdvance
Xbox gamepad emulation for DInput controllers. Connect any DInput controller - wheel, retro, or modern gamepad - map any buttons and axes to an Xbox gamepad, and enjoy the game. Works based on the driver [ViGEm](https://github.com/nefarius/ViGEmBus).

## Setup
1. Install [ViGEmBus](https://github.com/nefarius/ViGEmBus/releases).
2. Install Microsoft Visual C++ Redistributable 2017 or newer.
3. Connect any DInput controller (steering wheel, retro, or modern gamepad) except Xbox controllers.
4. Extract and launch JoyAdvance.
5. If necessary, modify the default profile in the `Config.ini` configuration file.
6. Copy the default profile `Default.ini` from the `Profiles` folder and create your own profile. You can check axis and button numbers in the Windows program `Joy.cpl`. To launch it, press `Win + R` and enter `joy.cpl`. Axis names for the profile can be found in the profile files. You can test the result in the `XInputTest.exe` program.
7. When using Sony controllers with Steam games, disable "PlayStation Configuration Support" in the controller settings.
8. When using Sony controllers with modern games, it is recommended to install [HidHide](https://github.com/nefarius/HidHide/releases). Then, in "HidHide Configuration Client," add `JoyAdvance.exe` and enable the `Enable device hiding` option (if disabled). This is necessary to ensure that the game detects only the emulated Xbox 360 gamepad instead of the actual controller.

## Download
>Version for Windows 10, 11.

**[Download](https://github.com/r57zone/JoyAdvance/releases)**

## Credits
* [ViGEm](https://github.com/ViGEm) for the ability to emulate different gamepads.

## Building
1. Download the sources and unzip them.
2. [Download](https://code.visualstudio.com/download) and [install](https://github.com/r57zone/RE4ExtendedControl/assets/9499881/69dafce6-fd57-4768-83eb-c1bb69901f07) Microsoft Visual Studio Code 2017+.
3. Update the project properties with your tools and SDK.
4. Choose the `Release` build type (if `Debug` is installed) and `x86`, then compile the project.

## Feedback
`r57zone[at]gmail.com`