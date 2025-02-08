// JoyAdvance
// https://github.com/r57zone

#include <windows.h>
#include <dbt.h>
#include <mutex>
#include <iostream>
#include "ViGEm\Client.h"
#include "IniReader\IniReader.h"
#include <mmsystem.h>
#include <atlstr.h>
#include "JoyAdvance.h"

#pragma comment(lib, "winmm.lib")

static std::mutex m;
VOID CALLBACK notification(
	PVIGEM_CLIENT Client,
	PVIGEM_TARGET Target,
	UCHAR LargeMotor,
	UCHAR SmallMotor,
	UCHAR LedNumber,
	LPVOID UserData
)
{
	m.lock();
	m.unlock();
}

void LoadProfile(std::string ProfileFile) {
	CIniReader IniFile("Profiles\\" + ProfileFile);
	ProfileButtons.LeftStickXMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_X", "0"));
	ProfileButtons.LeftStickYMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_Y", "0"));

	ProfileButtons.RightStickXMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_X", "0"));
	ProfileButtons.RightStickYMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_Y", "0"));

	ProfileButtons.LeftTriggerMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LT_AXIS", "0"));
	ProfileButtons.RightTriggerMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RT_AXIS", "0"));

	ProfileButtons.LeftTrigger = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LT_BUTTON", "0"));
	ProfileButtons.RightTrigger = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RT_BUTTON", "0"));

	ProfileButtons.LeftBumper = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LB_BUTTON", "0"));
	ProfileButtons.RightBumper = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RB_BUTTON", "0"));

	ProfileButtons.Back = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "BACK_BUTTON", "0"));
	ProfileButtons.Start = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "START_BUTTON", "0"));

	ProfileButtons.DPADIsStandalone = IniFile.ReadBoolean("GAMEPAD", "DPAD_ENABLED", false);

	ProfileButtons.DPADUp = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_UP", "0"));
	ProfileButtons.DPADLeft = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_LEFT", "0"));
	ProfileButtons.DPADRight = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_RIGHT", "0"));
	ProfileButtons.DPADDown = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_DOWN", "0"));

	ProfileButtons.DPADUpDownMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_UP_DOWN_AXIS", "0"));
	ProfileButtons.DPADLeftRightMode = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "DPAD_LEFT_RIGHT_AXIS", "0"));

	ProfileButtons.Y = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "BUTTON_Y", "0"));
	ProfileButtons.X = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "BUTTON_X", "0"));
	ProfileButtons.B = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "BUTTON_B", "0"));
	ProfileButtons.A = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "BUTTON_A", "0"));

	ProfileButtons.LeftStick = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_BUTTON", "0"));
	ProfileButtons.RightStick = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_BUTTON", "0"));

	ProfileButtons.LeftStickUp = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_UP", "0"));
	ProfileButtons.LeftStickLeft = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_LEFT", "0"));
	ProfileButtons.LeftStickRight = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_RIGHT", "0"));
	ProfileButtons.LeftStickDown = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "LS_DOWN", "0"));

	ProfileButtons.RightStickUp = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_UP", "0"));
	ProfileButtons.RightStickLeft = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_LEFT", "0"));
	ProfileButtons.RightStickRight = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_RIGHT", "0"));
	ProfileButtons.RightStickDown = GamepadKeyNameToKeyCode(IniFile.ReadString("GAMEPAD", "RS_DOWN", "0"));
}

void JoySearch() {
	AppStatus.JoyConnected = false;
	for (int JoyID = 0; JoyID < 4; ++JoyID) { // JOYSTICKID4 - 3
		JOYCAPS caps;
		if (joyGetDevCaps(JoyID, &caps, sizeof(JOYCAPS)) == JOYERR_NOERROR) {

			if (caps.wMid == 0x045E) continue; // Skip XBOX 360 gamepad with VID 0x045E

			if (joyGetPosEx(JoyID, &AppStatus.joyInfo) == JOYERR_NOERROR) {
				AppStatus.JoyIndex = JoyID;
				AppStatus.JoyConnected = true;
				break;
			}
		}
	}
}

void MainTextUpdate() {
	system("cls");
	printf("\n");

	if (AppStatus.JoyConnected)
			printf(" Joy controller connected\n");
		else
			printf(" Joy controller not connected\n");
	printf_s(" Gamepad profile: %s.\n Change profiles with \"Up | Down\"\n", GamepadProfiles[ProfileIndex].c_str());
}

