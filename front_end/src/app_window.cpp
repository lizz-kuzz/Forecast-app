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

const std::string PATH_FONT_1 = "../front_end/res/font/PassionOne-Regular.ttf";
const std::string PATH_IMAGE_1 =
    "../front_end/res/image/IMG_2439.JPG";
const std::string PATH_IMAGE_6 =
    "../front_end/res/image/IMG_20240506_214059_844.jpg";

const std::string PATH_PIC_SUN =
    "../front_end/res/image/Clipped_image_20240507_130758.png";
const std::string PATH_PIC_CLOUD =
    "../front_end/res/image/Clipped_image_20240507_130538.png";
const std::string PATH_PIC_RAIN =
    "../front_end/res/image/Clipped_image_20240507_130845.png";


//------------------------------------------------------------------------------------------------------

  std::string name_weather_pic(Weather_t weather_type)
  {
    if (weather_type == Clear_sky) return PATH_PIC_SUN;
    else if (weather_type == Rain) return PATH_PIC_RAIN;
    else return PATH_PIC_CLOUD;
  }

  sf::Sprite show_pic_weather(sf::Texture texture_pic, sf::Sprite sprite_pic, const std::string pic_name, float x_start,  float y_start, float x_scale,  float y_scale)
 {
  if (!texture_pic.loadFromFile(pic_name)) {std::cout << "Could not load enemy texture" << std::endl;}

  sprite_pic.setTexture(texture_pic);

  sprite_pic.setPosition(sf::Vector2f(x_start, y_start));
  sprite_pic.scale(sf::Vector2f(x_scale , y_scale));

  return sprite_pic;
 }

