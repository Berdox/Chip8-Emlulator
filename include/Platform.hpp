#pragma once

#include <cstdint>
#include <string>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include "../include/Chip8.hpp"



class Platform
{
	friend class Imgui;

	public:
		Platform(char const*, int, int, Chip8*);
		~Platform();
		std::string loadShader(const std::string&);
		GLuint compileShader(const std::string&, const std::string&);
		void create_framebuffer();
		void createTexture();
		void createRenderbuffer();
		void checkFramebufferStatus();
		void bind_framebuffer();
		void unbindFramebuffer();
		void bindTexture();
		void unbindTexture();
		void bindRenderBuffer();
		void unbindRenderbuffer();
		void resizeTexture(float width, float height);
		void resizeRenderbuffer(float width, float height);
		void updateTextureWithARGB(int width, int height);
		void checkShaderCompilation(GLuint shader);
		bool platformInitialization();
		void checkShaderCompilation(GLuint shader, const std::string& type);
		void checkProgramLinking(GLuint program);
		void mainLoop();
		void setupDockSpace();
		void debugWindow(bool);
		void renderWindow();
		void update();
		void cleanUp();
		//void Update(void const* buffer, int pitch);
		//bool ProcessInput(uint8_t* keys);

	private:
		GLFWwindow* window;
		ImGuiIO* io;
		GLuint VBO;
		GLuint VAO;
		GLuint FBO;
		GLuint RBO;
		GLuint texture_id;
		GLuint shaderProgram;
		int windowHeight;
		int windowWidth;
		glm::mat4 projectionMatrix;
		Chip8* chip;
		ImVec4 textColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f); // Green color


		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void rescale_framebuffer(float, float);
		//SDL_Window* window{};
		//SDL_GLContext gl_context{};
		//GLuint framebuffer_texture;
		//SDL_Renderer* renderer{};
		//SDL_Texture* texture{};
};
