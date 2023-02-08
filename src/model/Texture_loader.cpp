#include "texture_loader.h"

#include "model/Texture.h"
//#include "model/texture_cube.h"

#include "stb\stb_image.h"

Texture Texture_loader::Load_texture(const std::string& filename, GLenum target, GLenum internalFormat, bool srgb)
{
    Texture texture(true);
    char* path = Get_texture_path(filename);

    texture.set_Target(target);
    texture.set_Internal_format(internalFormat);
    
    switch (texture.get_Internal_format())
    {
    case GL_RGB:
        texture.set_Internal_format(srgb ? GL_SRGB : GL_RGB);
        break;
    case GL_SRGB:
        texture.set_Internal_format(srgb ? GL_SRGB : GL_RGB);
        break;
    case GL_SRGB_ALPHA: 
        texture.set_Internal_format(srgb ? GL_SRGB_ALPHA : GL_RGBA);
        break;
    case GL_RGBA:
        texture.set_Internal_format(srgb ? GL_SRGB_ALPHA : GL_RGBA);
        break;
    default:
        break;
    }

    // flip textures on their y coordinate while loading
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format { 0 };
        switch (nrComponents)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
        }

        if(target == GL_TEXTURE_1D)
            texture.Generate(width, texture.get_Internal_format(), format, GL_UNSIGNED_BYTE, data);
        else 
        if (target == GL_TEXTURE_2D)
            texture.Generate(width, height, texture.get_Internal_format(), format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        printf("Texture failed to load at path: %s", path);
        stbi_image_free(data);
        return texture;
    }
    texture.set_Width(width);
    texture.set_Height(height);

    return texture;
}

Texture Texture_loader::Load_HDR_texture(const std::string& filename)
{
    Texture texture;
    char* path = Get_texture_path(filename);

    texture.set_Target(GL_TEXTURE_2D);
	texture.set_Filter_min(GL_LINEAR);
	texture.set_Mipmapping(false);

    stbi_set_flip_vertically_on_load(true);

    if (stbi_is_hdr(path))
    {
        int width, height, nrComponents;
        float *data = stbi_loadf(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum internalFormat { 0 };
            GLenum format { 0 };

            switch (nrComponents)
            {
            case 3:
                internalFormat = GL_RGB32F;
                format = GL_RGB;
                break;
            case 4:
                internalFormat = GL_RGBA32F;
                format = GL_RGBA;
                break;
            default:
                break;
            }

            texture.Generate(width, height, internalFormat, format, GL_FLOAT, data);
            stbi_image_free(data);
        }
        texture.set_Width(width);
        texture.set_Height(height);
    }
    else
    {
        printf("Trying to load a HDR texture with invalid path or texture is not HDR:  %s.", path);
    }

    return texture;
}

char* Texture_loader::Get_texture_path(const std::string& filename)
{
    TCHAR c_path[MAX_PATH];
    char* result = nullptr;

    GetModuleFileName(NULL, c_path, (sizeof(c_path)));  // get execution filepath

    PathRemoveFileSpec(c_path); // remove name of program from path

    // make shader filepath
    std::string directory = std::string(c_path);
    directory = directory - "\\Debug" - "\\x64";
    directory = directory + "\\resources" + "\\textures\\";
    directory = directory + filename;

    result = new char[directory.length() + 1];

    result[directory.length()] = '\0';  // make sure that the new string is null terminated

    memcpy(result, directory.c_str(), directory.length() + 1);

    return result;
}

/*
TextureCube Texture_loader::Load_texture_cube(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back)
{
    TextureCube texture;

    // disable y flip on cubemaps
    stbi_set_flip_vertically_on_load(false);

    std::vector<std::string> faces = { top, bottom, left, right, front, back };
    for (unsigned int i = 0; i < faces.size(); ++i)
    {
        int width, height, nrComponents;
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        
        if (data)
        {
            GLenum format;
            if (nrComponents == 3)
                format = GL_RGB;
            else
                format = GL_RGBA;

            texture.GenerateFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, width, height, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            Log::Message("Cube texture at path: " + faces[i] + " failed to load.", LOG_WARNING);
            stbi_image_free(data);
            return texture;
        }
    }
    if(texture.Mipmapping)
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return texture;
}

TextureCube Texture_loader::Load_texture_cube(std::string folder)
{
    return TextureLoader::Load_texture_cube(folder + "right.jpg",
                                          folder + "left.jpg",
                                          folder + "top.jpg",
                                          folder + "bottom.jpg",
                                          folder + "front.jpg",
                                          folder + "back.jpg");
}
*/
