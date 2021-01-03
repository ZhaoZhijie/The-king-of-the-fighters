#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <string>
#include <map>
#include "fmod.h"

/*
LoopAudio  循环播放的音乐  一般指背景音乐
OnceAudio  只播放一次的音乐 一般指音效
*/

class CAudioManager
{
	//循环音频结构体
	struct _LOOPAUDIO
	{
		//声音流
		FSOUND_STREAM* _s;	//音频流
		//声道
		int _c;
		_LOOPAUDIO()
			:
		_s(0),
		_c(-1)
		{}
	};
	//正在播放的背景音乐
	std::string m_PlayingLoopAudio;
	//声道上限
	int m_MaxChannel;
	//背景音乐音量(0~255)
	int m_LoopVolume;
	//音效音量(0~255)
	int m_OnceVolume;
	//背景音乐存储
	std::map<std::string, _LOOPAUDIO> m_LoopAudio;
	//音效存储
	std::map<std::string, FSOUND_SAMPLE*> m_OnceAudio;

public:
	CAudioManager(int LoopVolume = 127,	//背景音乐音量
				int OnceVolume = 127,	//音效音量
				int MaxChannel = 32);	//声道上限
	
	virtual ~CAudioManager();

	//加载音乐
	bool PushLoopAudio(const char* key,		//音乐ID
					const char* AudioPath);	//音乐路径

	//加载音效
	bool PushOnceAudio(const char* key,		//音乐ID
					const char* AudioPath);	//音乐路径

	//释放音乐
	bool ReleaseLoopAudio(const char* key);
	//释放音效
	bool ReleaseOnceAudio(const char* key);
	//播放音乐
	bool PlayLoopAudio(const char* key);
	//停止音乐
	bool StopLoopAudio(const char* key);
	//播放音效
	bool PlayOnceAudio(const char* key);

	//获取 和 设置 音量
	int GetLoopVolume();
	void SetLoopVolume(int Volume);
	int GetOnceVolume();
	void SetOnceVolume(int Volume);
};

#endif