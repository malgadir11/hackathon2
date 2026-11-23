#pragma
#include <string>
#include "raylib.h"
using namespace std;

class MusicTech{

    public:
        void SetName(string nameInp);
        void SetInventYr(int yearInp);
        void SetDesc(string descInp);
        void SetImage(Texture2D picInp);
        void SetSound(Sound soundInp);

        string GetName();
        int GetInventYr();
        string GetDesc();
        Texture2D GetImage();
        Sound GetSound();


    private:
        string name;
        int inventYr;
        string desc;
        Texture2D image;
        Sound sound;


};