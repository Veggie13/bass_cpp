#include "bass_exception.h"
#include "bass_plugin.h"

using namespace BASS;


Plugin::Plugin(char* filename, bool unicodeName)
{
    m_handle = BASS_PluginLoad(
                    filename,
                    unicodeName? BASS_UNICODE:0 );
    BASS_ASSERT(m_handle);
}

Plugin::~Plugin()
{
    BOOL result = BASS_PluginFree(m_handle);
    BASS_ASSERT(result == TRUE);
}

const PluginInfo& Plugin::GetInfo()
{
    const PluginInfo* info = BASS_PluginGetInfo(m_handle);
    BASS_ASSERT(info);
    return *info;
}
