#include "win.h"

std::unordered_map<UINT, KeyState> Window::m_KeyStates;

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		Window::m_KeyStates[LOWORD(wParam)] = KeyState::Pressed;
		return 0;

	case WM_KEYUP:
		Window::m_KeyStates[LOWORD(wParam)] = KeyState::Released;
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(int width, int height, const wchar_t* title) : m_Width(width), m_Height(height)
{
	// Register the window class.
	const wchar_t* CLASS_NAME = L"Sample Window Class";
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS wc = { };

	wc.lpfnWndProc = Window::WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	m_Window = CreateWindow(
		CLASS_NAME,                     // Window class
		title,                          // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Position
		CW_USEDEFAULT, CW_USEDEFAULT,
		// Size
		width + 16, height + GetSystemMetrics(SM_CYSIZE) + 17,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	// Get device context
	m_DC = CreateCompatibleDC(GetDC(m_Window));

	// Setup DIB
	BITMAPINFOHEADER bi;
	memset(&bi, 0, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;   // Reverse the Y axis
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = width * height * 3;
	LPVOID ptr;  // The pointer to the location of the DIB bit values
	HBITMAP dib = CreateDIBSection(m_DC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &ptr, 0, 0);  // This is to obtain the pointer ptr
	if (dib) SelectObject(m_DC, dib);

	// Setup framebuffer
	m_FrameBuffer = (unsigned char*)ptr;

	if (m_Window == NULL)
	{
		return;
	}

	//SetupUI();

	ShowWindow(m_Window, SW_NORMAL);

	m_KeyStates = { 
		{KEY_SPACE, KeyState::Unpressed}, 
		{KEY_W, KeyState::Unpressed}, 
		{KEY_A, KeyState::Unpressed},
		{KEY_S, KeyState::Unpressed},
		{KEY_D, KeyState::Unpressed}
	};
	DispatchMsg();

	// Initialize framebuffer
	memset(m_FrameBuffer, 0, sizeof(unsigned char) * width * height * 3);
}

Window::~Window()
{
	//for (HWND hwnd : m_UIElements)
	//{
	//	CloseWindow(hwnd);
	//}
	CloseWindow(m_Window);
	DeleteDC(m_DC);
}

bool Window::IsAlive()
{
	return IsWindow(m_Window);
}

void Window::Draw(unsigned char const* framebuffer)
{
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			int srcIndex = (y * m_Width + x) * 3;
			int dstIndex = ((m_Height - 1 - y) * m_Width + x) * 3;
			m_FrameBuffer[dstIndex] = framebuffer[srcIndex + 2];
			m_FrameBuffer[dstIndex + 1] = framebuffer[srcIndex + 1];
			m_FrameBuffer[dstIndex + 2] = framebuffer[srcIndex];
		}
	}

	BitBlt(GetDC(m_Window), 0, 0, m_Width, m_Height, m_DC, 0, 0, SRCCOPY);
}

void Window::DispatchMsg()
{
	for (std::pair<const UINT, KeyState>& p : m_KeyStates)
	{
		if (p.second == KeyState::Pressed)
		{
			p.second = KeyState::Repeated;
		}
		else if (p.second == KeyState::Released)
		{
			p.second = KeyState::Unpressed;
		}
	}

	MSG msg;
	while (1)
	{
		// Peek does not block, Get bloacks��PM_NOREMOVE instructs not to remove the message from the list
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;  // Break if there is no message
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);  // Translate from virtual key value to keywords
			DispatchMessage(&msg);   // Dispatch message
		}
	}
}

//// UI setup
//void Window::SetupUI()
//{
//	// Create FPS display
//	m_UIElements.push_back(CreateWindow(
//		L"Static",								// Window class
//		L"FPS:",								// Window text
//		WS_VISIBLE | WS_CHILD,  // Window style
//		0, 0,									// Position
//		50, 20,									// Size
//		m_Window,								// Parent window    
//		NULL,									// Menu
//		NULL,									// Instance handle (no need as a child element)
//		NULL									// Additional application data
//	));
//
//	// Display UI
//	for (HWND hwnd : m_UIElements)
//	{
//		ShowWindow(hwnd, SW_NORMAL);
//	}
//}