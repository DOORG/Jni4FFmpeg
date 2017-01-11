package work.wanghao.jni4ffmpeg;

/**
 * @author doublemine
 *         Created  on 2017/01/10 21:21.
 *         Summary:
 */

public class LibavHelper {

  static {
    System.loadLibrary("ffmpeg");
    System.loadLibrary("jni4ffmpeg");
  }

  /**
   * @param commands run cmd
   * @return execute status
   */
  public native static int run(String[] commands);
}
