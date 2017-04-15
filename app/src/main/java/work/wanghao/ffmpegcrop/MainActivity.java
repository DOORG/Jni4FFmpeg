package work.wanghao.ffmpegcrop;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import work.wanghao.jni4ffmpeg.FFmpegHelper;

public class MainActivity extends AppCompatActivity {
  EditText mEditText;
  Button mButton;

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    mEditText = (EditText) findViewById(R.id.et);
    mButton = (Button) findViewById(R.id.button2);

    mButton.setOnClickListener(new View.OnClickListener() {
      @Override public void onClick(View v) {
        String cmdline = mEditText.getText().toString();
        FFmpegHelper.executeCommand(cmdline);
      }
    });

    final EditText editText = (EditText) findViewById(R.id.et2);
    Button button = (Button) findViewById(R.id.button3);
    button.setOnClickListener(new View.OnClickListener() {
      @Override public void onClick(View v) {
        FFmpegHelper.executeCommand(editText.getText().toString());
      }
    });

   /*
   该方法为静态方法可以直接调用，ffmpeg的命令需要手动校验合法性以及相应的权限，否则程序会直接crash，严重的可能会导致手机直接重启。
   命令使用一个空格间隔，为了保证命令计数的正确性，务必使用一个空格。以下是一个合法的剪裁命令：
   */
    String cropCommand =
        "ffmpeg -i /storage/emulated/0/test.mp4 -strict -2 -vf crop=800:800:0:420 /storage/emulated/0/crop.mp4";
    /*
    需要注意的是该方法为空返回值，如果需要判断执行的结果是否成功，需要自己实现对应的命令分割
    */
    //FFmpegHelper.executeCommand(cropCommand);

    /*
    如果需要自己实现命令的分割，请调用以下方法：
    */

  }
}
