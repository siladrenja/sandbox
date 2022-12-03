#pragma once

#include "GLAD/include/glad/glad.h"
#include "GLAD/include//KHR/khrplatform.h"

#include <mymath.hpp>
#include <ImageLibrary.hpp>
#include <WindowLibrary.hpp>

#pragma comment(lib, "opengl32.lib")

namespace myGL {
	namespace {
		bool InitGL() {
			static bool gladInitialized = false;
			if (gladInitialized)return true;
			if (!gladLoadGL())return false;
			return (gladInitialized = true);
			
		}
	}
	

	template <typename T, bool intrinEnable = false>
	struct BasicRect {
		math::BasicVector3<T, intrinEnable> TopLeft, BottomLeft, BottomRight, TopRight;
	};

	template <typename T, bool intrinEnable = false>
	struct BasicRect2 {
		math::BasicVector2<T, intrinEnable> TopLeft, BottomLeft, BottomRight, TopRight;
	};

	using Rect = BasicRect<float, true>;
	using Recti = BasicRect<int32_t, true>;
	using Rectd = BasicRect<double, true>;
	using Rectl = BasicRect<int64_t, true>;

	using Rect2 =  BasicRect2<float, true>;
	using Rect2i = BasicRect2<int32_t, true>;
	using Rect2d = BasicRect2<double, true>;
	using Rect2l = BasicRect2<int64_t, true>;

	template <typename T, bool intrinEnable = false>
	struct BasicTriangle {
		math::BasicVector3<T, intrinEnable> A,B,C;
	};

	template <typename T, bool intrinEnable = false>
	struct BasicTriangle2 {
		math::BasicVector2<T, intrinEnable> A, B, C;
	};

	using Triangle =  BasicTriangle<float, true>;
	using Trianglei = BasicTriangle<int32_t, true>;
	using Triangled = BasicTriangle<double, true>;
	using Trianglel = BasicTriangle<int64_t, true>;

	using Triangle2 =  BasicTriangle2<float, true>;
	using Triangle2i = BasicTriangle2<int32_t, true>;
	using Triangle2d = BasicTriangle2<double, true>;
	using Triangle2l = BasicTriangle2<int64_t, true>;

	enum class ShaderType {
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER,
		compute = GL_COMPUTE_SHADER,
		geometry = GL_GEOMETRY_SHADER,
		tessellationControl = GL_TESS_CONTROL_SHADER,
		tessellationEvaluation = GL_TESS_EVALUATION_SHADER
	};

	class Shader {
	public:
		Shader(const char* shaderData, ShaderType type) {
			shaderID = glCreateShader((GLenum)type);
			glShaderSource(shaderID, 1, &shaderData, NULL);
			glCompileShader(shaderID);
		}
		

		inline unsigned int GetID() const {
			return shaderID;
		}

		~Shader() {
			glDeleteShader(shaderID);
		}

	protected:
		unsigned int shaderID;
	};


	class ShaderProgram {
	public:
		ShaderProgram() {
			programID = glCreateProgram();
		}

		void AttachShader(const Shader* shad, size_t shaderNum = 1) {
			for (size_t i = 0; i < shaderNum; i++) {
				glAttachShader(programID, shad->GetID());
			}
		}

		void AttachShader(const Shader& shad) {
				glAttachShader(programID, shad.GetID());
		}

		inline void LinkProgram() {
			glLinkProgram(programID);
		}


		inline void Use() {
			glUseProgram(programID);
		}

		const unsigned int GetID() const {
			return programID;
		}

	protected:
		unsigned int programID;
	};

	class GlSession {
	public:
		

		GlSession(Win::Window& windowtoAttachTo, const math::Vector4& Dims = {0,0,1,1}, PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				32,
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,
				8,
				0,
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			}) {
			DimensionsInWindow = Dims;
			attachedTo = windowtoAttachTo.GetHDC();
			SetPixelFormat(attachedTo, ChoosePixelFormat(attachedTo, &pfd), &pfd);

			context = wglCreateContext(attachedTo);

			wglMakeCurrent(attachedTo, context);

			InitGL();

			RECT rect;
			if (GetWindowRect(windowtoAttachTo.GetHwnd(), &rect)) {
				int width = rect.right - rect.left;
				int height = rect.bottom - rect.top;

				glViewport(Dims.X * width, Dims.Y * height, Dims.Z * width, Dims.W * height);
			}


			windowtoAttachTo.AddResizeCallback([this](const WPARAM& wParam, const LPARAM& lParam, Win::Window& win) {
				int width = LOWORD(lParam);
				int height = HIWORD(lParam);
				glViewport(DimensionsInWindow.X * width, DimensionsInWindow.Y * height, DimensionsInWindow.Z * width, DimensionsInWindow.W * height);
				
			});
			
		}

		inline void MakeActive() {
			wglMakeCurrent(attachedTo, context);
		}

		inline math::Vector4 GetRelativeDimensions() const { return DimensionsInWindow; }

	private:
		HGLRC context;
		HDC attachedTo;
		math::Vector4 DimensionsInWindow;
	};
	struct Vertex {
		math::Vector3 Position;
		math::Vector3 Normal;
		math::Vector2 TexCoords;
	};

	class Mesh {
	public:

	private:
		unsigned int VAO, VBO, EBO;

		Vertex* vertices = 0;
		uint32_t* indices = 0;
		Texture* textures = 0;
		size_t numTextures = 0;
	};

	namespace PremadeShaders {
		//constexpr const char* Basic2DVertexShader =
		//	"#version 330 core\n"
		//	"layout (location = 0) in vec3 aPos;\n"
		//	"void main()\n"
		//	"{\n"
		//	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		//	"}\0"
		//	;

		Shader Basic2DVertexShader() {
			return Shader("#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0", ShaderType::vertex);
		}

		Shader Basic2DFragmentShader() {
			return Shader("#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\0", ShaderType::fragment);
		}
	}
}



#pragma region rect operators
template <typename T, bool intrinEnable = false>
myGL::BasicRect<T, intrinEnable> operator+(const myGL::BasicRect<T, intrinEnable>& _1_rect, const math::BasicVector3<T, intrinEnable>& _1_point) {
	return {_1_rect.TopLeft + _1_point, _1_rect.BottomLeft + _1_point, _1_rect.BottomRight + _1_point, _1_rect.TopRight + _1_point };
}
#pragma endregion