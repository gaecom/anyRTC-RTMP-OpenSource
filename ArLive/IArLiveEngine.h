/*
*  Copyright (c) 2021 The AnyRTC project authors. All Rights Reserved.
*
*  Please visit https://www.anyrtc.io for detail.
*
* The GNU General Public License is a free, copyleft license for
* software and other kinds of works.
*
* The licenses for most software and other practical works are designed
* to take away your freedom to share and change the works.  By contrast,
* the GNU General Public License is intended to guarantee your freedom to
* share and change all versions of a program--to make sure it remains free
* software for all its users.  We, the Free Software Foundation, use the
* GNU General Public License for most of our software; it applies also to
* any other work released this way by its authors.  You can apply it to
* your programs, too.
* See the GNU LICENSE file for more info.
*/
#ifndef __I_AR_LIVE_ENGINE_H__
#define __I_AR_LIVE_ENGINE_H__
#include <stdint.h>
#include "ArLiveBase.h"
#include "IArRtcEngine.h"
#include "IArLivePushKit.h"
#include "IArLivePlayKit.h"

namespace ar {
namespace live {

class IArAudioVolumeEvaluationListener
{
public:
	IArAudioVolumeEvaluationListener(void) {};
	virtual ~IArAudioVolumeEvaluationListener(void) {};

	virtual void onAudioVolumeEvaluationNotify(AR::uid_t uid, int volume) {
		(void)uid;
		(void)volume;
	}
};

class IArVideoRawDataListener
{
public:
	IArVideoRawDataListener(void) {};
	virtual ~IArVideoRawDataListener(void) {};

	virtual void onVideoRawDataAvailable(const char*uid, char* yuvBuffer, int width, int height, unsigned int timestamp) {
		(void)uid;
		(void)yuvBuffer;
		(void)width;
		(void)height;
		(void)timestamp;
	}
};

class IArAudioRawDataListener
{
public:
	IArAudioRawDataListener(void) {};
	virtual ~IArAudioRawDataListener(void) {};

	virtual void onPcmDataAvailable(const char*uid, short* buf, int nSampleHz, int nChannel, unsigned int timestamp) {
		(void)uid;
		(void)buf;
		(void)nSampleHz;
		(void)nChannel;
		(void)timestamp;
	}
};

class IArBGMEvent
{
	IArBGMEvent(void) {};
	virtual ~IArBGMEvent(void) {};

	/* BGM�ļ���ʱ����Ϣ
	������
		duration	int	��ǰ BGM ��ʱ�䣨ms����
	*/
	virtual void onBGMInfo(int duration) {};

	/* BGM��ʼ����
	*/
	virtual void onBGMStart() {};
	/* BGM���Ž���
	������
		progress	int	��ǰ BGM �Ѳ���ʱ�䣨ms����
		duration	int	��ǰ BGM ��ʱ�䣨ms����
	*/
	virtual void onBGMProgress(int progress, int duration) {};

	/* BGM����ֹͣ
	������
		err	int	0������������-1������������
	*/
	virtual void onBGMComplete(int err) {};
};

class IArLiveEngineEvent
{
public:
	IArLiveEngineEvent(void) {};
	virtual ~IArLiveEngineEvent(void) {};

};
	
class IArLiveEngine
{
public:

	IArLiveEngine(void) {};
	virtual ~IArLiveEngine(void) {};

	/* ��ʼ������
	������
		pEvent	IArLiveEngineEvent	�����¼�����ָ�롣
	*/
	virtual int initialize(IArLiveEngineEvent* pEvent) = 0;
	/* �ͷŶ���
	������
	*/
	virtual void release() = 0;

	/* ������������
	������
		pEvent	IArLivePushEvent	���������¼�����ָ�롣
	���أ�
		IArLivePushKit����
	*/
	virtual IArLivePushKit* createPushKit(IArLivePushEvent*pEvent) = 0;
	/* ������������
	������
		pEvent	IArLivePushEvent	���������¼�����ָ�롣
	���أ�
		IArLivePlayKit����
	*/
	virtual IArLivePlayKit* createPlayKit(IArLivePlayListener*pEvent) = 0;

	/* ����ʵ���� API �ӿ�(�������)��
	������
		jsonStr	String	jsonStr �ӿڼ����������� JSON �ַ�����
	*/
	virtual void callExperimentalAPI(const char* strJson) = 0;

