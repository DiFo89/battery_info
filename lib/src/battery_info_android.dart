import 'dart:ffi';

final DynamicLibrary _androidLib = DynamicLibrary.open(
  'libbattery_info_ffi.so',
);

int getBatteryLevel() {
  final func = _androidLib.lookupFunction<Int32 Function(), int Function()>(
    'getBatteryLevel',
  );
  return func();
}

bool isCharging() {
  final func = _androidLib.lookupFunction<Int8 Function(), int Function()>(
    'isCharging',
  );
  return func() != 0;
}
