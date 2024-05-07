#include "app_getinfo.h"

#include "weather.h"

//константы параметров окна
const float window_width = 1920;
const float window_height = 1080;

const bool NEED_CHANGE_CITY = 1;
const bool NO_NEED_CHANGE_CITY = 0;

//константы файлов фона и шрифта
const std::string simple_blue_bg =
    "../front_end/res/image/goluboj_tsvet_fon_1920x1080.jpg";
const std::string simple_thick_font =
    "../front_end/res/font/BlissproMedium.otf";

const std::string PATH_FONT_1 = "../front_end/res/font/PassionOne-Regular.ttf";
const std::string PATH_IMAGE_1 =
    "../front_end/res/image/IMG_2439.JPG";
const std::string PATH_IMAGE_2 =
    "../front_end/res/image/IMG_2441.JPG";
const std::string PATH_IMAGE_3 =
    "../front_end/res/image/IMG_2452.JPG";
const std::string PATH_IMAGE_4 =
    "../front_end/res/image/IMG_20240506_150214_141.jpg";
const std::string PATH_IMAGE_5 =
    "../front_end/res/image/IMG_2442.jpg";
const std::string PATH_IMAGE_6 =
    "../front_end/res/image/IMG_20240506_214059_844.jpg";
const std::string PATH_IMAGE_7 =
    "../front_end/res/image/SL-042221-42420-04.jpg";

const size_t MAX_NAME_SIZE = 25;

//--------------------------------------------------------------------------------------------------

User_mode_t window_choose_mode() {
    User_mode_t user_mode = MODE_AUTHORIZATION;

    // Создаём окно window
    sf::RenderWindow window;
    create_window(window, window_width, window_height);

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_1)) return user_mode;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return user_mode;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                          //размер шрифта
    Ftext.menu_text_color = Color(76, 93, 182);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);      //цвет обводки
    init_text(titul, 500, 100, "          Hello! \n    Choose mode", Ftext);  // 7000, 50 - позиция

    //------НАСТРОЙКА
    //МЕНЮ------------------------------------------------------------------------------------------------

    // Название пунктов меню
    std::vector<std::string> name_menu{"  log in", " sign up"};

    // Создаем объект меню
    App::Menu my_menu(
        window, 720, 490, 180, 190,
        name_menu, 1);  //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color(220, 224, 244), Color(119, 132, 204),
                                Color(220, 224, 244));  //основной, выделяемый, обводка
    my_menu.align_menu(0);  //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ
    //ОКНО------------------------------------------------------------------------------------------------

    //окно будет открыто, пока его не закроют клавищей Escape
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                // void process_menu_clicks(sf::Event event, App::Menu menu)
                //  События выбра пунктов меню
                if (event.key.code == Keyboard::Up) {
                    my_menu.move_up();
                }  // вверх
                if (event.key.code == Keyboard::Down) {
                    my_menu.move_down();
                }                                        // вниз
                if (event.key.code == Keyboard::Return) { //ввод
                // Переходим на выбранный пункт меню
                    switch (my_menu.get_selected_menu_number()) {
                        case 0: {
                            return MODE_AUTHORIZATION;
                            break;  // Authorization
                        }
                        case 1: {
                            return MODE_REGISTRATION;
                            break;  // Registration
                        }
                        default: {
                            break;
                        }
                    }
                }

            } else if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Отрисовка всех объектов
        window.clear();

        window.draw(background);
        window.draw(titul);
        my_menu.draw();

        window.display();
    }

    return user_mode;
}

