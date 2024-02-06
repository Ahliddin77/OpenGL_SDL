#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

float rotationX = 30.0f;
float rotationY = 60.0f;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0/480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    float leftX = -1.0f;
    float rightX = 1.0f;
    float bottomY = -1.0f;
    float topY = 1.0f;
    float frontZ = 1.0f;
    float backZ = -1.0f;
    float centerX = 0.0f;
    float roofY = 2.25;
    float centerZ = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -7.5);

    // Apply continuous rotation
    glRotatef(rotationX, 1, 0, 0);
    glRotatef(rotationY, 0, 1, 0);

    //Front Wall
    glColor3ub(255, 165, 0);
    glBegin(GL_QUADS);
        glVertex3f(leftX, bottomY, frontZ);
        glVertex3f(leftX, topY, frontZ);
        glVertex3f(rightX, topY, frontZ);
        glVertex3f(rightX, bottomY, frontZ);
    glEnd();

    //Right Wall
    glColor3ub(0, 128, 255);
    glBegin(GL_QUADS);
        glVertex3f(rightX, bottomY, frontZ);
        glVertex3f(rightX, topY, frontZ);
        glVertex3f(rightX, topY, backZ);
        glVertex3f(rightX, bottomY, backZ);
    glEnd();

    //Left Wall
    glColor3ub(0, 128, 255);
    glBegin(GL_QUADS);
        glVertex3f(leftX, bottomY, frontZ);
        glVertex3f(leftX, topY, frontZ);
        glVertex3f(leftX, topY, backZ);
        glVertex3f(leftX, bottomY, backZ);
    glEnd();

    //Back Wall
    glColor3ub(255, 165, 0);
    glBegin(GL_QUADS);
        glVertex3f(leftX, bottomY, backZ);
        glVertex3f(leftX, topY, backZ);
        glVertex3f(rightX, topY, backZ);
        glVertex3f(rightX, bottomY, backZ);
    glEnd();

    //Floor
    glColor3ub(255, 165, 205);
    glBegin(GL_QUADS);
        glVertex3f(leftX, bottomY, backZ);
        glVertex3f(leftX, bottomY, frontZ);
        glVertex3f(rightX, bottomY, frontZ);
        glVertex3f(rightX, bottomY, backZ);
    glEnd();

    //Front Roof
    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex3f(leftX, topY, frontZ);
        glVertex3f(rightX, topY, frontZ);
        glVertex3f(centerX, roofY, centerZ);
    glEnd();

    //Right Roof
    glColor3ub(0, 255, 0);
    glBegin(GL_TRIANGLES);
        glVertex3f(rightX, topY, frontZ);
        glVertex3f(rightX, topY, backZ);
        glVertex3f(centerX, roofY, centerZ);
    glEnd();

    //Left Roof
    glColor3ub(0, 255, 0);
    glBegin(GL_TRIANGLES);
        glVertex3f(leftX, topY, frontZ);
        glVertex3f(leftX, topY, backZ);
        glVertex3f(centerX, roofY, centerZ);
    glEnd();

    //Back Roof
    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex3f(leftX, topY, backZ);
        glVertex3f(rightX, topY, backZ);
        glVertex3f(centerX, roofY, centerZ);
    glEnd();

    SDL_GL_SwapBuffers();
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int petla = 1;
    SDL_Event zdarzenie;
    init();
    while (petla == 1)
    {
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                    petla = 0;
                    break;
            }
        }

        // Update rotation angles for animation
        rotationX += 0.5f;
        rotationY += 0.5f;

        display();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();
    return 0;
}
