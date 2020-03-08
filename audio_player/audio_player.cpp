

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

int main(int argc, char* argv[])
{
    AVFormatContext	            *pFormatCtx;
    AVCodecContext	            *pCodecCtx;
    AVCodec			            *pCodec;
    AVPacket		            *packet;
    AVFrame			            *pFrame;
    uint8_t			            *out_buffer;
    int                         i,audioStream;
    SDL_AudioSpec               wanted_spec;
    
    avformat_network_init();
    
    pFrame=av_frame_alloc();
    pFormatCtx = avformat_alloc_context();
    packet=(AVPacket *)av_malloc(sizeof(AVPacket));
    out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);
    
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) !=0 )
    {
		printf("Couldn't open input stream.\n");
		goto avformat_fail;
	}
    
    if(avformat_find_stream_info(pFormatCtx, NULL) <0 )
    {
		printf("Couldn't find stream information.\n");
		goto avformat_fail;
	}
    
    av_dump_format(pFormatCtx, 0, argv[1], false);
    
    audioStream=-1;
    
    for(i=0; i < pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
			audioStream=i;
			break;
		}
    }
    
    if(audioStream==-1)
    {
		printf("Didn't find a audio stream.\n");
		goto avformat_fail;
	}
	
    pCodecCtx=pFormatCtx->streams[audioStream]->codec;
    
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL)
    {
		printf("Codec not found.\n");
		goto avformat_fail;
	}
    
    if(avcodec_open2(pCodecCtx, pCodec, NULL) <0 )
    {
		printf("Could not open codec.\n");
		goto pCodec_fail;
	}
    
    av_init_packet(packet);
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
    int out_nb_samples = pCodecCtx->frame_size;
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    int out_sample_rate = 44100;
    int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {  
		printf( "Could not initialize SDL - %s\n", SDL_GetError()); 
		goto pCodec_fail;
	}

    
	wanted_spec.freq = out_sample_rate; 
	wanted_spec.format = AUDIO_S16SYS; 
	wanted_spec.channels = out_channels; 
	wanted_spec.silence = 0; 
	wanted_spec.samples = out_nb_samples; 
	wanted_spec.callback = fill_audio; 
	wanted_spec.userdata = pCodecCtx; 

    if (SDL_OpenAudio(&wanted_spec, NULL) <0 )
    { 
		printf("can't open audio.\n"); 
		return pCodec_fail; 
	}
    
    
pCodec_fail:
    avcodec_close(pCodecCtx);
avformat_fail:
    av_freep(pFrame);
    av_free_packet(packet);
    av_freep(out_buffer);
    avformat_close_input(&pFormatCtx);
}