std::string window_choose_name() {
    std::string user_name = "error";

    sf::RenderWindow window;
    create_window(window, window_width, window_height);

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_2)) return user_name;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return user_name;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                       //размер шрифта
    Ftext.menu_text_color = sf::Color(76, 93, 182);  //цвет текста
    Ftext.bord = 3;  //толщина обводки букв
    Ftext.border_color = sf::Color(242, 237, 253);  //цвет обводки
    init_text(titul, 500, 300, "Enter your name", Ftext);  // 7000, 50 - позиция

    //------------------------------------------------------------------------------------------------------

    //рисуем рамку
    sf::RectangleShape shape(sf::Vector2f(700, 700));
    shape.setSize(sf::Vector2f(1300, 200));
    shape.setPosition(sf::Vector2f(310, 650));
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color(103, 120, 201));
    shape.setFillColor(sf::Color(242, 237, 253));

    //------------------------------------------------------------------------------------------------------

    sf::Event event;
    sf::String playerInput;

    sf::Text playerText;
    playerText.setFont(font);

    TextFormat F_ntext;
    F_ntext.size_font = 100;                        //размер шрифта
    F_ntext.menu_text_color = sf::Color(119, 132, 204); //цвет текста
    F_ntext.bord = 3;                               //толщина обводки букв
    F_ntext.border_color = sf::Color(242, 237, 253);    //цвет обводки
    init_text(playerText, 360, 690, "", F_ntext);   // 7000, 50 - позиция

    size_t name_size = 0;

    //------------------------------------------------------------------------------------------------------

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Enter) {
                    user_name = playerInput.toAnsiString();
                    return user_name;
                } 
                if (event.key.code == Keyboard::BackSpace && name_size >= 2) {
                    playerInput.erase(name_size-2, 2);
                    //  -= event.text.unicode;
                    playerText.setString(playerInput);
                    name_size -= 2;
                }
            }
            if (event.type == sf::Event::TextEntered && name_size <= MAX_NAME_SIZE) {
                if (event.text.unicode < 128) {
                    playerInput += event.text.unicode;
                    playerText.setString(playerInput);
                    ++name_size;
                    // std::cout << playerInput.toAnsiString() << std::endl;
                }

            } else if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                window.close();
                user_name = playerInput.toAnsiString();
                return user_name;
            }
            window.draw(playerText);
        }

        window.clear();

        window.draw(background);
        window.draw(shape);
        window.draw(titul);
        window.draw(playerText);

        window.display();
    }

    user_name = playerInput.toAnsiString();
    return user_name;
}

int window_name_error(const std::string error_text)
{
    // Создаём окно window
    sf::RenderWindow window;
    create_window(window, window_width, window_height);

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_7)) return 2;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return 2;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                          //размер шрифта
    Ftext.menu_text_color = Color(234, 97, 77);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);      //цвет обводки
    init_text(titul, 800, 100, "Sorry!", Ftext);    // 7000, 50 - позиция

    // Текст с ошибкой
    sf::Text error_message;  //объект заголовок
    error_message.setFont(font);

    TextFormat Ftext_e;
    Ftext_e.size_font = 100;                          //размер шрифта
    Ftext_e.menu_text_color = Color(119, 132, 204);   //цвет текста
    Ftext_e.bord = 3;                                 //толщина обводки букв
    Ftext_e.border_color = Color(220, 224, 244);      //цвет обводки
    init_text(error_message, 550, 350, error_text + "\n\n       Please put ESC \n\n       and try again", Ftext_e);    // 7000, 50 - позиция


    //------БЕСКОНЕЧНОЕ
    //ОКНО------------------------------------------------------------------------------------------------

    //окно будет открыто, пока его не закроют клавищей Escape
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Отрисовка всех объектов
        window.clear();

        window.draw(background);
        window.draw(titul);
        window.draw(error_message);

        window.display();
    }   
}

User_city_t window_choose_city() {
    User_city_t user_city = DEFAULT;

    // Создаём окно window
    sf::RenderWindow window;
    create_window(window, window_width, window_height);

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_3)) return user_city;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return user_city;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                      //размер шрифта
    Ftext.menu_text_color = Color(76, 93, 182); //цвет текста
    Ftext.bord = 3;                             //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);  //цвет обводки
    init_text(titul, 500, 100, "Choose your city", Ftext);  // 7000, 50 - позиция

    //------НАСТРОЙКА
    //МЕНЮ------------------------------------------------------------------------------------------------

    // Название пунктов меню
    std::vector<std::string> name_menu{"Moscow", "St.Petersburg", "Novosibirsk",
                                        "Yekaterinburg", "Dolgoprudny"};

    // Создаем объект меню
    App::Menu my_menu(
        window, 950, 300, 100, 120,
        name_menu, 2);  //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color(220, 224, 244), Color(119, 132, 204),
                                Color(220, 224, 244));  //основной, выделяемый, обводка
    my_menu.align_menu(2);  //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ
    //ОКНО------------------------------------------------------------------------------------------------

    //окно будет открыто, пока его не закроют клавищей Escape
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                // void process_menu_clicks(sf::Event event, App::Menu menu)
                //  События выбра пунктов меню
                if (event.key.code == Keyboard::Up) {
                    my_menu.move_up();
                }  // вверх
                if (event.key.code == Keyboard::Down) {
                    my_menu.move_down();
                }                                        // вниз
                if (event.key.code == Keyboard::Return) { // ввод
                // Переходим на выбранный пункт меню
                    switch (my_menu.get_selected_menu_number()) {
                        case 0: {
                            return MOSCOW;
                        }
                        case 1: {
                            return STPETESBURG;
                        }
                        case 2: {
                            return NOVOSIBIRSK;
                        }
                        case 3: {
                            return YEKATERINBURG;
                        }
                        case 4: {
                            return DOLOGOPRUDNY;
                        }
                        default: {
                            break;
                        }
                    }
                }

            } else if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Отрисовка всех объектов
        window.clear();

        window.draw(background);
        window.draw(titul);
        my_menu.draw();

        window.display();
    }

    return user_city;
}

