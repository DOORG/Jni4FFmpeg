package work.wanghao.jni4ffmpeg;

import android.annotation.SuppressLint;
import android.util.Log;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author doublemine
 *         Created  on 2017/01/10 21:21.
 *         Summary:
 */

public class LibavHelper {
  private final static String TAG = LibavHelper.class.getSimpleName();

  static {
    System.loadLibrary("ffmpeg");
    System.loadLibrary("jni4ffmpeg");
  }

  /**
   * @param commands run cmd
   * @return execute status
   */
  public native static int run(String[] commands);

  public static long currentTime() {
    return System.currentTimeMillis();
  }

  public static String convert2String(long time) {
    @SuppressLint("SimpleDateFormat") SimpleDateFormat simpleDateFormat =
        new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    Log.d(TAG, "time=" + time);
    return simpleDateFormat.format(new Date(time));
  }

  public static native void test();
}
