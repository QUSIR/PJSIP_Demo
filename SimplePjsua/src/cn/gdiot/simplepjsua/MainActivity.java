package cn.gdiot.simplepjsua;

import java.lang.ref.WeakReference;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener{
	private Button testButton=null;
	private Button callButton=null;
	private TextView statusTextView=null;
	private PjsuaJni jni=null;
	private MainActivityHandler mainActivityHandler=null;
	private boolean isLogined=false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		testButton=(Button)findViewById(R.id.button_test);
		testButton.setOnClickListener(this);
		callButton=(Button)findViewById(R.id.button_call);
		callButton.setOnClickListener(this);
		statusTextView=(TextView)findViewById(R.id.textView_status);
		
		jni=new PjsuaJni();
		
		mainActivityHandler=new MainActivityHandler(this);
	}

	@Override
	public void onClick(View v) {
		switch(v.getId()){
		case R.id.button_test:
			testButton.setEnabled(false);
			if(!isLogined){
				int result=jni.initPjsip();
				mainActivityHandler.sendEmptyMessage(result);
			} else {
				jni.destroyPjsip();
				testButton.setText("init");
				testButton.setEnabled(true);
			}
			break;
		case R.id.button_call:
			if(isLogined) jni.call();
			break;
		default:
			break;
		}
		
	}
	
	static class MainActivityHandler extends Handler {
		WeakReference<MainActivity> mActivity;
		public MainActivityHandler(MainActivity activity){
			this.mActivity=new WeakReference<MainActivity>(activity);
		}
		@Override
		public void handleMessage(Message msg){
			MainActivity activity=this.mActivity.get();
			if(activity!=null){
				activity.handleMessage(msg);
			}
			super.handleMessage(msg);
		}
	}

	public void handleMessage(Message msg){
		switch(msg.what){
		case 0:
			isLogined=true;
			testButton.setEnabled(true);
			testButton.setText("destroy");
			statusTextView.setText("init pjsip is ok");
			break;
		default:
			testButton.setEnabled(true);
			statusTextView.setText("fail to init pjsip, error:"+msg.what);
			break;
		}
	}

}