	//**************************************************************************\\
	//**************************************************************************\\
	// Video Module
	/* ��������ͷԤ������
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int setupCameraView(const AR::VideoCanvas& canvas) = 0;
	/* ������Ƶ����
	������
		vidDimensions	VideoDimensions	��Ƶ�ֱ��ʡ�
		adjustBitrate	boolean	��̬���ʿ��ء�
		adjustResolution	boolean	��̬�зֱ��ʿ��ء�
		orientationMode	ORIENTATION_MODE �������Ƶ����
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int setVideoQuality(AR::VideoDimensions vidDimensions, bool adjustBitrate, bool adjustResolution, AR::ORIENTATION_MODE orientationMode) = 0;
	/* ��ʼ����ͷԤ��
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int startVideoPreview() = 0;
	/* ֹͣ����ͷԤ��
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int stopVideoPreview() = 0;
	/* ������Ƶ����
	���ܣ�
		�������ú󣬲��������������ͷ��ͼ�񣬵���ͼ�������Էǳ�С�ĺ������ݽ������ͣ���������Ŀ����Ϊ�˼��� H5 �ϵ� video ��ǩ������¼�Ƴ����� MP4 �ļ��и��õļ����ԡ�
	������
		mute: ture - �������� / false - �رս���
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int setVideoMute(bool mute) = 0;
	/* ����ͷ����
	���ܣ�
		�������ú󣬲���������ɼ�����ͷͼ�񣬵��Ǻ���(������Ƶ)�����������
	������
		mute: ture - �������� / false - �رս���
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int muteLocalVideoStream(bool mute) = 0;
	/* ��ƵSEI����
	*/
	virtual int setVideoSei(const char*pSei, int nLen) = 0;
	/* �Բɼ���Ƶ����
	*/
	virtual int setVideoCustomData() = 0;

	//**************************************************************************\\
	// Audio Module
	/* ������Ƶ����
	���ܣ�
		����������(����BGM)������������ɼ���˷�����������ǻ��÷ǳ��ͣ�5kbps���ң�����������α�������ݣ� ��������Ŀ����Ϊ�˼��� H5 �ϵ� video ��ǩ������¼�Ƴ����� MP4 �ļ��и��õļ����ԡ�
	������
		mute: ture - �������� / false - �رս���
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int setAudioMute(bool mute) = 0;
	/* Mic����
	���ܣ�
		����������(������BGM)������������ɼ���˷������������BGM�����������
	������
		mute: ture - �������� / false - �رս���
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int muteLocalAudioStream(bool mute) = 0;
	/*������˷�������С
	������
		nVolume	int	������С��100Ϊ������������Χ�ǣ�[0 ~ 400] ֮���������
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int adjustMicVolume(int nVolume) = 0;


	//**************************************************************************\\
	//**************************************************************************\\
	// Play Module - �������ýӿ�
	/* ���ò���������Ƶ��Ⱦ View��
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		canvas	ArVideoCanvas	��ͼ����
	*/
	virtual void setPlayerView(AR::uid_t userId, const AR::VideoCanvas& canvas) = 0;
	/* ���ò�����Ⱦģʽ��
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		mode	RENDER_MODE_TYPE	��Ƶ��Ⱦ��ģʽ����μ� RENDER_MODE_TYPE��
	*/
	virtual void setRenderMode(AR::uid_t uid, AR::RENDER_MODE_TYPE mode) = 0;

	/* ����ͼ����Ⱦ�Ƕȡ�
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		rotation	ORIENTATION_MODE	ͼ����Ⱦ�Ƕȣ�������ֵΪ��RENDER_ROTATION#RENDER_ROTATION_PORTRAIT��RENDER_ROTATION#RENDER_ROTATION_LANDSCAPE��
	*/
	virtual void setRenderRotation(AR::uid_t uid, AR::ORIENTATION_MODE rotation) = 0;
	/* ����Ӳ�����١�
	������
		enable	boolean	true��������ƵӲ���룬 false��������ƵӲ���롣
	*/
	virtual bool enableHardwareDecode(bool enable) = 0;

	/* �����Ƿ������š�
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		mute	boolean	true���������ţ�false�����������š�
	*/
	virtual int muteRemoteAudioStream(AR::uid_t userId, bool mute) = 0;
	/* �����Ƿ������Ƶ��
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		mute	boolean	true�����ţ�false�������š�
	*/
	virtual int muteRemoteVideoStream(AR::uid_t userId, bool mute) = 0;
	/* �����Ƿ������в��š�
	������
		mute	boolean	true���������ţ�false�����������š�
	*/
	virtual int muteAllRemoteAudioStreams(bool mute) = 0;
	/* ����Զ�����Ĵ�С��
	������
		userId	AR::uid_t		��ͼ��������ƣ�������Ĭ��Ϊ:"0"��������ԱΪ������Ա��UId
		streamType	REMOTE_VIDEO_STREAM_TYPE	����С
	*/
	virtual int setRemoteVideoStreamType(AR::uid_t userId, AR::REMOTE_VIDEO_STREAM_TYPE streamType) = 0;

