#include "bass_exception.h"
#include "bass_plugin.h"
#include "bass_sample.h"
#include "bass_stream.h"
#include "bass_system.h"

using namespace BASS;

System* System::instance = NULL;


System::System()  { }
System::~System() { }

System& System::Get()
{
    if (!instance)
    {
        instance = new System();
    }
    return *instance;
}

void System::Free()
{
    if (instance)
    {
        BOOL result = BASS_Free();
        BASS_ASSERT(result == TRUE);
        delete instance;
        instance = NULL;
    }
}

DWORD System::GetVersion()
{
    return BASS_GetVersion();
}

bool System::MajorVersionMatches()
{
    return ( HIWORD(BASS_GetVersion()) == BASSVERSION );
}

void System::Init(
    int   dev,
    DWORD rate,
    DWORD flags,
    HWND  win,
    GUID* clsid)
{
    BOOL result = BASS_Init(dev,rate,flags,win,clsid);
    BASS_ASSERT(result == TRUE);
}

Algorithm3D System::Get3DAlgorithm()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_3DALGORITHM);
    BASS_ASSERT(result != (DWORD)-1);
    return (Algorithm3D) result;
}

unsigned System::GetBufferLength()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_BUFFER);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

float System::GetCPU()
{
    return BASS_GetCPU();
}

DeviceId System::GetDevice()
{
    DWORD result = BASS_GetDevice();
    BASS_ASSERT(result != (DWORD)-1);
    return (DeviceId) result;
}

void System::GetDeviceInfo(DeviceId device, DeviceInfo& devInfo)
{
    BOOL result = BASS_GetDeviceInfo(device, &devInfo);
    BASS_ASSERT(result == TRUE);
}

unsigned System::GetFileFormatVerificationLength()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_VERIFY);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetGlobalMusicVolume()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_GVOL_MUSIC);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetGlobalSampleVolume()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetGlobalStreamVolume()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_GVOL_STREAM);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

IDirectSound* System::GetIDirectSound()
{
#ifdef _WIN32
    void* result = BASS_GetDSoundObject(BASS_OBJECT_DS);
    BASS_ASSERT(result);
    return reinterpret_cast<IDirectSound*>(result);
#else
	BASS_ASSERT(false);
	return NULL;
#endif
}

IDirectSound3DListener* System::GetIDirectSound3DListener()
{
#ifdef _WIN32
    void* result = BASS_GetDSoundObject(BASS_OBJECT_DS3DL);
    BASS_ASSERT(result);
    return reinterpret_cast<IDirectSound3DListener*>(result);
#else
	BASS_ASSERT(false);
	return NULL;
#endif
}

void System::GetInfo(Info& info)
{
    BOOL result = BASS_GetInfo(&info);
    BASS_ASSERT(result == TRUE);
}

unsigned System::GetMaxVirtualChannels()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_MUSIC_VIRTUAL);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

std::string System::GetNetAgentHeader()
{
    const char* str =
        reinterpret_cast<const char*>(
            BASS_GetConfigPtr(BASS_CONFIG_NET_AGENT) );
    BASS_ASSERT(str);
    return std::string(str);
}

unsigned System::GetNetBufferLength()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_NET_BUFFER);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetNetConnectionTimeout()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_NET_TIMEOUT);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetNetPrebufferAmount()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_NET_PREBUF);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

std::string System::GetNetProxySettings()
{
    const char* str =
        reinterpret_cast<const char*>(
            BASS_GetConfigPtr(BASS_CONFIG_NET_PROXY) );
    BASS_ASSERT(str);
    return std::string(str);
}

unsigned System::GetNumUpdateThreads()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_UPDATETHREADS);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetRecBufferLength()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_REC_BUFFER);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned System::GetUpdatePeriod()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_UPDATEPERIOD);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

float System::GetVolume()
{
    float result = BASS_GetVolume();
    BASS_ASSERT(result >= static_cast<float>(0.0));
    return result;
}

CurveStyle System::GetPanningCurve()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_CURVE_PAN);
    BASS_ASSERT(result != (DWORD)-1);
    return (CurveStyle) result;
}

CurveStyle System::GetVolumeCurve()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_CURVE_VOL);
    BASS_ASSERT(result != (DWORD)-1);
    return (CurveStyle) result;
}

