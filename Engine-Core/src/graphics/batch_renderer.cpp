#include "batch_renderer.h"

#include "util/orthographic_camera.h"

namespace ds {
	namespace graphics {
		std::unique_ptr<Shader> BatchRenderer::pShader = nullptr;
		void BatchRenderer::Init()
		{
			pShader = std::make_unique<Shader>("../Engine-Core/src/shaders/batch_shader/vs.glsl", "../Engine-Core/src/shaders/batch_shader/fs.glsl");

			int textureUnits[32];
			for (int i = 0; i < 32; i++)
				textureUnits[i] = i;
			// Setup the texture units
			pShader->Bind();
			pShader->SetUniform1iv("uTextureUnits", textureUnits, 32);
			pShader->Unbind();
		}

		void BatchRenderer::Draw(Tilemap* map)
		{
			map->BindTextures();

			map->GetVAO()->Bind();
			pShader->Bind();

			pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());
			pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
			pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());

			glDrawElements(GL_TRIANGLES, map->GetIBO()->GetIndiciesCount(), GL_UNSIGNED_SHORT, 0);

		}

		void BatchRenderer::Draw(Tilemap* map, Shader* shader)
		{
			map->BindTextures();
			map->GetVAO()->Bind();
			
			shader->Bind();

			shader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());
			shader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
			shader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());

			glDrawElements(GL_TRIANGLES, map->GetIBO()->GetIndiciesCount(), GL_UNSIGNED_SHORT, 0);
		}
	}
}
