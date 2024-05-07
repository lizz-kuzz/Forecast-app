#include "app_menu.h"

using namespace sf;


const std::string PATH_FONT = "../front_end/res/font/BlissproMedium.otf";
const std::string PATH_FONT_1 = "../front_end/res/font/PassionOne-Regular.ttf";
//меню
App::Menu::Menu(sf::RenderWindow& window, float menux, float menuy,
                int sizeFont, int step, std::vector<std::string>& name,
                int let_space)
    : menu_X(menux),
      menu_Y(menuy),
      menu_Step(step),
      max_menu(static_cast<int>(name.size())),
      size_font(sizeFont),
      main_menu(name.size()),
      mywindow(window) {

  if (!font.loadFromFile(PATH_FONT_1)) {
    exit(32);
  }

  for (int i = 0, ypos = static_cast<int>(menu_Y); i < max_menu;
       ++i, ypos += menu_Step) {
    set_init_text(main_menu[i], name[i], menu_X, static_cast<float>(ypos),
                  let_space);  //инициальзируем пункты меню, данным
                               //масивом, сдвигаемся вниз на step
  }

  main_menu_selected = 0;
  main_menu[main_menu_selected].setFillColor(
      chose_text_color);  //выбранный пункт меню ставим в нужный цвет
}

// Настройка текста меню
void App::Menu::set_init_text(sf::Text& text, const std::string& str,
                              float xpos, float ypos, int let_space) const {
  text.setCharacterSize(size_font);    //размер шрифта
  text.setPosition(xpos, ypos);        //положение надписи
  text.setString(str);                 //содержание надписи
  text.setFillColor(menu_text_color);  //цвет текста
  text.setOutlineThickness(3);         //толщина обводки
  text.setOutlineColor(border_color);  //цвет обводки
  text.setFont(font);                  //шрифт текста
  text.setLetterSpacing(let_space);
}

// Выравнивание положения меню(согласно заданным параметрам)
// 0 - по правому краю
// 1 - по левому краю
// 2 - по центру
void App::Menu::align_menu(int posx) {
  float nullx = 0;

  for (int i = 0; i < max_menu; i++) {
    switch (posx) {
      case 0: {
        nullx = 0;
        break;
      }
      case 1: {
        nullx = main_menu[i]
                    .getLocalBounds()
                    .width;  // getLocalBounds() возвращает лину текста
        break;
      }
      case 2: {
        nullx = main_menu[i].getLocalBounds().width / 2;
        break;
      }
      default: {
        break;
      }
    }

    main_menu[i].setPosition(main_menu[i].getPosition().x - nullx,
                             main_menu[i].getPosition().y);
  }
}

// Перемещение выбора меню вверх
void App::Menu::move_up() {
  main_menu_selected--;  //уменьшаем номер выбраноого пункта

  if (main_menu_selected >= 0) {
    main_menu[main_menu_selected].setFillColor(
        chose_text_color);  //изменяется только цвет текста
    main_menu[main_menu_selected + 1].setFillColor(menu_text_color);
  } else { //уходим вниз меню
    main_menu[0].setFillColor(menu_text_color);
    main_menu_selected = max_menu - 1;
    main_menu[main_menu_selected].setFillColor(chose_text_color);
  }
}

// Перемещение выбора меню вниз
void App::Menu::move_down() {
  main_menu_selected++;  //увеличиваем номер выбраноого пункта

  if (main_menu_selected < max_menu) {
    main_menu[main_menu_selected - 1].setFillColor(menu_text_color);
    main_menu[main_menu_selected].setFillColor(chose_text_color);
  } else  //уходим на верх меню
  {
    main_menu[max_menu - 1].setFillColor(menu_text_color);
    main_menu_selected = 0;
    main_menu[main_menu_selected].setFillColor(chose_text_color);
  }
}

// Рисует меню
void App::Menu::draw() {
  //по очереди отрисовываем каждый элемент
  for (int i = 0; i < max_menu; i++) {
    mywindow.draw(main_menu[i]);
  }
}

// Изменяет цвет всех элементов меню  
void App::Menu::set_color_text_menu(const sf::Color& menColor, const sf::Color& ChoColor,
                                    const sf::Color& BordColor) {

  menu_text_color = menColor;  //цвет текста
  chose_text_color = ChoColor;  //цвет выбранного элемента меню
  border_color = BordColor;  //цвет контура

  for (int i = 0; i < max_menu; i++) {
    main_menu[i].setFillColor(menu_text_color);
    main_menu[i].setOutlineColor(border_color);
  }

  main_menu[main_menu_selected].setFillColor(chose_text_color);
}