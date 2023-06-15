#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 2) in vec3 a_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 fragment_Position; // for diffuse lightning

void main()
{
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);
    fragment_Position = vec3(model * vec4(a_Pos, 1.0));

    // Normal = a_Normal;
    Normal = mat3(transpose(inverse(model))) * a_Normal;    // в случае если было неоднородное масштабирование, пересчитываем нормали
                                                            // чтобы они действительно были нормальны граням.
}