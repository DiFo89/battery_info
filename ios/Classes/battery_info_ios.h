#ifndef BATTERY_INFO_IOS_H
#define BATTERY_INFO_IOS_H

#import <Foundation/Foundation.h>

@interface BatteryInfoIos : NSObject

- (int)getBatteryLevel;
- (bool)isCharging;

@end

#endif // BATTERY_INFO_IOS_H