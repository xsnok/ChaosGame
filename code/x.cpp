// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    srand(static_cast<unsigned>(time(0))); // seed random

    // =============================
    // 1️⃣ FONT SETUP — move OUTSIDE the loop
    // =============================
    Font font;
    if (!font.loadFromFile("arial.ttf"))  // ensure this file is in same folder as your .exe
    {
        cout << "ERROR: Font not found!" << endl;
    }

    // =============================
    // 2️⃣ TEXT SETUP — move OUTSIDE the loop
    // =============================
    Text text;
    text.setFont(font);               // set font
    text.setString("Chaos Game!!");   // text to display
    text.setCharacterSize(48);        // in pixels
    text.setFillColor(Color::White);  // text color
    text.setStyle(Text::Bold | Text::Underlined); // optional style
    text.setPosition(20, 20);         // screen position

    while (window.isOpen())
    {
        // =============================
        // Handle the player's input
        // =============================
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "Left button pressed" << endl;
                    cout << "Mouse x: " << event.mouseButton.x << endl;
                    cout << "Mouse y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // =============================
        // Update points
        // =============================
        if (points.size() > 0)
        {
            int vNum = rand() % 3;
            float newX = (vertices[vNum].x + points.back().x) / 2.f;
            float newY = (vertices[vNum].y + points.back().y) / 2.f;
            points.push_back(Vector2f(newX, newY));
        }

        // =============================
        // Draw everything
        // =============================
        window.clear();

        // draw vertices
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(vertices[i]);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // draw points
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape pointRect(Vector2f(2, 2)); // smaller for fractal
            pointRect.setPosition(points[i]);
            pointRect.setFillColor(Color::White);
            window.draw(pointRect);
        }

        // =============================
        // draw the text
        // =============================
        window.draw(text);

        // display frame
        window.display();
    }
}