	/* ���ò���������
	������
		volume	int	������С��ȡֵ��Χ 0 - 100��
	*/
	virtual int adjustSpkrVolume(int volume) = 0;
	/* ������������ģʽ��
	���ܣ�
		����ģʽ������(��Android��iOS)��

		��Ͳ������������Ͳ������
		����������������������������
	*/
	virtual int setAudioRoute(int audioRoute) = 0;

	virtual int setAudioCustomData() = 0;
	
	//**************************************************************************\\
	// ���ݻص��ӿ�
	/* ����������С�ص��ӿڡ�
	������
		listener	IArAudioVolumeEvaluationListener	������С�ص��ӿڡ�
	*/
	virtual void setAudioVolumeEvaluationListener(IArAudioVolumeEvaluationListener* listener) = 0;

	/* ����������С������
	������
		intervalMs	int	intervalMs ������ onAudioVolumeEvaluationNotify �ص��Ĵ����������λΪms����С���Ϊ 100ms�����С�ڵ��� 0 ���رջص�����������Ϊ 300ms��
	*/
	virtual void enableAudioVolumeEvaluation(int intervalMs) = 0;
	/* ������������Ƶ���ݻص���
	������
		listener	IArVideoRawDataListener	��Ƶ���ݻص���
	*/
	virtual void setVideoRawDataListener(IArVideoRawDataListener* listener) = 0;

	/* ������Ƶ���ݻص���
	������
		listener	ITXAudioRawDataListener	��Ƶ���ݻص���
	*/
	virtual void setAudioRawDataListener(IArAudioRawDataListener* listener) = 0;

#ifdef ANY_RTC_CHAT
	//**************************************************************************\\
	//**************************************************************************\\
	//* For BGM
	/* ���������¼��ص�
	������
		pEvent	IArBGMEvent*	�ص�BGM�¼����ն���
	*/
	virtual void setArBGMEvent(IArBGMEvent*pEvent) = 0;
	/*���ű������֡�
	���ܣ�
		�Ὣ�������ֺ���˷�ɼ����������л�ϲ�һ�����͵��ƶˡ�
	���أ�
		true�����ųɹ���false������ʧ�ܡ�
	*/
	virtual bool playBGM(const char* path, int repeat) = 0;
	/* ֹͣ���ű������֡�
	���أ�
		true��ֹͣ���ųɹ��� false��ֹͣ����ʧ�ܡ�
	*/
	virtual bool stopBGM() = 0;
	/* ��ͣ���ű������֡�
	���أ�
		true��ֹͣ���ųɹ��� false��ֹͣ����ʧ�ܡ�
	*/
	virtual bool pauseBGM() = 0;
	/* �������ű����֡�
	���أ�
		true��ֹͣ���ųɹ��� false��ֹͣ����ʧ�ܡ�
	*/
	virtual int resumeBGM() = 0;
	/*���û���ʱ�������ֵ�������С�����ڲ��ű������ֻ���ʱʹ�á�
	������
		nVolume	int	������С��100Ϊ������������Χ�ǣ�[0 ~ 400] ֮���������
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int adjustBGMVolume(int nVolume) = 0;

	//**************************************************************************\\
	//**************************************************************************\\
	// ��Ļ�����ӿ�
#if defined(_WIN32)
	virtual int startScreenCaptureByScreenRect(const AR::Rectangle& screenRect, const AR::Rectangle& regionRect, const AR::ScreenCaptureParameters& captureParams) = 0;
#endif
	virtual int startScreenCaptureByWindowId(AR::view_t windowId, const AR::Rectangle& regionRect, const AR::ScreenCaptureParameters& captureParams) = 0;
	virtual int updateScreenCaptureParameters(const AR::ScreenCaptureParameters& captureParams) = 0;
	virtual int updateScreenCaptureRegion(const AR::Rectangle& regionRect) = 0;
	virtual int stopScreenCapture() = 0;

	//**************************************************************************\\
	//**************************************************************************\\
	// ����ӿ�
	virtual int initRtcEngine(const char*appId) = 0;
	virtual int setClientRole(AR::CLIENT_ROLE_TYPE role) = 0;
	virtual int joinChannel(const char* token, const char* channelId, const char* info, AR::uid_t uid) = 0;
	virtual int switchChannel(const char* token, const char* channelId) = 0;
	virtual int leaveChannel() = 0;
	virtual int renewToken(const char* token) = 0;

#endif
};
}
};



#endif	// __I_AR_LIVE_ENGINE_H__