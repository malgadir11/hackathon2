// *********************************************************************************************************
// Made by Mohamed Algadir and Son Le
// main.cpp
// The Development of Music Technology
//
// This is an interactive timeline of music technology. Each technology is a box on a rising
// line that goes from "physical" to "more abstract". Physical could be interpreted as how much music
// is seen or how much of it a person owns. "More abstract" can be interpreted as how the physical means
// of music has disappeared.
// 
// Technologies and eras taken from the "Communication devices" section of
// Crawford & Joler, Calculating Empires (2023), Source: https://calculatingempires.net
// 
// raylib 5.5 resources we built this from:
// core_basic_window, core_input_mouse, shapes_basic_shapes, textures_logo_raylib, textures_srcrec_dstrec
// https://www.raylib.com/examples.html
// Functions cheatsheet that we used to find how different functions in the library worked
// https://www.raylib.com/cheatsheet/cheatsheet.html
// 
// Zybooks chapters 1-7 helped with writing necessary vectors, for loops, if/else branches, as well as classes
// Used Claude AI for suggestions as to what functions from the cheat sheet could be used that is relevant
// to our goal. As well as for errors that we didn't understand when working with the raylib functions.
// We used it as well for the pop-up drawing codem n, but made sure to understand every part of it
// ********************************************************************************************************

