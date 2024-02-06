#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Screen Dimensions
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

// Shapes for making DVD text
void drawRectangle(float x, float y, float width, float height, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawCircle(float centerX, float centerY, float radius, int segments, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= segments; ++i)
    {
        float theta = static_cast<float>(i) / static_cast<float>(segments) * 2.0f * M_PI;
        float x = radius * cos(theta) + centerX;
        float y = radius * sin(theta) + centerY;
        glVertex2f(x, y);
    }
    glEnd();
}

// Color randomizer
void randomColor(float& r, float& g, float& b)
{
    r = static_cast<float>(rand()) / RAND_MAX;
    g = static_cast<float>(rand()) / RAND_MAX;
    b = static_cast<float>(rand()) / RAND_MAX;
}

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    // 2D Graphics Environment
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initial Position and Speed
    float xPosition = 50.0;
    float yPosition = 50.0;
    float xSpeed = 3.0;
    float ySpeed = 2.0;

    srand(static_cast<unsigned int>(time(NULL)));

    // Initial color
    float r = 1.0, g = 1.0, b = 0.0;

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            // Key caps interaction
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    // Increase speed
                    xSpeed += 1.0;
                    ySpeed += 1.0;
                    break;

                case SDLK_DOWN:
                    // Decrease speed
                    xSpeed -= 1.0;
                    ySpeed -= 1.0;
                    break;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Letter D
        drawRectangle(xPosition + 5, yPosition, 16, 60, r, g, b);
        drawCircle(xPosition + 35, yPosition + 30, 30, 45, r, g, b);
        drawCircle(xPosition + 38, yPosition + 30, 17, 40, 0.0, 0.0, 0.0);

        // Letter V
        drawTriangle(xPosition + 70, yPosition, xPosition + 140, yPosition, xPosition + 105, yPosition + 60, r, g, b);
        drawTriangle(xPosition + 80, yPosition - 10, xPosition + 130, yPosition - 10, xPosition + 105, yPosition + 40, 0.0, 0.0, 0.0);

        // Letter D
        drawRectangle(xPosition + 150, yPosition, 16, 60, r, g, b);
        drawCircle(xPosition + 180, yPosition + 30, 30, 45, r, g, b);
        drawCircle(xPosition + 183, yPosition + 30, 17, 40, 0.0, 0.0, 0.0);

        SDL_GL_SwapBuffers();
        SDL_Delay(10);

        // Adding Movement
        xPosition += xSpeed;
        yPosition += ySpeed;

        // Collision effect
        if (xPosition < 0 || xPosition + 183 > SCREEN_WIDTH - 20)
        {
            // Reverse movement
            xSpeed = -xSpeed;
            // Randomize color
            randomColor(r, g, b);
        }
        if (yPosition < 0 || yPosition + 90 > SCREEN_HEIGHT + 23)
        {
            ySpeed = -ySpeed;
            randomColor(r, g, b);
        }
    }

    SDL_Quit();
    return 0;
}
