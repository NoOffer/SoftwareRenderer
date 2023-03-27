#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <unordered_map>
#include <iostream>

#define KEY_SPACE VK_SPACE
#define KEY_W 0x57
#define KEY_A 0x41
#define KEY_S 0x53
#define KEY_D 0x44

enum class KeyState
{
	Pressed, Repeated, Released, Unpressed
};

inline std::ostream& operator<<(std::ostream& ostr, KeyState const& ks)
{
	switch (ks)
	{
	case KeyState::Pressed:
		ostr << "Pressed";
		break;
	case KeyState::Repeated:
		ostr << "Repeated";
		break;
	case KeyState::Released:
		ostr << "Released";
		break;
	case KeyState::Unpressed:
		ostr << "Unpressed";
		break;
	}
	return ostr;
}

class Window
{
public:
	Window(int width, int height, const wchar_t* title);
	~Window();

	bool IsAlive();
	void Draw(unsigned char const* framebuffer);
	void DispatchMsg();
	inline std::unordered_map<UINT, KeyState>& GetKeyStates() { return m_KeyStates; }

private:
	HWND           m_Window;
	HDC            m_DC;
	unsigned char* m_FrameBuffer;

	static std::unordered_map<UINT, KeyState> m_KeyStates;

	int m_Width;
	int m_Height;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};