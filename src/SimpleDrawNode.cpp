#include "SimpleDrawNode.h"

using namespace glm;

SimpleDrawNode::SimpleDrawNode(const ofMesh& mesh, const ofShader& shader)
    : mesh { mesh }, shader { shader }
{
}

void SimpleDrawNode::drawNode(const CameraMatrices& camera, const glm::mat4& model) const
{
    mat4 mv { camera.getView() * model };
    mat4 mvp { camera.getProj() * mv };
    shader.begin();
    shader.setUniformMatrix4f("mvp", mvp);
    shader.setUniformMatrix4f("modelView", mv);
    shader.setUniformMatrix4f("model", model);
    shader.setUniformMatrix3f("normalMatrix", transpose(inverse(model)));
    shader.setUniform3f("cameraPos", camera.getCamera().position);
    mesh.draw();
    shader.end();
}
