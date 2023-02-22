#include "win32.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

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
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(int width, int height, const wchar_t* title) : m_Width(width), m_Height(height)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
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
	m_FrameBuffer = (unsigned char*)ptr;

	//if (m_Window == NULL)
	//{
	//	return;
	//}

	ShowWindow(m_Window, SW_NORMAL);

	DispatchMsg();

	// Initialize framebuffer
	memset(m_FrameBuffer, 0, sizeof(unsigned char) * width * height * 3);
}

Window::~Window()
{
	CloseWindow(m_Window);
	DeleteDC(m_DC);
}

void Window::Draw(unsigned char const* framebuffer)
{
	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			int index = (i * m_Width + j) * 3;
			m_FrameBuffer[index] = framebuffer[index + 2];
			m_FrameBuffer[index + 1] = framebuffer[index + 1];
			m_FrameBuffer[index + 2] = framebuffer[index];
		}
	}

	BitBlt(GetDC(m_Window), 0, 0, m_Width, m_Height, m_DC, 0, 0, SRCCOPY);
}

void Window::DispatchMsg()
{
	MSG msg;
	while (1)
	{
		// Peek does not block, Get bloacks£¬PM_NOREMOVE instructs not to remove the message from the list
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;  // Break if there is no message
		if (!GetMessage(&msg, NULL, 0, 0)) break;

		TranslateMessage(&msg);  // Translate from virtual key value to keywords
		DispatchMessage(&msg);   // Dispatch message
	}
}