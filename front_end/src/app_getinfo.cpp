#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_getinfo.h"

//константы параметров окна
extern const float window_width;
extern const float window_height;

//константы файлов фона и шрифта
extern const std::string simple_blue_bg;
extern const std::string simple_thick_font;

std::string window_choose_name()
{
    std::string user_name = "error";

    sf::RenderWindow window;
    create_window(window, window_width, window_height);   

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(Vector2f(window_width, window_height)); //прямоугольник в размер окна

    Texture texture_window;          // (***)
    if (!texture_window.loadFromFile(simple_blue_bg)) return user_name;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана 
    sf::Font font; //объект шрифт // (***)
    if (!font.loadFromFile(simple_thick_font)) return user_name;

    // Текст с названием экрана
    sf::Text titul; //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                          //размер шрифта
    Ftext.menu_text_color = Color(0, 191, 255);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(255, 255, 255);      //цвет обводки
    init_text(titul, 400, 50, "Enter your name", Ftext);     // 7000, 50 - позиция

    //------------------------------------------------------------------------------------------------------

    //рисуем рамку
	sf::RectangleShape shape(sf::Vector2f(700, 700));
    shape.setSize(sf::Vector2f(1300, 200));
    shape.setPosition(sf::Vector2f(300, 360));
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(255, 255, 255));
	shape.setFillColor(sf::Color::Transparent);

    //------------------------------------------------------------------------------------------------------


    sf::Event event;
    sf::String playerInput;

    sf::Text playerText;
    playerText.setFont(font);

    TextFormat F_ntext;
    F_ntext.size_font = 100;                          //размер шрифта
    F_ntext.menu_text_color = Color(175, 238, 238);     //цвет текста
    F_ntext.bord = 3;                                 //толщина обводки букв
    F_ntext.border_color = Color(255, 255, 255);      //цвет обводки
    init_text(playerText, 700, 400, "", F_ntext);     // 7000, 50 - позиция

    size_t name_size = 0;

    //------------------------------------------------------------------------------------------------------

    while (window.isOpen())
        {
             while(window.pollEvent(event))
                {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == Keyboard::Enter) 
                    { 
                        user_name = playerInput.toAnsiString();
                        return user_name; 
                    }
                }
                if (event.type == sf::Event::TextEntered && name_size <= MAX_NAME_SIZE)
                {
                    if(event.text.unicode < 128)
                        {
                            playerInput += event.text.unicode;
                            playerText.setString(playerInput);
                            name_size++;
                            //std::cout << playerInput.toAnsiString() << std::endl;
                        }
                }
                else if (event.type == Event::Closed || event.key.code == Keyboard::Escape) 
                { 
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

int window_main()
{
    //===============================================================================================
    //===============================================================================================

    //sf::RenderWindow create_window(size_t window_width, size_t window_height);
    // 
    // Создаём окно start_window 
    sf::RenderWindow start_window;
    create_window(start_window, window_width, window_height); 

    //start_window.create(sf::VideoMode(window_width, window_height), "weather_app", sf::Style::Default);
    //
    ////отключаем видимость курсора
    //start_window.setMouseCursorVisible(false);

    //// Размер экрана(сохраняем значения)
    //auto width = static_cast<float>(VideoMode::getDesktopMode().width);
    //auto height = static_cast<float>(VideoMode::getDesktopMode().height);

    //------------------------------------------------------------------------------------------------------
    //sf::RectangleShape bacbackground_set(const std::str bg_file_name);

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(Vector2f(window_width, window_height)); //прямоугольник в размер окна

    Texture texture_window;          // (***)
    if (!texture_window.loadFromFile(simple_blue_bg)) return 1;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------
    //sf::Text create_titul(const std::str titul_str, const std::str font_file_name);
 
    // Шрифт для названия экрана 
    sf::Font font; //объект шрифт // (***)
    if (!font.loadFromFile(simple_thick_font)) return 2;

    // Текст с названием экрана
    sf::Text titul; //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                          //размер шрифта
    Ftext.menu_text_color = Color(0, 191, 255);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(255, 255, 255);      //цвет обводки
    init_text(titul, 700, 50, "weather", Ftext);     // 7000, 50 - позиция

    //------НАСТРОЙКА МЕНЮ------------------------------------------------------------------------------------------------
    //app::app_menu create_menu(std::vector<String> menu_items_name, const std::str font_file_name);

    // Название пунктов меню
    std::vector<std::string> name_menu{ "today","tomorrow", "3 days","10 days" };

    // Создаем объект меню
    app::app_menu my_menu(start_window,150, 350, 100, 120, name_menu); //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color::White, Color(175, 238, 238), Color::White); //основной, выделяемый, обводка
    my_menu.align_menu(0);      //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ ОКНО------------------------------------------------------------------------------------------------
    //void infinite_window_display(sf::RenderWindow window);

    //окно будет открыто, пока его не закроют клавищей Escape
    while (start_window.isOpen())
    {
        sf::Event event;
        while (start_window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                //void process_menu_clicks(sf::Event event, app::app_menu menu)
                // События выбра пунктов меню
                if (event.key.code == Keyboard::Up) { my_menu.move_up(); }      // вверх
                if (event.key.code == Keyboard::Down) { my_menu.move_down(); }  // вниз
                if (event.key.code == Keyboard::Return)                         // ввод
                {
                    // Переходим на выбранный пункт меню
                    switch (my_menu.get_selected_menu_number())
                    {
                    case 0:weath_today();    break;
                    case 1:weath_tomorrow(); break;
                    case 2:weath_3days();    break;
                    case 3:weath_10days();   break;
                    default:break;
                    }
                }

            }
            else if (event.type == Event::Closed || event.key.code == Keyboard::Escape) { start_window.close(); }
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

User_city_t window_choose_city()
{
    User_city_t user_city = ERROR;


    // Создаём окно window 
    sf::RenderWindow window;
    create_window(window, window_width, window_height); 

    //------------------------------------------------------------------------------------------------------

    // Устанавливаем фон экрана меню
    sf::RectangleShape background(Vector2f(window_width, window_height)); //прямоугольник в размер окна

    Texture texture_window;          // (***)
    if (!texture_window.loadFromFile(simple_blue_bg)) return user_city;
    background.setTexture(&texture_window);

    //------------------------------------------------------------------------------------------------------

    // Шрифт для названия экрана 
    sf::Font font; //объект шрифт // (***)
    if (!font.loadFromFile(simple_thick_font)) return user_city;

    // Текст с названием экрана
    sf::Text titul; //объект заголовок
    titul.setFont(font);

    TextFormat Ftext;
    Ftext.size_font = 150;                          //размер шрифта
    Ftext.menu_text_color = Color(0, 191, 255);     //цвет текста
    Ftext.bord = 3;                                 //толщина обводки букв
    Ftext.border_color = Color(255, 255, 255);      //цвет обводки
    init_text(titul, 400, 50, "Choose your city", Ftext);     // 7000, 50 - позиция

    //------НАСТРОЙКА МЕНЮ------------------------------------------------------------------------------------------------

    // Название пунктов меню
    std::vector<std::string> name_menu{ "Moscow","StPetersburg", "Novosibirsk","Yekaterinburg","Dolgoprudny" };

    // Создаем объект меню
    app::app_menu my_menu(window,150, 350, 100, 120, name_menu); //окно, координаты, размер шрифта, шаг, массив названий

    // Установка цвета отображения меню
    my_menu.set_color_text_menu(Color::White, Color(175, 238, 238), Color::White); //основной, выделяемый, обводка
    my_menu.align_menu(0);      //выровняем меню левому краю

    //------БЕСКОНЕЧНОЕ ОКНО------------------------------------------------------------------------------------------------

    //окно будет открыто, пока его не закроют клавищей Escape
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                //void process_menu_clicks(sf::Event event, app::app_menu menu)
                // События выбра пунктов меню
                if (event.key.code == Keyboard::Up) { my_menu.move_up(); }      // вверх
                if (event.key.code == Keyboard::Down) { my_menu.move_down(); }  // вниз
                if (event.key.code == Keyboard::Return)                         // ввод
                {
                    // Переходим на выбранный пункт меню
                    switch (my_menu.get_selected_menu_number())
                    {
                    case 0: return MOSCOW;    break;
                    case 1: return STPETESBURG; break;
                    case 2: return NOVOSIBIRSK;    break;
                    case 3: return YEKATERINBURG;   break;
                    case 4: return DOLOGOPRUDNY;   break;
                    default:break;
                    }
                }

            }
            else if (event.type == Event::Closed || event.key.code == Keyboard::Escape) { window.close(); }
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
