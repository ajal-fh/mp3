#include <stdio.h>
#include <lame/lame.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <dirent.h>


using namespace std;

bool has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}

int main(int argc, char **argv)
{
    int read, write;
    cout << "Directory name: ";
    string path;
    getline(cin, path);

    DIR *dir = opendir(path.c_str());
    if(!dir)
    {
        return 1;
    }

    dirent *entry;
    while((entry = readdir(dir))!=null) 
    {
        if(has_suffix(entry->d_name, ".wav"))
        {
            cout << entry->d_name << endl;

                FILE *pcm = fopen(path + /entry->d_name +".wav", "rb");
                FILE *mp3 = fopen(path + /entry->d_name +".mp3", "wb");

                const int PCM_SIZE = 8192;
                const int MP3_SIZE = 8192;

                short int pcm_buffer[PCM_SIZE*2];
                unsigned char mp3_buffer[MP3_SIZE];

                lame_t lame = lame_init();
                lame_set_in_samplerate(lame, 44100);
                lame_set_VBR(lame, vbr_default);
                lame_init_params(lame);

                do {
                    read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
                    if (read == 0)
                        write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
                    else
                        write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
                    fwrite(mp3_buffer, write, 1, mp3);
                } while (read != 0);

                lame_close(lame);
                fclose(mp3);
                fclose(pcm);

                    }
                }

    closedir(dir);
}



    

    
