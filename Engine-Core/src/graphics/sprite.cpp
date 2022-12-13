#include "sprite.h"

#include "util/orthographic_camera.h"
#include "util/error_handling.h"
#include <GL/glew.h>

namespace ds {
    namespace graphics {
        
        Shader* Sprite::pShader = nullptr;
        Sprite::Sprite(float x, float y, float width, float height)
            :pTexture(nullptr), pPosition(x, y), pSize(width, height), pVAO(nullptr), pVBO(nullptr), pVBO2(nullptr), pIBO(nullptr),
            collideableX(0), collideableY(0), collideableWidth(width), collideableHeight(height), pUsesTexture(false)
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
            using namespace maths;
            vec2 positions[4] =
            {
                vec2(-1.0f,  1.0f),
                vec2(-1.0f, -1.0f),
                vec2( 1.0f, -1.0f),
                vec2( 1.0f,  1.0f)
            };
            memcpy(initialVertexPos, positions, sizeof(maths::vec2) * 4);
            memcpy(vertexPos, positions, sizeof(maths::vec2) * 4);
            memcpy(initialCollideableVertexPos, positions, sizeof(maths::vec2) * 4);
            memcpy(collideableVertexPos, positions, sizeof(maths::vec2) * 4);

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
            pVBO = new VertexBuffer(sizeof(float) * 8, 0);
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
            for (int i = 0; i < 4; i++)
            {
                // Multiply the vertices with scale, combined rotate(camera and model) and combined translation(camera and model) matrices
                maths::vec4 vec = ((maths::vec4(initialVertexPos[i].x, initialVertexPos[i].y, 0.0f, 1.0f) * pScale) * pRotation * util::OrthographicCamera::GetCameraRotationMatrix()) * pTranslation * util::OrthographicCamera::GetCameraTranslationMatrix();
                vertexPos[i] = maths::vec2(vec.x, vec.y); // Store the final position data 

                vec = ((maths::vec4(initialCollideableVertexPos[i].x, initialCollideableVertexPos[i].y, 0.0f, 1.0f) * pScale) * pRotation * util::OrthographicCamera::GetCameraRotationMatrix()) * pTranslation * util::OrthographicCamera::GetCameraTranslationMatrix();
                collideableVertexPos[i] = maths::vec2(vec.x, vec.y); // Store the final collideable rect position data 
            }

            // Send the final position data to the gpu
            pVBO->SendDataIntoRegion(0, sizeof(maths::vec2) * 4, vertexPos);

            pVAO->Bind();
            pShader->Bind();

            pShader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

            pTexture->Bind(0);
            pShader->SetUniform1i("uTextureUnit", 0);
            pShader->SetUniformVec4f("uColor", pColor);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Draw(Shader* shader)
        {
            for (int i = 0; i < 4; i++)
            {
                // Multiply the vertices with scale, combined rotate(camera and model) and combined translation(camera and model) matrices
                maths::vec4 vec = ((maths::vec4(initialVertexPos[i].x, initialVertexPos[i].y, 0.0f, 1.0f) * pScale) * pRotation * util::OrthographicCamera::GetCameraRotationMatrix()) * pTranslation * util::OrthographicCamera::GetCameraTranslationMatrix();
                vertexPos[i] = maths::vec2(vec.x, vec.y); // Store the final position data 

                vec = ((maths::vec4(initialCollideableVertexPos[i].x, initialCollideableVertexPos[i].y, 0.0f, 1.0f) * pScale) * pRotation * util::OrthographicCamera::GetCameraRotationMatrix()) * pTranslation * util::OrthographicCamera::GetCameraTranslationMatrix();
                collideableVertexPos[i] = maths::vec2(vec.x, vec.y); // Store the final collideable rect position data 
            }

            // Send the final position data to the gpu
            pVBO->SendDataIntoRegion(0, sizeof(maths::vec2) * 4, vertexPos);

            pVAO->Bind();
            shader->Bind();

            shader->SetUniformMat4f("uProjection", util::OrthographicCamera::GetProjectionMatrix());

            pTexture->Bind(0);
            shader->SetUniform1i("uTextureUnit", 0);
            shader->SetUniformVec4f("uColor", pColor);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        }

