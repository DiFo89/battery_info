#import "battery_info_ios.h"
#import <UIKit/UIKit.h>

@implementation BatteryInfoIos

- (int)getBatteryLevel {
    UIDevice *device = [UIDevice currentDevice];
    device.batteryMonitoringEnabled = YES;
    float level = device.batteryLevel;
    return (int)(level * 100);
}

- (bool)isCharging {
    UIDevice *device = [UIDevice currentDevice];
    device.batteryMonitoringEnabled = YES;
    return device.batteryState == UIDeviceBatteryStateCharging || 
           device.batteryState == UIDeviceBatteryStateFull;
}

@end