bool System::PlayAllowedWhenPaused()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_PAUSE_NOPLAY);
    BASS_ASSERT(result != (DWORD)-1);
    return (bool) result;
}

bool System::ProcessingPlaylistUrls()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_NET_PLAYLIST);
    BASS_ASSERT(result != (DWORD)-1);
    return (bool) result;
}

bool System::UsingFloatForDSP()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_FLOATDSP);
    BASS_ASSERT(result != (DWORD)-1);
    return (bool) result;
}

bool System::UsingPassiveFtp()
{
    DWORD result = BASS_GetConfig(BASS_CONFIG_NET_PASSIVE);
    BASS_ASSERT(result != (DWORD)-1);
    return (bool) result;
}

void System::AllowPlayWhenPaused(bool allow)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_PAUSE_NOPLAY, (BOOL)allow);
    BASS_ASSERT(result == TRUE);
}

void System::Set3DAlgorithm(Algorithm3D algo)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_3DALGORITHM, algo);
    BASS_ASSERT(result == TRUE);
}

void System::SetBufferLength(unsigned length)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_BUFFER, (DWORD)length);
    BASS_ASSERT(result == TRUE);
}

void System::SetDevice(DeviceId dev)
{
    BOOL result = BASS_SetDevice(dev);
    BASS_ASSERT(result == TRUE);
}

void System::SetFileFormatVerificationLength(unsigned length)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_VERIFY, (DWORD)length);
    BASS_ASSERT(result == TRUE);
}

void System::SetGlobalMusicVolume(unsigned vol)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, (DWORD)vol);
    BASS_ASSERT(result == TRUE);
}

void System::SetGlobalSampleVolume(unsigned vol)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, (DWORD)vol);
    BASS_ASSERT(result == TRUE);
}

void System::SetGlobalStreamVolume(unsigned vol)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, (DWORD)vol);
    BASS_ASSERT(result == TRUE);
}

void System::SetMaxVirtualChannels(unsigned numVirt)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_MUSIC_VIRTUAL, (DWORD)numVirt);
    BASS_ASSERT(result == TRUE);
}

void System::SetNetAgentHeader(const std::string& header)
{
    BOOL result = BASS_SetConfigPtr(
                    BASS_CONFIG_NET_AGENT,
                    const_cast<char*>(header.c_str()) );
    BASS_ASSERT(result == TRUE);
}

void System::SetNetBufferLength(unsigned length)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_NET_BUFFER, (DWORD)length);
    BASS_ASSERT(result == TRUE);
}

void System::SetNewConnectionTimeout(unsigned to)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_NET_TIMEOUT, (DWORD)to);
    BASS_ASSERT(result == TRUE);
}

void System::SetNetPrebufferAmount(unsigned prebuf)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_NET_PREBUF, (DWORD)prebuf);
    BASS_ASSERT(result == TRUE);
}

void System::SetNetProxySettings(const std::string& settings)
{
    BOOL result = BASS_SetConfigPtr(
                    BASS_CONFIG_NET_PROXY,
                    const_cast<char*>(settings.c_str()) );
    BASS_ASSERT(result == TRUE);
}

void System::SetNumUpdateThreads(unsigned numThreads)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_UPDATETHREADS, (DWORD)numThreads);
    BASS_ASSERT(result == TRUE);
}

void System::SetRecBufferLength(unsigned length)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_REC_BUFFER, (DWORD)length);
    BASS_ASSERT(result == TRUE);
}

void System::SetUpdatePeriod(unsigned period)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, (DWORD)period);
    BASS_ASSERT(result == TRUE);
}

void System::SetVolume(float vol)
{
    BOOL result = BASS_SetVolume(vol);
    BASS_ASSERT(result == TRUE);
}

void System::SetPanningCurve(CurveStyle style)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_CURVE_PAN, (DWORD)style);
    BASS_ASSERT(result == TRUE);
}

void System::SetVolumeCurve(CurveStyle style)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_CURVE_VOL, (DWORD)style);
    BASS_ASSERT(result == TRUE);
}

void System::ProcessPlaylistUrls(bool process)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, (BOOL)process);
    BASS_ASSERT(result == TRUE);
}

