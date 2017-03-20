package work.wanghao.ffmpegcrop;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import java.io.File;
import work.wanghao.jni4ffmpeg.Native4FFmpegHelper;

public class MainActivity extends AppCompatActivity {
  ImageView imageView;
  private Bitmap bitmap;

  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    imageView = (ImageView) findViewById(R.id.tv_codec);
    //textView.setText(Native4FFmpegHelper.getAvCodec());
    MediaMetadataRetriever mediaMetadataRetriever = new MediaMetadataRetriever();
    mediaMetadataRetriever.setDataSource(
        new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath());
    bitmap = mediaMetadataRetriever.getFrameAtTime();
    imageView.setImageBitmap(bitmap);
    mediaMetadataRetriever.release();
    findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
      @Override public void onClick(View view) {
        ffun();
      }
    });
  }

  public void ffun() {

    //Native4FFmpegHelper.updateBitmap(bitmap);
    //imageView.setImageBitmap(bitmap);
    //MediaMetadataRetriever mediaMetadataRetriever = new MediaMetadataRetriever();
    //mediaMetadataRetriever.setDataSource(
    //    new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath());
    //Bitmap bitmap = mediaMetadataRetriever.getFrameAtTime();
    //
    //mediaMetadataRetriever.release();
    Bitmap tempBitmap = Bitmap.createBitmap(320, 240, Bitmap.Config.ARGB_8888);
    Native4FFmpegHelper.openFile(
        new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath());

    Native4FFmpegHelper.drawFrameAt(tempBitmap, 1);
    imageView.setImageBitmap(tempBitmap);
    //Log.d("TAG", "bitmap=" + bitmap.getWidth() + "--" + bitmap.getHeight());
    //BitmapFactory.Options config = new BitmapFactory.Options();
    //config.inJustDecodeBounds = true;

    //Native4FFmpegHelper.getBitmap(
    //    new File(Environment.getExternalStorageDirectory(), "test.mp4").getAbsolutePath(),
    //    Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "test.png");
  }
}
