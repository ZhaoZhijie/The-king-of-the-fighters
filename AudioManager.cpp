#include "AudioManager.h"
#include <iostream>

#pragma comment(lib, "fmodvc.lib")

CAudioManager::CAudioManager(int LoopVolume, int OnceVolume, int MaxChannel)
:
m_MaxChannel(MaxChannel),
m_OnceVolume(OnceVolume),
m_LoopVolume(LoopVolume)
{
	//FMOD初始化
	FSOUND_Init(44100, MaxChannel, 0);
}

CAudioManager::~CAudioManager()
{
	//通过迭代器 循环释放音频
	std::map<std::string, _LOOPAUDIO>::iterator i;
	for(i = m_LoopAudio.begin(); i != m_LoopAudio.end(); ++i)
	{
		FSOUND_Stream_Close(i->second._s);
	}
	std::map<std::string, FSOUND_SAMPLE*>::iterator j;
	for(j = m_OnceAudio.begin(); j != m_OnceAudio.end(); ++j)
	{
		FSOUND_Sample_Free(j->second);
	}

	//FMOD关闭
	FSOUND_Close();
}

//加载音乐
bool CAudioManager::PushLoopAudio(const char* key,		//音乐ID
					const char* AudioPath)	//音乐路径
{
	//如果找到该key 则加载失败 
	std::string s = key;
	if(m_LoopAudio.find(key) != m_LoopAudio.end())
	{
		return 0;
	}
	//如果没有找到 则加载音乐
	_LOOPAUDIO la;
	la._s = FSOUND_Stream_Open(AudioPath, FSOUND_LOOP_NORMAL, 0, 0);

	//放入映射中
	if(la._s)
	{
		m_LoopAudio[s] = la;
		return 1;
	}
	return 0;
}

//加载音效
bool CAudioManager::PushOnceAudio(const char* key,		//音乐ID
					const char* AudioPath)	//音乐路径
{
	std::string s = key;
	//判断key 是否存在 如果是 返回假
	if(m_OnceAudio.find(key) != m_OnceAudio.end())
		return 0;

	//加载音频
	FSOUND_SAMPLE* fs = FSOUND_Sample_Load(FSOUND_FREE, AudioPath, FSOUND_LOOP_OFF, 0, 0);
	if(fs)
	{
		
		m_OnceAudio[s] = fs;
		return 1;
	}
	return 0;
}

//释放音乐
bool CAudioManager::ReleaseLoopAudio(const char* key)
{
	std::string s = key;
	//如果没有找到 返回失败
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if(i == m_LoopAudio.end())
		return 0;
	//找到则释放
	FSOUND_Stream_Close(i->second._s);
	m_LoopAudio.erase(i);
	return 1;
}
//释放音效
bool CAudioManager::ReleaseOnceAudio(const char* key)
{
	std::string s = key;
	//如果没有找到 返回失败
	std::map<std::string, FSOUND_SAMPLE*>::iterator i = m_OnceAudio.find(s);
	if(i == m_OnceAudio.end())
		return 0;
	//找到则释放
	FSOUND_Sample_Free(i->second);
	m_OnceAudio.erase(i);
	return 1;
}


bool CAudioManager::PlayLoopAudio(const char* key)
{
	//如果当前有循环音频在播放 此次失败
	if(m_PlayingLoopAudio != std::string(""))
		return 0;
	
	//如果无法找到key 也播放失败
	std::string s = key;
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if(i == m_LoopAudio.end())
		return 0;

	//设置当前正在播放的音乐
	m_PlayingLoopAudio = s;
	//播放音频 并得到声道
	i->second._c = FSOUND_Stream_Play(FSOUND_FREE, i->second._s);
	
	//设置音量
	FSOUND_SetVolume( i->second._c, m_LoopVolume);
	return 1;
}

bool CAudioManager::StopLoopAudio(const char* key)
{
	std::string s = key;

	//如果不是当前正在播放的音乐 返回失败
	if(m_PlayingLoopAudio != s)
		return 0;
	//如果无法找到key 返回失败
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if(i == m_LoopAudio.end())
		return 0;

	//设置停止音乐
	m_PlayingLoopAudio = "";
	//停止音频播放
	FSOUND_Stream_Stop(i->second._s);
	//设置声道
	i->second._c = -1;
	return 1;
}

bool CAudioManager::PlayOnceAudio(const char* key)
{
	//如果无法找到key 播放失败
	std::string s = key;
	std::map<std::string, FSOUND_SAMPLE*>::iterator i = m_OnceAudio.find(s);
	if(i == m_OnceAudio.end())
		return 0;

	//播放音频并设置音量
	
	FSOUND_SetVolume(FSOUND_PlaySound(FSOUND_FREE, i->second), m_OnceVolume);
	return 1;
}

int CAudioManager::GetLoopVolume()
{
	//返回背景音乐的音量
	return m_LoopVolume;
}

void CAudioManager::SetLoopVolume(int Volume)
{
	//判断音量范围
	if(Volume < 0)
		Volume = 0;
	else if(Volume > 255)
		Volume = 255;

	m_LoopVolume = Volume;

	if(m_PlayingLoopAudio != std::string(""))
	{
		//设置该音频音量
		FSOUND_SetVolume(m_LoopAudio.find(m_PlayingLoopAudio)->second._c, m_LoopVolume);
	}
}

int CAudioManager::GetOnceVolume()
{
	//返回背景音乐的音量
	return m_OnceVolume;
}

void CAudioManager::SetOnceVolume(int Volume)
{
	//判断音量范围
	if(Volume < 0)
		Volume = 0;
	else if(Volume > 255)
		Volume = 255;

	//得到音量
	m_OnceVolume = Volume;
}


