package work.wanghao.jni4ffmpeg;

/**
 * @author doublemine
 *         Created  on 2017/01/11 10:31.
 *         Summary:
 */
public class FFmpegHelper {

  static {
    System.loadLibrary("ffmpeg");
    System.loadLibrary("native-lib");
  }

  public static void executeCommand(String cmd) {
    String[] argv = cmd.split(" ");
    Integer argc = argv.length;
    run(argc, argv);
  }

  public static native int run(int argc, String[] args);

  public static native String getAvCodec();
}
