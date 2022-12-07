#include "sprite.h"

#include "util/orthographic_camera.h"
#include "util/error_handling.h"
#include <GL/glew.h>

namespace ds {
    namespace graphics {
        Shader* Sprite::pShader = nullptr;
        Sprite::Sprite(float x, float y, float width, float height)
            :pTexture(nullptr), pPosition(x, y), pSize(width, height), pVAO(nullptr), pVBO(nullptr), pVBO2(nullptr), pIBO(nullptr), pTextureUnit(0), pUsesTexture(false)
        {
#if _DEBUG
            if (!util::OrthographicCamera::IsCameraInitialized())
            {
                THROW_ERROR("Initialize a camera before rendering anything!");
            }
            else {
                CreateRect();
            }
#else 
            CreateRect();
#endif
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
            float textCoords[8] =
            {
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f
            };

            unsigned char indices[6] = {
                0, 1, 2, 2, 0, 3
            };

            pVAO = new VertexArray();
            pVBO = new VertexBuffer(sizeof(float) * 8, positions);
            pVBO2 = new VertexBuffer(sizeof(float) * 8, textCoords);
            pIBO = new IndexBuffer(sizeof(unsigned char) * 6, indices);

            pVAO->Bind();

            pVBO->Bind();
            pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);
            pVBO2->Bind();
            pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);

            pIBO->Bind();

            pVAO->Unbind();
            pVBO->Unbind();
            pVBO2->Unbind();
            pIBO->Unbind();

            SetSize(pSize.x, pSize.y);
            SetColor(maths::vec4(1.0f, 1.0f, 1.0f, 1.0f));

            // Create the dummy texture
            unsigned char whitePixel[4] = { 255, 255, 255, 255 };
            pTexture = new Texture(1, 1, whitePixel);

            pUsesTexture = false;
            pColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        }

        void Sprite::Draw()
        {
            pVAO->Bind();
            pShader->Bind();

            pShader->SetUniformMat4f("uModelScale", pScale);
            pShader->SetUniformMat4f("uModelRotation", pRotation);
            pShader->SetUniformMat4f("uModelTranslation", pTranslation);
            pShader->SetUniformMat4f("uCameraRotation", util::OrthographicCamera::GetCameraRotationMatrix());
            pShader->SetUniformMat4f("uCameraTranslation", util::OrthographicCamera::GetCameraTranslationMatrix());
            pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

            pTexture->Bind(0);
            pShader->SetUniform1i("uTextureUnit", 0);
            pShader->SetUniformVec4f("uColor", pColor);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Draw(Shader* shader)
        {
            pVAO->Bind();
            shader->Bind();

            pTexture->Bind(0);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Init()
        {

            const char* vsCode = R"(

                #version 330 core
                
                layout(location = 0) in vec2 position;
                layout(location = 1) in vec2 textCoord;
                
                uniform mat4 uModelTranslation;
                uniform mat4 uModelScale;
                uniform mat4 uModelRotation;
                
                uniform mat4 uCameraTranslation;
                uniform mat4 uCameraRotation;
                
                uniform mat4 uProjection;
                
                out vec2 vTextCoord;
                
                void main()
                {
                	mat4 scale = uModelScale;
                	mat4 rotation = uModelRotation * uCameraRotation;
                	mat4 translation = uModelTranslation * uCameraTranslation;
                
                	gl_Position =  uProjection * translation * rotation * scale * vec4(position.x, position.y, 0.0f, 1.0f);
                	vTextCoord = textCoord;
                }


            )";

            const char* fsCode = R"(
                #version 330 core
                
                out vec4 uFragColor;
                
                in vec2 vTextCoord;
                
                uniform vec4 uColor;
                uniform sampler2D uTextureUnit;
                
                void main()
                {
                	uFragColor = uColor * texture(uTextureUnit, vTextCoord);
                }
            )";

            pShader = new Shader(vsCode, fsCode, true);

#if _DEBUG
            std::cout << " -> Sprite Rendering System Initialized!" << std::endl;
#endif
        }

        void Sprite::Free()
        {
            delete pShader;
        }

        bool Sprite::IsCollided(const Sprite* sprite)
        {
            float topA = pPosition.y;
            float bottomA = pPosition.y - pSize.y;
            float leftA = pPosition.x;
            float rightA = pPosition.x + pSize.x;

            float topB = sprite->GetPosition().y;
            float bottomB = sprite->GetPosition().y - sprite->GetSize().y;
            float leftB = sprite->GetPosition().x;
            float rightB = sprite->GetPosition().x + sprite->GetSize().x;

            if (topA < bottomB || topB < bottomA || rightA < leftB || rightB < leftA)
                return false;

            return true;
        }

        bool Sprite::IsCollided(const Tile* tile)
        {
            float topA = pPosition.y;
            float bottomA = pPosition.y - pSize.y;
            float leftA = pPosition.x;
            float rightA = pPosition.x + pSize.x;

            float topB = tile->y;
            float bottomB = tile->y - tile->height;
            float leftB = tile->x;
            float rightB = tile->x + tile->width;

            if (topA < bottomB || topB < bottomA || rightA < leftB || rightB < leftA)
                return false;

            return true;
        }

        bool Sprite::IsCollided(const Tile* tile, float& dx, float& dy)
        {
            float topA = pPosition.y;
            float bottomA = pPosition.y - pSize.y;
            float leftA = pPosition.x;
            float rightA = pPosition.x + pSize.x;

            float topB = tile->y;
            float bottomB = tile->y - tile->height;
            float leftB = tile->x;
            float rightB = tile->x + tile->width;

            if (topA < bottomB || topB < bottomA || rightA < leftB || rightB < leftA)
                return false;

            // Check in which axis that the collision has happed
            if (topA + dy < bottomB || topB < bottomA + dy || rightA < leftB || rightB < leftA)
                dx = 0;
            else
                dy = 0;

            return true;
        }

        void Sprite::SetTexture(const char* texturePath)
        {
            pUsesTexture = true;
            delete pTexture;

            pTexture = new Texture(texturePath);
            pColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        }

        void Sprite::SetPosition(float x, float y)
        {
            pPosition = maths::vec2(x, y);
            pTranslation = maths::translate(maths::vec3(pPosition.x + pSize.x / 2, pPosition.y - pSize.y / 2, 0.0f));
        }

        void Sprite::SetSize(float width, float height)
        {
            pSize = maths::vec2(width, height);
            pScale = maths::scale(maths::vec3(pSize.x / 2, pSize.y / 2, 1.0f)); // The size has to be divided by 2 because it is scaled evenly both on right and left

            SetPosition(pPosition.x, pPosition.y);
        }

        void Sprite::SetRotation(float angle)
        {
            pRotation = maths::rotate(-TO_RADIANS(angle), maths::vec3(0.0f, 0.0f, 1.0f));
        }

        void Sprite::SetColor(const maths::vec4& color)
        {
            if (!pUsesTexture)
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