bool IsKeyPressed(int KeyCode) {
	return (GetAsyncKeyState(KeyCode) & 0x8000) != 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DEVICECHANGE: // The list of devices has changed
		if (wParam == DBT_DEVNODES_CHANGED)
		{
			JoySearch();
			MainTextUpdate();
		}
		break;
		/*case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;*/
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int GetAxisValue(int Mode) {
	int value;
	switch (Mode) {
		case JOY_AXIS_X: value = AppStatus.joyInfo.dwXpos - 32767; break;
		case JOY_AXIS_Y: value = AppStatus.joyInfo.dwYpos - 32767; break;
		case JOY_AXIS_Z: value = AppStatus.joyInfo.dwZpos - 32767; break;
		case JOY_AXIS_R: value = AppStatus.joyInfo.dwRpos - 32767; break;
		case JOY_AXIS_U: value = AppStatus.joyInfo.dwUpos - 32767; break;
		case JOY_AXIS_V: value = AppStatus.joyInfo.dwVpos - 32767; break;
		default: return 0;
	}
	if (abs(value) < 257) value = 0;
	return max(-32767, min(32767, value));
}

BYTE GetTriggerValue(int Mode) {
	switch (Mode) {
		case JOY_AXIS_X: return AppStatus.joyInfo.dwXpos / 128;
		case JOY_AXIS_Y: return AppStatus.joyInfo.dwYpos / 128;
		case JOY_AXIS_Z: return AppStatus.joyInfo.dwZpos / 128;
		case JOY_AXIS_R: return AppStatus.joyInfo.dwRpos / 128;
		case JOY_AXIS_U: return AppStatus.joyInfo.dwUpos / 128;
		case JOY_AXIS_V: return AppStatus.joyInfo.dwVpos / 128;
		default: return 0;
	}
}

int main(int argc, char **argv)
{
	SetConsoleTitle("JoyAdvance 1.0");

	WNDCLASS AppWndClass = {};
	AppWndClass.lpfnWndProc = WindowProc;
	AppWndClass.hInstance = GetModuleHandle(NULL);
	AppWndClass.lpszClassName = "JoyAdvanceApp";
	RegisterClass(&AppWndClass);
	HWND AppWindow = CreateWindowEx(0, AppWndClass.lpszClassName, "JoyAdvanceApp", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
	MSG WindowMsgs = {};

	// Config parameters
	CIniReader IniFile("Config.ini");
	AppStatus.DefaultProfile = IniFile.ReadString("Gamepad", "DefaultProfile", "Default.ini");
	AppStatus.SleepTimeOut = IniFile.ReadInteger("Gamepad", "SleepTimeOut", 1);

	// Sound for switching profiles
	TCHAR ChangeEmuModeWav[MAX_PATH] = { 0 };
	GetSystemWindowsDirectory(ChangeEmuModeWav, sizeof(ChangeEmuModeWav));
	_tcscat_s(ChangeEmuModeWav, sizeof(ChangeEmuModeWav), _T("\\Media\\Windows Pop-up Blocked.wav"));

	// Search profiles
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile("Profiles\\*.ini", &ffd);
	GamepadProfiles.push_back("Default.ini");
	//GamepadProfiles.push_back("FPS.ini");
	int ProfileCounter = 0;

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			if (strcmp(ffd.cFileName, "Default.ini")) {// && strcmp(ffd.cFileName, "FPS.ini")) // Already added to the top of the list
				ProfileCounter++;
				if (strcmp(ffd.cFileName, AppStatus.DefaultProfile.c_str()) == 0)
					ProfileIndex = ProfileCounter;
				GamepadProfiles.push_back(ffd.cFileName);
				
			}
		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}

	LoadProfile(GamepadProfiles[ProfileIndex]);

	int SkipPollCount = 0;

	const auto client = vigem_alloc();
	auto ret = vigem_connect(client);

	const auto x360 = vigem_target_x360_alloc();
	ret = vigem_target_add(client, x360);
	ret = vigem_target_x360_register_notification(client, x360, &notification, nullptr);

	XUSB_REPORT report;

	AppStatus.joyInfo.dwFlags = JOY_RETURNALL;
	AppStatus.joyInfo.dwSize = sizeof(AppStatus.joyInfo);

	JoySearch();

	MainTextUpdate();

	while (! ( GetAsyncKeyState(VK_LMENU) & 0x8000 && GetAsyncKeyState(VK_ESCAPE) & 0x8000 ) )
	{
		if (PeekMessage(&WindowMsgs, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&WindowMsgs);
			DispatchMessage(&WindowMsgs);
			if (WindowMsgs.message == WM_QUIT) break;
		}

		XUSB_REPORT_INIT(&report);

		joyGetPosEx(AppStatus.JoyIndex, &AppStatus.joyInfo);

		if (SkipPollCount == 0) {
			if ((IsKeyPressed(VK_UP) || IsKeyPressed(VK_DOWN)) && GetConsoleWindow() == GetForegroundWindow())
			//if ((IsKeyPressed(VK_MENU) && (IsKeyPressed(VK_UP) || IsKeyPressed(VK_DOWN))) && GetConsoleWindow() == GetForegroundWindow())
			{
				SkipPollCount = 15;
				if (IsKeyPressed(VK_UP)) if (ProfileIndex > 0) ProfileIndex--; else ProfileIndex = GamepadProfiles.size() - 1;
				if (IsKeyPressed(VK_DOWN)) if (ProfileIndex < GamepadProfiles.size() - 1) ProfileIndex++; else ProfileIndex = 0;
				LoadProfile(GamepadProfiles[ProfileIndex]);
				MainTextUpdate();
			}
		}
		//printf("R: %d\tV: %d\n", AppStatus.joyInfo.dwRpos, AppStatus.joyInfo.dwVpos);

		if (ProfileButtons.DPADIsStandalone)
		switch (AppStatus.joyInfo.dwPOV) {
			case 0: report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			case 4500: report.wButtons |= XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_RIGHT; break;
			case 9000: report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; break;
			case 13500: report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_RIGHT; break;
			case 18000: report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; break;
			case 22500: report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_LEFT; break;
			case 27000: report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			case 31500: report.wButtons |= XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_LEFT; break;
		}

		report.sThumbLX = GetAxisValue(ProfileButtons.LeftStickXMode);
		report.sThumbLY = GetAxisValue(ProfileButtons.LeftStickYMode) * -1;
		report.sThumbRX = GetAxisValue(ProfileButtons.RightStickXMode);
		report.sThumbRY = GetAxisValue(ProfileButtons.RightStickYMode) * -1;

		report.bLeftTrigger = GetTriggerValue(ProfileButtons.LeftTriggerMode);
		report.bRightTrigger = GetTriggerValue(ProfileButtons.RightTriggerMode);

		if (ProfileButtons.LeftTriggerMode == 0 && AppStatus.joyInfo.dwButtons & ProfileButtons.LeftTrigger)
			report.bLeftTrigger = 255;
		if (ProfileButtons.RightTriggerMode == 0 && AppStatus.joyInfo.dwButtons & ProfileButtons.RightTrigger)
			report.bRightTrigger = 255;

		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.LeftBumper ? XINPUT_GAMEPAD_LEFT_SHOULDER : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.RightBumper ? XINPUT_GAMEPAD_RIGHT_SHOULDER : 0;

		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.Back ? XINPUT_GAMEPAD_BACK : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.Start ? XINPUT_GAMEPAD_START : 0;

		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.DPADUp ? XINPUT_GAMEPAD_DPAD_UP : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.DPADLeft ? XINPUT_GAMEPAD_DPAD_LEFT : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.DPADRight ? XINPUT_GAMEPAD_DPAD_RIGHT : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.DPADDown ? XINPUT_GAMEPAD_DPAD_DOWN : 0;

		//printf("R: %d\tV: %d\n", AppStatus.joyInfo.dwXpos, AppStatus.joyInfo.dwYpos);

		switch (ProfileButtons.DPADUpDownMode) {
			case JOY_AXIS_X: if (AppStatus.joyInfo.dwXpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwXpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break; // 32767 - center, 1638 - 5%
			case JOY_AXIS_Y: if (AppStatus.joyInfo.dwYpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwYpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			case JOY_AXIS_Z: if (AppStatus.joyInfo.dwZpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwZpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			case JOY_AXIS_R: if(AppStatus.joyInfo.dwRpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwRpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			case JOY_AXIS_U: if (AppStatus.joyInfo.dwUpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwUpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			case JOY_AXIS_V: if (AppStatus.joyInfo.dwVpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN; else if (AppStatus.joyInfo.dwVpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_UP; break;
			default: break;
		}

		switch (ProfileButtons.DPADLeftRightMode) {
			case JOY_AXIS_X: if (AppStatus.joyInfo.dwXpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwXpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break; // 32767 - center, 1638 - 5%
			case JOY_AXIS_Y: if (AppStatus.joyInfo.dwYpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwYpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			case JOY_AXIS_Z: if (AppStatus.joyInfo.dwZpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwZpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			case JOY_AXIS_R: if (AppStatus.joyInfo.dwRpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwRpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			case JOY_AXIS_U: if (AppStatus.joyInfo.dwUpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwUpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			case JOY_AXIS_V: if (AppStatus.joyInfo.dwVpos > 34405) report.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT; else if (AppStatus.joyInfo.dwVpos < 31129) report.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT; break;
			default: break;
		}

		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.Y ? XINPUT_GAMEPAD_Y : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.X ? XINPUT_GAMEPAD_X : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.B ? XINPUT_GAMEPAD_B : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.A ? XINPUT_GAMEPAD_A : 0;

		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.LeftStick ? XINPUT_GAMEPAD_LEFT_THUMB : 0;
		report.wButtons |= AppStatus.joyInfo.dwButtons & ProfileButtons.RightStick ? XINPUT_GAMEPAD_RIGHT_THUMB : 0;

		if (AppStatus.joyInfo.dwButtons & ProfileButtons.LeftStickUp) report.sThumbLY = 32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.LeftStickLeft) report.sThumbLX = -32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.LeftStickRight) report.sThumbLX = 32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.LeftStickDown) report.sThumbLY = -32767;

		if (AppStatus.joyInfo.dwButtons & ProfileButtons.RightStickUp) report.sThumbRY = 32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.RightStickLeft) report.sThumbRX = -32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.RightStickRight) report.sThumbRX = 32767;
		if (AppStatus.joyInfo.dwButtons & ProfileButtons.RightStickDown) report.sThumbRY = -32767;

		if (SkipPollCount > 0) SkipPollCount--;
		
		ret = vigem_target_x360_update(client, x360, report);

		Sleep(AppStatus.SleepTimeOut);
	}

	vigem_target_x360_unregister_notification(x360);
	vigem_target_remove(client, x360);
	vigem_target_free(x360);
}
