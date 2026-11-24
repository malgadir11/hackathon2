// main.cpp
// The Development of Music Technology
// An interactive timeline: boxes sit along a rising line (music becoming
// more abstract over time). Click a box to open its pop-up, play its sound,
// and see its source printed in the terminal.
//
// Technologies and eras taken from the "Communication devices" section of
// Crawford & Joler, Calculating Empires (2023): https://calculatingempires.net
//
// raylib examples used: core_basic_window, core_input_mouse,
// textures_logo_raylib, textures_srcrec_dstrec, audio_sound_loading
// https://www.raylib.com/examples.html
// Function reference: https://www.raylib.com/cheatsheet/cheatsheet.html


#include "raylib.h"
#include "MusicTech.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// raylib's DrawText() doesn't wrap lines, so this breaks text into words
// and starts a new line whenever the next word would go past maxWidth.
void DrawWrappedText(string text, int x, int y, int maxWidth, int fontSize, Color color) {
    istringstream words(text);
    string word;
    string line;

    while (words >> word) {
        string test = line.empty() ? word : line + " " + word;
        if (MeasureText(test.c_str(), fontSize) > maxWidth && !line.empty()) {
            DrawText(line.c_str(), x, y, fontSize, color);
            y += fontSize + 6;
            line = word;
        } else {
            line = test;
        }
    }
    if (!line.empty()) {
        DrawText(line.c_str(), x, y, fontSize, color);
    }
}

