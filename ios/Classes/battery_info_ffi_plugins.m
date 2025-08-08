#import "battery_info_ffi_plugin.h"
#import "battery_info_ios.h"

@implementation BatteryInfoFfiPlugin

static BatteryInfoIos* batteryInfo = nil;

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  batteryInfo = [[BatteryInfoIos alloc] init];
  
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"battery_info_ffi"
            binaryMessenger:[registrar messenger]];
  
  [registrar addMethodCallDelegate:self channel:channel];
}

+ (int)getBatteryLevel {
  return [batteryInfo getBatteryLevel];
}

+ (bool)isCharging {
  return [batteryInfo isCharging];
}

@end

// FFI функции
int get_battery_level() {
  return [BatteryInfoFfiPlugin getBatteryLevel];
}

int is_charging() {
  return [BatteryInfoFfiPlugin isCharging] ? 1 : 0;
}