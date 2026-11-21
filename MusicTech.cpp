#include "MusicTech.h"

void MusicTech::SetName(string nameInp){
    name = nameInp;
}

void MusicTech::SetInventYr(int yearInp){
    inventYr = yearInp;
}

void MusicTech::SetDesc(string descInp){
    desc = descInp;
}

void MusicTech::SetImage(Texture2D picInp){
    image = picInp;
}

void MusicTech::SetSound(Sound soundInp){
    sound = soundInp;
}

string MusicTech::GetName(){
    return name;
}

int MusicTech::GetInventYr(){
    return inventYr;
}

string MusicTech::GetDesc(){
    return desc;
}

Texture2D MusicTech::GetImage(){
    return image;
}

Sound MusicTech::GetSound(){
    return sound;
}