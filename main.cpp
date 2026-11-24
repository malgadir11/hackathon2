// Made by Mohamed Algadir and Son Le

// main.cpp
// The Development of Music Technology
//
// Technologies and eras taken from the "Communication devices" section of
// Crawford & Joler, Calculating Empires (2023), Source: https://calculatingempires.net

#include "raylib.h"
#include "MusicTech.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // ---------- Terminal intro ----------
    cout << "=== The Development of Music Technology ===" << endl;
    cout << "Click a technology in the window to learn about it." << endl;
    cout << "Its source will print here." << endl;

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "The Development of Music Technology");
    SetTargetFPS(60);

    SetTextLineSpacing(6);

    // ---------- Data for each technology ----------
    vector<string> names = { "Phonograph", "Vinyl LP", "Cassette Tape", "CD",
                             "MP3", "Spotify", "AI Music" };

    vector<int> years = { 1877, 1948, 1963, 1982, 1995, 2006, 2024 };

    vector<string> files = { "phonograph", "vinyl", "cassette", "cd",
                             "mp3", "spotify", "ai" };

    // Descriptions written for this project from the sources below
    vector<string> descs = {
        // Phonograph
        // Source: https://www.smithsonianmag.com/arts-culture/phonograph-changed-music-forever-180957677/
        "Thomas Edison invented the Phonograph in\n" 
        "1877. This marks the beginning of an era\n"
        "where music can be recorded once and heard\n"
        "by thousands of people.\n\n"
        "Abstraction: A live performance becomes a\n"
        "groove, a physical copy of sound you can\n"
        "see. The sound of instruments people used\n"
        "to hear in person is now stored as lines\n"
        "and waves on a cylinder.",
        
        

        // Vinyl LP
        "",

        // Cassette Tape
        "",

        // CD
        "",

        // MP3
        "",

        // Spotify
        "",

        // AI Music
        ""
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
    // Textures can only load AFTER InitWindow()
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
            DrawText(tech.GetDesc().c_str(), popup.x + 360, popup.y + 80, 20, DARKGRAY);

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