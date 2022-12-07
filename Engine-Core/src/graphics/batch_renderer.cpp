#include "batch_renderer.h"

#include "util/orthographic_camera.h"
#include <GL/glew.h>

namespace ds {
	namespace graphics {
		Shader* BatchRenderer::pShader = nullptr;
		void BatchRenderer::Init()
		{
			// Create the shader strings
			const char* vsCode = R"(
				#version 330 core
				
				layout(location = 0) in vec2 position;
				layout(location = 1) in vec2 textCoord;
				layout(location = 2) in float textIndex;
				
				uniform mat4 uCameraTranslation;
				uniform mat4 uCameraRotation;
				
				uniform mat4 uProjection;
				
				out vec2 vTextCoord;
				out float vTextIndex;
				
				void main()
				{
					gl_Position = uProjection * uCameraTranslation * uCameraRotation * vec4(position.x, position.y, 0.0f, 1.0f);
					vTextCoord = textCoord;
					vTextIndex = textIndex;
				}
			)";

			const char* fsCode = R"(
				#version 330 core
				
				out vec4 uFragColor;
				
				in vec2 vTextCoord;
				in float vTextIndex;
				
				uniform sampler2D uTextureUnits[32];
				
				void main()
				{
					int textIndex = int(vTextIndex);
					uFragColor = texture(uTextureUnits[textIndex], vTextCoord);
				}
			)";

			pShader = new Shader(vsCode, fsCode, true);

			int textureUnits[32];
			for (int i = 0; i < 32; i++)
				textureUnits[i] = i;
			// Setup the texture units
			pShader->Bind();
			pShader->SetUniform1iv("uTextureUnits", textureUnits, 32);
			pShader->Unbind();

#if _DEBUG
			std::cout << " -> Batch Renderer Initialized!" << std::endl;
#endif
		}

		void BatchRenderer::Free()
		{
			delete pShader;
		}

		void BatchRenderer::Draw(Tilemap* map)
		{
			map->BindTextures();

			map->GetVAO()->Bind();
			pShader->Bind();

			pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
			pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
			pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

			glDrawElements(GL_TRIANGLES, map->GetIBO()->GetIndiciesCount(), GL_UNSIGNED_SHORT, 0);

		}

		void BatchRenderer::Draw(Tilemap* map, Shader* shader)
		{
			map->BindTextures();
			map->GetVAO()->Bind();

			shader->Bind();

			shader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
			shader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
			shader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

			glDrawElements(GL_TRIANGLES, map->GetIBO()->GetIndiciesCount(), GL_UNSIGNED_SHORT, 0);
		}
	}
}
