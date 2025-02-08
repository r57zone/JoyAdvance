#pragma once

#define JOY_AXIS_X			1
#define JOY_AXIS_Y			2
#define JOY_AXIS_Z			3
#define JOY_AXIS_R			4
#define JOY_AXIS_U			5
#define JOY_AXIS_V			6

#define XINPUT_GAMEPAD_DPAD_UP           0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN         0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT         0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT        0x0008
#define XINPUT_GAMEPAD_GUIDE             0x0400
#define XINPUT_GAMEPAD_START             0x0010
#define XINPUT_GAMEPAD_BACK              0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB        0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB       0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER     0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER    0x0200
#define XINPUT_GAMEPAD_A                 0x1000
#define XINPUT_GAMEPAD_B                 0x2000
#define XINPUT_GAMEPAD_X                 0x4000
#define XINPUT_GAMEPAD_Y				 0x8000
#define XINPUT_GAMEPAD_LEFT_STICK_UP     0x010000
#define XINPUT_GAMEPAD_LEFT_STICK_DOWN   0x020000
#define XINPUT_GAMEPAD_LEFT_STICK_LEFT   0x040000
#define XINPUT_GAMEPAD_LEFT_STICK_RIGHT  0x080000
#define XINPUT_GAMEPAD_RIGHT_STICK_UP    0x100000
#define XINPUT_GAMEPAD_RIGHT_STICK_DOWN  0x200000
#define XINPUT_GAMEPAD_RIGHT_STICK_LEFT  0x400000
#define XINPUT_GAMEPAD_RIGHT_STICK_RIGHT 0x800000

struct _AppStatus {
	bool JoyConnected = false;
	int JoyIndex = 0;
	JOYINFOEX joyInfo;
	int SleepTimeOut = 0;
	std::string DefaultProfile;
}; _AppStatus AppStatus;

std::vector <std::string> GamepadProfiles;
int ProfileIndex = 0;

struct _ProfileButtons {

	int RightStickXMode;
	int RightStickYMode;

	int LeftStickXMode;
	int LeftStickYMode;

	int LeftTriggerMode = 0;
	int RightTriggerMode = 0;

	int LeftStick = 0;
	int RightStick = 0;
	
	bool DPADIsStandalone = false;
	
	int DPADUp = 0;
	int DPADLeft = 0;
	int DPADRight = 0;
	int DPADDown = 0;

	int DPADUpDownMode;
	int DPADLeftRightMode;

	int Y = 0;
	int X = 0;
	int B = 0;
	int A = 0;
	int Back = 0;
	int Start = 0;
	int LeftTrigger = 0;
	int RightTrigger = 0;
	int LeftBumper = 0;
	int RightBumper = 0;

	int LeftStickUp = 0;
	int LeftStickLeft = 0;
	int LeftStickRight = 0;
	int LeftStickDown = 0;

	int RightStickUp = 0;
	int RightStickLeft = 0;
	int RightStickRight = 0;
	int RightStickDown = 0;

}; _ProfileButtons ProfileButtons;

int GamepadKeyNameToKeyCode(std::string KeyName) {
	std::transform(KeyName.begin(), KeyName.end(), KeyName.begin(), ::toupper);

	if (KeyName == "0") return 0;
	else if (KeyName == "1") return JOY_BUTTON1;
	else if (KeyName == "2") return JOY_BUTTON2;
	else if (KeyName == "3") return JOY_BUTTON3;
	else if (KeyName == "4") return JOY_BUTTON4;
	else if (KeyName == "5") return JOY_BUTTON5;
	else if (KeyName == "6") return JOY_BUTTON6;
	else if (KeyName == "7") return JOY_BUTTON7;
	else if (KeyName == "8") return JOY_BUTTON8;
	else if (KeyName == "9") return JOY_BUTTON9;
	else if (KeyName == "10") return JOY_BUTTON10;
	else if (KeyName == "11") return JOY_BUTTON11;
	else if (KeyName == "12") return JOY_BUTTON12;
	else if (KeyName == "13") return JOY_BUTTON13;
	else if (KeyName == "14") return JOY_BUTTON14;
	else if (KeyName == "15") return JOY_BUTTON15;
	else if (KeyName == "16") return JOY_BUTTON16;
	else if (KeyName == "17") return JOY_BUTTON17;
	else if (KeyName == "18") return JOY_BUTTON18;
	else if (KeyName == "19") return JOY_BUTTON19;
	else if (KeyName == "20") return JOY_BUTTON20;
	else if (KeyName == "21") return JOY_BUTTON21;
	else if (KeyName == "22") return JOY_BUTTON22;
	else if (KeyName == "23") return JOY_BUTTON23;
	else if (KeyName == "24") return JOY_BUTTON24;
	else if (KeyName == "25") return JOY_BUTTON25;
	else if (KeyName == "26") return JOY_BUTTON26;
	else if (KeyName == "27") return JOY_BUTTON27;
	else if (KeyName == "28") return JOY_BUTTON28;
	else if (KeyName == "29") return JOY_BUTTON29;
	else if (KeyName == "30") return JOY_BUTTON30;
	else if (KeyName == "31") return JOY_BUTTON31;
	else if (KeyName == "32") return JOY_BUTTON32;

	else if (KeyName == "AXIS_X") return JOY_AXIS_X;
	else if (KeyName == "AXIS_Y") return JOY_AXIS_Y;
	else if (KeyName == "AXIS_Z") return JOY_AXIS_Z;
	else if (KeyName == "AXIS_R") return JOY_AXIS_R;
	else if (KeyName == "AXIS_U") return JOY_AXIS_U;
	else if (KeyName == "AXIS_V") return JOY_AXIS_V;

	else return 0;
}