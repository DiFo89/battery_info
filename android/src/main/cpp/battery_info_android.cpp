#include <jni.h>

extern "C" JNIEXPORT jint JNICALL
Java_com_example_battery_info_ffi_BatteryInfoFfiPlugin_getBatteryLevel(JNIEnv *env, jobject thiz)
{
    // Получаем уровень заряда батареи через Android NDK
    jclass batteryManagerClass = env->FindClass("android/os/BatteryManager");
    jmethodID getSystemService = env->GetStaticMethodID(batteryManagerClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

    jstring serviceName = env->NewStringUTF("batterymanager");
    jobject batteryManager = env->CallStaticObjectMethod(batteryManagerClass, getSystemService, serviceName);

    jmethodID getIntMethod = env->GetMethodID(batteryManagerClass, "getIntProperty", "(I)I");
    jint batteryLevel = env->CallIntMethod(batteryManager, getIntMethod, 4); // 4 = BATTERY_PROPERTY_CAPACITY

    return batteryLevel;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_battery_info_ffi_BatteryInfoFfiPlugin_isCharging(JNIEnv *env, jobject thiz)
{
    // Проверяем, заряжается ли устройство

    return JNI_FALSE;
}

// Функции для Dart FFI
extern "C" JNIEXPORT jint JNICALL
get_battery_level(JNIEnv *env, jobject thiz, jobject context)
{
    return Java_com_example_battery_info_ffi_BatteryInfoFfiPlugin_getBatteryLevel(env, thiz);
}

extern "C" JNIEXPORT jboolean JNICALL
is_charging(JNIEnv *env, jobject thiz, jobject context)
{
    return Java_com_example_battery_info_ffi_BatteryInfoFfiPlugin_isCharging(env, thiz);
}