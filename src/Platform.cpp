#include "../include/Platform.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
bool Platform::ProcessInput(uint8_t* keys)
{
	bool quit = false;

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				quit = true;
			} break;

			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						quit = true;
					} break;

					case SDLK_x:
					{
						keys[0] = 1;
					} break;

					case SDLK_1:
					{
						keys[1] = 1;
					} break;

					case SDLK_2:
					{
						keys[2] = 1;
					} break;

					case SDLK_3:
					{
						keys[3] = 1;
					} break;

					case SDLK_q:
					{
						keys[4] = 1;
					} break;

					case SDLK_w:
					{
						keys[5] = 1;
					} break;

					case SDLK_e:
					{
						keys[6] = 1;
					} break;

					case SDLK_a:
					{
						keys[7] = 1;
					} break;

					case SDLK_s:
					{
						keys[8] = 1;
					} break;

					case SDLK_d:
					{
						keys[9] = 1;
					} break;

					case SDLK_z:
					{
						keys[0xA] = 1;
					} break;

					case SDLK_c:
					{
						keys[0xB] = 1;
					} break;

					case SDLK_4:
					{
						keys[0xC] = 1;
					} break;

					case SDLK_r:
					{
						keys[0xD] = 1;
					} break;

					case SDLK_f:
					{
						keys[0xE] = 1;
					} break;

					case SDLK_v:
					{
						keys[0xF] = 1;
					} break;
				}
			} break;

			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_x:
					{
						keys[0] = 0;
					} break;

					case SDLK_1:
					{
						keys[1] = 0;
					} break;

					case SDLK_2:
					{
						keys[2] = 0;
					} break;

					case SDLK_3:
					{
						keys[3] = 0;
					} break;

					case SDLK_q:
					{
						keys[4] = 0;
					} break;

					case SDLK_w:
					{
						keys[5] = 0;
					} break;

					case SDLK_e:
					{
						keys[6] = 0;
					} break;

					case SDLK_a:
					{
						keys[7] = 0;
					} break;

					case SDLK_s:
					{
						keys[8] = 0;
					} break;

					case SDLK_d:
					{
						keys[9] = 0;
					} break;

					case SDLK_z:
					{
						keys[0xA] = 0;
					} break;

					case SDLK_c:
					{
						keys[0xB] = 0;
					} break;

					case SDLK_4:
					{
						keys[0xC] = 0;
					} break;

					case SDLK_r:
					{
						keys[0xD] = 0;
					} break;

					case SDLK_f:
					{
						keys[0xE] = 0;
					} break;

					case SDLK_v:
					{
						keys[0xF] = 0;
					} break;
				}
			} break;
		}
	}

	return quit;
}*/


Platform::Platform(char const* title, int winWidth, int winHeight, Chip8* chip8) 
	: windowWidth(winWidth), windowHeight(winHeight), chip(chip8), window(nullptr), FBO(0), texture_id(0), RBO(0), VAO(0), VBO(0), shaderProgram(0) {
	platformInitialization();
}

Platform::~Platform() {
	cleanUp();
}

/*void Platform::create_framebuffer()
{
	/*glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);* /

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create texture for color attachment
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

	// Create renderbuffer for depth and stencil
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Check framebuffer completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	// Unbind framebuffer to avoid accidental rendering
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Platform::bind_framebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void Platform::unbind_framebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}*/

void Platform::create_framebuffer() {
	glGenFramebuffers(1, &FBO);
	bind_framebuffer();

	// Create texture for color attachment
	createTexture();

	// Create renderbuffer for depth and stencil
	createRenderbuffer();

	// Check framebuffer completeness
	checkFramebufferStatus();

	// Unbind framebuffer
	unbindFramebuffer();
}

void Platform::createTexture() {
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
}

void Platform::createRenderbuffer() {
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

void Platform::checkFramebufferStatus() {
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
}

void Platform::unbindFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Platform::bind_framebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void Platform::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Platform::bindRenderBuffer() {
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
}

void Platform::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind the 2D texture
}

void Platform::unbindRenderbuffer() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind the renderbuffer
}


//void Platform::unbind_framebuffer() {
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

/*void Platform::rescale_framebuffer(float width, float height)
{
	/*glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);


	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);* /
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Resize texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Resize renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR::FRAMEBUFFER:: Rescaled framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}*/

