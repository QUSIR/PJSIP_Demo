package cn.gdiot.simplepjsua;

public class PjsuaJni {
	public native void test();
	public native int initPjsip();
	public native void destroyPjsip();
	public native void call();

	public PjsuaJni() {
		System.loadLibrary("SimplePjsua");
	}
}
