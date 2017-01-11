package work.wanghao.ffmpegcrop;

import android.os.AsyncTask;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import work.wanghao.jni4ffmpeg.LibavHelper;
import work.wanghao.jni4ffmpeg.Native4FFmpegHelper;

public class MainActivity extends AppCompatActivity {

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    //new AsyncTask<Void, Void, Void>() {
    //  @Override protected Void doInBackground(Void... params) {
    //    LibavHelper.exec(new String[] { "ffmpeg" });
    //    return null;
    //  }
    //}.execute();

    //LibavHelper.exec(new String[]{"",""});
    String base = Environment.getExternalStorageDirectory().getPath();
    String[] commands = new String[9];
    commands[0] = "ffmpeg";
    commands[1] = "-i";
    commands[2] = base + "/input.mp4";
    commands[3] = "-i";
    commands[4] = base + "/input.mp3";
    commands[5] = "-strict";
    commands[6] = "-2";
    commands[7] = "-y";
    commands[8] = base + "/merge.mp4";

    new Native4FFmpegHelper().run(commands.length, commands);
  }
}
