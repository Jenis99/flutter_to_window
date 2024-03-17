import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  static const platform = MethodChannel('com.flutterwindow.flutter_to_window');

  String _message = 'No message yet';

  void _getMessageFromNative() async {
    String message;
    try {
      final String result = await platform.invokeMethod('getMessage');
      message = 'Received message: $result';
    } on PlatformException catch (e) {
      message = 'Error: ${e.message}';
    }

    setState(() {
      _message = message;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('MethodChannel Example'),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(_message),
              ElevatedButton(
                onPressed: _getMessageFromNative,
                child: Text('Get Message from Native'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
