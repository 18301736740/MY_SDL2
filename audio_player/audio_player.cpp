#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 使用c99中的一些东西
#define __STDC_CONSTANT_MACROS
#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio


#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <SDL2/SDL.h>
#ifdef __cplusplus
};
#endif



/*Buffer:
 *|-----------|-------------|
 *chunk-------pos---len-----|
*/

static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;

/* The audio function callback takes the following parameters:
 * stream: A pointer to the audio buffer to be filled
 * len: The length (in bytes) of the audio buffer
*/

void  fill_audio(void *udata, Uint8 *stream, int len)
{
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);	/*  Mix  as  much  data  as  possible  */

    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}

int main(int argc, char *argv[])
{
    AVFormatContext	            *pFormatCtx;
    AVCodecContext	            *pCodecCtx;
    AVCodec			            *pCodec;
    AVPacket		            *packet;
    AVFrame			            *pFrame;
    uint8_t			            *out_buffer;
    int                         got_picture, index = 0, ret, i, audioStream;
    SDL_AudioSpec               wanted_spec;
    int64_t                     in_channel_layout;
    uint32_t                    len = 0;
    struct SwrContext           *au_convert_ctx;
    uint64_t                    out_channel_layout;
    int                         out_nb_samples;
    AVSampleFormat              out_sample_fmt;
    int                         out_sample_rate;
    int                         out_channels;
    int                         out_buffer_size;

    avformat_network_init();

    pFrame = av_frame_alloc();
    pFormatCtx = avformat_alloc_context();
    packet = (AVPacket *)av_malloc(sizeof(AVPacket));
    out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);

    if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
    {
        printf("Couldn't open input stream.\n");
        goto avformat_fail;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        printf("Couldn't find stream information.\n");
        goto avformat_fail;
    }

    av_dump_format(pFormatCtx, 0, argv[1], false);

    audioStream = -1;

    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioStream = i;
            break;
        }
    }

    if (audioStream == -1)
    {
        printf("Didn't find a audio stream.\n");
        goto avformat_fail;
    }

    pCodecCtx = pFormatCtx->streams[audioStream]->codec;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL)
    {
        printf("Codec not found.\n");
        goto avformat_fail;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("Could not open codec.\n");
        goto pCodec_fail;
    }

    av_init_packet(packet);
    out_channel_layout = AV_CH_LAYOUT_STEREO;
    out_nb_samples = pCodecCtx->frame_size;
    out_sample_fmt = AV_SAMPLE_FMT_S16;
    out_sample_rate = 44100;
    out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        goto pCodec_fail;
    }


    wanted_spec.freq = out_sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = out_channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = out_nb_samples;
    wanted_spec.callback = fill_audio;
    wanted_spec.userdata = pCodecCtx;

    if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
    {
        printf("can't open audio.\n");
        goto pCodec_fail;
    }

    //FIX:Some Codec's Context Information is missing
    in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);
    //Swr
    au_convert_ctx = swr_alloc();
    au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, out_channel_layout, out_sample_fmt, out_sample_rate,
                                        in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);

    swr_init(au_convert_ctx);
    //Play
    SDL_PauseAudio(0);
    while (av_read_frame(pFormatCtx, packet) >= 0)
    {
        if (packet->stream_index == audioStream)
        {
            ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, packet);
            if (ret < 0)
            {
                printf("Error in decoding audio frame.\n");
                goto pCodec_fail;
            }
            if (got_picture > 0)
            {
                swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE,
                            (const uint8_t **)pFrame->data, pFrame->nb_samples);

                printf("index:%5d\t pts:%lld\t packet size:%d\n", index, packet->pts, packet->size);
                index++;
            }

            //Wait until finish
            while (audio_len > 0)
                SDL_Delay(1);

            //Set audio buffer (PCM data)
            audio_chunk = (Uint8 *) out_buffer;
            //Audio buffer length
            audio_len = out_buffer_size;
            audio_pos = audio_chunk;
        }
        av_free_packet(packet);
    }

    SDL_CloseAudio();
    SDL_Quit();
    swr_free(&au_convert_ctx);

pCodec_fail:
    avcodec_close(pCodecCtx);
avformat_fail:
    av_freep(pFrame);
    av_freep(out_buffer);
    avformat_close_input(&pFormatCtx);

    return 0;
}
