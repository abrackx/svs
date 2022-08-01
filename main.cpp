#include <cstdio>
#include <iostream>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
    #include <libavutil/log.h>
    #include <vlc/vlc.h>
}


int main (int argc, char *argv[])
{
    libvlc_instance_t *inst = libvlc_new (0, NULL);
    libvlc_media_player_t *x = libvlc_media_player_new(inst);
    libvlc_audio_output_device_t *y = libvlc_audio_output_device_enum(x);

    while (y) {
        std::cout << y->psz_device;
        std::cout <<  "\n";
        y = y->p_next;
    }

    av_log_set_level(AV_LOG_MAX_OFFSET);
    AVFormatContext *fmt_ctx = NULL;
    const AVDictionaryEntry *tag = NULL;
    int ret;

    if (argc != 2) {
        printf("usage: %s <input_file>\n"
               "example program to demonstrate the use of the libavformat metadata API.\n"
               "\n", argv[0]);
        return 1;
    }

    if ((ret = avformat_open_input(&fmt_ctx, "../blah.webm", NULL, NULL)))
        return ret;

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        printf("%s=%s\n", tag->key, tag->value);

    avformat_close_input(&fmt_ctx);
    return 0;
}