#include "multi_cam.h"

// Constructor
MultiCam::MultiCam() {
    // Initialize with 5 camera positions near the cube positions
    cameraPositions = {
       glm::vec3(1.0f, 3.0f, 5.0f),    // A position looking down from above
       glm::vec3(0.0f, 0.0f, 3.0f),   // A position from the left side
       glm::vec3(0.0f, 2.0f, 1.0f),  // A position further back, looking at the scene from behind
       glm::vec3(-3.0f, 4.0f, 2.0f),   // A higher angle, from the right side
       glm::vec3(0.0f, 0.5f, 7.0f)     // A close-up camera looking at the objects
    };

}

// Destructor
MultiCam::~MultiCam() {}

// Select camera by index
glm::vec3 MultiCam::selectCam(int selectedCam) {
    if (selectedCam >= 0 && selectedCam < cameraPositions.size()) {
        return cameraPositions[selectedCam];
    }
    // Return the first camera if index is out of range
    return cameraPositions[0];
}

// Add a new camera position
void MultiCam::addCam(const glm::vec3& cameraPos) {
    cameraPositions.push_back(cameraPos);
}

// Remove a camera by index
void MultiCam::removeCam(int selectedCam) {
    if (selectedCam >= 0 && selectedCam < cameraPositions.size()) {
        cameraPositions.erase(cameraPositions.begin() + selectedCam);
    }
}

// Get the number of cameras
size_t MultiCam::getNumCams() const {
    return cameraPositions.size();
}
