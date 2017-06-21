#include "ui.h"





ui::ui()
{

}


ui::~ui()
{
}

void ui::setup(player* player) {
	_player = player;
}

void ui::draw() {
	ofSetColor(255, 255, 255, 180);
	ofRect(20, 20, 100, 300);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Energy: " +boost::lexical_cast<std::string>(_player->_energy), 20, 50);
	ofDrawBitmapString("Ladders: " + boost::lexical_cast<std::string>(_player->_ladders), 20, 70);
	ofDrawBitmapString("Pillars: " + boost::lexical_cast<std::string>(_player->_pillars), 20, 90);

	ofDrawBitmapString("Silver: " + boost::lexical_cast<std::string>(_player->_resourcesVector[1]), 20, 130);
	ofDrawBitmapString("Gold: " + boost::lexical_cast<std::string>(_player->_resourcesVector[2]), 20, 150);
	ofDrawBitmapString("Diamond: " + boost::lexical_cast<std::string>(_player->_resourcesVector[3]), 20, 170);
}