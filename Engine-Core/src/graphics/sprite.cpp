#include "sprite.h"

#include "util/orthographic_camera.h"
#include "util/error_handling.h"
namespace ds {
    namespace graphics {
        Shader* Sprite::pShader = nullptr;
         Sprite::Sprite(int x, int y, int width, int height)
            :pTexture(nullptr), pPosition(x, y), pSize(width, height), pVAO(nullptr), pVBO(nullptr), pVBO2(nullptr), pIBO(nullptr)
        {
            if (!util::OrthographicCamera::IsCameraInitialized())
            {
               THROW_ERROR("Initialize a camera before rendering anything!");
            }
            else {
                CreateRect();
            }
        }

        Sprite::~Sprite()
        {
            delete pVAO;
            delete pVBO;
            delete pVBO2;
            delete pIBO;

            if (pTexture != nullptr)
                delete pTexture;
        }

        void Sprite::CreateRect()
        {
            float positions[8] =
            {
                -1.0f,   1.0f,
                -1.0f,  -1.0f,
                 1.0f,  -1.0f,
                 1.0f,   1.0f
            };
            unsigned char indices[6] = {
                0, 1, 2, 2, 0, 3
            };

            pVAO = new VertexArray();
            pVAO->Bind();

            pVBO = new VertexBuffer(sizeof(float) * 8, positions);
            pVBO->Bind();

            pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);

            pIBO = new IndexBuffer(sizeof(unsigned char) * 6, indices);
            pIBO->Bind();

            pVAO->Unbind();
            pVBO->Unbind();
            pIBO->Unbind();

            SetSize(pSize);
            SetColor(maths::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        void Sprite::Draw()
        {
            pVAO->Bind();

            pShader->Bind();

            if (pTexture == nullptr)
            {
                pShader->SetUniformMat4f("uModelScale", pScale);
                pShader->SetUniformMat4f("uModelRotation", pRotation);
                pShader->SetUniformMat4f("uModelTranslation", pTranslation);
                pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
                pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
                pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

                pShader->SetUniform1i("uUseTexture", 0);
                pShader->SetUniformVec4f("uColor", pColor);
            }
            else
            {
                pShader->SetUniformMat4f("uModelScale", pScale);
                pShader->SetUniformMat4f("uModelRotation", pRotation);
                pShader->SetUniformMat4f("uModelTranslation", pTranslation);
                pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
                pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
                pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

                pTexture->Bind(0);
                pShader->SetUniform1i("uUseTexture", 1);
            }

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Draw(Shader* shader)
        {
            pVAO->Bind();
            shader->Bind();

            if (pTexture == nullptr)
            {
                shader->SetUniformMat4f("uModelScale", pScale);
                shader->SetUniformMat4f("uModelRotation", pRotation);
                shader->SetUniformMat4f("uModelTranslation", pTranslation);
                shader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
                shader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
                shader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

                shader->SetUniform1i("uUseTexture", 0);
                shader->SetUniformVec4f("uColor", pColor);
            }
            else
            {
                shader->SetUniformMat4f("uModelScale", pScale);
                shader->SetUniformMat4f("uModelRotation", pRotation);
                shader->SetUniformMat4f("uModelTranslation", pTranslation);
                shader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
                shader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
                shader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

                pTexture->Bind(0);
                shader->SetUniform1i("uUseTexture", 1);
            }

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Init()
        {
            pShader = new Shader("../Engine-Core/src/shaders/sprite_shader/vs.glsl", "../Engine-Core/src/shaders/sprite_shader/fs.glsl");

            #if _DEBUG
                std::cout << " -> Sprite Rendering System Initialized!" << std::endl;
            #endif
        }

        void Sprite::Free()
        {
            delete pShader;
        }

        void Sprite::SetTexture(const char* texturePath)
        {
            if (pTexture != nullptr)
                delete pTexture;

            float textCoords[8] =
            {
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f
            };

            pVBO2 = new VertexBuffer(sizeof(float) * 8, textCoords);

            pVAO->Bind();
            pVBO2->Bind();

            pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);

            pVAO->Unbind();
            pVBO2->Unbind();

            pTexture = new Texture(texturePath);
            
        }

        void Sprite::SetPosition(const maths::vec2& pos)
        {
            pPosition = pos;
            pTranslation = maths::translate(maths::vec3(pos.x + pSize.x / 2, pos.y - pSize.y / 2, 0.0f));
        }

        void Sprite::SetSize(const maths::vec2& size)
        {
            pSize = size;
            pScale = maths::scale(maths::vec3(size.x / 2, size.y / 2, 1.0f)); // The size has to be divided by 2 because it is scaled evenly both on right and left

            SetPosition(pPosition);
        }

        void Sprite::SetRotation(const float& angle)
        {
            pRotation = maths::rotate(-TO_RADIANS(angle), maths::vec3(0.0f, 0.0f, 1.0f));
        }

        void Sprite::SetColor(const maths::vec4& color)
        {
            pColor = color;
        }

        void Sprite::SetTextureClipRect(int x, int y, int width, int height)
        {
            float newTextCoords[8] =
            {
                        x / (float)(pTexture->GetWidth())                ,       ((pTexture->GetHeight()) - y) / (float)(pTexture->GetHeight()),
                        x / (float)(pTexture->GetWidth())                ,       ((pTexture->GetHeight()) - (y + height)) / (float)(pTexture->GetHeight()),
                       (x + width) / (float)(pTexture->GetWidth())       ,      ((pTexture->GetHeight()) - (y + height)) / ((float)pTexture->GetHeight()),
                       (x + width) / (float)(pTexture->GetWidth())       ,      ((pTexture->GetHeight() - y) / (float)(pTexture->GetHeight())),
            };

            pVBO2->Bind();
            pVBO2->SendDataIntoRegion(0, sizeof(float) * 8, newTextCoords);

            pVBO2->Unbind();
        }
    }
}