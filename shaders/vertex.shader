#version 330                                                          
                                                                        
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex; 
layout(location = 2) in vec3 norm; // Задаем нормаль по поверхности для диффузного света                                     
                                                                        
out vec4 vCol; 
out vec2 TexCoord; 
//flat out vec3 Normal; // not a Phong shading;    
out vec3 Normal;    // и отправляем ее на выход на фрагмент шейдер.                                                      
                                                                        
uniform mat4 model;                                                     
uniform mat4 projection; 
uniform mat4 view;                                               
                                                                        
void main()                                                             
{                                                                       
    gl_Position = projection * view * model * vec4(pos, 1.0);                  
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f); 

    TexCoord = tex;  

    Normal = mat3(transpose(inverse(model))) * norm;    
    // надо понимать что, это просто направление по поверхности.  
    // и это умножение нужно для того чтобы нормаль была всегда под нужным углом к
    // поверхности(90градусов) даже если объект перемещается или поворачивается.
    // но это не касается случая масштабирования, тогда нормали искажаются
    // для того чтобы этого не было, мы инициализируем из модели матрицу 3x3(ивертированную),
    // вместо того чтобы просто умножить model * normal;                 
}