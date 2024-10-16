#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal; // normal attribute

out vec3 FragPos;
out vec3 ourColor;
out vec3 Normal;
out vec3 colorFromObjectPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Get fragment position in world space
    FragPos = vec3(model * vec4(aPos, 1.0)); 

    // Pass color to fragment shader
    ourColor = aColor;  

    // Transform normals properly
    Normal = mat3(transpose(inverse(model))) * aNormal; 

    // Calculate color from object position (normalize to range [0,1] for color use)
    colorFromObjectPosition = normalize(FragPos);  

    // Final vertex position
    gl_Position = projection * view * model * vec4(aPos, 1.0f);


}
