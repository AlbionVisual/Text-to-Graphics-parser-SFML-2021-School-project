// 2021 год, я в 9-ом классе
#include <iostream>
#include "LayoutReader.h"

void command();

int step = 1;
bool presing[4] = { false, false, false, false };
bool entering[3] = { false, false , false};
int clr = 120;
std::string str = "";
std::string object = "triangle";

int main() {
	
	LayoutReader lay("layout.txt");
	
	lay.refreshWindow();

	

	while (lay.window.isOpen()) {
		sf::Event event;
		while (lay.window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) lay.window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) lay.window.close();
				//if (event.key.code == sf::Keyboard::P) system("pause");
				//if (event.key.code == sf::Keyboard::C) command();
				if (event.key.code == sf::Keyboard::Backspace && str.size() >= 1) str = str.substr(0, str.size() - 1);
			}

			//Inputs
			{
				for (int i = 1; i <= 2; i++)
					if (event.type == sf::Event::TextEntered) {
						if (entering[i]) {
							if (event.text.unicode != 8)
								str = str + static_cast<char>(event.text.unicode);
							lay.windowObjects[lay.findObject("input" + std::to_string(i))].text = str;
						}
					}

				for (int i = 1; i <= 2; i++) {
					if (event.type == sf::Event::MouseButtonPressed && lay.windowObjects[lay.findObject("inCheck" + std::to_string(i))].display) {
						if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "input" + std::to_string(i))) {
							lay.windowObjects[lay.findObject("input" + std::to_string(i))].color = sf::Color(180, 180, 180);
							entering[i] = true;
							str = lay.windowObjects[lay.findObject("input" + std::to_string(i))].text;
						}
						else {
							lay.windowObjects[lay.findObject("input" + std::to_string(i))].color = sf::Color(200, 200, 200);
							entering[i] = false;
						}
					}
				}
			}
			//CheckButtons
			{
				for (int i = 1; i <= 2; i++) {
					if (event.type == sf::Event::MouseMoved) {
						if (lay.isInAreaOfObject(event.mouseMove.x, event.mouseMove.y, "checkButton" + std::to_string(i)) && lay.windowObjects[lay.findObject("checkButton" + std::to_string(i))].color != sf::Color(120, 120, 120)) {
							lay.windowObjects[lay.findObject("checkButton" + std::to_string(i))].color = sf::Color(180, 180, 180);
						}
						else if(lay.windowObjects[lay.findObject("checkButton" + std::to_string(i))].color != sf::Color(120, 120, 120)) lay.windowObjects[lay.findObject("checkButton" + std::to_string(i))].color = sf::Color(200, 200, 200);
					}
					if (event.type == sf::Event::MouseButtonPressed) {
						if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "checkButton" + std::to_string(i))) {
							lay.windowObjects[lay.findObject("checkButton" + std::to_string(i))].color = sf::Color(120, 120, 120);
							if (lay.windowObjects[lay.findObject("inCheck" + std::to_string(i))].display) {
								lay.windowObjects[lay.findObject("inCheck" + std::to_string(i))].display = false;
								lay.windowObjects[lay.findObject("input" + std::to_string(i))].color = sf::Color(120, 120, 120);
								entering[i] = false;
							}
							else {
								lay.windowObjects[lay.findObject("inCheck" + std::to_string(i))].display = true;
								lay.windowObjects[lay.findObject("input" + std::to_string(i))].color = sf::Color(200, 200, 200);
							}
						}
					}
				}
			}
			//Buttons
			{
				for (int i = 1; i <= 2; i++) {
					if (event.type == sf::Event::MouseMoved) {
						if (lay.isInAreaOfObject(event.mouseMove.x, event.mouseMove.y, "button" + std::to_string(i)) && lay.windowObjects[lay.findObject("button" + std::to_string(i))].color == sf::Color(120, 120, 120)) {
							lay.windowObjects[lay.findObject("button" + std::to_string(i))].color = sf::Color(150, 150, 150);
						}
						else if(lay.windowObjects[lay.findObject("button" + std::to_string(i))].color == sf::Color(120, 120, 120)) lay.windowObjects[lay.findObject("button" + std::to_string(i))].color = sf::Color(180, 180, 180);
					}
					if (event.type == sf::Event::MouseButtonPressed) {
						if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "button" + std::to_string(i))) {
							lay.windowObjects[lay.findObject("button" + std::to_string(i))].color = sf::Color(120, 120, 120);
						}
					}
					if (event.type == sf::Event::MouseButtonReleased) {
						if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "button" + std::to_string(i))) {
							lay.windowObjects[lay.findObject("button" + std::to_string(i))].color = sf::Color(150, 150, 150);
						}
						else lay.windowObjects[lay.findObject("button" + std::to_string(i))].color = sf::Color(180, 180, 180);
						if (lay.windowObjects[lay.findObject("button" + std::to_string(i))].color == sf::Color(120, 120, 120)) {
							//something doing
						}
					}
				}
			}

		}
		lay.refreshWindow();
		
	}

    
	return 0;
}

void command() {
	std::string buffer = "-";
	while (buffer != "continue") {
		std::cin >> buffer;
		if (buffer == "step") std::cin >> step;
		if (buffer == "object") std::cin >> object;
		if (buffer == "clr") std::cin >> clr;
	}
};


/*			if (event.type == sf::Event::KeyPressed) {	
				if (event.key.code == sf::Keyboard::Backspace && str.size() >= 2) str = str.substr(0, str.size() - 2);
			}
			if (event.type == sf::Event::TextEntered) {
				if (entering) {
					str = str + static_cast<char>(event.text.unicode);
					lay.windowObjects[lay.findObject("input1")].text = str;
				}
			}
			

			if (event.type == sf::Event::MouseMoved) {
				if (lay.isInAreaOfObject(event.mouseMove.x, event.mouseMove.y, "button1")) {
					lay.windowObjects[lay.findObject("button1")].color = sf::Color(150, 150, 150);
				} else lay.windowObjects[lay.findObject("button1")].color = sf::Color(180, 180, 180);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "button1")) {
					lay.windowObjects[lay.findObject("button1")].color = sf::Color(120, 120, 120);
					lay.background = sf::Color(clr, clr, clr);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "button1")) {
					lay.windowObjects[lay.findObject("button1")].color = sf::Color(150, 150, 150);
				} else lay.windowObjects[lay.findObject("button1")].color = sf::Color(180, 180, 180);
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (lay.isInAreaOfObject(event.mouseButton.x, event.mouseButton.y, "input1")) {
					lay.windowObjects[lay.findObject("input1")].color = sf::Color(180, 180, 180);
					entering = true;
				}
				else {
					lay.windowObjects[lay.findObject("input1")].color = sf::Color(200, 200, 200);
					entering = false;
					if (str != "") {
						clr = std::stoi(str);
						str = "";
					}
				}
			}*/
