#include "window.h"

int main() {
    // Initialize window and OpenGL context
    Window FLEngine(800, 800);
    FLEngine.init();

    // Start the window's main loop
    FLEngine.run();

    return 0;
}
