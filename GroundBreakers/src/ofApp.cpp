#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	isInMenu = true;
	level.setup(gameData.numberOfBlockInLevelRow, gameData.numberOfBlockInLevelCol);
	player.setup(&level);
	ui.setup(&player);
	isAlive = true;
	isDrawingGameOverScreen = false;
	isInMenu = true;
	tempYOffset = 0;
	musicPlayer.load("music/majula.mp3");
	musicPlayer.setVolume(0.3f);
	musicPlayer.setLoop(true);
	shadowOfMine.load("images/shadow.png");
	viewExpX = 0;
	viewExpY = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (isInMenu)
	{
		return;
	}
	// Player has died
	if (!player.isAlive)
	{
		gameOver();
	}
	// Frame rate
	/*std::cout << ofGetFrameRate() << std::endl;*/
	player.update();
	level.update();
	camera.setCameraCenter(player.x + player.size/2, player.y + player.size/2 - tempYOffset);
	if (camera.y + camera.height - tempYOffset > ofGetWindowHeight() * 0.9)
	{
		tempYOffset += camera.y + camera.height - ofGetWindowHeight() * 0.9;
	}
	// Calc left side offset
	leftSideOffset = (ofGetWindowWidth() - gameData.mineWidth*camera.zoomLevel) / 2;
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (isDrawingGameOverScreen)
	{
		drawGameOverScreen();
		return;
	}
	else if (isInMenu)
	{
		menu.draw();
		return;
	}
	ofClear(0, 0, 0);

	// Drawing methods
	level.draw(leftSideOffset, camera, tempYOffset);
	player.draw(leftSideOffset, camera, tempYOffset);

	drawShadowOfMine();
	drawBlackFilter();
	if (gameData.debugMode)
	{
		camera.draw(leftSideOffset, tempYOffset);
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(player.state, 50, 50);
	}
	ofSetColor(255, 255, 255);
	ui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (player.state != player::Standing)
	{
		return;
	}

	switch (key)
	{
	case 'w':
		player.move(player::Up);
		break;
	case 'a':
		player.move(player::Left);
		break;
	case 'd':
		player.move(player::Right);
		break;
	case 's':
		player.move(player::Down);
		break;
	case ' ':
		if (player._ladders > 0)
		{
			player.setUpLadder();
		}
	case 'e':
		if (player._pillars > 0)
		{
			player.setUpPillar();
		}
		
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (isInMenu)
	{
		int i = 0;
		while (i < menu.buttonList.size())
		{
			if (menu.buttonList[i].x <= x && x <= menu.buttonList[i].x + menu.buttonList[i].width && menu.buttonList[i].y <= y && y <= menu.buttonList[i].y + menu.buttonList[i].height) {
				menu.buttonList[i].enableDisableHighlight(true);
			}
			else
			{
				menu.buttonList[i].enableDisableHighlight(false);
			}
			i++;
		}

	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (isInMenu)
	{
		int i = 0;
		while (i < menu.buttonList.size())
		{
			if (menu.buttonList[i].x <= x && x <= menu.buttonList[i].x + menu.buttonList[i].width && menu.buttonList[i].y <= y && y <= menu.buttonList[i].y + menu.buttonList[i].height) {
				if (menu.buttonList[i].buttonName == "startGameButton")
				{
					// Start game method
					startGame();
				}
				else if (menu.buttonList[i].buttonName == "exitGameButton")
				{
					// Exit game method
					ofApp::exit();
				}
			}
			i++;
		}

	}
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



void ofApp::drawShadowOfMine() {
	shadowOfMine.draw(player.x - camera.width/2 + leftSideOffset + player.size/2 - viewExpX, player.y - camera.height/2 - tempYOffset + player.size/2 - viewExpY, camera.width + viewExpX, camera.height + viewExpY);
}

void ofApp::drawBlackFilter() {
	ofSetColor(0, 0, 0);
	//Bot
	ofRect(0, player.y - tempYOffset + player.size / 2 + camera.height/2 + viewExpY, ofGetWindowWidth(), ofGetWindowHeight());
	//Top
	ofRect(0, player.y - tempYOffset + player.size / 2 - camera.height / 2 - ofGetWindowHeight() - viewExpY, ofGetWindowWidth(), ofGetWindowHeight());
	//Left
	ofRect(0, 0, player.x + player.size/2 + leftSideOffset - camera.width/ 2 - viewExpX, ofGetWindowHeight());
	//Right
	ofRect(player.x + player.size / 2 + leftSideOffset + camera.width / 2 + viewExpX, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void ofApp::drawGameOverScreen() {
	ofSetColor(255, 255, 255, 255);
	ofClear(0, 0, 0);
	ofDrawBitmapString("Game Over", ofGetWindowWidth() / 2 - 72, ofGetWindowHeight() / 2);
}

void ofApp::gameOver() {
	isDrawingGameOverScreen = true;
	printf("You have died");
	musicPlayer.setVolume(0.1f);

	
}

void ofApp::startGame() {
	isInMenu = false;
	musicPlayer.play();
}

void ofApp::recalcView() {
	viewExpX = player.visionExpansion;
	viewExpY = viewExpX / camera._aspectRatio;
}