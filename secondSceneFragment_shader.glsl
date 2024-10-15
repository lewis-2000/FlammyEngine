#version 330 core
in vec3 FragPos;    // Position of the fragment in world space
in vec3 Normal;     // Normal of the fragment for lighting
in vec3 colorFromObjectPosition; // Color from object Position (Expected Rainbows)

out vec4 FragColor;

uniform vec3 lightPos;   // Light source position
uniform vec3 viewPos;    // Camera position
uniform vec3 lightColor; // Light color
uniform vec3 objectColor; // Object color (use this instead of `ourColor`)

void main() {
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (optional)
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine all lighting components
    vec3 result = (ambient + diffuse + specular) * colorFromObjectPosition;
    //vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);  // Output the final color
}
