#include <string>
#include <jni.h>
#include "android-log.h"
#include <string.h>
#include <stdio.h>
#include <android/bitmap.h>


extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "ffmpeg_utils.h"
#include "ffmpeg.h"


/* Cheat to keep things simple and just use some globals. */
AVFormatContext *pFormatCtx;
AVCodecContext *pCodecCtx;
AVFrame *pFrame;
AVFrame *pFrameRGB;
int videoStream;


/*
 * Write a frame worth of video (in pFrame) into the Android bitmap
 * described by info using the raw pixel buffer.  It's a very inefficient
 * draw routine, but it's easy to read. Relies on the format of the
 * bitmap being 8bits per color component plus an 8bit alpha channel.
 */

static void fill_bitmap(AndroidBitmapInfo *info, void *pixels, AVFrame *pFrame) {
    uint8_t *frameLine;

    int yy;
    for (yy = 0; yy < info->height; yy++) {
        uint8_t *line = (uint8_t *) pixels;
        frameLine = (uint8_t *) pFrame->data[0] + (yy * pFrame->linesize[0]);

        int xx;
        for (xx = 0; xx < info->width; xx++) {
            int out_offset = xx * 4;
            int in_offset = xx * 3;

            line[out_offset] = frameLine[in_offset];
            line[out_offset + 1] = frameLine[in_offset + 1];
            line[out_offset + 2] = frameLine[in_offset + 2];
            line[out_offset + 3] = 0;
        }
        pixels = (char *) pixels + info->stride;
    }
}


int seek_frame(int tsms) {
    int64_t frame;

    frame = av_rescale(tsms, pFormatCtx->streams[videoStream]->time_base.den,
                       pFormatCtx->streams[videoStream]->time_base.num);
    frame /= 1000;

    if (avformat_seek_file(pFormatCtx, videoStream, 0, frame, frame, AVSEEK_FLAG_FRAME) < 0) {
        return 0;
    }

    avcodec_flush_buffers(pCodecCtx);

    return 1;
}


//Output FFmpeg's av_log()
void custom_log(void *ptr, int level, const char *fmt, va_list vl) {

    //To TXT file

    FILE *fp = fopen("/storage/emulated/0/av_log.txt", "a+");
    if (fp) {
        vfprintf(fp, fmt, vl);
        fflush(fp);
        fclose(fp);
    }


    //To Logcat
    //LOGE(fmt, vl);
}


JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_FFmpegHelper_run(JNIEnv *env, jclass type, jint argc,
                                              jobjectArray args) {



    //FFmpeg av_log() callback
//    av_log_set_callback(custom_log);

//    int argc = cmdnum;
    char **argv = (char **) malloc(sizeof(char *) * argc);

    int i = 0;
    for (i = 0; i < argc; i++) {
        jstring string = (jstring) env->GetObjectArrayElement(args, i);
        const char *tmp = env->GetStringUTFChars(string, 0);
        argv[i] = (char *) malloc(sizeof(char) * 1024);
        strcpy(argv[i], tmp);
    }

    ffmpeg_main(argc, argv);

    for (i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
    return 0;


//    char buff[1024];
//    snprintf(buff, sizeof(buff), "ffmpeg -ss 00:00:01 -i %s %s -r 1 -vframes 1 -an -vcodec mjpeg",
//             "Hello", "world");
//    std::string buffAsStdStr = buff;
//
//
//    char tab2[1024];
//    strncpy(tab2, buffAsStdStr.c_str(), sizeof(tab2));
//    tab2[sizeof(tab2) - 1] = 0;
//
//    int resultCode = ffmpeg_main(strlen(tab2), (char **) tab2);





}

JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_FFmpegHelper_getAvCodec(JNIEnv *env, jclass type) {

    return env->NewStringUTF(avcodec_configuration());
}


JNIEXPORT jint JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_getBitmap(JNIEnv *env, jclass type,
                                                           jstring sourcePath_, jstring savePath_) {
    const char *sourcePath = env->GetStringUTFChars(sourcePath_, 0);
    const char *savePath = env->GetStringUTFChars(savePath_, 0);
    LOGD(sourcePath);
    LOGD(savePath);

    char *argv[30];
    int argc = 0;


    argv[argc++] = (char *) "ffmpeg";
    argv[argc++] = (char *) "-ss";
    argv[argc++] = (char *) "00:00:01";
    argv[argc++] = (char *) "-i";
    argv[argc++] = (char *) sourcePath;
    argv[argc++] = (char *) "-f";
    argv[argc++] = (char *) "image2";
    argv[argc++] = (char *) "-y";
    argv[argc++] = (char *) savePath;

    int resultCode = ffmpeg_main(argc, argv);
    if (resultCode == 0) {
        LOGD("返回值为0");
    } else {
        LOGE("返回值为非0");
    }

    env->ReleaseStringUTFChars(sourcePath_, sourcePath);
    env->ReleaseStringUTFChars(savePath_, savePath);
}


JNIEXPORT void JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_openFile(JNIEnv *env, jclass type, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);


    int ret;
    int err;
    int i;
    AVCodec *pCodec;
    uint8_t *buffer;
    int numBytes;

    av_register_all();
    LOGE("Registered formats");
//    err = av_open_input_file(&pFormatCtx, "file:/sdcard/vid.3gp", NULL, 0, NULL);
    err = avformat_open_input(&pFormatCtx, path, NULL, NULL);


    LOGE("Called open file");
    if (err != 0) {
        LOGE("Couldn't open file");
        return;
    }
    LOGE("Opened file");

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGE("Unable to get stream info");
        return;
    }

    videoStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1) {
        LOGE("Unable to find video stream");
        return;
    }

    LOGI("Video stream is [%d]", videoStream);

    pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        LOGE("Unsupported codec");
        return;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        LOGE("Unable to open codec");
        return;
    }

    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    LOGI("Video size is [%d x %d]", pCodecCtx->width, pCodecCtx->height);

    numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

    avpicture_fill((AVPicture *) pFrameRGB, buffer, PIX_FMT_RGB24,
                   pCodecCtx->width, pCodecCtx->height);

    env->ReleaseStringUTFChars(path_, path);
}


