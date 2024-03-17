#include <bits/stdc++.h>
#include <flutter/flutter_view.h>
#include <windows.h>

std::string GetMessageFromFlutter() {
  return "Hello from Windows!";
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  if (uMsg == WM_PAINT) {
    hdc = BeginPaint(hwnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
    return 0;
  } else if (uMsg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* lpCmdLine, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"FlutterEmbedder";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    CLASS_NAME,                     // Window class
    L"MethodChannel Example",       // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,

    NULL,       // Parent window
    NULL,       // Menu
    hInstance,  // Instance handle
    NULL        // Additional application data
  );

  if (hwnd == NULL) {
    return 0;
  }

  flutter::FlutterView flutter_view;
  flutter_view.SetWindow(hwnd);

flutter::MethodChannel method_channel(flutter_view.binary_messenger(), "com.flutterwindow.flutter_to_window.flutter_to_window");
  method_channel.SetMethodCallHandler([](const MethodCall<Json::Value>& call) -> Json::Value {
    if (call.method_name().compare("getMessage") == 0) {
      std::string message = GetMessageFromFlutter();
      return Json::Value(message);
    }
    return Json::Value();
  });

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
