#include "bass_channel.h"
#include "bass_exception.h"
#include "bass_sample.h"

using namespace BASS;


Sample::Sample(
    unsigned length,
    unsigned freq,
    unsigned chans,
    unsigned max,
    DWORD    flags )
: m_max(max)
{
    m_handle = BASS_SampleCreate(
                    (DWORD)length,
                    (DWORD)freq,
                    (DWORD)chans,
                    (DWORD)max,
                    flags );
    BASS_ASSERT(m_handle);
}

Sample::Sample(
    char*         filename,
    unsigned long offset,
    unsigned      length,
    unsigned      max,
    DWORD         flags )
: m_max(max)
{
    m_handle = BASS_SampleLoad(
                    FALSE,
                    filename,
                    (QWORD)offset,
                    (DWORD)length,
                    (DWORD)max,
                    flags );
    BASS_ASSERT(m_handle);
}

Sample::Sample(
    void*    memloc,
    unsigned length,
    unsigned max,
    DWORD    flags )
: m_max(max)
{
    m_handle = BASS_SampleLoad(
                    TRUE,
                    memloc,
                    (QWORD)0,
                    (DWORD)length,
                    (DWORD)max,
                    flags );
    BASS_ASSERT(m_handle);
}

Sample::~Sample()
{
    BOOL result = BASS_SampleFree(m_handle);
    BASS_ASSERT(result == TRUE);
}

Channel* Sample::GetChannel(bool onlynew)
{
    HCHANNEL chanHandle = BASS_SampleGetChannel(m_handle, (BOOL)onlynew);
    BASS_ASSERT(chanHandle != (HCHANNEL)0);
    return new Channel(chanHandle);
}

unsigned Sample::GetChannels(Channel** chans)
{
    HCHANNEL* tempArr = new HCHANNEL[m_max];
    DWORD nChans = BASS_SampleGetChannels(m_handle, tempArr);
    BASS_ASSERT(nChans != (DWORD)-1);
    for (unsigned n = 0; n < m_max; ++n)
    {
        if (!tempArr[n]) continue;
        chans[n] = new Channel( tempArr[n] );
    }
    delete[] tempArr;

    return (unsigned) nChans;
}

void Sample::GetData(void* data)
{
    BOOL result = BASS_SampleGetData(m_handle, data);
    BASS_ASSERT(result == TRUE);
}

void Sample::GetInfo(SampleInfo& info)
{
    BOOL result = BASS_SampleGetInfo(m_handle, &info);
    BASS_ASSERT(result == TRUE);
}

void Sample::SetData(void* data)
{
    BOOL result = BASS_SampleSetData(m_handle, data);
    BASS_ASSERT(result == TRUE);
}

void Sample::SetInfo(const SampleInfo& info)
{
    BOOL result = BASS_SampleSetInfo(m_handle, &info);
    BASS_ASSERT(result == TRUE);
}

void Sample::Stop()
{
    BOOL result = BASS_SampleStop(m_handle);
    BASS_ASSERT(result == TRUE);
}

