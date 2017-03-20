package work.wanghao.jni4ffmpeg;

import android.graphics.Bitmap;
import android.media.MediaMetadataRetriever;
import android.util.Log;

/**
 * @author doublemine
 *         Created  on 2017/01/11 10:31.
 *         Summary:
 */
public class Native4FFmpegHelper {

  protected int flag;

  static {
    System.loadLibrary("ffmpeg");
    System.loadLibrary("native-lib");
  }

  public static int ffmpegRunCommand(String command) {

    if (command.isEmpty()) {
      return 1;
    }
    String[] args = command.split("###");
    for (int i = 0; i < args.length; i++) {
      Log.d("libav4jni", args[i]);
    }
    return run(args.length, args);
  }

  public static native int run(int argc, String[] args);

  public static native int getBitmap(String sourcePath, String savePath);

  public static native String getAvCodec();

  public static native void openFile(String path);

  public static native void drawFrame(Bitmap bitmap);

  public static native void drawFrameAt(Bitmap bitmap, int secs);

  public static native void updateBitmap(Bitmap bitmap);


}