JNIEXPORT void JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_drawFrame(JNIEnv *env, jclass type,
                                                           jobject bitmap) {
    AndroidBitmapInfo info;
    void *pixels;
    int ret;

    int err;
    int i;
    int frameFinished = 0;
    AVPacket packet;
    static struct SwsContext *img_convert_ctx;
    int64_t seek_target;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }
    LOGE("Checked on the bitmap");

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }
    LOGE("Grabbed the pixels");

    i = 0;
    while ((i == 0) && (av_read_frame(pFormatCtx, &packet) >= 0)) {
        if (packet.stream_index == videoStream) {
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            if (frameFinished) {
                LOGE("packet pts %llu", packet.pts);
                // This is much different than the tutorial, sws_scale
                // replaces img_convert, but it's not a complete drop in.
                // This version keeps the image the same size but swaps to
                // RGB24 format, which works perfect for PPM output.
                int target_width = 320;
                int target_height = 240;
                img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                                 pCodecCtx->pix_fmt,
                                                 target_width, target_height, PIX_FMT_RGB24,
                                                 SWS_BICUBIC,
                                                 NULL, NULL, NULL);
                if (img_convert_ctx == NULL) {
                    LOGE("could not initialize conversion context\n");
                    return;
                }
                sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize,
                          0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

//                 save_frame(pFrameRGB, target_width, target_height, i);
                fill_bitmap(&info, pixels, pFrameRGB);
                i = 1;
            }
        }
        av_free_packet(&packet);
    }

    AndroidBitmap_unlockPixels(env, bitmap);

}

JNIEXPORT void JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_drawFrameAt(JNIEnv *env, jclass type,
                                                             jobject bitmap, jint secs) {


    AndroidBitmapInfo info;
    void *pixels;
    int ret;

    int err;
    int i;
    int frameFinished = 0;
    AVPacket packet;
    static struct SwsContext *img_convert_ctx;
    int64_t seek_target;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }
    LOGE("Checked on the bitmap");

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }
    LOGE("Grabbed the pixels");

    seek_frame(secs * 1000);

    i = 0;
    while ((i == 0) && (av_read_frame(pFormatCtx, &packet) >= 0)) {
        if (packet.stream_index == videoStream) {
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            if (frameFinished) {
                // This is much different than the tutorial, sws_scale
                // replaces img_convert, but it's not a complete drop in.
                // This version keeps the image the same size but swaps to
                // RGB24 format, which works perfect for PPM output.
                int target_width = 320;
                int target_height = 240;
                img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                                 pCodecCtx->pix_fmt,
                                                 target_width, target_height, PIX_FMT_RGB24,
                                                 SWS_BICUBIC,
                                                 NULL, NULL, NULL);
                if (img_convert_ctx == NULL) {
                    LOGE("could not initialize conversion context\n");
                    return;
                }
//                sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize,
//                          0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

                // save_frame(pFrameRGB, target_width, target_height, i);
                fill_bitmap(&info, pixels, pFrameRGB);
                i = 1;
            }
        }
        av_free_packet(&packet);
    }

    AndroidBitmap_unlockPixels(env, bitmap);

}


