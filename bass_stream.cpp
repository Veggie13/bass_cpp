#include "bass_exception.h"
#include "bass_stream.h"

using namespace BASS;


Stream::Stream(
        unsigned         freq,
        unsigned         chans,
        DWORD            flags,
        StreamProcedure* proc,
        void*            user )
: Channel(0)
{
    HSTREAM handle = BASS_StreamCreate(
                        (DWORD)freq,
                        (DWORD)chans,
                        flags,
                        proc,
                        user );
    BASS_ASSERT(handle);
    m_handle = handle;
}

Stream::Stream(
        char*         file,
        unsigned long offset,
        unsigned long length,
        DWORD         flags )
: Channel(0)
{
    HSTREAM handle = BASS_StreamCreateFile(
                        FALSE,
                        file,
                        (QWORD)offset,
                        (QWORD)length,
                        flags );
    BASS_ASSERT(handle);
    m_handle = handle;
}

Stream::Stream(
        void*         memloc,
        unsigned long length,
        DWORD         flags )
: Channel(0)
{
    HSTREAM handle = BASS_StreamCreateFile(
                        TRUE,
                        memloc,
                        (QWORD)0,
                        (QWORD)length,
                        flags );
    BASS_ASSERT(handle);
    m_handle = handle;
}

Stream::Stream(
        DWORD           system,
        DWORD           flags,
        FileProcedures* procs,
        void*           user )
: Channel(0)
{
    HSTREAM handle = BASS_StreamCreateFileUser(
                        system,
                        flags,
                        procs,
                        user );
    BASS_ASSERT(handle);
    m_handle = handle;
}

Stream::Stream(
        char*              url,
        unsigned           offset,
        DWORD              flags,
        DownloadProcedure* proc,
        void*              user )
: Channel(0)
{
    HSTREAM handle = BASS_StreamCreateURL(
                        url,
                        (DWORD)offset,
                        flags,
                        proc,
                        user );
    BASS_ASSERT(handle);
    m_handle = handle;
}

Stream::~Stream()
{
    BOOL result = BASS_StreamFree(m_handle);
    BASS_ASSERT(result == TRUE);
}

unsigned long Stream::GetFilePosition(DWORD mode)
{
    QWORD result = BASS_StreamGetFilePosition(m_handle, mode);
    BASS_ASSERT(result != (QWORD)-1);
    return (unsigned long) result;
}

unsigned Stream::PutData(void* buffer, unsigned length)
{
    DWORD result = BASS_StreamPutData(m_handle, buffer, (DWORD)length);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}

unsigned Stream::PutFileData(void* buffer, unsigned length)
{
    DWORD result = BASS_StreamPutFileData(m_handle, buffer, (DWORD)length);
    BASS_ASSERT(result != (DWORD)-1);
    return (unsigned) result;
}
