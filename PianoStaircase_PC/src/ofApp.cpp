#include "ofApp.h"
#include <bitset>
#include "SerialCommOFW.h"

//--------------------------------------------------------------
void ofApp::setup(){
	serialHandler = new SerialCommOFW("COM9", 9600);

	trede1.load("Piano1.mp3");
	trede2.load("Piano2.mp3");
	trede3.load("Piano3.mp3");
	trede4.load("Piano4.mp3");
	trede5.load("Piano5.mp3");
	trede6.load("Piano6.mp3");
	trede7.load("Piano7.mp3");
	trede8.load("Piano8.mp3");

	trede1.setVolume(1);
	trede2.setVolume(1);
	trede3.setVolume(1);
	trede4.setVolume(1);
	trede5.setVolume(1);
	trede6.setVolume(1);
	trede7.setVolume(1);
	trede8.setVolume(1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	char bitInfo;
	bool succes = false;
	if (succes = serialHandler->GetAllSensorsV2(bitInfo))
	{
		std::bitset<8> x(bitInfo);
		std::cout << '\n' << "oke: " << x << '\n';
	}

	
	if (succes)
	{
		if ((bitInfo >> 0) & 1)
		{
			trede1.play();
		}
		if ((bitInfo >> 1) & 1)
		{
			trede2.play();
		}
		if ((bitInfo >> 2) & 1)
		{
			trede3.play();
		}
		if ((bitInfo >> 3) & 1)
		{
			trede4.play();
		}
		if ((bitInfo >> 4) & 1)
		{
			trede5.play();
		}
		if ((bitInfo >> 5) & 1)
		{
			trede6.play();
		}
		if ((bitInfo >> 6) & 1)
		{
			trede7.play();
		}
		if ((bitInfo >> 7) & 1)
		{
			trede8.play();
		}
	}



	//

	



	//unsigned char doody[BUFFER_SIZE];
	//if (serialHandler->ReadAll(doody))
	//{
	//	std::cout << "Dag: " << doody;
	//}
	//ofCircle(ofGetWindowHeight() / 2, ofGetWindowHeight() / 2, serialHandler->ReadAll());
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
