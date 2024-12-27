#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1200, 1000), "Bouncing Ball");
    window.setFramerateLimit(100);

    CircleShape ball(50.f); //Create a circle shape for the ball
    ball.setFillColor(Color::Blue);// Set the initial color of the ball to blue
    ball.setPosition(window.getSize().x / 2 - ball.getRadius(), window.getSize().y / 2 - ball.getRadius()); //Position the ball at the center of the window

    float ballSpeedX = 5.f;  //Set the initial speed of the ball in the X direction
    float ballSpeedY = 2.f; //Set the initial speed of the ball in the Y direction

    int bounceCount = 0; //Counter to keep track of the number of bounces
    bool changeBackground = true; //Flag to indicate if the background needs to be changed
    Color backgroundColor = Color::Cyan; //Set the initial background color to cyan

    Font font;
    if (!font.loadFromFile("C:\\Users\\ASUS\\source\\repos\\test ball2\\Project1\\fonts\\Arial.ttf")) { //Load the font from file
        cout << "Failed to load font!" << endl;
        return -1;
    }

    Text bounceText;
    bounceText.setFont(font);
    bounceText.setCharacterSize(24);
    bounceText.setFillColor(Color::Black);
    bounceText.setPosition(10.f, 10.f);

    Text colorText;
    colorText.setFont(font);
    colorText.setCharacterSize(24);
    colorText.setFillColor(Color::Black);
    colorText.setPosition(10.f, 40.f);

    Texture texture1, texture2, texture3;
    if (!texture1.loadFromFile("C:\\Users\\ASUS\\Downloads\\images sfml\\bonk.png") || //Load the background textures from file
        !texture2.loadFromFile("\\Users\\ASUS\\Downloads\\images sfml\\huh.png") ||
        !texture3.loadFromFile("\\Users\\ASUS\\Downloads\\images sfml\\shy.png")) {
        cout << "Failed to load background image!" << endl;
        return -1;
    }

    Sprite background;
    background.setTexture(texture1); //Set the initial background texture

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        ball.move(ballSpeedX, ballSpeedY); //Move the ball based on its current speed

        if (ball.getPosition().x + ball.getRadius() > window.getSize().x) //Check right edge collision
        {
            ball.setPosition(window.getSize().x - ball.getRadius(), ball.getPosition().y); //Place the ball at the right edge
            ballSpeedX = -ballSpeedX; //Reverse the X speed to bounce the ball back
            changeBackground = true; //Set the flag to change the background

            ++bounceCount; //Increment the bounce counter
        }
        else if (ball.getPosition().x - ball.getRadius() < 0) //Check left edge collision
        {
            ball.setPosition(ball.getRadius(), ball.getPosition().y); //Place the ball at the left edge
            ballSpeedX = -ballSpeedX; //Reverse the X speed to bounce the ball back
            changeBackground = true; //Set the flag to change the background

            ++bounceCount; //Increment the bounce counter
        }

        if (ball.getPosition().y + ball.getRadius() > window.getSize().y) //Check bottom edge collision
        {
            ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius()); //Place the ball at the bottom edge
            ballSpeedY = -ballSpeedY; //Reverse the Y speed to bounce the ball back
            changeBackground = true; //Set the flag to change the background

            ++bounceCount; //Increment the bounce counter
        }
        else if (ball.getPosition().y - ball.getRadius() < 0) //Check top edge collision
        {
            ball.setPosition(ball.getPosition().x, ball.getRadius()); //Place the ball at the top edge
            ballSpeedY = -ballSpeedY; //Reverse the Y speed to bounce the ball back
            changeBackground = true; //Set the flag to change the background

            ++bounceCount; //Increment the bounce counter
        }

        if (changeBackground)
        {
            if (backgroundColor == Color::Cyan)
                backgroundColor = Color::White;
            else if (backgroundColor == Color::White)
                backgroundColor = Color::Magenta;
            else if (backgroundColor == Color::Magenta)
                backgroundColor = Color::Red;
            else
                backgroundColor = Color::Cyan;

            if (ball.getFillColor() == Color::Blue)
                ball.setFillColor(Color::Red);
            else if (ball.getFillColor() == Color::Red)
                ball.setFillColor(Color::Yellow);
            else if (ball.getFillColor() == Color::Yellow)
                ball.setFillColor(Color::Green);
            else if (ball.getFillColor() == Color::Green)
                ball.setFillColor(Color::Black);
            else if (ball.getFillColor() == Color::Black)
                ball.setFillColor(Color::Blue);

            if (bounceCount % 3 == 0)
                background.setTexture(texture1);
            else if (bounceCount % 3 == 1)
                background.setTexture(texture2);
            else if (bounceCount % 3 == 2)
                background.setTexture(texture3);

            changeBackground = false; //Reset the flag to indicate that the background has been changed
        }

        ostringstream oss;
        oss << "Ball Bounced: " << bounceCount << " times";
        bounceText.setString(oss.str());

        string colorString;
        if (ball.getFillColor() == Color::Blue)
            colorString = "Color of Ball is: Blue";
        else if (ball.getFillColor() == Color::Red)
            colorString = "Color of Ball is: Red";
        else if (ball.getFillColor() == Color::Yellow)
            colorString = "Color of Ball is: Yellow";
        else if (ball.getFillColor() == Color::Green)
            colorString = "Color of Ball is: Green";
        else if (ball.getFillColor() == Color::Black)
            colorString = "Color of Ball is: Black";
        colorText.setString(colorString);

        window.clear(backgroundColor);
        window.draw(background);
        window.draw(ball);
        window.draw(bounceText);
        window.draw(colorText);
        window.display();

        if (bounceCount >= 20) //Exit the loop after a certain number of bounces
            break;
    }

    return 0;
}