#define RGB565_R(p) ((((p) & 0xF800) >> 11) << 3)
#define RGB565_G(p) ((((p) & 0x7E0 ) >> 5)  << 2)
#define RGB565_B(p) ( ((p) & 0x1F  )        << 3)
#define MAKE_RGB565(r, g, b) ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))

#define RGBA_A(p) (((p) & 0xFF000000) >> 24)
#define RGBA_R(p) (((p) & 0x00FF0000) >> 16)
#define RGBA_G(p) (((p) & 0x0000FF00) >>  8)
#define RGBA_B(p)  ((p) & 0x000000FF)
#define MAKE_RGBA(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

JNIEXPORT void JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_updateBitmap(JNIEnv *env, jclass type,
                                                              jobject zBitmap) {

    if (zBitmap == NULL) {
        LOGE("bitmap is null\n");
        return;
    }


//    头文件：#include <string.h>
//
//         memset() 函数用来将指定内存的前n个字节设置为特定的值，其原型为：
//    void * memset( void * ptr, int value, size_t num );
//
//    参数说明：
//    ptr 为要操作的内存的指针。
//    value 为要设置的值。你既可以向 value 传递 int 类型的值，也可以传递 char 类型的值，int 和 char 可以根据 ASCII 码相互转换。
//    num 为 ptr 的前 num 个字节，size_t 就是unsigned int。
//
//    【函数说明】memset() 会将 ptr 所指的内存区域的前 num 个字节的值都设置为 value，然后返回指向 ptr 的指针。
//
//    memset() 可以将一段内存空间全部设置为特定的值，所以经常用来初始化字符数组。例如：
//    char str[20];
//    memset(str, '\0', sizeof(str)-1);
//
//    【返回值】返回指向 ptr 的指针。


    // Get bitmap info
    AndroidBitmapInfo info;
    memset(&info, 0, sizeof(info));
    AndroidBitmap_getInfo(env, zBitmap, &info);
    // Check format, only RGB565 & RGBA are supported
    if (info.width <= 0 || info.height <= 0 ||
        (info.format != ANDROID_BITMAP_FORMAT_RGB_565 &&
         info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)) {
        LOGE("invalid bitmap\n");
        env->ThrowNew(env->FindClass("java/io/IOException"), "invalid bitmap");
        return;
    }

    // Lock the bitmap to get the buffer
    void *pixels = NULL;
    int res = AndroidBitmap_lockPixels(env, zBitmap, &pixels);
    if (pixels == NULL) {
        LOGE("fail to lock bitmap: %d\n", res);
        env->ThrowNew(env->FindClass("java/io/IOException"), "fail to open bitmap");
        return;
    }

    LOGE("Effect: %dx%d, %d\n", info.width, info.height, info.format);

    int x = 0, y = 0;
    // From top to bottom
    for (y = 0; y < info.height; ++y) {
        // From left to right
        for (x = 0; x < info.width; ++x) {
            int a = 0, r = 0, g = 0, b = 0;
            void *pixel = NULL;
            // Get each pixel by format
            if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {

                pixel = ((uint16_t *) pixels) + y * info.width + x;
                uint16_t v = *(uint16_t *) pixel;
                r = RGB565_R(v);
                g = RGB565_G(v);
                b = RGB565_B(v);
            } else {// RGBA
                pixel = ((uint32_t *) pixels) + y * info.width + x;
                uint32_t v = *(uint32_t *) pixel;
                a = RGBA_A(v);
                r = RGBA_R(v);
                g = RGBA_G(v);
                b = RGBA_B(v);
            }

            // Grayscale
            int gray = (r * 38 + g * 75 + b * 15) >> 7;

            // Write the pixel back
            if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
                *((uint16_t *) pixel) = MAKE_RGB565(gray, gray, gray);
            } else {// RGBA
                *((uint32_t *) pixel) = MAKE_RGBA(gray, gray, gray, a);
            }
        }
    }


    AndroidBitmap_unlockPixels(env, zBitmap);

}

}
