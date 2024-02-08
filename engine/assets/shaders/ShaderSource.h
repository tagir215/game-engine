
struct ShaderSource {
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec2 texCoordi;\n"
		"uniform mat4 MVP;\n"
		"out vec2 texCoord;\n"
		"out vec4 transformedPosition;\n"
		"void main(){\n"
		"	texCoord = texCoordi;\n"
		"	transformedPosition = MVP * vec4(position.x,position.y,position.z,1.0);\n"
		"	gl_Position = transformedPosition;\n"
		"}\n";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"uniform sampler2D texture0;\n"
		"in vec2 texCoord;\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = texture2D(texture0, texCoord);\n"
		"}\n";
	const char* vertexShaderSourceNoTexture =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"uniform mat4 MVP;\n"
		"out vec4 transformedPosition;\n"
		"void main(){\n"
		"	transformedPosition = MVP * vec4(position.x,position.y,position.z,1.0);\n"
		"	gl_Position = transformedPosition;\n"
		"}\n";
	const char* fragmentShaderSourceNoTexture =
		"#version 330 core\n"
		"uniform vec4 color;\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = color;\n"
		"}\n";
};