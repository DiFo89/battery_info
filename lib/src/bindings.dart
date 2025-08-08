import 'dart:ffi';
import 'package:flutter/foundation.dart';

typedef GetBatteryLevelFunc = Int32 Function(); // C-сторона
typedef GetBatteryLevelDartFunc = int Function(); // Dart-сторона

typedef IsChargingFunc = Int8 Function(); // C-сторона (0 или 1)
typedef IsChargingDartFunc = int Function(); // Dart-сторона

class NativeBatteryInfo {
  static DynamicLibrary _loadLibrary() {
    if (defaultTargetPlatform == TargetPlatform.android) {
      return DynamicLibrary.open('libbattery_info_ffi.so');
    } else if (defaultTargetPlatform == TargetPlatform.iOS) {
      return DynamicLibrary.process();
    }
    throw UnsupportedError('Platform not supported');
  }

  final DynamicLibrary _library = _loadLibrary();

  late final GetBatteryLevelDartFunc getBatteryLevel = _library
      .lookupFunction<GetBatteryLevelFunc, GetBatteryLevelDartFunc>(
        'get_battery_level',
      );

  late final IsChargingDartFunc _isCharging = _library
      .lookupFunction<IsChargingFunc, IsChargingDartFunc>(
        'is_charging',
        isLeaf: true, // Оптимизация для простых функций
      );
  bool isCharging() => _isCharging() != 0;
}
