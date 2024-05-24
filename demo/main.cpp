#include <iostream>
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

// FOR CROSS COMPILING
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include "UI.hh"
#include "Translator.hh"
#include "EventEnum.hh"

// State machine enums
enum ProgramState {
    STARTUP,
    PROCESSING,
    HELP,
    ERROR,
    SUCCESS
};

// Main menu class
class Menu {
public:
    // Constructor
    Menu(float width, float height);
    // Render window
    void draw(sf::RenderWindow &window);
    // Move selectred menu option up
    void moveUp();
    // Move selectred menu option down
    void moveDown();
    // Get the index of the selected menu item (SFML::Text)
    int getSelectedIndex() { return selectedIndex; }

    // List of menu item names
    std::vector<sf::Text> menuItems;
    // Font to use
    sf::Font font;
    // Index currently selected by the user
    int selectedIndex;

private:
    sf::Text title;
};

// Init main menu
Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/arial/arial.ttf")) {
        // Handle error if font load fails
    }

    // Initialize title
    title.setFont(font);
    title.setFillColor(sf::Color::Yellow);
    title.setString("Use My Assembler (USA)");
    // title.setCharacterSize(50);
    title.setCharacterSize(100);
    title.setPosition(sf::Vector2f(width / 2 - title.getGlobalBounds().width / 2, height / 8));


    // Add items to the main menu
    std::string items[] = {"Run", "Options", "Help", "Exit"};
    for (size_t i = 0; i < sizeof(items)/sizeof(items[0]); ++i) {
        sf::Text text;
        text.setFont(font);
        // Make first option selected by default and make it blue
        text.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::White);
        text.setString(items[i]);
        // text.setCharacterSize(30);  // Set character size for menu items
        text.setCharacterSize(60);  // Set character size for menu items
        // text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, height / 4 + (i + 1) * 50));
        text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, height / 4 + (i + 1) * 100));
        menuItems.push_back(text);
    }

    selectedIndex = 0;
}

// Render all Main Menu items
void Menu::draw(sf::RenderWindow &window) {
    window.draw(title);
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

// Move selected option up (does not wrap)
void Menu::moveUp() {
    if (selectedIndex - 1 >= 0) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(sf::Color::Blue);
    }
}

// Move selected option down (does not wrap)
void Menu::moveDown() {
    if (selectedIndex + 1 < menuItems.size()) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(sf::Color::Blue);
    }
}

// Show Help window
void showHelp(sf::RenderWindow &window, sf::Font &font) {
    // Load help background texture
    sf::Texture helpBackgroundTexture;
    if (!helpBackgroundTexture.loadFromFile("assets/Among_Us_American_theme.jpeg")) {
        std::cerr << "Error loading help_background.jpg" << std::endl;
        return;
    }

    // Create help background sprite
    sf::Sprite helpBackgroundSprite;
    helpBackgroundSprite.setTexture(helpBackgroundTexture);

    // Scale the background sprite to fill the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = helpBackgroundTexture.getSize();
    helpBackgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    // Create help text
    sf::Text helpText;
    helpText.setFont(font);
    helpText.setFillColor(sf::Color::White);

    // Descriptive help text
    std::string helpMessage =
        "-------------------------------------------------------------\n"
        "----------------------------- HELP ---------------------------\n"
        "-------------------------------------------------------------\n"
        "Welcome to Use My Assembler (USA)! This program assembles source code\n"
        "from an assembly language file into a machine code output file.\n\n"
        "To use this assembler, input the following into the command line:\n"
        "    ./assemble <INPUT_FILE> <OUTPUT_FILE>\n\n"
        "MAIN MENU OPTIONS:\n"
        "Run: Processes the input assembly file and generates the output file.\n"
        "Options: Allows you to set the input and output file paths.\n"
        "Help: Displays this help screen.\n"
        "Exit: Closes the application.\n\n"
        "Press any key or click the mouse to return to the main menu.";
    helpText.setString(helpMessage);

    // Set character size based on window size
    helpText.setCharacterSize(windowSize.y / 30); // Adjust this value for larger or smaller text

    // Center the help text
    sf::FloatRect textRect = helpText.getLocalBounds();
    helpText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    helpText.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) {
                return;
            }
        }

        window.clear();
        window.draw(helpBackgroundSprite);
        window.draw(helpText);
        window.display();
    }
}

