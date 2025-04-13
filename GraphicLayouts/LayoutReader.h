// 2021 год, я в 9-ом классе
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>

class LayoutReader {
private:
	std::ifstream                            layoutFile;

	struct                                   Coordinates {
		double x = 0;
		double y = 0;
	};

	std::string								 windowName;

	int                                      lengthWin = 1600,
		heightWin = 900;
	sf::ContextSettings                      contexSettings;
	std::map <std::string, std::vector<int>> names;

	sf::RectangleShape						 rect;
	sf::ConvexShape							 convex;
	sf::CircleShape							 circle;
	sf::Text								 text;

	sf::Font font;
public:
	struct               object {
		Coordinates cords;

		sf::Color   color = sf::Color(0, 0, 0);
		sf::Color   thicknessColor = sf::Color(256, 256, 256);
		sf::Color   textColor = sf::Color(0, 0, 0);

		std::string text = "-";
		std::string name;
		std::string type = "-";
		std::string defaultText = "input";

		bool display = true;

		double		sizeX = 10;
		double		sizeY = 10;
		double		thickness = 0;
		double	    radius = 5;
		double		rotate = 0;
		double		angles = 50;
		double      characterSize = 24;

		std::vector <Coordinates> pointsCords;
	};
	std::vector <object> windowObjects;
	bool                 fileOpened = false;
	int                  fps = 120;
	std::string          path;
	sf::RenderWindow     window;
	sf::Color			 background = sf::Color(256, 256, 256);

	void openFile(std::string pathFunc);
	int findObject(std::string name = "-", int queue = 0);
	void openFont(std::string path);
	void refreshWindow();
	bool isInAreaOfObject(double x, double y, std::string name = "_", int queue = 0);

	LayoutReader(std::string pathFunc = "-");
};