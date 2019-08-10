#include <stdio.h>

#define __STDC_CONSTANT_MACROS
 
#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "SDL/SDL.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#ifdef __cplusplus
};
#endif
#endif

//Refresh
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT    (SDL_USEREVENT + 2)

bool thread_exit = false;
bool thread_pause = false;

// Thread 每40s响应一次SFM_REFRESH_EVENT事件
int sfp_refresh_thread(void * opaque)
{
    
	thread_exit = false;
	thread_pause = false;
    
    SDL_Event event;
    while(!thread_exit)
    {
        if(!thread_pause)
        {
            event.type = SFM_REFRESH_EVENT;
            SDL_PushEvent(&event);
        }
        SDL_Delay(40);
    }
    thread_exit = false;
    thread_pause = false;
    
    // break
    event.type = SFM_BREAK_EVENT;
    SDL_PushEvent(&event);
    return 0;
}

// 实现：1.图像色彩空间转换；2.分辨率缩放；3.前后图像滤波处理。
int my_av_read_frame(
	AVFormatContext   *pFormatCtx,
	AVPacket          *packet,
	AVCodecContext    *pCodecCtx,
	AVFrame           *pFrame,
	AVFrame           *pFrameYUV,
	int               videoindex,
	struct SwsContext *img_convert_ctx,
    SDL_Texture       *sdlTexture,
    SDL_Renderer      *sdlRenderer)
{
	int ret = -1,got_picture = 0;
    while(1)
    {
        if(av_read_frame(pFormatCtx, packet)<0)
        {
            thread_exit=1;
        }
        if(packet->stream_index==videoindex)
        {
            break;
        }
    }
    ret = avcodec_decode_video2(pCodecCtx,pFrame,&got_picture,packet);
    if(ret < 0)
			{
				printf("Decode Error.\n");
				return -1;
			}
    
    if(got_picture)
    {
        sws_scale(img_convert_ctx,(const uint8_t* const*)pFrame->data,pFrame->linesize,0,pCodecCtx->height,pFrameYUV->data,pFrameYUV->linesize);
        // SDL
        SDL_UpdateTexture( sdlTexture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0] );
        SDL_RenderClear( sdlRenderer );
        SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent( sdlRenderer );
    }
    av_free_packet(packet);
}

int main(int argc,char *argv[])
{
    AVFormatContext   *pFormatCtx;
    AVCodecContext    *pCodecCtx;
    AVCodec           *pCodec;
    AVPacket          *packet;
    AVFrame           *pFrame,*pFrameYUV;
    struct SwsContext *img_convert_ctx;
    unsigned char     *out_buffer;
    // SDL2
    SDL_Window        *screen;
    SDL_Renderer      *sdlRenderer;
    SDL_Texture       *sdlTexture;
    SDL_Rect          sdlRect;
    SDL_Thread        *video_tid;
    SDL_Event         event;
    int               screen_w = 0,screen_h = 0;
    int               i,videoindex = -1;
        
    //avdevice_register_all();
    avformat_network_init();
    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();
    pFormatCtx = avformat_alloc_context();
    packet = (AVPacket *)av_malloc(sizeof(AVPacket));
    
    if(0 != avformat_open_input(&pFormatCtx,argv[1],NULL,NULL))
    {
        printf("couldn't open input stream.\n");
        return -1;
    }
    
    if(avformat_find_stream_info(pFormatCtx,NULL) < 0)
    {
        printf("couldn't find stream information.\n");
        return -1;
    }
    
    for(i = 0;i < pFormatCtx->nb_streams;i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
            break;
        }
    }
    
    if(-1 == videoindex)
    {
        printf("Didn't find a video stream.\n");
        return -1;
    }
    
    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec == NULL)
    {
        printf("Codec not found.\n");
        return -1;
    }
    
    if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0)
    {
        printf("could not open codec.\n");
        return -1;
    }
    
    out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  pCodecCtx->width, pCodecCtx->height,1));
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height,1);
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        printf("could not initialize SDL - %s\n",SDL_GetError());
        return -1;
    }
    
    screen_w = pCodecCtx->width;
    screen_h = pCodecCtx->height;
    screen = SDL_CreateWindow("qun_player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,screen_w, screen_h,SDL_WINDOW_OPENGL);
    //screen = SDL_CreateWindow("qun_player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,screen_w, screen_h,SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(!screen)
    {
        printf("SDL: could not set video mode - exiting:%s\n");
        return -1;
    }
    
    sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    
    sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,pCodecCtx->width,pCodecCtx->height);
    
    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = screen_w;
    sdlRect.h = screen_h;
    
    printf("------------File Information-----------\n");
    av_dump_format(pFormatCtx,0,argv[1],0);
    printf("-----------------End--------------------\n");
    
	// 初始化sws_scale
    img_convert_ctx = sws_getContext(screen_w,screen_h,pCodecCtx->pix_fmt,screen_w,screen_h,AV_PIX_FMT_YUV420P,SWS_BICUBIC,NULL,NULL,NULL);
    
    video_tid = SDL_CreateThread(sfp_refresh_thread,NULL,NULL);
    
    for(;;)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SFM_REFRESH_EVENT:
                my_av_read_frame(pFormatCtx, packet, pCodecCtx, pFrame, pFrameYUV, videoindex, img_convert_ctx, sdlTexture, sdlRenderer);
                break;
            case SDL_KEYDOWN:
            {
                if(event.key.keysym.sym==SDLK_SPACE)
                    thread_pause=!thread_pause;
                break;
            }
            case SDL_QUIT:
                thread_exit=1;
                break;
            case SFM_BREAK_EVENT:
                break;
            default:
                printf("could not know the event\n");
        }
    }
    
    SDL_Quit();
    sws_freeContext(img_convert_ctx);
    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    
    return 0;
}
