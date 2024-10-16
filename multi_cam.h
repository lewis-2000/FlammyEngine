#pragma once
#include <glm/glm.hpp>
#include <vector>

#ifndef MULTI_CAM
#define MULTI_CAM

class MultiCam
{
public:
    MultiCam();
    ~MultiCam();

    // Function to select a camera by index
    glm::vec3 selectCam(int selectedCam);

    // Function to add a camera position
    void addCam(const glm::vec3& cameraPos);

    // Function to remove a camera position by index
    void removeCam(int selectedCam);

    // Getter for the number of cameras
    size_t getNumCams() const;

private:
    std::vector<glm::vec3> cameraPositions; // Stores camera positions
};

#endif // !MULTI_CAM
