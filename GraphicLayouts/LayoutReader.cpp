// 2021 год, я в 9-ом классе
#include "LayoutReader.h"

LayoutReader::LayoutReader(std::string pathFunc) {
		if (pathFunc != "-") openFile(pathFunc);

		std::cout << "LayoutReader >> Rendering window...\n";
		window.create(sf::VideoMode(lengthWin, heightWin), windowName);
		window.setFramerateLimit(fps);
		openFont("futuralight.ttf");

		refreshWindow();
	}

void LayoutReader::openFont(std::string path) {
		if (!font.loadFromFile(path)) std::cout << "FontLoader >> load failed;\n";
		text.setFont(font);
	}

int LayoutReader::findObject(std::string name, int queue) {
		return names[name][0];
	}
	
void LayoutReader::openFile(std::string pathFunc) { // READING FILE
		std::cout << "LayoutReader >> Opening file..\n";
		path = pathFunc;
		windowName = path;
		layoutFile.open(path);
		if (!layoutFile.is_open())std::cout << "LayoutReader >> Opening failed;\n";
		else {
			std::cout << "LayoutReader >> Opening success, reading...\n";
			fileOpened = true;
			std::string buffer;
			while (!layoutFile.eof()) {

				layoutFile >> buffer;
				if (buffer == "layout") { // MAIN PART OF LAYOUT READING

					while (buffer != "/layout") {
						layoutFile >> buffer;

						if (buffer == "settings") { // SETTINGS
							while (buffer != "/settings") {
								layoutFile >> buffer;
								{ // OPTIONS
									if (buffer == "window_height") {
										layoutFile >> heightWin;
									}
									if (buffer == "window_weight") {
										layoutFile >> lengthWin;
									}
									if (buffer == "antialiasing") {
										layoutFile >> contexSettings.antialiasingLevel;
									}
									if (buffer == "background") {
										int num;
										layoutFile >> num;
										background.r = num;
										layoutFile >> num;
										background.g = num;
										layoutFile >> num;
										background.b = num;
									}
									if (buffer == "name") {
										
										layoutFile >> windowName;

									}
								} // /OPTIONS

							}
						} // /SETTINGS

						/*if (buffer == "example") {
							while (buffer != "/example") {
								layoutFile >> buffer;				IN FUTURE

							}
						}//*/

						if (buffer == "window") { // WINDOW OBJECTS
							while (buffer != "/window") {
								layoutFile >> buffer;
								{ // WIN OBJECTSS
									object shape;

									if (buffer == "convex") shape.type = "convex";
									else if (buffer == "circle") shape.type = "circle";
									else if (buffer == "rectangle") shape.type = "rectangle";
									else if (buffer == "text") shape.type = "text";
									else if (buffer == "input") shape.type = "input";
									else if (buffer == "button") shape.type = "button";


									while (buffer != '/' + shape.type && shape.type != "-") {
										layoutFile >> buffer;
										if (buffer == "name") {
											layoutFile >> shape.name;
											names[shape.name].push_back(windowObjects.size());
										}
										if (buffer == "point") {
											Coordinates cords;
											double num;
											layoutFile >> num;
											cords.x = num;
											layoutFile >> num;
											cords.y = num;
											shape.pointsCords.push_back(cords);
										}
										if (buffer == "color") {
											int num;
											layoutFile >> num;
											shape.color.r = num;
											layoutFile >> num;
											shape.color.g = num;
											layoutFile >> num;
											shape.color.b = num;
										}
										if (buffer == "thickness_color") {
											int num;
											layoutFile >> num;
											shape.thicknessColor.r = num;
											layoutFile >> num;
											shape.thicknessColor.g = num;
											layoutFile >> num;
											shape.thicknessColor.b = num;
										}
										if (buffer == "textColor") {
											int num;
											layoutFile >> num;
											shape.textColor.r = num;
											layoutFile >> num;
											shape.textColor.g = num;
											layoutFile >> num;
											shape.textColor.b = num;
										}
										if (buffer == "rotate") layoutFile >> shape.rotate;
										if (buffer == "string") std::getline(layoutFile, shape.text);
										if (buffer == "x") layoutFile >> shape.cords.x;
										if (buffer == "y") layoutFile >> shape.cords.y;
										if (buffer == "radius") layoutFile >> shape.radius;
										if (buffer == "angles") layoutFile >> shape.angles;
										if (buffer == "sizeX") layoutFile >> shape.sizeX;
										if (buffer == "sizeY") layoutFile >> shape.sizeY;
										if (buffer == "thickness") layoutFile >> shape.thickness;
										if (buffer == "size") layoutFile >> shape.characterSize;
										if (buffer == "default") layoutFile >> shape.defaultText;
										if (buffer == "display") layoutFile >> shape.display;

									}
									if (shape.type != "-") windowObjects.push_back(shape);
								} // /WIN OBJECTS
							}
						} // /WINDOW OBJECTS
					}
				} // / MAIN PART OF LAYOUT
			}

		}
	}
	
