// ********************************************************************************
// Defines the functions that were declared in MusicTech.h
// Each setter stores a value in the tech object's private variables, and then
// each getter returns that value so that main.cpp can use it
// 
// Main.cpp can only reach the variables through these functions, since
// they are private.
// 
// We built our setters and getters using the ideas from Zybooks Week 11 Reading 
// Based on Chapter 7 Objects and Classes
// ********************************************************************************


#include "MusicTech.h"

// Setters:
// These are the setters that take an input and stores it in 
// that specific tech object

// Stores the tech's name
void MusicTech::SetName(string nameInput){
    name = nameInput;
}

// Stores the year that the tech was introduced
void MusicTech::SetInventYr(int yearInput){
    inventYr = yearInput;
}

// Stores the description of the tech
void MusicTech::SetDesc(string descInput){
    desc = descInput;
}

// Stores the tech's picture. Texture2D is created in main.cpp w/ LoadTexture()
// then it passes here.
// Source: https://github.com/raysan5/raylib/blob/master/examples/textures/textures_logo_raylib.c
void MusicTech::SetImage(Texture2D picInput){
    image = picInput;
}

// Getters:
// These are the getters that returns the value stored in the tech object's
// private variable

// Returns the name that is used to draw the timeline box, and the pop-up window title
string MusicTech::GetName(){
    return name;
}

// Returns the year that is used under the name on the timeline box
int MusicTech::GetInventYr(){
    return inventYr;
}

// Returns the description, that is drawn in the pop-up window with DrawText()
// DrawText() is defined in raylib's rtext.c
// Source: https://github.com/raysan5/raylib/blob/master/src/rtext.c
string MusicTech::GetDesc(){
    return desc;
}
// Returns the picture. It is drawn in the pop-up window using DrawTexturePro()
// Source: https://github.com/raysan5/raylib/blob/master/examples/textures/textures_srcrec_dstrec.c
Texture2D MusicTech::GetImage(){
    return image;
}

