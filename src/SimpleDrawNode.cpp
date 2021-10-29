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

    //shader.setUniform3f("meshColor", vec3(1.0f, 1.0f, 1.0f));
    shader.setUniformMatrix4f("mvp", mvp);
    shader.setUniform3f("meshColor", vec3(0.3f, 1.0f, 0.3f)); // Green surface
    shader.setUniform3f("lightColor", vec3(1)); // white color
    shader.setUniform3f("ambientColor", vec3(0.1));
    shader.setUniform3f("lightDir", normalize(vec3(1, 1, 1)));
    //shader.setUniformMatrix4f("modelView", mv);
   // shader.setUniformMatrix4f("model", model);
    //shader.setUniformMatrix3f("normalMatrix", transpose(inverse(model)));
   // shader.setUniform3f("cameraPos", camera.getCamera().position);
    mesh.draw();
    shader.end();
}
