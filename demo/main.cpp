#include <iostream>
#include "UI.hh"
#include "Translator.hh"
#include "EventEnum.hh"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

enum ProgramState {
    STARTUP,
    PROCESSING,
    HELP,
    ERROR,
    SUCCESS
};


class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() { return selectedIndex; }

    std::vector<sf::Text> menuItems;
    sf::Font font;
    int selectedIndex;

private:
};

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/arial/arial.ttf")) {
        // Handle error
    }

    std::string items[] = {"Run", "Options", "Help", "Exit"};
    for (int i = 0; i < 4; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setString(items[i]);
        text.setPosition(sf::Vector2f(width / 2, height / (4 + 1) * (i + 1)));
        menuItems.push_back(text);
    }

    selectedIndex = 0;
}

void Menu::draw(sf::RenderWindow &window) {
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedIndex - 1 >= 0) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex + 1 < menuItems.size()) {
        menuItems[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void showHelp(sf::RenderWindow &window, sf::Font &font) {
    // Load help background texture
    sf::Texture helpBackgroundTexture;
    if (!helpBackgroundTexture.loadFromFile("assets/bootlogo.png")) {
        std::cerr << "Error loading help_background.jpg" << std::endl;
        return;
    }

    // Create help background sprite
    sf::Sprite helpBackgroundSprite;
    helpBackgroundSprite.setTexture(helpBackgroundTexture);

    // Create help text
    sf::Text helpText;
    helpText.setFont(font);
    helpText.setFillColor(sf::Color::White);
    helpText.setString("Help Page\n\nThis is where you can put your help text.\nPress any key or click the mouse to return to the main menu.");
    helpText.setCharacterSize(24);
    helpText.setPosition(50, 50);

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

void showLoadingScreen(sf::RenderWindow &window, sf::Font &font) {
    // Load loading background texture
    sf::Texture loadingBackgroundTexture;
    if (!loadingBackgroundTexture.loadFromFile("assets/MUSH3.jpg")) {
        std::cerr << "Error loading loading_background.jpg" << std::endl;
        return;
    }

    // Create loading background sprite
    sf::Sprite loadingBackgroundSprite;
    loadingBackgroundSprite.setTexture(loadingBackgroundTexture);

    // Display loading screen
    window.clear();
    window.draw(loadingBackgroundSprite);
    window.display();

    // Simulate some work (e.g., running translator code)
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate delay

    // Show message screen after loading
    showMessage(window, font, "Translator code has finished running.\nPress any key or click the mouse to return to the main menu.", "assets/smileyface.png");
}

void showOptions(sf::RenderWindow &window, sf::Font &font, Translator &translator) {
    // Load options background texture
    sf::Texture optionsBackgroundTexture;
    if (!optionsBackgroundTexture.loadFromFile("assets/IMG_3050.JPG")) {
        std::cerr << "Error loading options_background.jpg" << std::endl;
        return;
    }

    // Create options background sprite
    sf::Sprite optionsBackgroundSprite;
    optionsBackgroundSprite.setTexture(optionsBackgroundTexture);

    // Create input boxes and labels
    sf::Text assemblyLabel("Enter assembly file path:", font, 20);
    assemblyLabel.setPosition(50, 50);
    sf::RectangleShape assemblyBox(sf::Vector2f(300, 30));
    assemblyBox.setPosition(50, 80);
    assemblyBox.setFillColor(sf::Color::White);
    sf::Text assemblyText("", font, 20);
    assemblyText.setPosition(55, 80);
    assemblyText.setFillColor(sf::Color::Black);

    sf::Text outputLabel("Enter output file path:", font, 20);
    outputLabel.setPosition(50, 150);
    sf::RectangleShape outputBox(sf::Vector2f(300, 30));
    outputBox.setPosition(50, 180);
    outputBox.setFillColor(sf::Color::White);
    sf::Text outputText("", font, 20);
    outputText.setPosition(55, 180);

    // Create save buttons
    sf::Text saveButton1("Save", font, 20);
    saveButton1.setPosition(360, 80);
    sf::RectangleShape saveBox1(sf::Vector2f(60, 30));
    saveBox1.setPosition(360, 80);
    saveBox1.setFillColor(sf::Color::Green);

    sf::Text saveButton2("Save", font, 20);
    saveButton2.setPosition(360, 180);
    sf::RectangleShape saveBox2(sf::Vector2f(60, 30));
    saveBox2.setPosition(360, 180);
    saveBox2.setFillColor(sf::Color::Green);

    // Create back button
    sf::Text backButton("Back (press space)", font, 20);
    backButton.setPosition(50, 250);
    sf::RectangleShape backBox(sf::Vector2f(200, 30));
    backBox.setPosition(50, 250);
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
                        translator.set_asmFilePath(assemblyText.getString().toAnsiString());
                    } else if (saveBox2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Save output file path
                        std::cout << "Save output file path: " << outputText.getString().toAnsiString() << std::endl;
                        translator.set_outputFilePath(outputText.getString().toAnsiString());
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu");

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/bigchinhead.jpg")) {
        std::cerr << "Error loading background.jpg" << std::endl;
        return -1;
    }

    // Create background sprite
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/arial/arial.ttf")) {
        std::cerr << "Error loading arial.ttf" << std::endl;
        return -1;
    }

    // Initalize main menu
    Menu menu(window.getSize().x, window.getSize().y);

    // Initalize translator
    Translator translator = Translator("input.asm", "output.hex");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                } else if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                    int selectedIndex = menu.getSelectedIndex();
                    std::cout << "Selected option: " << selectedIndex << std::endl;
                    if (selectedIndex == 0) {  // Run option
                        showLoadingScreen(window, font);
                    } else if (selectedIndex == 1) {  // Options option
                        showOptions(window, font, translator);
                    } else if (selectedIndex == 2) {  // Help option
                        showHelp(window, font);
                    } else if (selectedIndex == 3) {  // Exit option
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
                                showLoadingScreen(window, font);
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
// int main(int argc, char *argv[]) {
//     if (argc == 2){
// 		if (argv[1] == "help" or argv[1] == "-h"){
// 			print_help();
// 		}
// 		else {
// 			printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
// 		}
// 		return;
// 	}
// 	if (argc == 1 or argc > 3){
// 		printf("Improper format. For help, enter './assemble help' or './assemble -h'.");
// 		return;
// 	}
// 	string inputPath = argv[1];
// 	string outputPath = argv[2];
// 	UI ui = UI(inputPath, outputPath);
// 	ui.run();


//     return 0;
// }


void print_help(){
	printf("------------------------------------------------------------- \n");
	printf("-----------------------------HELP---------------------------- \n");
	printf("------------------------------------------------------------- \n \n");
	printf("To use this assembler, input the following into command line: \n");
	printf("            ./assemble <INPUT_FILE> <OUTPUT_FILE>             \n");
	printf("------------------------------------------------------------- \n");

}

