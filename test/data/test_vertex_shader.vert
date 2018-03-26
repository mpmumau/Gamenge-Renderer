#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform vec3 LightPosition;

void main()
{
    gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
    
    Position_worldspace = (ModelMatrix * vec4(vertexPosition_modelspace, 1)).xyz;
    
    vec3 vertexPosition_cameraspace = (ViewMatrix * ModelMatrix * vec4(vertexPosition_modelspace, 1)).xyz;
    EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;

    vec3 LightPosition_cameraspace = (ViewMatrix * vec4(LightPosition, 1)).xyz;
    LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
    
    Normal_cameraspace = (ViewMatrix * ModelMatrix * vec4(vertexNormal_modelspace, 0)).xyz;
    
    UV = vertexUV;
}
