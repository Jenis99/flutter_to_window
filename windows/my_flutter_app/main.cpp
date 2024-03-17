#include <flutter/flutter_window_controller.h>
#include <flutter/flutter_window.h>
#include <flutter/method_channel.h>
#include <flutter/event_channel.h>
#include <flutter/standard_method_codec.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Popups.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Popups;
using namespace flutter;

int main() {
  // Initialize Win32 application

  // Create FlutterWindowController and FlutterWindow
  auto controller = std::make_unique<FlutterWindowController>();
  auto window = std::make_unique<FlutterWindow>(std::move(controller));

  // Register method channel
  auto channel = std::make_shared<MethodChannel<flutter::EncodableValue>>(
    window->engine()->messenger(), "com.flutterwindow.flutter_to_window/methods",
    &flutter::StandardMethodCodec::GetInstance());

  // Register method handler
  channel->SetMethodCallHandler([](const auto& call, auto result) {
    if (call.method_name().compare("sendMessage") == 0) {
      // Handle the method call and send a response back
      std::string message = call.arguments().ToString();
      std::wstring wmessage(message.begin(), message.end());
      MessageDialog dialog(ref new Platform::String(wmessage.c_str()));
      dialog.ShowAsync();

      result->Success(flutter::EncodableValue("Message received!"));
    } else {
      result->NotImplemented();
    }
  });

  // Run Win32 message loop

  return 0;
}