size_t window_show_city(User_city_t user_city) {
    size_t change_city = NO_NEED_CHANGE_CITY;

    // Создаём окно window
    sf::RenderWindow window;
    create_window(window, window_width, window_height);

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_4)) return change_city;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return change_city;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                      //размер шрифта
    Ftext.menu_text_color = Color(76, 93, 182);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);      //цвет обводки
    init_text(titul, 650, 160, "Your city is:", Ftext);  // 7000, 50 - позиция

    //------ВЫВОД ГОРОДА
    //ПОЛЬЗОВАТЕЛЯ------------------------------------------------------------------------------------

    std::string city_name;

    switch (user_city) {
        case MOSCOW: {
            city_name = "Moscow";
            break;
        }
        case STPETESBURG: {
            city_name = "St.Petersburg";
            break;
        }
        case NOVOSIBIRSK: {
            city_name = "Novosibirsk";
            break;
        }
        case YEKATERINBURG: {
            city_name = "Yekaterinburg";
            break;
        }
        case DOLOGOPRUDNY: {
            city_name = "Dolgoprudny";
            break;
        }
        default: {
            break;
        }
    }

    sf::Text text_city_name;  //объект заголовок
    text_city_name.setFont(font);

    TextFormat City_Ftext;
    City_Ftext.size_font = 100;  //размер шрифта
    City_Ftext.menu_text_color = Color(119, 132, 204);  //цвет текста
    City_Ftext.bord = 3;  //толщина обводки букв
    City_Ftext.border_color = Color(220, 224, 244);  //цвет обводки
    init_text(text_city_name, 700, 420, city_name,
                City_Ftext);  // 7000, 50 - позиция

    //рисуем рамку
    sf::RectangleShape shape(sf::Vector2f(700, 700));
    shape.setSize(sf::Vector2f(700, 150));
    shape.setPosition(sf::Vector2f(620, 420));
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color(103, 120, 201));
    shape.setFillColor(sf::Color(216, 213, 249));

    //------НАСТРОЙКА
    //МЕНЮ------------------------------------------------------------------------------------------------

    sf::Text question_change_city;  //объект заголовок
    question_change_city.setFont(font);
    init_text(question_change_city, 500, 540, "Change your city?",
                Ftext);  // 7000, 50 - позиция

    // Название пунктов меню
    std::vector<std::string> name_menu{"Yes", "No"};

    // Создаем объект меню
    App::Menu my_menu(
        window, 960, 720, 120, 120,
        name_menu, 2);  //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color(220, 224, 244), Color(119, 132, 204),
                                Color(220, 224, 244));  //основной, выделяемый, обводка
    my_menu.align_menu(2);  //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ
    //ОКНО------------------------------------------------------------------------------------------------

    //окно будет открыто, пока его не закроют клавищей Escape
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                // void process_menu_clicks(sf::Event event, App::Menu menu)
                //  События выбра пунктов меню
                if (event.key.code == Keyboard::Up) {
                    my_menu.move_up();
                }  // вверх
                if (event.key.code == Keyboard::Down) {
                    my_menu.move_down();
                }                                        // вниз
                if (event.key.code == Keyboard::Return) {// ввод
                // Переходим на выбранный пункт меню
                    switch (my_menu.get_selected_menu_number()) {
                        case 0: {
                            return NEED_CHANGE_CITY;
                        }
                        case 1: {
                            return NO_NEED_CHANGE_CITY;
                        }
                        default: {
                            break;
                        }
                    }
                }

            } else if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Отрисовка всех объектов
        window.clear();

        window.draw(background);
        window.draw(titul);
  
        window.draw(question_change_city);
        window.draw(shape);
        window.draw(text_city_name);
        my_menu.draw();

        window.display();
    }

    return change_city;
}

