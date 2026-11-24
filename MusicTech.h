// ***********************************************************************************
// Declares the MusicTech class that holds data for each technology on the timeline.
// For each technology, MusicTech stores the name, year, description, and image.
// 
// The MusicTech class is an abstraction, as main.cpp uses only set/get functions
// and never needs to know how the data is stored inside the class.
// 
// We built our class structure using the ideas from Zybooks Week 11 Reading
// Based on Chapter 7 Objects and Classes
// We kept this class data-only to keep it simple and matches what we learned in
// Chapter 7. All drawing happens in main.cpp.
// ***********************************************************************************
#include <string>
#include "raylib.h"
using namespace std;

class MusicTech{

    public:
        // Setters that store values for each object
        void SetName(string nameInput);     // Stores name for tech ex. "Phonograph"
        void SetInventYr(int yearInput);    // Stores year ex. "1877"
        void SetDesc(string descInput);     // Stores description for tech
        
        // Stores the tech's picture. The picture is loaded in main.cpp using 
        // LoadTexture(). All images load once after startup, after InitWindow(),
        // because raylib won't load the textures until the window exists.
    
        void SetImage(Texture2D picInput);

        // Getters

        string GetName();
        int GetInventYr();
        string GetDesc();
        Texture2D GetImage();       // used by DrawTexturePro() in main.cpp



    private:
        string name;        // tech name
        int inventYr;       // year introduced
        string desc;        // desc shown in popup
        Texture2D image;    // Raylib texture: gives info about image and its width/height
                            // Source: raylib cheatsheet, for Texture2D structure
                            // https://www.raylib.com/cheatsheet/cheatsheet.html


};

// For Texture2D
// Source: https://github.com/raysan5/raylib/blob/master/src/raylib.h
// For LoadTexture() and InitWindow()
// Source: https://github.com/raysan5/raylib/blob/master/examples/textures/textures_logo_raylib.c
