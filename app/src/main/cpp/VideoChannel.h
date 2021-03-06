
#ifndef PLAYER_VIDEOCHANNEL_H
#define PLAYER_VIDEOCHANNEL_H


#include "BaseChannel.h"
#include "AudioChannel.h"

extern "C" {
#include <libswscale/swscale.h>
};

/**
 * 1、解码
 * 2、播放
 */
typedef void (*RenderFrameCallback)(uint8_t *,int,int,int);
class VideoChannel : public BaseChannel {
public:
    VideoChannel(int id, AVCodecContext *avCodecContext, int fps, AVRational time_base);

    ~VideoChannel();

    void setAudioChannel(AudioChannel *audioChannel);

    //解码+播放
    void play();

    void decode();

    void render();

    void setRenderFrameCallback(RenderFrameCallback callback);
private:
    pthread_t pid_decode;
    pthread_t pid_render;

    SwsContext *swsContext=0;
    RenderFrameCallback callback;
    //帧率
    int fps = 0;

    double clock;
    AudioChannel *audioChannel = 0;
};


#endif //PLAYER_VIDEOCHANNEL_H
