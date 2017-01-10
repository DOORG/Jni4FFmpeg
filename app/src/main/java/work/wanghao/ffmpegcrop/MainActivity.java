package work.wanghao.ffmpegcrop;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import work.wanghao.jni4ffmpeg.LibavHelper;

public class MainActivity extends AppCompatActivity {

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    new AsyncTask<Void, Void, Void>() {
      @Override protected Void doInBackground(Void... params) {
        LibavHelper.exec(new String[] { "ffmpeg" });
        return null;
      }
    }.execute();

    //LibavHelper.exec(new String[]{"",""});
  }
}
