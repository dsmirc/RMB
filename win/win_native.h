#pragma once

#include "../native.h"

#define OEMRESOURCE
#include <Windows.h>
#include <vector>
#include <unordered_map>

class WinNative : public Native
{
public:
	WinNative();

	WinNative(const WinNative&) = delete;
	WinNative& operator=(const WinNative&) = delete;

	static WinNative* GetInstance();

	~WinNative() override;

	void RegisterHotKey(uint32_t key, uint32_t modifier) override;
	void UnregisterHotKey(uint32_t key, uint32_t modifier) override;
	void SendKeysDown(uint32_t* keys, size_t count) override;
	void SendKeysUp(uint32_t* keys, size_t count) override;
	void SetMousePos(double x, double y) override;
	bool SetFocusOnProcess(const std::string& process_name) override;
	void CursorHide(bool hide) override;
	void Update() override {};

private:
	struct RegKey
	{
		uint32_t id, key, modifier;
	};

	const LPCWSTR szWindowClass = L"win_native_reg_window";

	/*
	struct key_state
	{
		uint32_t key;
		bool is_down;
		float press_time;
	};

	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	bool OnKeyPress(KBDLLHOOKSTRUCT* info);
	bool OnKeyRelease(KBDLLHOOKSTRUCT* info);
	uint32_t GetKeyFrom(uint32_t key, uint32_t type = 0); // type = 0(VK to GLFW), 1(GLFW TO VK)
	key_state last_key_;
	HHOOK kbd_hook_;
	*/

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static WinNative* instance_;

	uint32_t GetModKeyFrom(uint32_t g_key);

	uint32_t GetAvailableId();

	void OnHotkey(uint32_t id);

	std::unordered_map<std::string, RegKey> registered_keys_;
	std::unordered_map<uint32_t, std::string> registered_ids_;
	HWND reg_window_;
	HCURSOR default_arrow_;
};