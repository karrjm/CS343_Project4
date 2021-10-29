#include "ofApp.h"
#include "CameraMatrices.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	//ofEnableDepthTest();

    shader.load("my.vert", "my.frag");
}

//--------------------------------------------------------------
void ofApp::update()
{
	using namespace glm;
	camera.position += mat3(rotate(cameraHead, vec3(0, 1, 0))) * velocity * ofGetLastFrameTime();
	camera.rotation = rotate(cameraHead, vec3(0, 1, 0)) * rotate(cameraPitch, vec3(1, 0, 0));
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	cameraHead += dx;
	cameraPitch += dy;

	using namespace glm;
	cameraPitch = clamp(cameraPitch, -static_cast<float>(PI) / 2, static_cast<float>(PI) / 2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;

	float width{ static_cast<float>(ofGetViewportWidth()) };
	float height{ static_cast<float>(ofGetViewportHeight()) };
	float aspect = width / height;

	CameraMatrices camMatrices{ camera, aspect, 0.01f, 10.0f, };

	mat4 model { };

	shader.begin();
	shader.setUniformMatrix4f("mvp", camMatrices.getProj() * camMatrices.getView() * model);
	shader.end();
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
        // Update camera rotation based on mouse movement
        updateCameraRotation(mouseSensitivity * (x - prevX), mouseSensitivity * (y - prevY));
    }

    // Remember where the mouse was this frame.
    prevX = x;
    prevY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