void Platform::rescale_framebuffer(float width, float height) {

	// Resize texture and renderbuffer
	bind_framebuffer();
	resizeTexture(width, height);
	resizeRenderbuffer(width, height);

	checkFramebufferStatus();

	unbindFramebuffer();
	unbindTexture();
	unbindRenderbuffer();
}

void Platform::resizeTexture(float width, float height) {
	bindTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Platform::resizeRenderbuffer(float width, float height) {
	bindRenderBuffer();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}


/*void Platform::updateTextureWithARGB(int width, int height) {
	std::vector<uint8_t> rgbaData(width * height * 4, 0);

	float scaleX = static_cast<float>(width) / VIDEO_WIDTH;
	float scaleY = static_cast<float>(height) / VIDEO_HEIGHT;

	for (int y = 0; y < VIDEO_HEIGHT; ++y) {
		for (int x = 0; x < VIDEO_WIDTH; ++x) {
			uint32_t argb = chip->video[y * VIDEO_WIDTH + x];
			int startX = static_cast<int>(x * scaleX);
			int startY = static_cast<int>(y * scaleY);
			int endX = static_cast<int>((x + 1) * scaleX);
			int endY = static_cast<int>((y + 1) * scaleY);

			for (int py = startY; py < endY; ++py) {
				for (int px = startX; px < endX; ++px) {
					int index = (py * width + px) * 4;
					rgbaData[index + 0] = (argb >> 16) & 0xFF; // Red
					rgbaData[index + 1] = (argb >> 8) & 0xFF;  // Green
					rgbaData[index + 2] = (argb) & 0xFF;        // Blue
					rgbaData[index + 3] = (argb >> 24) & 0xFF; // Alpha
				}
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData.data());
}*/

void Platform::updateTextureWithARGB(int width, int height) {
	std::vector<uint8_t> rgbaData(width * height * 4, 0);

	float scaleX = static_cast<float>(width) / VIDEO_WIDTH;
	float scaleY = static_cast<float>(height) / VIDEO_HEIGHT;

	for (int y = 0; y < VIDEO_HEIGHT; ++y) {
		for (int x = 0; x < VIDEO_WIDTH; ++x) {
			uint32_t argb = chip->video[y * VIDEO_WIDTH + x];
			int startX = static_cast<int>(x * scaleX);
			int startY = static_cast<int>(y * scaleY);
			int endX = static_cast<int>((x + 1) * scaleX);
			int endY = static_cast<int>((y + 1) * scaleY);

			for (int py = startY; py < endY; ++py) {
				for (int px = startX; px < endX; ++px) {
					int index = (py * width + px) * 4;
					rgbaData[index + 0] = (argb >> 16) & 0xFF; // Red
					rgbaData[index + 1] = (argb >> 8) & 0xFF;  // Green
					rgbaData[index + 2] = (argb) & 0xFF;        // Blue
					rgbaData[index + 3] = (argb >> 24) & 0xFF; // Alpha
				}
			}
		}
	}

	bindTexture();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData.data());
}


std::string Platform::loadShader(const std::string& filename) {
	std::ifstream shaderFile(filename);

	// Check if the file opened successfully
	if (!shaderFile.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	return shaderStream.str();
}

GLuint Platform::compileShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	std::string vertexCode, fragmentCode;

	try {
		vertexCode = loadShader(vertexShaderFilePath);
		fragmentCode = loadShader(fragmentShaderFilePath);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw; // Rethrow the exception
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode, nullptr);
	glCompileShader(vShader);
	checkShaderCompilation(vShader);

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderCode, nullptr);
	glCompileShader(fShader);
	checkShaderCompilation(fShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	checkProgramLinking(shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return shaderProgram;
}

void Platform::checkShaderCompilation(GLuint shader) {
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
	}
}

void Platform::checkProgramLinking(GLuint program) {
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked != GL_TRUE) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
	}
}

void Platform::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	if (height == 0) height = 1; // Avoid divide by zero
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	// Adjust orthographic projection based on the aspect ratio
	projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

	glViewport(0, 0, width, height);
}