//функция создания окна //нельзя возвращать и присваивать sf::RenderWindow
void create_window(sf::RenderWindow& window, const size_t window_width,
                   const size_t window_height) {
  // sf::RenderWindow window;
  window.create(sf::VideoMode(window_width, window_height), "weather_app",
                sf::Style::Default);

  //отключаем видимость курсора
  window.setMouseCursorVisible(false);

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
  if (!texture_window.loadFromFile(PATH_IMAGE_6)) exit(3);  // const str
  nday_background.setTexture(&texture_window);

  // Шрифт для названия экрана
  Font font;
  if (!font.loadFromFile(PATH_FONT_1)) exit(4);

  // Текст с названием экрана
  Text titul;
  titul.setFont(font);

  TextFormat Ftext;
  Ftext.size_font = 150;
    Ftext.menu_text_color = Color(76, 93, 182);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);      //цвет обводки
  init_text(titul, 500, 100, "Weather for today", Ftext);


  char ascii_deg = (char)176;
  std::string degree_sign;
  degree_sign += ascii_deg;

  // Текст с погодой
  Text weather1;
  weather1.setFont(font);

  TextFormat Ftext_w;
  Ftext_w.size_font = 70;
  Ftext_w.menu_text_color =  Color(119, 132, 204);
  Ftext_w.bord = 3;
  init_text(weather1, 100, 300, "", Ftext_w);
  std::string info1 =
      " date : \n tempr, c:   \n feels like, c:   \n press, mmHg:   \n wind, m/s:  ";
  weather1.setLetterSpacing(2);
  weather1.setOutlineColor(Color(220, 224, 244));
  weather1.setString(info1);


  size_t grid_x_base = 600;
  size_t grid_x_step = 260;

  Text weather2;
  weather2.setFont(font);

  init_text(weather2, grid_x_base + grid_x_step*0 , 300, "", Ftext_w);
  std::string info2 =
      "" + arr[0].date.date +
      "\n" + fmt::format("{:.1f}", arr[0].temp) +
      "\n" + fmt::format("{:.1f}", arr[0].temp_feels_like) +
      "\n" + fmt::format("{:.0f}", arr[0].pressure/133.322*100) +
      "\n" + fmt::format("{:.1f}", arr[0].wind) + "";
  weather2.setLetterSpacing(2);
  weather2.setOutlineColor(Color(220, 224, 244));
  weather2.setString(info2);

  Text weather3;
  weather3.setFont(font);

  init_text(weather3, grid_x_base + grid_x_step*1, 300, "", Ftext_w);
  std::string info3 =
      "" + arr[1].date.date +
      "\n" + fmt::format("{:.1f}", arr[1].temp) +
      "\n" + fmt::format("{:.1f}", arr[1].temp_feels_like) +
      "\n" + fmt::format("{:.0f}", arr[1].pressure/133.322*100) +
      "\n" + fmt::format("{:.1f}", arr[1].wind) + "";
  weather3.setLetterSpacing(2);
  weather3.setOutlineColor(Color(220, 224, 244));
  weather3.setString(info3);

  Text weather4;
  weather4.setFont(font);

  init_text(weather4, grid_x_base + grid_x_step*2, 300, "", Ftext_w);
  std::string info4 =
      "" + arr[2].date.date +
      "\n" + fmt::format("{:.1f}", arr[2].temp) +
      "\n" + fmt::format("{:.1f}", arr[2].temp_feels_like) +
      "\n" + fmt::format("{:.0f}", arr[2].pressure/133.322*100) +
      "\n" + fmt::format("{:.1f}", arr[2].wind) + "";
  weather4.setLetterSpacing(2);
  weather4.setOutlineColor(Color(220, 224, 244));
  weather4.setString(info4);

  Text weather5;
  weather5.setFont(font);

  init_text(weather5, grid_x_base + grid_x_step*3, 300, "", Ftext_w);
  std::string info5 =
      "" + arr[3].date.date +
      "\n" + fmt::format("{:.1f}", arr[3].temp) +
      "\n" + fmt::format("{:.1f}", arr[3].temp_feels_like) +
      "\n" + fmt::format("{:.0f}", arr[3].pressure/133.322*100) +
      "\n" + fmt::format("{:.1f}", arr[3].wind) + "";
  weather5.setLetterSpacing(2);
  weather5.setOutlineColor(Color(220, 224, 244));
  weather5.setString(info5);

  Text weather6;
  weather6.setFont(font);

  init_text(weather6, grid_x_base + grid_x_step*4, 300, "", Ftext_w);
  std::string info6 =
      "" + arr[4].date.date +
      "\n" + fmt::format("{:.1f}", arr[4].temp) +
      "\n" + fmt::format("{:.1f}", arr[4].temp_feels_like) +
      "\n" + fmt::format("{:.0f}", arr[4].pressure/133.322*100) +
      "\n" + fmt::format("{:.1f}", arr[4].wind) + "";
  weather6.setLetterSpacing(2);
  weather6.setOutlineColor(Color(220, 224, 244));
  weather6.setString(info6);



  //------------Рисуем сетку--------------------------------------------------

  int columns = 6;
  int rows = 5;
  sf::RectangleShape grid_g[columns][rows]; //gorizontal
  sf::RectangleShape grid_v[columns][rows]; //vertical

  double start_x = 80;
  double start_y = 390;
  double step_x = 300;
  double step_y = 77;


  //--------------------------------------------------------------------------

  // sf::Texture texture_sun;
  // if (!texture_sun.loadFromFile(PATH_PIC_SUN)) {std::cout << "Could not load enemy texture" << std::endl;}
  // sf::Sprite sprite_sun;
  // sprite_sun.setTexture(texture_sun);
  // sprite_sun.setPosition(sf::Vector2f(800,100));
  // sprite_sun.scale(sf::Vector2f(0.5, 0.5));

  for(int i = 0; i <= 4; i++)
  {
    std::cout << arr[i].type << "   ";
  }
  std::cout << std::endl;

  sf::Texture texture1;
  std::string path_pic1 = name_weather_pic(arr[0].type);
  if (!texture1.loadFromFile(path_pic1)) {std::cout << "Could not load enemy texture" << std::endl;}
  sf::Sprite sprite1;
  sprite1.setTexture(texture1);
  sprite1.setPosition(sf::Vector2f(1*(step_x-40) + start_x + 270, 4*(step_y + 22) + start_y - 77));
  sprite1.scale(sf::Vector2f(0.5, 0.5));

  sf::Texture texture2;
  std::string path_pic2 = name_weather_pic(arr[1].type);
  if (!texture2.loadFromFile(path_pic2)) {std::cout << "Could not load enemy texture" << std::endl;}
  sf::Sprite sprite2;
  sprite2.setTexture(texture2);
  sprite2.setPosition(sf::Vector2f(2*(step_x-40) + start_x + 270, 4*(step_y + 22) + start_y - 77));
  sprite2.scale(sf::Vector2f(0.5, 0.5));

  sf::Texture texture3;
  std::string path_pic3 = name_weather_pic(arr[2].type);
  if (!texture3.loadFromFile(path_pic3)) {std::cout << "Could not load enemy texture" << std::endl;}
  sf::Sprite sprite3;
  sprite3.setTexture(texture3);
  sprite3.setPosition(sf::Vector2f(3*(step_x-40) + start_x + 270, 4*(step_y + 22) + start_y - 77));
  sprite3.scale(sf::Vector2f(0.5, 0.5));

  sf::Texture texture4;
  std::string path_pic4 = name_weather_pic(arr[3].type);
  if (!texture4.loadFromFile(path_pic4)) {std::cout << "Could not load enemy texture" << std::endl;}
  sf::Sprite sprite4;
  sprite4.setTexture(texture4);
  sprite4.setPosition(sf::Vector2f(4*(step_x-40) + start_x + 270, 4*(step_y + 22) + start_y - 77));
  sprite4.scale(sf::Vector2f(0.5, 0.5));

  sf::Texture texture5;
  std::string path_pic5 = name_weather_pic(arr[4].type);
  if (!texture5.loadFromFile(path_pic5)) {std::cout << "Could not load enemy texture" << std::endl;}
  sf::Sprite sprite5;
  sprite5.setTexture(texture5);
  sprite5.setPosition(sf::Vector2f(5*(step_x-40) + start_x + 270, 4*(step_y + 22) + start_y - 77));
  sprite5.scale(sf::Vector2f(0.5, 0.5));

  //--------------Рисуем картинки----------------------------------------------

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
    nday_window.draw(weather1);
    nday_window.draw(weather2);
    nday_window.draw(weather3);
    nday_window.draw(weather4);
    nday_window.draw(weather5);
    nday_window.draw(weather6);
    
    for(int i=0;i<columns;i++)
    {
      for(int j=0;j<rows;j++)
      {
        grid_g[i][j].setSize(sf::Vector2f(step_x, 0.1));
        grid_g[i][j].setOutlineThickness(4);
        grid_g[i][j].setOutlineColor(sf::Color(103, 120, 201));
        grid_g[i][j].setFillColor(sf::Color::Transparent);

        grid_g[i][j].setPosition(i*step_x + start_x - 20, j*step_y + start_y);

        nday_window.draw(grid_g[i][j]);

        if(i > 0)
        {
          grid_v[i][j].setSize(sf::Vector2f(0.1, step_y + 26));
          grid_v[i][j].setOutlineThickness(4);
          grid_v[i][j].setOutlineColor(sf::Color(103, 120, 201));
          grid_v[i][j].setFillColor(sf::Color::Transparent);

          grid_v[i][j].setPosition(i*(step_x-40) + start_x + 200, j*(step_y + 26) + start_y - 77);

          nday_window.draw(grid_v[i][j]);
        }
      }
    }    
    
    nday_window.draw(sprite1);
    nday_window.draw(sprite2);
    nday_window.draw(sprite3);
    nday_window.draw(sprite4);
    nday_window.draw(sprite5);

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

// окно погоды на 5 дней
void weath_5days(const std::vector<Weather_info>& arr) {
  // Создаём окно nday_window
  sf::RenderWindow nday_window(VideoMode(window_width, window_height), "5days",
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
  init_text(titul, 500, 50, "Weather for 5 days", Ftext);

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