void System::UseFloatForDSP(bool use)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_FLOATDSP, (BOOL)use);
    BASS_ASSERT(result == TRUE);
}

void System::UsePassiveFtp(bool use)
{
    BOOL result = BASS_SetConfig(BASS_CONFIG_NET_PASSIVE, (BOOL)use);
    BASS_ASSERT(result == TRUE);
}

void System::Pause()
{
    BOOL result = BASS_Pause();
    BASS_ASSERT(result == TRUE);
}

void System::Start()
{
    BOOL result = BASS_Start();
    BASS_ASSERT(result == TRUE);
}

void System::Stop()
{
    BOOL result = BASS_Stop();
    BASS_ASSERT(result == TRUE);
}

void System::Update(unsigned length)
{
    BOOL result = BASS_Update((DWORD)length);
    BASS_ASSERT(result == TRUE);
}

Plugin* System::LoadPlugin(char* filename, bool unicodeName)
{
    return new Plugin(filename, unicodeName);
}

void System::Apply3D()
{
    BASS_Apply3D();
}

void System::Get3DFactors(float* distf, float* rollf, float* doppf)
{
    BOOL result = BASS_Get3DFactors(distf, rollf, doppf);
    BASS_ASSERT(result == TRUE);
}

void System::Get3DPosition(
        Vector3D* pos,
        Vector3D* vel,
        Vector3D* front,
        Vector3D* top )
{
    BOOL result = BASS_Get3DPosition(pos, vel, front, top);
    BASS_ASSERT(result == TRUE);
}

void System::GetEAXParameters(
        EaxEnvironment* env,
        float* vol,
        float* decay,
        float* damp )
{
#ifdef _WIN32
    BOOL result = BASS_GetEAXParameters(env, vol, decay, damp);
    BASS_ASSERT(result == TRUE);
#else
	BASS_ASSERT(false);
#endif
}

void System::Set3DFactors(float distf, float rollf, float doppf)
{
    BOOL result = BASS_Set3DFactors(distf, rollf, doppf);
    BASS_ASSERT(result == TRUE);
}

void System::Set3DPosition(
        Vector3D* pos,
        Vector3D* vel,
        Vector3D* front,
        Vector3D* top )
{
    BOOL result = BASS_Set3DPosition(pos, vel, front, top);
    BASS_ASSERT(result == TRUE);
}

void System::SetEAXParameters(
        EaxEnvironment env,
        float vol,
        float decay,
        float dampening )
{
#ifdef _WIN32
    BOOL result = BASS_SetEAXParameters(env, vol, decay, dampening);
    BASS_ASSERT(result == TRUE);
#else
	BASS_ASSERT(false);
#endif
}

Sample* System::CreateSample(
            unsigned length,
            unsigned freq,
            unsigned chans,
            unsigned max,
            DWORD    flags )
{
    return new Sample(length, freq, chans, max, flags);
}

Sample* System::LoadSampleFromFile(
            char*         filename,
            unsigned long offset,
            unsigned      length,
            unsigned      max,
            DWORD         flags )
{
    return new Sample(filename, offset, length, max, flags);
}

Sample* System::LoadSampleFromMemory(
            void*    memloc,
            unsigned length,
            unsigned max,
            DWORD    flags )
{
    return new Sample(memloc, length, max, flags);
}

Stream* System::CreateStream(
            unsigned         freq,
            unsigned         chans,
            DWORD            flags,
            StreamProcedure* proc,
            void*            user )
{
    return new Stream(freq, chans, flags, proc, user);
}

Stream* System::LoadStreamFromFile(
            char*         file,
            unsigned long offset,
            unsigned long length,
            DWORD         flags )
{
    return new Stream(file, offset, length, flags);
}

Stream* System::LoadStreamFromMemory(
            void*         memloc,
            unsigned long length,
            DWORD         flags )
{
    return new Stream(memloc, length, flags);
}

Stream* System::LoadStreamUsingUser(
            DWORD           system,
            DWORD           flags,
            FileProcedures* procs,
            void*           user )
{
    return new Stream(system, flags, procs, user);
}

Stream* System::LoadStreamFromUrl(
            char*              url,
            unsigned           offset,
            DWORD              flags,
            DownloadProcedure* proc,
            void*              user )
{
    return new Stream(url, offset, flags, proc, user);
}
