#include "Shader.h"

void Shader::CreateFromFiles(const char* vShader, const char* fShader)
{
	std::string vShaderCode = readShaderCodeFromFile(vShader);
	std::string fShaderCode = readShaderCodeFromFile(fShader);

	compileShaders(vShaderCode.c_str(), fShaderCode.c_str());
}

std::string Shader::readShaderCodeFromFile(const char* shaderPath)
{
	std::string code;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Открываем файлы
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// Считываем данные в потоки
		shaderStream << shaderFile.rdbuf();
		// Закрываем файлы
		shaderFile.close();
		// Преобразовываем потоки в массив GLchar
		code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader file " << shaderPath << " cannot be read" << std::endl;
	}

	return code;
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	glLinkProgram(theShader);
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(errLog), NULL, errLog);
		std::cerr << "Error compiling the " << shaderType << " shader: '" << errLog << "'\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::compileShaders(const char* vShaderCode, const char* fShaderCode)
{
	shaderID = glCreateProgram();

	if (!shaderID) {
		std::cerr << "Error creating shader program\n";
		return;
	}

	addShader(shaderID, vShaderCode, GL_VERTEX_SHADER);
	addShader(shaderID, fShaderCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errLog), NULL, errLog);
		std::cerr << "Error linking program: '" << errLog << "'\n";
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errLog), NULL, errLog);
		std::cerr << "Error validating program: '" << errLog << "'\n";
		return;
	}

	// Засовываем модель, проекцю на экран, вид экрана, и освещение непосредственно в шейдер
	uniformModel				= glGetUniformLocation(shaderID, "model");
	uniformProjection			= glGetUniformLocation(shaderID, "projection");
	uniformView					= glGetUniformLocation(shaderID, "view");
	uniformEyePosition			= glGetUniformLocation(shaderID, "eyePosition");
	uniformAmbientColour		= glGetUniformLocation(shaderID, "dirLight.colour");			// look at fragment.shader DirectionalLight struct
	uniformAmbientIntensity		= glGetUniformLocation(shaderID, "dirLight.ambientIntensity");	// look at fragment.shader DirectionalLight struct
	uniformDirection			= glGetUniformLocation(shaderID, "dirLight.direction");			// look at fragment.shader DirectionalLight struct
	uniformDiffuseIntensity		= glGetUniformLocation(shaderID, "dirLight.diffuseIntensity");	// look at fragment.shader DirectionalLight struct
	uniformShininess			= glGetUniformLocation(shaderID, "material.shininess");			// look at fragment.shader Material struct
	uniformSpecularIntensity	= glGetUniformLocation(shaderID, "material.specularIntensity");	// look at fragment.shader Material struct
}