bool Platform::platformInitialization() {
    try {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(windowWidth, windowHeight, "CHIP8 Emulator", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable V-Sync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        glViewport(0, 0, windowWidth, windowHeight);

		//glfwSetFramebufferSizeCallback(window, Platform::framebuffer_size_callback);
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
		io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
		//io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
            throw std::runtime_error("Failed to initialize ImGui GLFW backend");
        }

        if (!ImGui_ImplOpenGL3_Init("#version 330")) {
            throw std::runtime_error("Failed to initialize ImGui OpenGL backend");
        }

		//// Vertex data for a triangle
		//float vertices[] = {
		//	-0.5f, -0.5f, 0.0f, // Bottom left
		//	 0.5f, -0.5f, 0.0f, // Bottom right
		//	 0.0f,  0.5f, 0.0f  // Top
		//};


		//glGenVertexArrays(1, &VAO);
		//glGenBuffers(1, &VBO);
		//glBindVertexArray(VAO);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);

		projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // Default value

		create_framebuffer();

		shaderProgram = compileShader("./src/Shaders/v_shader.glsl", "./src/Shaders/f_shader.glsl");

		GLint projLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
		if (projLoc == -1) {
			throw std::runtime_error("projectionMatrix not found in shader program");
		}

		for (int i = 0; i < VIDEO_HEIGHT * VIDEO_WIDTH; i++) {
			chip->video[i] = 1;
		}

    } catch (const std::exception& e) {
        std::cerr << "Error during initialization: " << e.what() << "\n";
        glfwTerminate();
        return false; // Initialization failed
    }

	return true;
}

void Platform::mainLoop() {

	while (!glfwWindowShouldClose(window)) {
		try {
			update();
		}
		catch (const std::exception& e) {
			std::cerr << "Exception in update(): " << e.what() << "\n";
			glfwSetWindowShouldClose(window, true); // Stop the loop
			break; // Exit the loop immediately
		}
	}
}

void Platform::setupDockSpace() {
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::Begin("DockSpace Demo", nullptr, window_flags);
	ImGui::PopStyleVar(2);

	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	ImGui::End();
}

void Platform::debugWindow(bool showDebug) {
	// Text Window
	if (showDebug) {
		ImGui::Begin("Debug Tab", &showDebug);
		ImGui::TextColored(textColor, "PC: %d", chip->getPC());
		ImGui::TextColored(textColor, "Index: %d", chip->getIndex());
		ImGui::TextColored(textColor, "Opcode: %d", chip->getOPCODE());
		ImGui::TextColored(textColor, "Stack Pointer: %d", chip->getSP());
		std::unique_ptr<uint16_t[]> stack = chip->GetStack();
		for (int i = 0; i < STACK_LEVELS; i++) {
			ImGui::TextColored(textColor, "Stack[%d]: %d", i, stack[i]);
		}
		std::unique_ptr<uint16_t[]> registers = chip->GetStack();
		for (int i = 0; i < STACK_LEVELS; i++) {
			ImGui::TextColored(textColor, "Registers[%d]: %d", i, registers[i]);
		}
		ImGui::End();
	}
}

void Platform::renderWindow() {
	/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui::Begin("Chip8 Display");

	const float window_width = ImGui::GetContentRegionAvail().x;
	const float window_height = ImGui::GetContentRegionAvail().y;

	if (window_height > 0) {
		// Adjust the orthographic projection matrix for the aspect ratio
		float aspectRatio = window_width / window_height;
		projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

		rescale_framebuffer(window_width, window_height);
		glViewport(0, 0, window_width, window_height);
	}

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage(
		(void*)texture_id,
		ImVec2(pos.x, pos.y),
		ImVec2(pos.x + window_width, pos.y + window_height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);

	ImGui::End();*/
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start rendering
	ImGui::Begin("Video Display");
	float window_width = ImGui::GetContentRegionAvail().x;
	float window_height = ImGui::GetContentRegionAvail().y;

	// Resize framebuffer if window size changes
	if (window_height > 0) {
		rescale_framebuffer(window_width, window_height);
		glViewport(0, 0, window_width, window_height);
	}

	updateTextureWithARGB(window_width, window_height);

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddImage(
		(void*)(intptr_t)texture_id,  // Cast to avoid warnings
		ImVec2(pos.x, pos.y),
		ImVec2(pos.x + window_width, pos.y + window_height),
		ImVec2(0, 1), ImVec2(1, 0)
	);

	ImGui::End();

	// Draw additional content to framebuffer
	bind_framebuffer();

	glUseProgram(shaderProgram);
	GLint projLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);

	unbindFramebuffer();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}

}

void Platform::update() {
	glfwPollEvents();

	// Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// DockSpace setup
	setupDockSpace();

	// Other windows
	debugWindow(true);
	//renderWindow();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void Platform::cleanUp() {
	io = nullptr;
	/*ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();*/

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texture_id);
	glDeleteRenderbuffers(1, &RBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	if (window) {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
