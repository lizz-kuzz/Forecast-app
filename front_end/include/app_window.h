#pragma once
#include "tools.h"
#include "app_menu.h" //for create_menu
using namespace sf;

struct TextFormat
{
    int size_font = 60;                      //размер шрифта
    Color menu_text_color = Color::White;    //основной цвет букв
    float bord = 0.0f;                       //толщина границы букв
    Color border_color = Color::White;       //цвет границы букв
};

//------------------------------------------------------------------------------------------------------

//функция создания окна
void create_window(sf::RenderWindow& window, const size_t window_width, const size_t window_height);

//функция выставления фона
//int bacbackground_set(const std::string bg_file_name);

//функция создания надписи на экране
sf::Text create_titul(const std::string titul_str, const std::string font_file_name);

//функция создания меню
app::app_menu create_menu(std::vector<String> menu_items_name, const std::string font_file_name);

//функция бесконечного отборажения окна, пока не будет нажат ESC
void infinite_window_display(sf::RenderWindow window);

//функция перемещения по меню
void process_menu_clicks(sf::Event event, app::app_menu menu);

//------------------------------------------------------------------------------------------------------

// функция настройки текста
void init_text(Text& mtext, float xpos, float ypos, const std::string& str, TextFormat Ftext);

//функции вывода информации о погоде на n дней
void weath_today();   
void weath_tomorrow();
void weath_3days();
void weath_10days();