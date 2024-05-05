#include "app_window.h"

#include "tools.h"
#include "weather.h"
// #include <format>
#include <fmt/core.h>
using namespace sf;

const float window_width = 1920;
const float window_height = 1080;

const std::string PATH_FONT = "../front_end/res/font/BlissproMedium.otf";
const std::string PATH_IMAGE =
    "../front_end/res/image/goluboj_tsvet_fon_1920x1080.jpg";

//------------------------------------------------------------------------------------------------------

//функция создания окна //нельзя возвращать и присваивать sf::RenderWindow
void create_window(sf::RenderWindow& window, const size_t window_width,
                   const size_t window_height) {
  // sf::RenderWindow window;
  window.create(sf::VideoMode(window_width, window_height), "weather_app",
                sf::Style::Default);

  //отключаем видимость курсора
  window.setMouseCursorVisible(false);

  // Размер экрана(сохраняем значения)
  auto width = static_cast<float>(VideoMode::getDesktopMode().width);
  auto height = static_cast<float>(VideoMode::getDesktopMode().height);

  // return window;
}

//функция выставления фона
// int bacbackground_set(const std::string bg_file_name, const size_t bg_width,
// const size_t bg_height)
//{
//    sf::rectangleshape background(vector2f(bg_width, bg_height));
//    //прямоугольник в размер окна
//
//    texture texture_window;          // (***)
//    if (!texture_window.loadfromfile(bg_file_name)) return 1;
//    background.settexture(&texture_window);
//}

//функция создания надписи на экране
sf::Text create_titul(const std::string titul_str,
                      const std::string font_file_name);

//функция создания меню
App::Menu create_menu(std::vector<String> menu_items_name,
                      const std::string font_file_name);

//функция бесконечного отборажения окна, пока не будет нажат ESC
void infinite_window_display(sf::RenderWindow window);

//функция перемещения по меню
void process_menu_clicks(sf::Event event, App::Menu menu);

//------------------------------------------------------------------------------------------------------

// функция настройки текста
void init_text(Text& mtext, float xpos, float ypos, const std::string& str,
               TextFormat Ftext) {
  mtext.setCharacterSize(Ftext.size_font);  //размер шрифта
  mtext.setPosition(xpos, ypos);            //положение надписи
  mtext.setString(str);  //содержание надписи
  mtext.setFillColor(Ftext.menu_text_color);  //цвет текста
  mtext.setOutlineThickness(Ftext.bord);      //толщина обводки
  mtext.setOutlineColor(Ftext.border_color);  //цвет обводки
}

// окно погоды на сегодня
void weath_today(const std::vector<Weather_info>& arr) {
  // Создаём окно nday_window
  sf::RenderWindow nday_window(VideoMode(window_width, window_height), "today",
                               sf::Style::Default);

  // Устанавливаем фон экрана меню
  sf::RectangleShape nday_background(
      Vector2f(window_width, window_height));  //прямоугольник в размер окна

  Texture texture_window;                                 // (***)
  if (!texture_window.loadFromFile(PATH_IMAGE)) exit(3);  // const str
  nday_background.setTexture(&texture_window);

  // Шрифт для названия экрана
  Font font;
  if (!font.loadFromFile(PATH_FONT)) exit(4);

  // Текст с названием экрана
  Text titul;
  titul.setFont(font);

  TextFormat Ftext;
  Ftext.size_font = 120;
  Ftext.menu_text_color = Color::White;
  Ftext.bord = 3;
  init_text(titul, 500, 50, "Weather for today", Ftext);

  // Текст с погодой
  Text weather;
  weather.setFont(font);

  TextFormat Ftext_w;
  Ftext_w.size_font = 50;
  Ftext_w.menu_text_color = Color(175, 238, 238);
  Ftext_w.bord = 3;
  init_text(weather, 100, 200, "", Ftext_w);
  std::string info1 =
      " data : " + arr[0].date.date +
      " \n tempr : " + fmt::format("{:.1f}", arr[0].temp) +
      " \n feels like : " + fmt::format("{:.1f}", arr[0].temp_feels_like) +
      " \n pressure : " + fmt::format("{:.1f}", arr[0].pressure) +
      " \n wind : " + fmt::format("{:.1f}", arr[0].wind) + "";
  weather.setLetterSpacing(2);
  weather.setOutlineColor(Color(62, 95, 138));
  weather.setString(info1);

  //--------------------------------------------------------------------------

  while (nday_window.isOpen()) {
    Event nday_event;
    while (nday_window.pollEvent(nday_event)) {
      if (nday_event.type == Event::Closed) nday_window.close();
      if (nday_event.type == Event::KeyPressed) {
        if (nday_event.key.code == Keyboard::Escape) {
          nday_window.close();
        }
      }
    }

    nday_window.clear();
    nday_window.draw(nday_background);
    nday_window.draw(titul);
    nday_window.draw(weather);
    nday_window.display();
  }
}