#include "raylib.h"
#include "MusicTech.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // Intro
    // Explains how to use the the app 
    cout << "=== The Development of Music Technology ===" << endl;
    cout << "Click a technology in the window to learn about it." << endl;
    cout << "The technology you open will print here." << endl;

    // Window setup for app, creates screen dimensions with a familiar resolution (from fps games)
    // And runs the app at 60 frames per second
    // Source: https://github.com/raysan5/raylib/blob/master/examples/core/core_basic_window.c
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "The Development of Music Technology");
    SetTargetFPS(60);
    // Increases the spacing between the lines just to make it more readable
    // Source: raylib cheat sheet, SetTextLineSpacing()
    SetTextLineSpacing(6);

    // Data for each technology
    // Vector that contains all the names of each tech, the index starts from 0 up to 6
    vector<string> names = { "Phonograph", "Vinyl LP", "Cassette Tape", "CD",
                             "MP3", "Spotify", "AI Music" };
    // Vector that contains all the years of each tech aligned with the name from index 0 to 6
    vector<int> years = { 1877, 1948, 1963, 1982, 1995, 2006, 2024 };
    
    // Image sources:
    // phonograph.png: https://svensktvisarkiv.se/en/sami-voices/phonograph-the-first-recording-technology/
    // vinyl.png:      https://en.wikipedia.org/wiki/LP_record
    // cassette.png:   https://clivethompson.medium.com/the-empowering-style-of-cassette-tapes-e3a620590d42
    // cd.png:         https://www.britannica.com/technology/compact-disc
    // mp3.png:        https://www.britannica.com/technology/iPod
    // spotify.png:    https://www.spotify.com/us/download/windows/
    // ai.png:         https://limelight-arts.com.au/features/the-explainer-generative-ai-music-and-you/
    //                 https://www.logo.dev/search/brands/suno.com
    // The image file names that correlate to the names in the resources folder. The resource folder
    // contains all the png images that are named to match these names
    vector<string> files = { "phonograph", "vinyl", "cassette", "cd",
                             "mp3", "spotify", "ai" };

    // Descriptions written for this project
    // Text uses raylib's built-in default font
    // Source: https://github.com/raysan5/raylib/blob/master/src/rtext.c
    // The source for each one is in the comment above it
    // Raylib's DrawText() doesn't auto-wrap the text to fit the pop-up screen.
    // So we made each line to have a max of 44 characters and then we used "\n" to start a new line
    // This is one big vector that matches the description to the correct index
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


    // Musitech Object 
    // Loops through all the technology and fills it with the setters and 
    // adds it to the techs vector
    // Textures can only load after InitWindow()
    // Source: raylib example "textures_logo_raylib"
    // https://github.com/raysan5/raylib/blob/master/examples/textures/textures_logo_raylib.c
    vector<MusicTech> techs;
    for (int i = 0; i < static_cast<int>(names.size()); i++) {
        MusicTech tech;
        tech.SetName(names.at(i));
        tech.SetInventYr(years.at(i));
        tech.SetDesc(descs.at(i));
    // This loads the image from the resources folder by taking each name from the files vector 
    // then finding the image that correlates to the tech
        tech.SetImage(LoadTexture(("resources/" + files.at(i) + ".png").c_str()));
        techs.push_back(tech);
    }

    // Drawing lines and boxes
    // Vector2 is raylib's x, y point type. Y=0 is the top and increases at it descends
    // Source: raylib cheat sheet, Vector2
    Vector2 lineStart;          // bottom-left end of the rising line
    lineStart.x = 80;
    lineStart.y = 640;

    Vector2 lineEnd;            // top-right end of the rising line
    lineEnd.x = 1200;
    lineEnd.y = 200;

    // Same size for every button: 150 x 50 pixels
    
    const float boxWidth = 150;
    const float boxHeight = 50;

    // Both vectors start empty and get filled by the loop below,
    // one point and one box for each technology
    vector<Vector2> connectPoints;   // the point on the line where each box connects
    vector<Rectangle> techBoxes;     // each box's position and size, used for clicking

       // Places the 7 boxes evenly along the rising line.
    // fraction is how far along the line each box is (0 = start, 1 = end).
    // Adding 0.5 centers each box in its own section of the line.
    // x and y then move that fraction of the way from lineStart to lineEnd.
    for (int i = 0; i < static_cast<int>(techs.size()); i++) {
        float fraction = (i + 0.5f) / static_cast<float>(techs.size());
        float x = lineStart.x + fraction * (lineEnd.x - lineStart.x);
        float y = lineStart.y + fraction * (lineEnd.y - lineStart.y);

    // The point on the line where this box connects
    Vector2 point;
    point.x = x;
    point.y = y;
    connectPoints.push_back(point);

    // Even boxes go above the line and odd boxes go below it, so the boxes
    // sit nicely. i % 2 gives the remainder of i / 2:
    // 0 for even numbers, 1 for odd numbers.
    // Both positions leave a 50 pixel gap between the box and the line:
    // above = y - 100 (which is 50 gap + 50 box height), below = y + 50 (50 gap).
    // Source: zyBooks modulo operator 
    float boxTop;
    if (i % 2 == 0) {
            boxTop = y - 100;   // above the line
    } else {
            boxTop = y + 50;    // below the line
    }

    // The box itself, centered on the point (x - half the box width)
    // Source: raylib cheat sheet, Rectangle
    Rectangle box;
    box.x = x - boxWidth / 2;
    box.y = boxTop;
    box.width = boxWidth;
    box.height = boxHeight;
    techBoxes.push_back(box);
    }
    
    // Pop-up layout
    // A 900 x 500 box in the middle of the screen, with the X button in the
    // top right corner and a 300 x 300 space for the image on the left
    // Pop-up: a 900 x 500 box centered in the window
    Rectangle popupBox;
    popupBox.x = 190;
    popupBox.y = 110;
    popupBox.width = 900;
    popupBox.height = 500;

    // X button: 35 x 35, in the top right corner of the pop-up
    Rectangle closeButton;
    closeButton.x = popupBox.x + popupBox.width - 50;
    closeButton.y = popupBox.y + 15;
    closeButton.width = 35;
    closeButton.height = 35;

    // Image area: 300 x 300, on the left side of the pop-up below the title
    Rectangle imageArea;
    imageArea.x = popupBox.x + 30;
    imageArea.y = popupBox.y + 80;
    imageArea.width = 300;
    imageArea.height = 300;

    int selected = -1;   // which tech's pop-up is open, -1 means none are open

    // Main loop
    // Runs 60 times a second until the window is closed (b/c we set the fps to 60). Each time, it checks
    // the mouse first (update), then it redraws everything on screen
    // Source: https://github.com/raysan5/raylib/blob/master/examples/core/core_basic_window.c
    while (!WindowShouldClose()) {
    // Where the mouse is and whether the left button was just clicked
    // Source: https://github.com/raysan5/raylib/blob/master/examples/core/core_input_mouse.c
    Vector2 mousePos = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    
    if (selected == -1) {
    // No pop-up open, so check if a box was clicked.
    // CheckCollisionPointRec() is true when the mouse is inside the box.
    // Source: raylib cheat sheet, CheckCollisionPointRec()
    // Keeps checking boxes until one is clicked.
    // Once selected changes from -1, the loop condition becomes false and the loop ends.
        for (int i = 0; i < static_cast<int>(techBoxes.size()) && selected == -1; i++) {
            if (clicked && CheckCollisionPointRec(mousePos, techBoxes.at(i))) {
                selected = i;
                // Prints the tech's name, year, and description in the terminal
                cout << endl << "--- " << techs.at(i).GetName() << " (" << techs.at(i).GetInventYr() << ") ---" << endl;
                cout << techs.at(i).GetDesc() << endl;
                }
            }
        } else {
    // A pop-up is open, so close it if the X was clicked
        if (clicked && CheckCollisionPointRec(mousePos, closeButton)) {
                selected = -1;
            }
        }

    // Draw
    // Everything gets redrawn from scratch every frame
    BeginDrawing();
    ClearBackground(Color{ 20, 20, 30, 255 });   // dark blue-gray background

    // Title and instructions at the top
    DrawText("The Development of Music Technology", 60, 40, 40, RAYWHITE);
    DrawText("Click a technology to learn more", 60, 90, 20, GRAY);

    // The rising line set to 4 pixels thick and its labels
    // Source: https://github.com/raysan5/raylib/blob/master/examples/shapes/shapes_basic_shapes.c
    DrawLineEx(lineStart, lineEnd, 4, GRAY);
    DrawText("physical", 70, 655, 20, GRAY);
    DrawText("more abstract", 1110, 240, 20, GRAY);

    // Connectors: a short line from each box down or up to the main line,
    // with a small dot where they meet
    // Connectors: a short line from each box down or up to the main line,
    // with a small dot where they meet
    for (int i = 0; i < static_cast<int>(techBoxes.size()); i++) {
            Vector2 edgePoint;
            edgePoint.x = connectPoints.at(i).x;
            if (i % 2 == 0) {
                edgePoint.y = techBoxes.at(i).y + boxHeight;   // bottom edge of a box above the line
            } else {
                edgePoint.y = techBoxes.at(i).y;               // top edge of a box below the line
            }
            DrawLineEx(edgePoint, connectPoints.at(i), 2, DARKGRAY);
            DrawCircleV(connectPoints.at(i), 6, LIGHTGRAY);
        }

    // Boxes: white normally, gold when the mouse hovers over them
    // (only when no pop-up is open)
    for (int i = 0; i < static_cast<int>(techBoxes.size()); i++) {
        bool isHovered = (selected == -1) && CheckCollisionPointRec(mousePos, techBoxes.at(i));

    Color boxColor;
        if (isHovered) {
            boxColor = GOLD;
        } else {
            boxColor = RAYWHITE;
        }
        DrawRectangleRec(techBoxes.at(i), boxColor);
        DrawRectangleLinesEx(techBoxes.at(i), 2, DARKGRAY);   // box outline

    // Centers the name and year inside each box.
    // MeasureText() gives the text's width in pixels, so
    // (box width - text width) / 2 is where the text should start.
    // Source: raylib cheat sheet, MeasureText()
        string name = techs.at(i).GetName();
        string year = to_string(techs.at(i).GetInventYr());   // turns the int into a string
        int nameW = MeasureText(name.c_str(), 18);
        int yearW = MeasureText(year.c_str(), 16);
        DrawText(name.c_str(), techBoxes.at(i).x + (boxWidth - nameW) / 2, techBoxes.at(i).y + 8, 18, BLACK);
        DrawText(year.c_str(), techBoxes.at(i).x + (boxWidth - yearW) / 2, techBoxes.at(i).y + 29, 16, DARKGRAY);
        }

    // Pop-up, drawn last so it shows on top of everything
        if (selected != -1) {
            MusicTech currentTech = techs.at(selected);

    // Darkens the timeline behind the pop-up.
    // Fade() makes a color see-through (0.6 = 60% visible).
    // Source: raylib cheat sheet, Fade() and DrawRectangleRounded()
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
        DrawRectangleRounded(popupBox, 0.05f, 8, RAYWHITE);

    // Pop-up title, ex. "Phonograph (1877)"
        string popupTitle = currentTech.GetName() + " (" + to_string(currentTech.GetInventYr()) + ")";
        DrawText(popupTitle.c_str(), popupBox.x + 30, popupBox.y + 25, 32, BLACK);

    // X button: light gray normally, red when hovered
        bool hoverClose = CheckCollisionPointRec(mousePos, closeButton);
        Color closeColor;
        if (hoverClose) {
            closeColor = RED;
        } else {
            closeColor = LIGHTGRAY;
        }
        DrawRectangleRec(closeButton, closeColor);
        DrawText("X", closeButton.x + 11, closeButton.y + 7, 22, BLACK);

    // Draws the tech's image stretched to fit the 300 x 300 space.
    // fullImage is the whole picture, imageArea is where and how big to draw it.
    // If the image didn't load (id is 0), a gray box shows instead.
    // Source: https://github.com/raysan5/raylib/blob/master/examples/textures/textures_srcrec_dstrec.c
    Texture2D picture = currentTech.GetImage();
    if (picture.id > 0) {
    // The whole picture, starting from its top-left corner
        Rectangle fullImage;
        fullImage.x = 0;
        fullImage.y = 0;
        fullImage.width = static_cast<float>(picture.width);
        fullImage.height = static_cast<float>(picture.height);

    // No rotation point offset, so the image isn't shifted
        Vector2 origin;
        origin.x = 0;
        origin.y = 0;

    DrawTexturePro(picture, fullImage, imageArea, origin, 0.0f, WHITE);
    } 
        else {
    DrawRectangleRec(imageArea, LIGHTGRAY);
    DrawText("image missing", imageArea.x + 80, imageArea.y + 140, 20, DARKGRAY);
    }

    // Description, DrawText() starts a new line at every "\n"
    // Source: https://github.com/raysan5/raylib/blob/master/src/rtext.c
    DrawText(currentTech.GetDesc().c_str(), popupBox.x + 360, popupBox.y + 80, 20, DARKGRAY);
    }

        EndDrawing();
    }

    // Clean up: frees every image from memory, then closes the window
    // Source: https://github.com/raysan5/raylib/blob/master/examples/textures/textures_logo_raylib.c
    for (int i = 0; i < static_cast<int>(techs.size()); i++) {
        UnloadTexture(techs.at(i).GetImage());
    }
    CloseWindow();
    return 0;
}

// videos that helped with learning key parts of the building
// "raylibs button tutorial (OOP)" 
// https://www.youtube.com/watch?v=0Ct9ZWEUm7M&list=PLwR6ZGPvjVOTIMqUXnqyWaIfQg0xdHNZn&index=9 
// 
// https://www.youtube.com/watch?v=Yeo_0buZTVc  "Explaining Raylib's DrawRectanglePro() function"
// Source: "Load Textures, Sprite Animations, Image Upscale and More! | Raylib 2D C++ Tutorial #3"
// https://www.youtube.com/watch?v=wKiEA0PVCoE
// https://www.youtube.com/watch?v=weYACOm6d8Y "Drawing Sprites in Raylib"
// sources on github that helped
// https://github.com/raysan5/raylib/wiki/Frequently-Asked-Questions
// https://github.com/educ8s/Intro-To-raylib-Tutorial
