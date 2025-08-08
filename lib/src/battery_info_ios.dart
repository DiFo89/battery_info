import 'dart:ffi';

final DynamicLibrary _iosLib = DynamicLibrary.process();

int getBatteryLevel() {
  final func = _iosLib.lookupFunction<Int32 Function(), int Function()>(
    'get_battery_level',
  );
  return func();
}

bool isCharging() {
  final func = _iosLib.lookupFunction<Int8 Function(), int Function()>(
    'is_charging',
  );
  return func() != 0;
}