int window_main(const std::vector<Weather_info>& arr) {
    //===============================================================================================
    //===============================================================================================

    // sf::RenderWindow create_window(size_t window_width, size_t window_height);
    //
    //  Создаём окно start_window
    sf::RenderWindow start_window;
    create_window(start_window, window_width, window_height);

    // start_window.create(sf::VideoMode(window_width, window_height),
    // "weather_app", sf::Style::Default);
    //
    ////отключаем видимость курсора
    // start_window.setMouseCursorVisible(false);

    //// Размер экрана(сохраняем значения)
    // auto width = static_cast<float>(VideoMode::getDesktopMode().width);
    // auto height = static_cast<float>(VideoMode::getDesktopMode().height);

    //------------------------------------------------------------------------------------------------------
    // sf::RectangleShape bacbackground_set(const std::str bg_file_name);

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(
        Vector2f(window_width, window_height));  //прямоугольник в размер окна

    Texture texture_window;  // (***)
    if (!texture_window.loadFromFile(PATH_IMAGE_5)) return 1;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------
    // sf::Text create_titul(const std::str titul_str, const std::str
    // font_file_name);

    // Шрифт для названия экрана
    sf::Font font;  //объект шрифт // (***)
    if (!font.loadFromFile(PATH_FONT_1)) return 2;

    // Текст с названием экрана
    sf::Text titul;  //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 250;                      //размер шрифта
    Ftext.menu_text_color = Color(76, 93, 182);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(220, 224, 244);      //цвет обводки
    init_text(titul, 560, 100, "Weather", Ftext);  // 7000, 50 - позиция

    //------НАСТРОЙКА
    //МЕНЮ------------------------------------------------------------------------------------------------
    // App::Menu create_menu(std::vector<String> menu_items_name, const std::str
    // font_file_name);

    // Название пунктов меню
    std::vector<std::string> name_menu{"today", "tomorrow", "3 days", "5 days"};

    // Создаем объект меню
    App::Menu my_menu(
        start_window, 950, 400, 140, 120,
        name_menu, 2);  //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color(220, 224, 244), Color(119, 132, 204),
                                Color(220, 224, 244));  //основной, выделяемый, обводка
    my_menu.align_menu(2);  //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ
    //ОКНО------------------------------------------------------------------------------------------------
    // void infinite_window_display(sf::RenderWindow window);

    //окно будет открыто, пока его не закроют клавищей Escape
    while (start_window.isOpen()) {
        sf::Event event;
        while (start_window.pollEvent(event)) {
            if (event.type == Event::KeyReleased) {
                // void process_menu_clicks(sf::Event event, App::Menu menu)
                //  События выбра пунктов меню
                if (event.key.code == Keyboard::Up) {
                    my_menu.move_up();
                }  // вверх
                if (event.key.code == Keyboard::Down) {
                    my_menu.move_down();
                }                                        // вниз
                if (event.key.code == Keyboard::Return) { // ввод
                // Переходим на выбранный пункт меню
                switch (my_menu.get_selected_menu_number()) {
                    case 0: {
                        weath_today(arr);
                        break;
                    }
                    case 1: {
                        weath_tomorrow(arr);
                        break;
                    }
                    case 2: {
                        weath_3days(arr);
                        break;
                    }
                    case 3: {
                        weath_5days(arr);
                        break;
                    }
                    default: {
                        break;
                    }
                }
                }

            } else if (event.type == Event::Closed ||
                        event.key.code == Keyboard::Escape) {
                start_window.close();
            }
        }

        // Отрисовка всех объектов
        start_window.clear();

        start_window.draw(background);
        start_window.draw(titul);
        my_menu.draw();

        start_window.display();
    }

    return 0;
}