// Show the results after loading
void showMessage(sf::RenderWindow &window, sf::Font &font, const std::string &message, const std::string &backgroundImage) {
    // Load message background texture
    sf::Texture messageBackgroundTexture;
    if (!messageBackgroundTexture.loadFromFile(backgroundImage)) {
        std::cerr << "Error loading " << backgroundImage << std::endl;
        return;
    }

    // Create message background sprite
    sf::Sprite messageBackgroundSprite;
    messageBackgroundSprite.setTexture(messageBackgroundTexture);

    // Scale the help background sprite to fit the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = messageBackgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    messageBackgroundSprite.setScale(scaleX, scaleY);

    // Create message text
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setFillColor(sf::Color::White);
    messageText.setString(message);
    messageText.setCharacterSize(24);
    messageText.setPosition(50, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) {
                return;
            }
        }

        window.clear();
        window.draw(messageBackgroundSprite);
        window.draw(messageText);
        window.display();
    }
}

// Show loading screen while loading
void showLoadingScreen(sf::RenderWindow &window, sf::Font &font, Translator &translator) {
    // Load loading background texture
    sf::Texture loadingBackgroundTexture;
    if (!loadingBackgroundTexture.loadFromFile("assets/MUSH3.jpg")) {
        std::cerr << "Error loading loading_background.jpg" << std::endl;
        return;
    }

    // Create loading background sprite
    sf::Sprite loadingBackgroundSprite;
    loadingBackgroundSprite.setTexture(loadingBackgroundTexture);

    // Scale the help background sprite to fit the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = loadingBackgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    loadingBackgroundSprite.setScale(scaleX, scaleY);

    // Display loading screen
    window.clear();
    window.draw(loadingBackgroundSprite);
    window.display();

    // Running translator code
    std::string resulting_message;
    if (translator.define_lines(translator.get_input_file_path()) == EventEnum::SUCCESS) {
        if (translator.first_pass() == EventEnum::SUCCESS) {
            if (translator.second_pass() ==  EventEnum::SUCCESS) {
                resulting_message = "Translator code has finished running successfully!";
            }
            else {
                resulting_message = translator.get_error_message();
            }
            
        } else {
            resulting_message = translator.get_error_message();
        }
    }
    else {
        resulting_message = translator.get_error_message();
    }

    // THE LINE BELOW IS A DELAY
    // std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate delay

    // Show message screen after loading
    resulting_message.append("\nPress any key or click the mouse to return to the main menu.");
    showMessage(window, font, resulting_message, "assets/smileyface.png");
    //OLD DEFAULT: "Translator code has finished running.\nPress any key or click the mouse to return to the main menu."
}

