#include "ofApp.h"
#include "FallingBallContainer.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	balls = new FallingBallContainer(2000);
	balls->setup();

	movingUp = true;
	upper = 0;
	downer = 255;
}

//--------------------------------------------------------------
void ofApp::update(){
	balls->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (upper >= 205)
	{
		movingUp = false;
	}
	if (upper <= 50)
	{
		movingUp = true;
	}

	if (movingUp)
	{
		upper++;
		downer--;
	}
	else
	{
		upper--;
		downer++;
	}

	ofSetBackgroundColor(0xFF00FF);
	//ofColor colorOne(upper, 0, 0);
	//ofColor colorTwo(0, 0, downer);
	//ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

	ofSetColor(0);

	balls->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
