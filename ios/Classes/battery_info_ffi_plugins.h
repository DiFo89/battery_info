#import <Flutter/Flutter.h>

@interface BatteryInfoFfiPlugin : NSObject <FlutterPlugin>
@end

// FFI функции
int get_battery_level();
bool is_charging();