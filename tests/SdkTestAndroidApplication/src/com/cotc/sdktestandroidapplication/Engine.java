package com.cotc.sdktestandroidapplication;

public class Engine {
    static {
        System.loadLibrary("CppApplication");
    }
 
    public static native void startup();
    public static native void update();
    public static native void terminate();
}
