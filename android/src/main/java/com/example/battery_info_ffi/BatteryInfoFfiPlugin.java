
package com.example.battery_info_ffi;

import androidx.annotation.NonNull;
import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import android.content.Context;
import android.os.Looper;

public class BatteryInfoFfiPlugin implements FlutterPlugin, MethodChannel.MethodCallHandler {
    private MethodChannel channel;

    private Context context;

    static {
        System.loadLibrary("battery_info_ffi");
    }

    @Override
    public void onAttachedToEngine(@NonNull FlutterPluginBinding binding) {
        context = binding.getApplicationContext();
        channel = new MethodChannel(binding.getBinaryMessenger(), "battery_info_ffi");
        channel.setMethodCallHandler(this);
    }
    @Override
    public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
        channel.setMethodCallHandler(null);
    }

    @Override
    public void onMethodCall(@NonNull MethodCall call, @NonNull MethodChannel.Result result) {
        if (Looper.myLooper() == null) {
            Looper.prepare();
        }
        try{
            if (call.method.equals("getBatteryLevel")) {
                result.success(getBatteryLevel(context));
            }
            if (call.method.equals("isCharging")) {
                result.success(isCharging());
            } else {
                result.notImplemented();
            }
        }catch(Exception e){
            result.error("NATIVE_ERROR", e.getMessage(), null);
        }
        
    }


    public native boolean isCharging();
    public native int getBatteryLevel(Context context);
}