#include "bass_channel.h"
#include "bass_exception.h"

using namespace BASS;


Channel::Channel(DWORD handle)
: m_handle(handle)
{ }

Channel::~Channel() { }

double Channel::Bytes2Seconds(unsigned long pos)
{
    double result = BASS_ChannelBytes2Seconds(m_handle, (QWORD)pos);
    BASS_ASSERT(result >= static_cast<double>(0.0));
    return result;
}

unsigned long Channel::Seconds2Bytes(double pos)
{
    QWORD result = BASS_ChannelSeconds2Bytes(m_handle, pos);
    BASS_ASSERT(result != (QWORD)-1);
    return (unsigned long) result;
}

DWORD Channel::Flags(DWORD flags, DWORD mask)
{
    DWORD result = BASS_ChannelFlags(m_handle, flags, mask);
    BASS_ASSERT(result != (DWORD)-1);
    return result;
}

void Channel::Get3DAttributes(
                    DWORD* mode,
                    float* min,
                    float* max,
                    DWORD* iangle,
                    DWORD* oangle,
                    float* outvol )
{
    BOOL result = BASS_ChannelGet3DAttributes(
                        m_handle,
                        mode,
                        min,
                        max,
                        iangle,
                        oangle,
                        outvol );
    BASS_ASSERT(result == TRUE);
}

void Channel::Get3DPosition(
                    Vector3D* pos,
                    Vector3D* orient,
                    Vector3D* vel )
{
    BOOL result = BASS_ChannelGet3DPosition(
                        m_handle,
                        pos,
                        orient,
                        vel );
    BASS_ASSERT(result == TRUE);
}

void Channel::GetAttribute(DWORD attrib, float* value)
{
    BOOL result = BASS_ChannelGetAttribute(m_handle, attrib, value);
    BASS_ASSERT(result == TRUE);
}

void Channel::GetData(void* buffer, DWORD length)
{
    BOOL result = BASS_ChannelGetData(m_handle, buffer, length);
    BASS_ASSERT(result == TRUE);
}

DeviceId Channel::GetDevice()
{
    DWORD result = BASS_ChannelGetDevice(m_handle);
    BASS_ASSERT(result != (DWORD)-1);
    return (DeviceId) result;
}

void Channel::GetInfo(ChannelInfo& info)
{
    BOOL result = BASS_ChannelGetInfo(m_handle, &info);
    BASS_ASSERT(result == TRUE);
}

unsigned long Channel::GetLength(bool useOrders)
{
    QWORD result = BASS_ChannelGetLength(
                        m_handle,
                        useOrders ? BASS_POS_MUSIC_ORDER : BASS_POS_BYTE );
    BASS_ASSERT(result != (QWORD)-1);
    return (unsigned long) result;
}

DWORD Channel::GetLevel()
{
    DWORD result = BASS_ChannelGetLevel(m_handle);
    BASS_ASSERT(result != (DWORD)-1);
    return result;
}

unsigned long Channel::GetPosition(bool useOrders)
{
    QWORD result = BASS_ChannelGetPosition(
                        m_handle,
                        useOrders ? BASS_POS_MUSIC_ORDER : BASS_POS_BYTE );
    BASS_ASSERT(result != (QWORD)-1);
    return (unsigned long) result;
}

const char* Channel::GetTags(DWORD tags)
{
    const char* result = BASS_ChannelGetTags(m_handle, tags);
    BASS_ASSERT(result);
    return result;
}

ChannelState Channel::GetActiveState()
{
    DWORD result = BASS_ChannelIsActive(m_handle);
    return (ChannelState) result;
}

bool Channel::AttributeIsSliding(DWORD attrib)
{
    BOOL result = BASS_ChannelIsSliding(m_handle, attrib);
    return (bool) result;
}

void Channel::Set3DAttributes(
                    int mode,
                    float min,
                    float max,
                    int iangle,
                    int oangle,
                    float outvol )
{
    BOOL result = BASS_ChannelSet3DAttributes(
                        m_handle,
                        mode,
                        min,
                        max,
                        iangle,
                        oangle,
                        outvol );
    BASS_ASSERT(result == TRUE);
}