// Show options menu
void showOptions(sf::RenderWindow &window, sf::Font &font, Translator &translator) {
    // Get window dimensions
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // Load options background texture
    sf::Texture optionsBackgroundTexture;
    if (!optionsBackgroundTexture.loadFromFile("assets/Darker_industrial_vintage_scene_for_white_text_overlay.jpg")) {
        std::cerr << "Error loading options_background.jpg" << std::endl;
        return;
    }

    // Create options background sprite
    sf::Sprite optionsBackgroundSprite;
    optionsBackgroundSprite.setTexture(optionsBackgroundTexture);

    // Scale the background to fit the window
    optionsBackgroundSprite.setScale(windowWidth / optionsBackgroundTexture.getSize().x, windowHeight / optionsBackgroundTexture.getSize().y);

    // Calculate positions and sizes based on window dimensions
    float boxWidth = windowWidth * 0.6f;
    float boxHeight = windowHeight * 0.05f;
    float labelCharacterSize = windowHeight * 0.04f;
    float buttonCharacterSize = windowHeight * 0.04f;
    float spacing = windowHeight * 0.02f;
    float buttonWidth = windowWidth * 0.1f;
    float buttonHeight = windowHeight * 0.05f;

    // Create input boxes and labels
    sf::Text assemblyLabel("Enter assembly file path:", font, labelCharacterSize);
    assemblyLabel.setPosition((windowWidth - boxWidth) / 2, windowHeight * 0.2f);
    sf::RectangleShape assemblyBox(sf::Vector2f(boxWidth, boxHeight));
    assemblyBox.setPosition((windowWidth - boxWidth) / 2, assemblyLabel.getPosition().y + labelCharacterSize + spacing);
    assemblyBox.setFillColor(sf::Color::White);
    sf::Text assemblyText("", font, labelCharacterSize);
    assemblyText.setPosition(assemblyBox.getPosition().x + 5, assemblyBox.getPosition().y + (boxHeight - labelCharacterSize) / 2);
    assemblyText.setFillColor(sf::Color::Black);

    sf::Text outputLabel("Enter output file path:", font, labelCharacterSize);
    outputLabel.setPosition((windowWidth - boxWidth) / 2, assemblyBox.getPosition().y + boxHeight + 2 * spacing + labelCharacterSize);
    sf::RectangleShape outputBox(sf::Vector2f(boxWidth, boxHeight));
    outputBox.setPosition((windowWidth - boxWidth) / 2, outputLabel.getPosition().y + labelCharacterSize + spacing);
    outputBox.setFillColor(sf::Color::White);
    sf::Text outputText("", font, labelCharacterSize);
    outputText.setPosition(outputBox.getPosition().x + 5, outputBox.getPosition().y + (boxHeight - labelCharacterSize) / 2);
    outputText.setFillColor(sf::Color::Black);

    // Create save buttons
    sf::Text saveButton1("Save", font, buttonCharacterSize);
    saveButton1.setPosition((windowWidth + boxWidth) / 2 + spacing, assemblyBox.getPosition().y);
    sf::RectangleShape saveBox1(sf::Vector2f(buttonWidth, buttonHeight));
    saveBox1.setPosition((windowWidth + boxWidth) / 2 + spacing, assemblyBox.getPosition().y);
    saveBox1.setFillColor(sf::Color::Green);

    sf::Text saveButton2("Save", font, buttonCharacterSize);
    saveButton2.setPosition((windowWidth + boxWidth) / 2 + spacing, outputBox.getPosition().y);
    sf::RectangleShape saveBox2(sf::Vector2f(buttonWidth, buttonHeight));
    saveBox2.setPosition((windowWidth + boxWidth) / 2 + spacing, outputBox.getPosition().y);
    saveBox2.setFillColor(sf::Color::Green);

    // Create back button
    sf::Text backButton("Back (press space)", font, buttonCharacterSize);
    backButton.setPosition((windowWidth - boxWidth) / 2, outputBox.getPosition().y + boxHeight + 2 * spacing + labelCharacterSize);
    sf::RectangleShape backBox(sf::Vector2f(boxWidth, buttonHeight));
    backBox.setPosition((windowWidth - boxWidth) / 2, backButton.getPosition().y);
    backBox.setFillColor(sf::Color::Red);

    bool isAssemblyBoxSelected = false;
    bool isOutputBoxSelected = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (backBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return;
                    }

                    if (assemblyBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isAssemblyBoxSelected = true;
                        isOutputBoxSelected = false;
                    } else if (outputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isAssemblyBoxSelected = false;
                        isOutputBoxSelected = true;
                    } else {
                        isAssemblyBoxSelected = false;
                        isOutputBoxSelected = false;
                    }

                    // Check if save buttons are clicked
                    if (saveBox1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Save assembly file path
                        std::cout << "Save assembly file path: " << assemblyText.getString().toAnsiString() << std::endl;
                        translator.set_input_file_path(assemblyText.getString().toAnsiString());
                    } else if (saveBox2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Save output file path
                        std::cout << "Save output file path: " << outputText.getString().toAnsiString() << std::endl;
                        translator.set_output_file_path(outputText.getString().toAnsiString());
                    }
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (isAssemblyBoxSelected) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!assemblyText.getString().isEmpty()) {
                            std::string str = assemblyText.getString();
                            str.pop_back();
                            assemblyText.setString(str);
                        }
                    } else if (event.text.unicode < 128) {
                        assemblyText.setString(assemblyText.getString() + static_cast<char>(event.text.unicode));
                    }
                } else if (isOutputBoxSelected) {
                    if (event.text.unicode == '\b') { // Handle backspace
                        if (!outputText.getString().isEmpty()) {
                            std::string str = outputText.getString();
                            str.pop_back();
                            outputText.setString(str);
                        }
                    } else if (event.text.unicode < 128) {
                        outputText.setString(outputText.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }
        }

        window.clear();
        window.draw(optionsBackgroundSprite);
        window.draw(assemblyLabel);
        window.draw(assemblyBox);
        window.draw(assemblyText);
        window.draw(saveBox1);
        window.draw(saveButton1);
        window.draw(outputLabel);
        window.draw(outputBox);
        window.draw(outputText);
        window.draw(saveBox2);
        window.draw(saveButton2);
        window.draw(backBox);
        window.draw(backButton);
        window.display();
    }
}

