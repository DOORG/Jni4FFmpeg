package work.wanghao.jni4ffmpeg;

import android.util.Log;

/**
 * @author doublemine
 *         Created  on 2017/01/11 10:31.
 *         Summary:
 */
public class Native4FFmpegHelper {
  static {
    System.loadLibrary("ffmpeg");
    System.loadLibrary("jni4ffmpeg");
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
}
