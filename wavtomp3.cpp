#include <stdio.h>
#include <lame/lame.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <dirent.h>
#include <cstddef>

lame_global_flags *lame;
lame = lame_init();


#define NULL 0

using namespace std;

bool has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
}

int main(int argc, char **argv)
{
    int read, write;
    cout << "Directory name: ";
    string path,strOldfile,strNewfile;
    

    getline(cin, path);

    DIR *dir = opendir(path.c_str());
    if(!dir)
    {
        return 1;
    }

    dirent *entry;
    while((entry = readdir(dir))!=NULL) 
    {
        if(has_suffix(entry->d_name, ".wav"))
        {   
            string fName = entry->d_name;
            //cout << entry->d_name << endl;
                int fileLen = (fName).length();
                strOldfile = path + "/" + (fName).substr(0,fileLen - 4) + ".wav";
                strNewfile = path + "/" + (fName).substr(0,fileLen - 4) + ".mp3";
                cout << strOldfile << endl;
                cout << strNewfile << endl;
                const char * oldF = strOldfile.c_str();
                const char * newF = strNewfile.c_str();

                FILE *pcm = fopen(oldF, "rb");
                FILE *mp3 = fopen(newF, "wb");

                const int PCM_SIZE = 8192;
                const int MP3_SIZE = 8192;

                short int pcm_buffer[PCM_SIZE*2];
                unsigned char mp3_buffer[MP3_SIZE];

                //lame_t lame = lame_init();
                lame_set_in_samplerate(lame, 44100);
                //lame_set_VBR(lame, vbr_default);
                lame_init_params(lame);
                
                lame_set_brate(lame,128);
                //lame_set_mode(lame,1);
                lame_set_quality(lame,2);

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



    

    
