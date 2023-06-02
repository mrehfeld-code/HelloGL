/* include basic io functions*/
#include <iostream>

/* include SDL3 */
#include <SDL3/SDL.h>
/* include GLEW */
#include <GL/glew.h>

/* define default window properties */
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_SIZE   WINDOW_WIDTH, WINDOW_HEIGHT
#define APP_NAME      "HelloGL"

/* define error codes */
#define ERROR_STD 1
#define ERROR_SDL 2
#define ERROR_OGL 3

int main(int argc, char* argv[]) {
    /* initialize SDL and handle error */
    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL!\n%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    /* set buffer sizes for the context */
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,  32);
    /* enable double buffering */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

    /* create a window and handle error */
    SDL_Window* window = SDL_CreateWindow(APP_NAME, WINDOW_SIZE, SDL_WINDOW_OPENGL);
    if(!window) {
        fprintf(stderr, "Cannot create a window!\n%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    /* create an OpenGL context */
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    /* initialize GLEW and handle error */
    if(GLenum err = glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW!\n%s\n", glewGetErrorString(err));
        return ERROR_OGL;
    }

    /* print OpenGL vendor, renderer and version strings */
    printf("GL vendor string:   %s\n", glGetString(GL_VENDOR));
    printf("GL renderer string: %s\n", glGetString(GL_RENDERER));
    printf("GL version string:  %s\n", glGetString(GL_VERSION));
    printf("GLU version string: %s\n", gluGetString(GLU_VERSION));

    /* set the clear color to RGBA(00, 00, 00, FF) */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* create variables for the main loop */
    SDL_Event event;
    bool loop = true;
    /* enter the main loop */
    while(loop) {
        /* clear the buffers */
        glClear(GL_COLOR_BUFFER_BIT);

        /* render a colored triangle with the old pipeline */
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.75f, -0.75f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.75f, -0.75f);
            glColor3f(0.0f, 0.3f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        /* swap the double buffer */
        SDL_GL_SwapWindow(window);

        /* enter event loop */
        while(SDL_PollEvent(&event)) {
            /* exit the main loop when the 
               window close button was pressed */
            if(event.type == SDL_EVENT_QUIT) {
                loop = false;
            }
        }
    }

    /* delete the context */
    SDL_GL_DeleteContext(glContext);
    /* delete the window */
    SDL_DestroyWindow(window);
    /* free memory used by SDL */
    SDL_Quit();

    return 0;
}