        void Sprite::Init()
        {
            const char* vsCode = R"(

                #version 330 core
                
                layout(location = 0) in vec2 position;
                layout(location = 1) in vec2 textCoord;
                                
                uniform mat4 uProjection;
                
                out vec2 vTextCoord;
                
                void main()
                {                
                	gl_Position = uProjection * vec4(position.x, position.y, 0.0f, 1.0f);
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
            float topA = pPosition.y - collideableY;
            float bottomA = topA - collideableHeight;
            float leftA = pPosition.x + collideableX;
            float rightA = leftA + collideableWidth;

            float topB = sprite->GetPosition().y - sprite->GetCollideableRect().y;
            float bottomB = topB - sprite->GetCollideableRect().w;
            float leftB = sprite->GetPosition().x + sprite->GetCollideableRect().x;
            float rightB = leftB + sprite->GetCollideableRect().z;

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

        bool Sprite::CheckCollisisonSAT(Sprite* sprite)
        {
            // Calculate the edge normals from the position data for both the quads
            // Quad 1
            maths::mat4 rotationMat = maths::rotate(TO_RADIANS(90.0f), maths::vec3(0.0f, 0.0f, 1.0f));
            
            maths::vec2 parallelVec = (vertexPos[3] - vertexPos[0]).Normalize();
            maths::vec4 normalVec = maths::vec4(parallelVec.x, parallelVec.y, 0.0f, 1.0f) * rotationMat;
            edgeNormals[0] = maths::vec2(normalVec.x, normalVec.y);

            parallelVec = (vertexPos[0] - vertexPos[1]).Normalize();
            normalVec = maths::vec4(parallelVec.x, parallelVec.y, 0.0f, 1.0f) * rotationMat;
            edgeNormals[1] = maths::vec2(normalVec.x, normalVec.y);

            // Quad 2
            parallelVec = (sprite->vertexPos[3] - sprite->vertexPos[0]).Normalize();
            normalVec = maths::vec4(parallelVec.x, parallelVec.y, 0.0f, 1.0f) * rotationMat;
            sprite->edgeNormals[0] = maths::vec2(normalVec.x, normalVec.y);

            parallelVec = (sprite->vertexPos[0] - sprite->vertexPos[1]).Normalize();
            normalVec = maths::vec4(parallelVec.x, parallelVec.y, 0.0f, 1.0f) * rotationMat;
            sprite->edgeNormals[1] = maths::vec2(normalVec.x, normalVec.y);

            maths::vec2 normals[4] = { edgeNormals[0], edgeNormals[1], sprite->edgeNormals[0], sprite->edgeNormals[1]};

            // Project both quad's vertices onto each the normals
            float projMinA, projMaxA, projMinB, projMaxB;
           
            // Check, for each normal, if any projections do not overlap
            for (int i = 0; i < 4; i++)
            {
                GetProjections(normals[i], this, sprite, projMinA, projMaxA, projMinB, projMaxB);
                if (!CheckOverlap(projMinA, projMaxA, projMinB, projMaxB))
                    return false;
            }

            // If every normal has overlaps in projection then collision exists so return true
            return true;
        }

        void Sprite::SetTexture(const char* texturePath)
        {
            pUsesTexture = true;
            delete pTexture;

            pTexture = new Texture(texturePath);
            pColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        }

        void Sprite::SetTexture(Texture* texture)
        {
            pUsesTexture = true;

            pTexture = texture;
            pColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        }

        void Sprite::SetPosition(float x, float y)
        {
            pPosition = maths::vec2(x, y);
            pTranslation = maths::translate(maths::vec3(pPosition.x + pSize.x / 2, pPosition.y - pSize.y / 2, 0.0f));
        }

        void Sprite::SetSize(float width, float height)
        {
            using namespace maths;
            pSize = maths::vec2(width, height);
            pScale = maths::scale(maths::vec3(pSize.x / 2, pSize.y / 2, 1.0f)); // The size has to be divided by 2 because it is scaled evenly both on right and left

            SetPosition(pPosition.x, pPosition.y);

            // Set the collideable rect dimensions
            maths::vec2 positions[4] =
            {
               maths::vec2(collideableX,  collideableY),
               maths::vec2(collideableX, collideableY + collideableHeight),
               maths::vec2(collideableX + collideableWidth, collideableY + collideableHeight),
               maths::vec2(collideableX + collideableWidth, collideableY),
            };

            mat4 projection = orthographic(0.0f, pSize.x, 0.0, pSize.y, 1.0f, -1.0f);

            for (int i = 0; i < 4; i++)
            {
                vec4 pos = vec4(positions[i].x, positions[i].y, 0.0f, 1.0f) * projection;
                initialCollideableVertexPos[i] = vec2(pos.x, pos.y);
            }
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
            pVBO2->SendDataIntoRegion(0, sizeof(float) * 8, newTextCoords);
        }
        void Sprite::SetSpriteCollideRect(float x, float y , float width, float height)
        {
            collideableX = x;
            collideableY = y;
            collideableWidth = width;
            collideableHeight = height;

            // Set the collideable rect dimensions
            maths::vec2 positions[4] =
            {
               maths::vec2(collideableX,  collideableY),
               maths::vec2(collideableX, collideableY + collideableHeight),
               maths::vec2(collideableX + collideableWidth, collideableY + collideableHeight),
               maths::vec2(collideableX + collideableWidth, collideableY),
            };

            maths::mat4 projection = maths::orthographic(0.0f, pSize.x, 0.0, pSize.y, 1.0f, -1.0f);

            for (int i = 0; i < 4; i++)
            {
                maths::vec4 pos = maths::vec4(positions[i].x, positions[i].y, 0.0f, 1.0f) * projection;
                initialCollideableVertexPos[i] = maths::vec2(pos.x, pos.y);
            }

        }
     
        void GetProjections(maths::vec2& normal, Sprite* s1, Sprite* s2, float& projMinA, float& projMaxA, float& projMinB, float& projMaxB)
        {
            // Quad 1: Finding projMinA and projMaxA
            float projections[4];
            float projMin, projMax;

            for (int i = 0; i < 4; i++) 
                projections[i] = s1->collideableVertexPos[i].Dot(normal);

            // Find the minimum and maximum projections
            projMin = projections[0];
            projMax = projections[0];

            for (int i = 0; i < 4; i++)
            {
                if (projections[i] < projMin)
                    projMin = projections[i];
                else if (projections[i] > projMax)
                    projMax = projections[i];
            }

            // Give these projection values to the user
            projMinA = projMin;
            projMaxA = projMax;
        
            // Quad 2: Finding projMinA and projMaxA
            for (int i = 0; i < 4; i++)
                projections[i] = s2->collideableVertexPos[i].Dot(normal);

            // Find the minimum and maximum projections
            projMin = projections[0];
            projMax = projections[0];

            for (int i = 0; i < 4; i++)
            {
                if (projections[i] < projMin)
                    projMin = projections[i];
                else if (projections[i] > projMax)
                    projMax = projections[i];
            }

            // Give these projection values to the user
            projMinB = projMin;
            projMaxB = projMax;
        }
        bool CheckOverlap(const float& projMinA, const float& projMaxA, const float& projMinB, const float& projMaxB)
        {
            // Check if any projections of A is inside the projections of B
            if ((projMinA > projMinB && projMinA < projMaxB) || (projMaxA > projMinB && projMaxA < projMaxB))
                return true;
            else if ((projMinB > projMinA && projMinB < projMaxA) || (projMaxB > projMinA && projMaxB < projMaxA)) // Check if any projections of B is inside the projections of B
                return true;

            return false;
        }
}
}