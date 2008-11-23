#include <bass.h>

#include "bass_exception.h"

using namespace BASS;


Exception::Exception(const char* msg)
: m_msg(msg)
{
    fprintf(stderr, "Exception: %s\n", msg);
}

Exception::~Exception() throw() { }

const char* Exception::what()
{
    return m_msg.c_str();
}

void Exception::ThrowError()
{
    const char* msg;
    switch ( BASS_ErrorGetCode() )
    {
    case BASS_ERROR_MEM:
        msg = "memory error";
        break;
    case BASS_ERROR_FILEOPEN:
        msg = "can't open the file";
        break;
    case BASS_ERROR_DRIVER:
        msg = "can't find a free/valid driver";
        break;
    case BASS_ERROR_BUFLOST:
        msg = "the sample buffer was lost";
        break;
    case BASS_ERROR_HANDLE:
        msg = "invalid handle";
        break;
    case BASS_ERROR_FORMAT:
        msg = "unsupported sample format";
        break;
    case BASS_ERROR_POSITION:
        msg = "invalid position";
        break;
    case BASS_ERROR_INIT:
        msg = "BASS_Init has not been successfully called";
        break;
    case BASS_ERROR_START:
        msg = "BASS_Start has not been successfully called";
        break;
    case BASS_ERROR_ALREADY:
        msg = "already initialized/paused/whatever";
        break;
    case BASS_ERROR_NOCHAN:
        msg = "can't get a free channel";
        break;
    case BASS_ERROR_ILLTYPE:
        msg = "an illegal type was specified";
        break;
    case BASS_ERROR_ILLPARAM:
        msg = "an illegal parameter was specified";
        break;
    case BASS_ERROR_NO3D:
        msg = "no 3D support";
        break;
    case BASS_ERROR_NOEAX:
        msg = "no EAX support";
        break;
    case BASS_ERROR_DEVICE:
        msg = "illegal device number";
        break;
    case BASS_ERROR_NOPLAY:
        msg = "not playing";
        break;
    case BASS_ERROR_FREQ:
        msg = "illegal sample rate";
        break;
    case BASS_ERROR_NOTFILE:
        msg = "the stream is not a file stream";
        break;
    case BASS_ERROR_NOHW:
        msg = "no hardware voices available";
        break;
    case BASS_ERROR_EMPTY:
        msg = "the MOD music has no sequence data";
        break;
    case BASS_ERROR_NONET:
        msg = "no internet connection could be opened";
        break;
    case BASS_ERROR_CREATE:
        msg = "couldn't create the file";
        break;
    case BASS_ERROR_NOFX:
        msg = "effects are not available";
        break;
    case BASS_ERROR_NOTAVAIL:
        msg = "requested data is not available";
        break;
    case BASS_ERROR_DECODE:
        msg = "the channel is a decoding channel";
        break;
    case BASS_ERROR_DX:
        msg = "a sufficient DirectX version is not installed";
        break;
    case BASS_ERROR_TIMEOUT:
        msg = "connection timedout";
        break;
    case BASS_ERROR_FILEFORM:
        msg = "unsupported file format";
        break;
    case BASS_ERROR_SPEAKER:
        msg = "unavailable speaker";
        break;
    case BASS_ERROR_VERSION:
        msg = "invalid BASS version (used by add-ons)";
        break;
    case BASS_ERROR_CODEC:
        msg = "codec is not available/supported";
        break;
    case BASS_ERROR_ENDED:
        msg = "the channel/file has ended";
        break;
    case BASS_ERROR_UNKNOWN:
        msg = "some other mystery problem";
        break;
    case BASS_OK:
    default:
        return;
    }

    throw Exception(msg);
}
