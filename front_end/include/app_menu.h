#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

namespace App {

class Menu {
private:
	float menu_X;   // Координаты меню по X
	float menu_Y;   // Координаты меню по Y
	int menu_Step;  // Расстояние между пунктами меню
	int max_menu;   // Максимальное количество пунктов меню
	int size_font;           // Размер шрифта
	int main_menu_selected;  // Номер текущего пункта меню
	sf::Font font;           // Шрифт меню
	std::vector<sf::Text> main_menu;  // Динамический массив названий меню

	sf::Color menu_text_color = sf::Color::White;    // Цвет меню
	sf::Color chose_text_color = sf::Color::Yellow;  // Цвет выбора меню
	sf::Color border_color = sf::Color::White;       // Цвет обводки текста

	sf::RenderWindow& mywindow;  // Ссылка на графическое окно

	// Настройка текста меню
	void set_init_text(sf::Text& text, const std::string& str, float xpos,
						float ypos, int let_space) const;

public:
	//конструктор
	Menu(sf::RenderWindow& window, float menux, float menuy, int sizeFont,
		int step, std::vector<std::string>& name, int let_space);

	~Menu(){};  //деструктор

	//------------------------------------------------------------------------------------------------------

	void draw();  // Рисует меню

	void move_up();  // Перемещение выбора меню вверх

	void move_down();  // Перемещение выбора меню вниз

	// Изменяет цвет всех элементов меню
	void set_color_text_menu(sf::Color menColor, sf::Color ChoColor,
							sf::Color BordColor);

	void align_menu(int posx);  // Выравнивание положения меню
								// 0 - по правому краю
								// 1 - по левому краю
								// 2 - по центру

	int get_selected_menu_number() const  // Возвращает номер выбраного элемента
	{
		return main_menu_selected;
	}
};
}  // namespace App