int main() {
    // Init fullscreen
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "USA", sf::Style::Fullscreen);

    // Attempt to set (or disable) vertical sync
    // window.setVerticalSyncEnabled(false);

    // Set frame rate limit as an alternative
    window.setFramerateLimit(60);

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/Flag.jpg")) {
        std::cerr << "Error loading background.jpg" << std::endl;
        return -1;
    }

    // Create background sprite
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background sprite to fit the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/arial/arial.ttf")) {
        std::cerr << "Error loading arial.ttf" << std::endl;
        return -1;
    }

    // Initalize main menu
    Menu menu(window.getSize().x, window.getSize().y);

    // Initalize translator
    // WE WILL HAVE DEFAULT FILES FOR NOW
    Translator translator = Translator("demo/input.asm", "demo/output.hex");

    // Load music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/Star_Spangled_Banner_choral.ogg")) {
        std::cerr << "Error loading background music" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true);  // Loop the music
    backgroundMusic.play();

    // Main loop
    while (window.isOpen()) {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle specific key presses
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                } else if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                    // Upon enter or space, handle selected option
                    int selectedIndex = menu.getSelectedIndex();
                    std::cout << "Selected option: " << selectedIndex << std::endl;
                    if (selectedIndex == 0) {           // Run option
                        showLoadingScreen(window, font, translator);
                    } else if (selectedIndex == 1) {    // Options option
                        showOptions(window, font, translator);
                    } else if (selectedIndex == 2) {    // Help option
                        showHelp(window, font);
                    } else if (selectedIndex == 3) {    // Exit option
                        window.close();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < menu.menuItems.size(); ++i) {
                        if (menu.menuItems[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            std::cout << "Selected option: " << i << std::endl;
                            if (i == 0) {  // Run option
                                showLoadingScreen(window, font, translator);
                            } else if (i == 1) {  // Options option
                                showOptions(window, font, translator);
                            } else if (i == 2) {  // Help option
                                showHelp(window, font);
                            } else if (i == 3) {  // Exit option
                                window.close();
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);  // Draw the background
        menu.draw(window);  // Draw the menu items
        window.display();
    }

    return 0;
}
