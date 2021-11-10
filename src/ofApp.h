#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "SceneGraphNode.h"
using namespace glm;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void reloadShaders();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:
	ofShader shader;
	ofMesh robotMesh;
	ofMesh radarMesh;
	ofMesh gunMesh;
	bool needsReload = true;
	int prevX{ 0 }, prevY{ 0 };
	float mouseSensitivity{ 0.01f };
	float cameraHead{ 0 };
	float cameraPitch{ 0 };
	glm::vec3 velocity{};
	Camera camera { vec3(0,0,2) };
	SceneGraphNode sceneGraphRoot{};
	std::shared_ptr<SceneGraphNode> robotNode{};
	std::shared_ptr<SceneGraphNode> radarNode{};
	std::shared_ptr<SceneGraphNode> gunNode{};
	void updateCameraRotation(float dx, float dy);
	void updateModelRotation(float dt);
	double time { 0 };
};
