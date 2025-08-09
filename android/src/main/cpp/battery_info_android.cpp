#include <jni.h>
#include <android/log.h>

#define LOG_TAG "BatteryNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

JavaVM *g_jvm = nullptr;

extern "C" JNIEXPORT jint JNICALL
Java_com_example_battery_1info_1ffi_BatteryInfoFfiPlugin_getBatteryLevel(JNIEnv *env, jobject thiz, jobject context)
{
    if (!env)
        return -1;

    jint batteryLevel = -1;

    // 2. Получаем классы
    jclass contextClass = env->GetObjectClass(context);
    jclass batteryManagerClass = env->FindClass("android/os/BatteryManager");
    if (!contextClass || !batteryManagerClass)
    {
        LOGE("Class lookup failed");
        return -1;
    }

    // 3. Получаем BATTERY_SERVICE константу
    jfieldID batteryServiceField = env->GetStaticFieldID(
        contextClass,
        "BATTERY_SERVICE",
        "Ljava/lang/String;");
    jobject batteryServiceName = env->GetStaticObjectField(contextClass, batteryServiceField);

    // 4. Получаем BatteryManager
    jmethodID getSystemService = env->GetMethodID(
        contextClass,
        "getSystemService",
        "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject batteryManager = env->CallObjectMethod(context, getSystemService, batteryServiceName);

    // 5. Получаем уровень заряда
    jfieldID capacityField = env->GetStaticFieldID(
        batteryManagerClass,
        "BATTERY_PROPERTY_CAPACITY",
        "I");
    jint capacityId = env->GetStaticIntField(batteryManagerClass, capacityField);

    jmethodID getIntMethod = env->GetMethodID(
        batteryManagerClass,
        "getIntProperty",
        "(I)I");
    batteryLevel = env->CallIntMethod(batteryManager, getIntMethod, capacityId);

    return batteryLevel;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_battery_1info_1ffi_BatteryInfoFfiPlugin_isCharging(JNIEnv *env, jobject thiz)
{
    // Проверяем, заряжается ли устройство

    return JNI_FALSE;
}

// Функции для Dart FFI
extern "C" JNIEXPORT jint JNICALL
get_battery_level(JNIEnv *env, jobject thiz, jobject context)
{
    return Java_com_example_battery_1info_1ffi_BatteryInfoFfiPlugin_getBatteryLevel(env, thiz, context);
}

extern "C" JNIEXPORT jboolean JNICALL
is_charging(JNIEnv *env, jobject thiz, jobject context)
{
    return Java_com_example_battery_1info_1ffi_BatteryInfoFfiPlugin_isCharging(env, thiz);
}