void LayoutReader::refreshWindow() { // REBUILDING WINDOW
		if (fileOpened && window.isOpen()) {
			sf::Event event;

			window.clear(background);

			for (int i = 0; i < windowObjects.size(); i++) if (windowObjects[i].display) {
				if (windowObjects[i].type == "rectangle") {
					rect.setSize(sf::Vector2f(windowObjects[i].sizeX, windowObjects[i].sizeY));
					rect.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					rect.setFillColor(windowObjects[i].color);
					rect.setRotation(windowObjects[i].rotate);
					rect.setOutlineThickness(windowObjects[i].thickness);
					rect.setOutlineColor(windowObjects[i].thicknessColor);
					window.draw(rect);
				}
				if (windowObjects[i].type == "circle") {
					circle.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					circle.setRadius(windowObjects[i].radius);
					circle.setFillColor(windowObjects[i].color);
					circle.setPointCount(windowObjects[i].angles);
					circle.setOutlineThickness(windowObjects[i].thickness);
					circle.setOutlineColor(windowObjects[i].thicknessColor);
					circle.setRotation(windowObjects[i].rotate);
					window.draw(circle);
				}
				if (windowObjects[i].type == "convex") {
					convex.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					convex.setPointCount(windowObjects[i].pointsCords.size());
					convex.setFillColor(windowObjects[i].color);
					for (int n = 0; n < windowObjects[i].pointsCords.size(); n++)
						convex.setPoint(n, sf::Vector2f(windowObjects[i].pointsCords[n].x, windowObjects[i].pointsCords[n].y));
					convex.rotate(windowObjects[i].rotate);
					convex.setOutlineThickness(windowObjects[i].thickness);
					convex.setOutlineColor(windowObjects[i].thicknessColor);
					window.draw(convex);
				}
				if (windowObjects[i].type == "text") {
					text.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					text.setFillColor(windowObjects[i].color);
					text.rotate(windowObjects[i].rotate);
					text.setString(windowObjects[i].text);
					text.setCharacterSize(windowObjects[i].characterSize);

					window.draw(text);
				}
				if (windowObjects[i].type == "input") {
					rect.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					rect.setSize(sf::Vector2f(windowObjects[i].sizeX, windowObjects[i].sizeY));
					text.setPosition(sf::Vector2f(windowObjects[i].cords.x + 1, windowObjects[i].cords.y + 1));
					text.setCharacterSize(windowObjects[i].sizeY - 5);
					rect.setFillColor(windowObjects[i].color);
					text.setFillColor(windowObjects[i].textColor);
					rect.setRotation(windowObjects[i].rotate);
					text.setRotation(windowObjects[i].rotate);
					text.setString(windowObjects[i].text);
					rect.setOutlineThickness(windowObjects[i].thickness);
					rect.setOutlineColor(windowObjects[i].thicknessColor);

					window.draw(rect);
					window.draw(text);
				}
				if (windowObjects[i].type == "button") {
					rect.setPosition(sf::Vector2f(windowObjects[i].cords.x, windowObjects[i].cords.y));
					rect.setSize(sf::Vector2f(windowObjects[i].sizeX, windowObjects[i].sizeY));
					text.setPosition(sf::Vector2f(windowObjects[i].cords.x + 1, windowObjects[i].cords.y + 1));
					text.setCharacterSize(windowObjects[i].sizeY - 5);
					rect.setFillColor(windowObjects[i].color);
					text.setFillColor(windowObjects[i].textColor);
					rect.setRotation(windowObjects[i].rotate);
					text.setRotation(windowObjects[i].rotate);
					text.setString(windowObjects[i].text);
					rect.setOutlineThickness(windowObjects[i].thickness);
					rect.setOutlineColor(windowObjects[i].thicknessColor);

					window.draw(rect);
					window.draw(text);
				}//*/
			}

			window.display();
		}
	}

bool LayoutReader::isInAreaOfObject(double x, double y, std::string name, int queue) {
		//  --  windowObjects[findObject(name, queue)]  --  our object
		object shape = windowObjects[findObject(name, queue)];
		if (shape.type == "rectangle" or shape.type == "input" or shape.type == "button") {
			if (sf::IntRect(shape.cords.x, shape.cords.y, shape.sizeX, shape.sizeY).contains(sf::Vector2i(x, y))) {
				return true;
			}
			else return false;
		}
		if (windowObjects[findObject(name, queue)].type == "circle") {
			double centerX = shape.cords.x + shape.radius, centerY = shape.cords.y + shape.radius;
			if ((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y) <= shape.radius * shape.radius) 
				return true;
			else return false;
		}
		if (shape.type == "convex") {
			/*
				shape.pointsCords[pointIndex].x or y
				Coordinates
				
				
				
			*/
			Coordinates segment[2];
			
			std::vector <Coordinates[2]> segments;

		}
	}
