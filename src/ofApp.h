#pragma once

#include "ofMain.h"
#include "Camera.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
	Camera camera;
	ofShader shader;
	int prevX{ 0 }, prevY{ 0 };
	float mouseSensitivity{ 0.01f };
	float cameraHead{ 0 };
	float cameraPitch{ 0 };
	glm::vec3 velocity{};
	void updateCameraRotation(float dx, float dy);
};
