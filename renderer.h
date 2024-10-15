#pragma once

class Renderer {
public:
    virtual void init() = 0;        // Initialize the rendering system (OpenGL setup, etc.)
    virtual void clear() = 0;       // Clear the screen (color buffer, depth buffer)
    virtual void draw() = 0;        // Draw objects
    virtual void swapBuffers() = 0; // Swap the buffers (double buffering)

    virtual ~Renderer() = default;  // Ensure proper cleanup in derived classes
};