void Channel::Set3DPosition(
                    Vector3D* pos,
                    Vector3D* orient,
                    Vector3D* vel )
{
    BOOL result = BASS_ChannelSet3DPosition(
                        m_handle,
                        pos,
                        orient,
                        vel );
    BASS_ASSERT(result == TRUE);
}

void Channel::SetAttribute(DWORD attrib, float value)
{
    BOOL result = BASS_ChannelSetAttribute(m_handle, attrib, value);
    BASS_ASSERT(result == TRUE);
}

void Channel::SetDevice(DeviceId dev)
{
    BOOL result = BASS_ChannelSetDevice(m_handle, (DWORD)dev);
    BASS_ASSERT(result == TRUE);
}

DspHandle Channel::SetDSP(DspProcedure* dsp, void* user, int priority)
{
    DspHandle result = BASS_ChannelSetDSP(m_handle, dsp, user, priority);
    BASS_ASSERT(result);
    return result;
}

EffectHandle Channel::SetEffect(DWORD type, int priority)
{
    EffectHandle result = BASS_ChannelSetFX(m_handle, type, priority);
    BASS_ASSERT(result);
    return result;
}

void Channel::SetLink(Channel* chan)
{
    BOOL result = BASS_ChannelSetLink(m_handle, chan->m_handle);
    BASS_ASSERT(result == TRUE);
}

void Channel::SetPosition(unsigned long pos, DWORD mode)
{
    BOOL result = BASS_ChannelSetPosition(m_handle, (QWORD)pos, mode);
    BASS_ASSERT(result == TRUE);
}

SyncHandle Channel::SetSync(DWORD type, QWORD param, SyncProcedure* proc, void* user)
{
    SyncHandle result = BASS_ChannelSetSync(m_handle, type, param, proc, user);
    BASS_ASSERT(result);
    return result;
}

void Channel::SlideAttribute(DWORD attrib, float value, unsigned time)
{
    BOOL result = BASS_ChannelSlideAttribute(m_handle, attrib, value, (DWORD)time);
    BASS_ASSERT(result == TRUE);
}

void Channel::Lock()
{
    BOOL result = BASS_ChannelLock(m_handle, TRUE);
    BASS_ASSERT(result == TRUE);
}

void Channel::UnLock()
{
    BOOL result = BASS_ChannelLock(m_handle, FALSE);
    BASS_ASSERT(result == TRUE);
}

void Channel::Pause()
{
    BOOL result = BASS_ChannelPause(m_handle);
    BASS_ASSERT(result == TRUE);
}

void Channel::Play(bool restart)
{
    BOOL result = BASS_ChannelPlay(m_handle, (BOOL)restart);
    BASS_ASSERT(result == TRUE);
}

void Channel::Stop()
{
    BOOL result = BASS_ChannelStop(m_handle);
    BASS_ASSERT(result == TRUE);
}

void Channel::Update(unsigned length)
{
    BOOL result = BASS_ChannelUpdate(m_handle, (DWORD)length);
    BASS_ASSERT(result == TRUE);
}

void Channel::RemoveDSP(DspHandle dsp)
{
    BOOL result = BASS_ChannelRemoveDSP(m_handle, dsp);
    BASS_ASSERT(result == TRUE);
}

void Channel::RemoveEffect(EffectHandle fx)
{
    BOOL result = BASS_ChannelRemoveFX(m_handle, fx);
    BASS_ASSERT(result == TRUE);
}

void Channel::RemoveLink(Channel* chan)
{
    BOOL result = BASS_ChannelRemoveLink(m_handle, chan->m_handle);
    BASS_ASSERT(result == TRUE);
}

void Channel::RemoveSync(SyncHandle sync)
{
    BOOL result = BASS_ChannelRemoveSync(m_handle, sync);
    BASS_ASSERT(result == TRUE);
}

