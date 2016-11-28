#include <stdio.h>

#include <bass_channel.h>
#include <bass_sample.h>
#include <bass_stream.h>
#include <bass_system.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Usage: basstemp PATH1 PATH2\n\n"
               "    PATH1 - The filename of the first sound file.\n"
               "    PATH2 - The filename of the second sound file.\n");
        return 0;
    }

    // check the correct BASS was loaded
    if ( !BASS::System::MajorVersionMatches() )
    {
        printf("An incorrect version of BASS.DLL was loaded\n");
        return 0;
    }

    BASS::System& sys = BASS::System::Get();
    sys.Init(-1,44100,0,0,NULL);

    BASS::Sample* sam1 = sys.LoadSampleFromFile(argv[1],0,0,3,BASS_SAMPLE_OVER_POS);
    BASS::Stream* sam2 = sys.LoadStreamFromFile(argv[2],0,0,0);

    BASS::Channel* chan1 = sam1->GetChannel(true);
    BASS::Channel* chan2 = sam2;

    chan1->Play();

    int n;
    for (n = 0; n < 300000; ++n)
    {
        printf("%6d", n);
        for (int j = 0; j < 3000; ++j);
        printf("\b\b\b\b\b\b");
    }

    chan2->Play();

    for (; n < 600000; ++n)
    {
        printf("%6d", n);
        for (int j = 0; j < 3000; ++j);
        printf("\b\b\b\b\b\b");
    }

    chan1->Stop();
    delete chan1;
    delete sam1;

    for (; n < 900000; ++n)
    {
        printf("%6d", n);
        for (int j = 0; j < 3000; ++j);
        printf("\b\b\b\b\b\b");
    }

    chan2->Stop();
    delete chan2;

    BASS::System::Free();

    return 0;
}
