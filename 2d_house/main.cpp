#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the house
    drawRectangle(1.0, 1.0, 4.0, 3.0, 0.5, 0.5, 0.5);  // Base
    drawRectangle(1.0, 4.0, 4.0, 2.0, 0.6, 0.3, 0.1);  // Roof
    drawRectangle(1.5, 1.0, 1.0, 2.0, 0.6, 0.4, 0.3);  // Door
    drawRectangle(3.3, 2.5, 1.0, 1.0, 0.2, 0.2, 0.8);  // window
    drawTriangle(2.0, 6.0, 1.0, 4.0, 3.0, 4.0, 0.2, 0.8, 0.2);  // Tree

    SDL_GL_SwapBuffers();
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    gluOrtho2D(0.0, 8.0, 0.0, 8.0);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        renderScene();
    }

    SDL_Quit();
    return 0;
}
