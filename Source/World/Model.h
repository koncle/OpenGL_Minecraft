#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "glhead.h"
#include "../Utils/NonCopyable.h"

class Model : public NonCopyable
{
    public:
        Model() = default;
    Model(const std::vector<GLfloat>& vertexPositions,
          const std::vector<GLfloat>& textureCoords,
          const std::vector<GLuint>&  indices);

        Model(const std::vector<GLfloat>& vertexPositions,
              const std::vector<GLfloat>& textureCoords,
              const std::vector<GLfloat>& norms,
              const std::vector<GLuint>&  indices);
        ~Model();

    void addData(const std::vector<GLfloat>& vertexPositions,
                 const std::vector<GLfloat>& textureCoords,
                 const std::vector<GLuint>&  indices);

        void addData(const std::vector<GLfloat>& vertexPositions,
                     const std::vector<GLfloat>& textureCoords,
                     const std::vector<GLfloat>& norms,
                     const std::vector<GLuint>&  indices);

        void deleteData();

        void addVBO(int dimensions, const std::vector<GLfloat>& data);
        void bindVAO() const;
        void unbindVAO() const;

        int getIndicesCount() const;

        GLuint m_vao = 0;

    private:
        void addEBO(const std::vector<GLuint>& indices);

        int m_vboCount = 0;
        int m_indicesCount = 0;
        std::vector<GLuint> m_buffers;
};

#endif // MODEL_H_INCLUDED