// окно погоды на завтра
void weath_tomorrow(const std::vector<Weather_info>& arr) {
  // Создаём окно nday_window
  sf::RenderWindow nday_window(VideoMode(window_width, window_height),
                               "tomorrow", sf::Style::Default);

  // Устанавливаем фон экрана меню
  sf::RectangleShape nday_background(
      Vector2f(window_width, window_height));  //прямоугольник в размер окна

  Texture texture_window;  // (***)
  if (!texture_window.loadFromFile(PATH_IMAGE)) exit(3);
  nday_background.setTexture(&texture_window);

  // Шрифт для названия экрана
  Font font;
  if (!font.loadFromFile(PATH_FONT)) exit(4);

  // Текст с названием экрана
  Text titul;
  titul.setFont(font);

  TextFormat Ftext;
  Ftext.size_font = 120;
  Ftext.menu_text_color = Color::White;
  Ftext.bord = 3;
  init_text(titul, 500, 50, "Weather for tomorrow", Ftext);

  while (nday_window.isOpen()) {
    Event nday_event;
    while (nday_window.pollEvent(nday_event)) {
      if (nday_event.type == Event::Closed) nday_window.close();
      if (nday_event.type == Event::KeyPressed) {
        if (nday_event.key.code == Keyboard::Escape) {
          nday_window.close();
        }
      }
    }

    nday_window.clear();
    nday_window.draw(nday_background);
    nday_window.draw(titul);
    nday_window.display();
  }
}

// окно погоды на 3 дня
void weath_3days(const std::vector<Weather_info>& arr) {
  // Создаём окно nday_window
  sf::RenderWindow nday_window(VideoMode(window_width, window_height), "3days",
                               sf::Style::Default);

  // Устанавливаем фон экрана меню
  sf::RectangleShape nday_background(
      Vector2f(window_width, window_height));  //прямоугольник в размер окна

  Texture texture_window;  // (***)
  if (!texture_window.loadFromFile(PATH_IMAGE)) exit(3);
  nday_background.setTexture(&texture_window);

  // Шрифт для названия экрана
  Font font;
  if (!font.loadFromFile(PATH_FONT)) exit(4);

  // Текст с названием экрана
  Text titul;
  titul.setFont(font);

  TextFormat Ftext;
  Ftext.size_font = 120;
  Ftext.menu_text_color = Color::White;
  Ftext.bord = 3;
  init_text(titul, 500, 50, "Weather for 3 days", Ftext);

  while (nday_window.isOpen()) {
    Event nday_event;
    while (nday_window.pollEvent(nday_event)) {
      if (nday_event.type == Event::Closed) nday_window.close();
      if (nday_event.type == Event::KeyPressed) {
        if (nday_event.key.code == Keyboard::Escape) {
          nday_window.close();
        }
      }
    }

    nday_window.clear();
    nday_window.draw(nday_background);
    nday_window.draw(titul);
    nday_window.display();
  }
}

// окно погоды на 10 дней
void weath_10days(const std::vector<Weather_info>& arr) {
  // Создаём окно nday_window
  sf::RenderWindow nday_window(VideoMode(window_width, window_height), "10days",
                               sf::Style::Default);

  // Устанавливаем фон экрана меню
  sf::RectangleShape nday_background(
      Vector2f(window_width, window_height));  //прямоугольник в размер окна

  Texture texture_window;  // (***)
  if (!texture_window.loadFromFile(PATH_IMAGE)) exit(3);
  nday_background.setTexture(&texture_window);

  // Шрифт для названия экрана
  Font font;
  if (!font.loadFromFile(PATH_FONT)) exit(4);

  // Текст с названием экрана
  Text titul;
  titul.setFont(font);

  TextFormat Ftext;
  Ftext.size_font = 120;
  Ftext.menu_text_color = Color::White;
  Ftext.bord = 3;
  init_text(titul, 500, 50, "Weather for 6 days", Ftext);

  while (nday_window.isOpen()) {
    Event nday_event;
    while (nday_window.pollEvent(nday_event)) {
      if (nday_event.type == Event::Closed) nday_window.close();
      if (nday_event.type == Event::KeyPressed) {
        if (nday_event.key.code == Keyboard::Escape) {
          nday_window.close();
        }
      }
    }

    nday_window.clear();
    nday_window.draw(nday_background);
    nday_window.draw(titul);
    nday_window.display();
  }
}