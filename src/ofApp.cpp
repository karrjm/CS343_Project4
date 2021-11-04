#include "ofApp.h"
#include "GLFW/glfw3.h"
#include "CameraMatrices.h"
#include "SimpleDrawNode.h"
using namespace glm;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofDisableArbTex();
    ofEnableDepthTest();
    //glEnable(GL_CULL_FACE);

    reloadShaders();

    robotMesh.load("models/robotBodyV2.ply");
    robotMesh.flatNormals();
    radarMesh.load("models/robotRadarV2.ply");
    radarMesh.flatNormals();
    gunMesh.load("models/robotCannonV2.ply");
    gunMesh.flatNormals();

    for (size_t i{ 0 }; i < robotMesh.getNumNormals(); i++)
    {
        robotMesh.setNormal(i, -robotMesh.getNormal(i));
    }

    for (size_t i{ 0 }; i < radarMesh.getNumNormals(); i++)
    {
        radarMesh.setNormal(i, -radarMesh.getNormal(i));
    }

    for (size_t i{ 0 }; i < gunMesh.getNumNormals(); i++)
    {
        gunMesh.setNormal(i, -gunMesh.getNormal(i));
    }

    // add non-drawing nod to represent static robot body
    sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode{});
    robotNode = sceneGraphRoot.childNodes.back();
    robotNode->childNodes.emplace_back(new SimpleDrawNode{ robotMesh, shader });
    auto robotMeshNode = robotNode->childNodes.back();


    // add non-drawing node to represent rotating radar
    sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode{});
    radarNode = sceneGraphRoot.childNodes.back();
    radarNode->childNodes.emplace_back(new SimpleDrawNode{ radarMesh, shader });
    auto radarMeshNode = radarNode->childNodes.back();

    // add non-drawing node to represent rotating gun
    sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode{});
    gunNode = sceneGraphRoot.childNodes.back();
    gunNode->childNodes.emplace_back(new SimpleDrawNode{ gunMesh, shader });
    auto gunMeshNode = gunNode->childNodes.back();




    /*sceneGraphRoot.childNodes.emplace_back(new SimpleDrawNode{ radarMesh, shader });
    turretsNode = sceneGraphRoot.childNodes.back();
    sceneGraphRoot.childNodes.emplace_back(new SimpleDrawNode{ gunMesh, shader });
    turretsNode = sceneGraphRoot.childNodes.back();*/


    //// add a nondrawing node to scene graph
    //sceneGraphRoot.childNodes.emplace_back(new SceneGraphNode{});




    ofSetBackgroundColor(53, 81, 98);
}

void ofApp::reloadShaders() {
    shader.load("my.vert", "my.frag");
    needsReload = false;
}

//--------------------------------------------------------------
void ofApp::update()
{
	camera.position += mat3(rotate(cameraHead, vec3(0, 1, 0))) * velocity * ofGetLastFrameTime();
	camera.rotation = rotate(cameraHead, vec3(0, 1, 0)) * rotate(cameraPitch, vec3(1, 0, 0));
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	cameraHead -= dx;
	cameraPitch -= dy;

	cameraPitch = clamp(cameraPitch, -static_cast<float>(PI) / 2, static_cast<float>(PI) / 2);
}

void ofApp::updateModelRotation(float dx, float dy)
{
    mat3 currentRadarRotation = { mat3(radarNode->localTransform) };
    vec3 currentRadarTranslation = { radarNode->localTransform[3] };
    radarNode->localTransform = translate(currentRadarTranslation) * rotate(dx, vec3(0, 1, 0)) * mat4(currentRadarRotation);

    mat3 currentGunRotation = { mat3(gunNode->localTransform) };
    vec3 currentGunTranslation = { gunNode->localTransform[3] };
    gunNode->localTransform = translate(currentGunTranslation) * rotate(dx, vec3(0, 1, 0)) * mat4(currentGunRotation);
}

void ofApp::updateJointRotation(float dx, float dy)
{
}

//--------------------------------------------------------------
void ofApp::draw()
{

    float width{ static_cast<float>(ofGetViewportWidth()) };
    float height{ static_cast<float>(ofGetViewportHeight()) };
    float aspect = width / height;

    CameraMatrices camMatrices{ camera, aspect, 0.01f, 10.0f, };

    sceneGraphRoot.drawSceneGraph(camMatrices);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'w')
    {
        velocity.z = -1;
    }
    else if (key == 's')
    {
        velocity.z = 1;
    }
    else if (key == 'a')
    {
        velocity.x = -1;
    }
    else if (key == 'd')
    {
        velocity.x = 1;
    }
    else if (key == 'e')
    {
        velocity.y = 1;
    }
    else if (key == 'q')
    {
        velocity.y = -1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == 'w' || key == 's')
    {
        velocity.z = 0;
    }
    else if (key == 'a' || key == 'd')
    {
        velocity.x = 0;
    }
    else if (key == 'e' || key == 'q')
    {
        velocity.y = 0;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    if (prevX != 0 && prevY != 0)
    {
        int dx = x - prevX;
        int dy = y - prevY;

        // Update camera rotation based on mouse movement
        updateCameraRotation(mouseSensitivity * dx, mouseSensitivity * dy);
    }

    // Remember where the mouse was this frame.
    prevX = x;
    prevY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if (prevX != 0 && prevY != 0)
    {
        int dx = x - prevX;
        int dy = y - prevY;


        if (button == 0) 
        {
            // Update camera rotation based on mouse movement
            updateModelRotation(mouseSensitivity * dx, mouseSensitivity * dy);
        }
        else if (button == 1) 
        {
            updateJointRotation(mouseSensitivity * dx, mouseSensitivity * dy);
        }
    }

    // Remember where the mouse was this frame.
    prevX = x;
    prevY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
