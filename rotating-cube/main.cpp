#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

float squareX = 0.0f;
float squareY = 0.0f;
float squareSize = 0.5f;
float rotationAngle = 0.0f;

void handleInput(SDL_Event &event)
{
    const float rotationSpeed = 5.0f;
    const float movementSpeed = 0.1f;

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            rotationAngle -= rotationSpeed;
            break;
        case SDLK_RIGHT:
            rotationAngle += rotationSpeed;
            break;
        case SDLK_UP:
            squareX += movementSpeed * cos(rotationAngle * M_PI / 180.0f);
            squareY += movementSpeed * sin(rotationAngle * M_PI / 180.0f);
            break;
        }
        break;
    }
}

void drawSquare()
{
    glBegin(GL_QUADS);
    glVertex3f(-squareSize / 2, -squareSize / 2, 0.0f);
    glVertex3f(squareSize / 2, -squareSize / 2, 0.0f);
    glVertex3f(squareSize / 2, squareSize / 2, 0.0f);
    glVertex3f(-squareSize / 2, squareSize / 2, 0.0f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(squareX, squareY, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    glColor3ub(173, 216, 230);
    drawSquare();

    SDL_GL_SwapBuffers();
}

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    bool isRunning = true;
    SDL_Event event;

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            handleInput(event);
        }

        display();
    }

    SDL_Quit();
    return 0;
}
