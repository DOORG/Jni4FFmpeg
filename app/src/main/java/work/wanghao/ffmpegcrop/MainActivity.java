package work.wanghao.ffmpegcrop;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import java.io.File;
import work.wanghao.jni4ffmpeg.Native4FFmpegHelper;

public class MainActivity extends AppCompatActivity {

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    TextView textView = (TextView) findViewById(R.id.tv_codec);
    textView.setText(Native4FFmpegHelper.getAvCodec());
    findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
      @Override public void onClick(View view) {
        ffun();
      }
    });
  }

  public void ffun() {

    MediaMetadataRetriever mediaMetadataRetriever = new MediaMetadataRetriever();
    mediaMetadataRetriever.setDataSource(
        new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath());
    Bitmap bitmap = mediaMetadataRetriever.getFrameAtTime();
    mediaMetadataRetriever.release();

    Native4FFmpegHelper.openFile(
        new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath());

    Log.d("TAG", "bitmap=" + bitmap.getWidth() + "--" + bitmap.getHeight());
    //BitmapFactory.Options config = new BitmapFactory.Options();
    //config.inJustDecodeBounds = true;

    //Native4FFmpegHelper.getBitmap(
    //    new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath(),
    //    Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "test.png");
  }
}