int main() {
    // ---------- Terminal intro ----------
    cout << "=== The Development of Music Technology ===" << endl;
    cout << "Click a technology in the window to learn about it." << endl;
    cout << "Its source will print here." << endl;

    // ---------- Window + audio setup ----------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "The Development of Music Technology");
    SetTargetFPS(60);

    // ---------- Data for each technology ----------
    vector<string> names = { "Phonograph", "Vinyl LP", "Cassette Tape", "CD",
                             "MP3", "Spotify", "AI Music" };

    vector<int> years = { 1877, 1948, 1963, 1982, 1995, 2006, 2024 };

    // file names for resources/<name>.png and resources/<name>.wav
    vector<string> files = { "phonograph", "vinyl", "cassette", "cd",
                             "mp3", "spotify", "ai" };

    // Descriptions written for this project from the sources below
    vector<string> descs = {
        // Phonograph
        "Thomas Edison's phonograph was the first machine that could record sound and play it back. "
        "A needle carved the sound wave into a groove, so music became a physical shape you could see and touch. "
        "Before it, the only way to hear a song was live. "
        "Abstraction: sound becomes a physical groove.",

        // Vinyl LP
        "Columbia Records introduced the 33 1/3 rpm long-playing record in 1948. "
        "One 12-inch disc held over 20 minutes per side, compared to a few minutes on older 78s, "
        "which made the full album possible. Sound is still a groove, but now mass-produced on cheap vinyl. "
        "Efficient for whom? Labels could now sell whole albums.",

        // Cassette Tape
        "Philips, with a team led by Lou Ottens, introduced the Compact Cassette in 1963. "
        "Sound became an invisible magnetic pattern on tape. It was small, cheap and recordable, "
        "so anyone could copy songs or make a mixtape. Philips licensed it free to other companies, "
        "which made it a world standard. Abstraction: sound becomes a magnetic pattern.",

        // CD
        "Sony and Philips developed the compact disc together, and it went on sale in Japan in 1982. "
        "Music became a list of numbers (44,100 per second) read by a laser: no hiss, no wear, "
        "and perfect copies. But you can no longer see the sound at all. "
        "Abstraction: sound becomes numbers.",

        // MP3
        "Researchers at Germany's Fraunhofer Institute developed MP3 compression and named the "
        ".mp3 file type in 1995. It throws away sounds our ears are unlikely to notice, shrinking "
        "a song to about a tenth of its size. That made music small enough to share online, and file "
        "sharing like Napster followed. Abstraction: compressed numbers, with information lost on purpose.",

        // Spotify
        "Spotify was founded in Sweden in 2006 and launched in 2008. Instead of owning music, "
        "listeners pay for access to a library stored on company servers. Artists are paid from a share "
        "of revenue based on their share of all streams, not per sale. The app also tracks what you "
        "play and skip. Abstraction: music becomes a link to someone else's server.",

        // AI Music
        "Tools like Suno and Udio generate whole songs, including vocals, from a text prompt in seconds. "
        "In 2024, major record labels sued both companies, claiming they trained on copyrighted "
        "recordings without permission or payment. No performer is needed at all. "
        "Abstraction: sound generated from patterns in data. Efficient for whom?"
    };

    vector<string> sources = {
        "Smithsonian Magazine, How the Phonograph Changed Music Forever: smithsonianmag.com/arts-culture/phonograph-changed-music-forever-180957677",
        "Library of Congress, The First Long-Playing Disc: blogs.loc.gov/now-see-hear/2019/04/inside-the-archival-box-the-first-long-playing-disc",
        "Philips Museum, Soundtrack to People's Lives: philips.nl/en/a-w/philips-museum/stories/soundtrack-to-peoples-lives.html",
        "The Register, Happy Birthday Compact Disc (2012): theregister.com/2012/10/01/compact_disc_is_30_years_old",
        "Fraunhofer IIS, The mp3 History: mp3-history.com/en/whatismp3.html; heise, 30 Years of MP3: heise.de/-10485563",
        "EBSCO, Spotify (company): ebsco.com/research-starters/business-and-management/spotify-company",
        "NBC News, Record labels sue AI music generators (2024): nbcnews.com/tech/tech-news/us-record-labels-are-suing-ai-music-generators-alleging-copyright-infr-rcna158660"
    };

    // ---------- Build the MusicTech objects ----------
    // Textures and sounds can only load AFTER InitWindow() and InitAudioDevice()
    vector<MusicTech> techs;
    for (int i = 0; i < (int)names.size(); i++) {
        MusicTech tech;
        tech.SetName(names[i]);
        tech.SetInventYr(years[i]);
        tech.SetDesc(descs[i]);
        tech.SetImage(LoadTexture(("resources/" + files[i] + ".png").c_str()));
        techs.push_back(tech);
    }

    // ---------- Layout: rising line with boxes above and below ----------
    Vector2 lineStart = { 80, 640 };    // bottom-left
    Vector2 lineEnd   = { 1200, 200 };  // top-right

    const float boxW = 150;
    const float boxH = 50;
    vector<Vector2> linePoints;   // where each box connects to the line
    vector<Rectangle> boxes;      // each box's clickable area

    for (int i = 0; i < (int)techs.size(); i++) {
        float t = (i + 0.5f) / techs.size();    // 0 = start of line, 1 = end
        float x = lineStart.x + t * (lineEnd.x - lineStart.x);
        float y = lineStart.y + t * (lineEnd.y - lineStart.y);
        linePoints.push_back(Vector2{ x, y });

        float boxY;
        if (i % 2 == 0) {
            boxY = y - 100;   // above the line
        } else {
            boxY = y + 50;    // below the line
        }
        boxes.push_back(Rectangle{ x - boxW / 2, boxY, boxW, boxH });
    }

    // ---------- Pop-up layout ----------
    Rectangle popup    = { 190, 110, 900, 500 };
    Rectangle closeBtn = { popup.x + popup.width - 50, popup.y + 15, 35, 35 };
    Rectangle imgArea  = { popup.x + 30, popup.y + 80, 300, 300 };

    int selected = -1;   // index of the open pop-up, -1 means none

    // ---------- Main loop ----------
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // ----- Update -----
        if (selected == -1) {
            for (int i = 0; i < (int)boxes.size(); i++) {
                if (clicked && CheckCollisionPointRec(mouse, boxes[i])) {
                    selected = i;
                    cout << endl << "--- " << techs[i].GetName()
                         << " (" << techs[i].GetInventYr() << ") ---" << endl;
                    cout << "Source: " << sources[i] << endl;
                    break;
                }
            }
        } else {
            if (clicked && CheckCollisionPointRec(mouse, closeBtn)) {
                selected = -1;
            } 
        }

        // ----- Draw -----
        BeginDrawing();
        ClearBackground(Color{ 20, 20, 30, 255 });

        // Title
        DrawText("The Development of Music Technology", 60, 40, 40, RAYWHITE);
        DrawText("Click a technology to learn more", 60, 90, 20, GRAY);

        // Rising line
        DrawLineEx(lineStart, lineEnd, 4, GRAY);
        // Label the meaning of the line: physical sound -> abstract data
        DrawText("physical", 70, 655, 20, GRAY);
        DrawText("more abstract", 1110, 240, 20, GRAY);

        // Connectors from each box to the line
        for (int i = 0; i < (int)boxes.size(); i++) {
            Vector2 boxEdge;
            boxEdge.x = linePoints[i].x;
            if (i % 2 == 0) {
                boxEdge.y = boxes[i].y + boxH;   // bottom of an above-line box
            } else {
                boxEdge.y = boxes[i].y;          // top of a below-line box
            }
            DrawLineEx(boxEdge, linePoints[i], 2, DARKGRAY);
            DrawCircleV(linePoints[i], 6, LIGHTGRAY);
        }

        // Boxes (highlight when hovered)
        for (int i = 0; i < (int)boxes.size(); i++) {
            bool hovered = (selected == -1) && CheckCollisionPointRec(mouse, boxes[i]);
            DrawRectangleRec(boxes[i], hovered ? GOLD : RAYWHITE);
            DrawRectangleLinesEx(boxes[i], 2, DARKGRAY);

            string name = techs[i].GetName();
            string year = to_string(techs[i].GetInventYr());
            int nameW = MeasureText(name.c_str(), 18);
            int yearW = MeasureText(year.c_str(), 16);
            DrawText(name.c_str(), boxes[i].x + (boxW - nameW) / 2, boxes[i].y + 8, 18, BLACK);
            DrawText(year.c_str(), boxes[i].x + (boxW - yearW) / 2, boxes[i].y + 29, 16, DARKGRAY);
        }

        // Pop-up (drawn last so it's on top)
        if (selected != -1) {
            MusicTech tech = techs[selected];

            // Dim the background
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
            DrawRectangleRounded(popup, 0.05f, 8, RAYWHITE);

            // Title
            string title = tech.GetName() + " (" + to_string(tech.GetInventYr()) + ")";
            DrawText(title.c_str(), popup.x + 30, popup.y + 25, 32, BLACK);

            // Close button
            bool overClose = CheckCollisionPointRec(mouse, closeBtn);
            DrawRectangleRec(closeBtn, overClose ? RED : LIGHTGRAY);
            DrawText("X", closeBtn.x + 11, closeBtn.y + 7, 22, BLACK);

            // Image, stretched to fit the image area
            Texture2D img = tech.GetImage();
            if (img.id > 0) {
                Rectangle source = { 0, 0, (float)img.width, (float)img.height };
                DrawTexturePro(img, source, imgArea, Vector2{ 0, 0 }, 0.0f, WHITE);
            } else {
                DrawRectangleRec(imgArea, LIGHTGRAY);
                DrawText("image missing", imgArea.x + 80, imgArea.y + 140, 20, DARKGRAY);
            }

            // Description
            DrawWrappedText(tech.GetDesc(), popup.x + 360, popup.y + 80, 510, 20, DARKGRAY);

        }

        EndDrawing();
    }
    // ---------- Clean up ----------
    for (int i = 0; i < (int)techs.size(); i++) {
        UnloadTexture(techs[i].GetImage());
    }
    CloseWindow();
    return 0;
}