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
    cout << "The technology you open will print here." << endl;

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

    // Descriptions written for this project
    // The source for each one is in the comment above it
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
        

        // Vinyl
        // Source: https://blogs.loc.gov/now-see-hear/2019/04/inside-the-archival-box-the-first-long-playing-disc/ 
        "Columbia Records introduced the Vinyl LP\n"
        "in 1948. Before the invention of the LP\n"
        "(\"long playing\" because it plays longer\n"
        "than older records), an album consisted of\n"
        "several discs that could only hold a few \n"
        "minutes of music. Now an entire album could\n"
        "fit on one record, so musicians started to\n"
        "prioritize making full albums rather than\n"
        "singles.\n\n"
        "Abstraction: Many discs became one disc.\n"
        "Sound is still a groove, but squeezed into\n"
        "thinner lines so more music can fit on a\n"
        "single object. The early disc designs were\n"
        "able to hold up to 45 minutes worth of\n"
        "music.",

        // Cassette Tape
        // Sources: https://www.npr.org/2021/03/10/975598869/lou-ottens-inventor-of-the-cassette-tape-has-died
        // https://www.philips.nl/en/a-w/philips-museum/stories/soundtrack-to-peoples-lives.html
        "Lou Ottens and his team at Philips invented\n"
        "the cassette tape in 1963. It gave anyone\n"
        "the ability to not just play music, but\n"
        "record on it too. Anyone could make\n"
        "mixtapes, copy music, or record their own\n"
        "songs at home with no studio or factory\n"
        "needed.\n\n"
        "Abstraction: Instead of grooves you can see,\n"
        "sound is now an invisible magnetic pattern\n"
        "on tape, so you can't see the music anymore.\n"
        "Tapes could be erased and recorded over,\n"
        "making them more versatile than records.",

        // CD
        // Source: https://www.theregister.com/2012/10/01/compact_disc_is_30_years_old/
        "Sony and Philips teamed up in 1979 to build\n"
        "a disc that stores music digitally. The\n"
        "first CDs and CD players were sold in Japan\n"
        "in 1982. The CD turned music into computer\n"
        "data that reads as 1s and 0s. Because music\n"
        "was now numbers instead of a physical copy,\n"
        "it could be perfectly copied and read by\n"
        "computers, which opened the door to\n"
        "digital music.\n\n"
        "Abstraction: Grooves and magnetic patterns\n"
        "stored copies of sound waves. A CD only\n"
        "describes the wave using numbers, which\n"
        "requires a machine to turn them into sound.\n"
        "Therefore, real music is replaced by a\n"
        "description of it in the form of numbers.",

        // MP3
        // Sources: https://www.mp3-history.com/en/whatismp3.html
        // https://heise.de/-10485563
        "The MP3 was invented by Karlheinz\n"
        "Brandenburg and his team of researchers at\n"
        "the Fraunhofer Institute in Germany in\n"
        "1995. Songs were compressed to about 10% of\n"
        "their original size, which made it small\n"
        "enough to be able to download and share\n"
        "online. You could now carry thousands of\n"
        "songs just on a small MP3 player.\n\n"
        "Abstraction: The CD turned music into\n"
        "numbers, and the MP3 compressed those\n"
        "numbers by deleting what we wouldn't notice.\n"
        "The trade-off for convenience is that we\n"
        "lose quality of the sound and the full song\n"
        "for mass storage of music.",
        
        // Spotify
        // Sources: https://www.ebsco.com/research-starters/business-and-management/spotify-company
        // https://lex.dk/Spotify
        "Spotify was founded by Daniel Ek and Martin\n"
        "Lorentzon in Stockholm, Sweden, in 2006.\n"
        "Spotify is a music streaming service where\n"
        "the music lives on Spotify's computers\n"
        "instead of yours. It is streamed to you with\n"
        "the requirement of having a subscription or\n"
        "watching ads.\n\n"
        "Abstraction: Instead of owning music like\n"
        "you did with CDs or records or even MP3\n"
        "files, now you own nothing. Millions of\n"
        "songs are available and can be played\n"
        "anywhere at an instant, but in exchange for\n"
        "convenience, music became a service we rent\n"
        "rather than something we own.",

        // AI Music
        // Sources: https://www.technologyreview.com/2024/06/27/1094379/ai-music-suno-udio-lawsuit-record-labels-youtube-licensing/
        // https://www.nbcnews.com/tech/tech-news/us-record-labels-are-suing-ai-music-generators-alleging-copyright-infr-rcna158660
        "Suno and Udio released AI music generators\n"
        "that became popular in 2024, where you can\n"
        "create full songs with vocals from a short\n"
        "text prompt in seconds. The AI was trained\n"
        "on music that was created by people. That\n"
        "same year, major record labels sued both\n"
        "companies for using their music without\n"
        "permission.\n\n"
        "Abstraction: Every earlier technology\n"
        "started with a real person performing. Now\n"
        "no performer is needed at all. Sound is\n"
        "generated from patterns in data, making\n"
        "music easier to create than ever, but at\n"
        "the cost of identity and originality."
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
                    cout << techs[i].GetDesc() << endl;
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