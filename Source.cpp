#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include <random>
#include <fstream>
using namespace std;
using namespace sf;

Vector2f normalize(Vector2f vector) {                                  
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0.0f) {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

// Ghost structure to store ghost properties
struct Ghost {
    Sprite sprite;
    Vector2f target;
    Vector2f direction;
    float speed;

    Ghost() : speed(1.0f) {}
};

int main()

{
    RenderWindow window0(VideoMode(1000, 1000), "Pac-Man");

    //sound for the start screen
    Sound introsound;
    SoundBuffer introBuffer;
    introBuffer.loadFromFile("intro.wav");
    introsound.setBuffer(introBuffer);
    introsound.play();
    Music introtheme;
    introtheme.openFromFile("introtheme.wav");
    introtheme.setLoop(true);
    introtheme.play();

    float playerSpeed = 0.0;
    const int GHOST_SIZE = 30;
    const int GHOST_SPEED = 1;

    // Set up the ghosts
    Sprite ghost1;
    Sprite ghost2;
    Sprite ghost3;
    Sprite ghost4;

    Texture ghost1Texture;
    Texture ghost2Texture;
    Texture ghost3Texture;
    Texture ghost4Texture;


    // Set up the main text
    Font fonttitle;
    if (!fonttitle.loadFromFile("CrackMan.TTF")) {
        // Error loading font
        return -1;
    }

    Text text1;
    text1.setFont(fonttitle);
    text1.setString("P a c - M a n!");
    text1.setCharacterSize(100);
    text1.setFillColor(Color::Yellow);

    FloatRect text1Bounds = text1.getLocalBounds();
    text1.setOrigin(text1Bounds.width / 2, text1Bounds.height / 2);
    text1.setPosition(window0.getSize().x / 2, window0.getSize().y / 2);

    Font fontsub;
    if (!fontsub.loadFromFile("Roboto-Bold.TTF")) {
        // Error loading font
        return -1;
    }

    Text text2;
    text2.setFont(fontsub);
    text2.setString("Press spacebar to start");
    text2.setCharacterSize(30);
    text2.setFillColor(Color::Blue);

    FloatRect text2Bounds = text2.getLocalBounds();
    text2.setOrigin(text2Bounds.width / 2, text2Bounds.height);
    text2.setPosition(window0.getSize().x / 2, window0.getSize().y - text2Bounds.height - 180);



    if (!ghost1Texture.loadFromFile("redghost.png")) {
        // Error loading texture
        return -1;
    }
    if (!ghost2Texture.loadFromFile("greenghost.png")) {
        // Error loading texture
        return -1;
    }
    if (!ghost3Texture.loadFromFile("blueghost.png")) {
        // Error loading texture
        return -1;
    }
    if (!ghost4Texture.loadFromFile("yellowghost.png")) {
        // Error loading texture
        return -1;
    }

    ghost1.setTexture(ghost1Texture);
    ghost2.setTexture(ghost2Texture);
    ghost3.setTexture(ghost3Texture);
    ghost4.setTexture(ghost4Texture);

    ghost1.setScale(Vector2f(2.5f, 2.5f));
    ghost2.setScale(Vector2f(2.5f, 2.5f));
    ghost3.setScale(Vector2f(2.5f, 2.5f));
    ghost4.setScale(Vector2f(2.5f, 2.5f));



    Vector2f ghost1Direction;
    Vector2f ghost2Direction;
    Vector2f ghost3Direction;
    Vector2f ghost4Direction;


    Vector2f ghost1Position = { Vector2f(100.f, 100.f) };
    Vector2f ghost2Position = { Vector2f(200.f, 200.f) };
    Vector2f ghost3Position = { Vector2f(300.f, 300.f) };
    Vector2f ghost4Position = { Vector2f(400.f, 400.f) };



    ghost1.setOrigin(GHOST_SIZE / 2, GHOST_SIZE / 2);
    ghost1.setPosition(ghost1Position);
    ghost1Direction = Vector2f(GHOST_SPEED / 2, GHOST_SPEED / 2);
    ghost2.setOrigin(GHOST_SIZE / 2, GHOST_SIZE / 2);
    ghost2.setPosition(ghost2Position);
    ghost2Direction = Vector2f(GHOST_SPEED / 2, GHOST_SPEED / 2);
    ghost4.setOrigin(GHOST_SIZE / 2, GHOST_SIZE / 2);
    ghost3.setPosition(ghost3Position);
    ghost3Direction = Vector2f(GHOST_SPEED / 2, GHOST_SPEED / 2);
    ghost4.setOrigin(GHOST_SIZE / 2, GHOST_SIZE / 2);
    ghost4.setPosition(ghost4Position);
    ghost4Direction = Vector2f(GHOST_SPEED / 2, GHOST_SPEED / 2);


    default_random_engine randomEngine(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> randomDirection(0, 3);


    Clock clock;

    while (window0.isOpen())
    {
        Event event;
        while (window0.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window0.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    window0.close();
                }
            }
        }

        // Update ghost positions
        if (clock.getElapsedTime().asMilliseconds() > 200) {

            int direction = randomDirection(randomEngine);
            switch (direction) {
            case 0: // Up
                ghost1Direction = Vector2f(0, -GHOST_SPEED);
                break;
            case 1: // Down
                ghost1Direction = Vector2f(0, GHOST_SPEED);
                break;
            case 2: // Left
                ghost1Direction = Vector2f(-GHOST_SPEED, 0);
                break;
            case 3: // Right
                ghost1Direction = Vector2f(GHOST_SPEED, 0);
                break;
            }

            direction = randomDirection(randomEngine);

            switch (direction) {
            case 0: // Up
                ghost2Direction = Vector2f(0, -GHOST_SPEED);
                break;
            case 1: // Down
                ghost2Direction = Vector2f(0, GHOST_SPEED);
                break;
            case 2: // Left
                ghost2Direction = Vector2f(-GHOST_SPEED, 0);
                break;
            case 3: // Right
                ghost2Direction = Vector2f(GHOST_SPEED, 0);
                break;
            }

            direction = randomDirection(randomEngine);

            switch (direction) {
            case 0: // Up
                ghost3Direction = Vector2f(0, -GHOST_SPEED);
                break;
            case 1: // Down
                ghost3Direction = Vector2f(0, GHOST_SPEED);
                break;
            case 2: // Left
                ghost3Direction = Vector2f(-GHOST_SPEED, 0);
                break;
            case 3: // Right
                ghost3Direction = Vector2f(GHOST_SPEED, 0);
                break;
            }

            direction = randomDirection(randomEngine);

            switch (direction) {
            case 0: // Up
                ghost4Direction = Vector2f(0, -GHOST_SPEED);
                break;
            case 1: // Down
                ghost4Direction = Vector2f(0, GHOST_SPEED);
                break;
            case 2: // Left
                ghost4Direction = Vector2f(-GHOST_SPEED, 0);
                break;
            case 3: // Right
                ghost4Direction = Vector2f(GHOST_SPEED, 0);
                break;
            }


            clock.restart();
        }

        ghost1Position += ghost1Direction;
        ghost1.setPosition(ghost1Position);
        ghost2Position += ghost2Direction;
        ghost2.setPosition(ghost2Position);
        ghost3Position += ghost3Direction;
        ghost3.setPosition(ghost3Position);
        ghost4Position += ghost4Direction;
        ghost4.setPosition(ghost4Position);

        window0.clear();
        window0.draw(text1);
        window0.draw(text2);
        window0.draw(ghost1);
        window0.draw(ghost2);
        window0.draw(ghost3);
        window0.draw(ghost4);
        window0.display();
    }
    introtheme.stop();
    //screen 2

    RenderWindow window2(VideoMode(800, 600), "Player Selection");


    Text titleText("Select a Player", fontsub, 40);
    titleText.setFillColor(Color::Yellow);
    titleText.setPosition(220.f, 50.f);

    Text player1Text("Khadija, press a to select", fontsub, 20);
    player1Text.setFillColor(Color::Blue);
    player1Text.setPosition(100.f, 200.f);

    Text player2Text("Noor, press b to select", fontsub, 20);
    player2Text.setFillColor(Color::Magenta);
    player2Text.setPosition(400.f, 200.f);

    Text player3Text("Ammar, press c to select", fontsub, 20);
    player3Text.setFillColor(Color::Green);
    player3Text.setPosition(100.f, 400.f);

    Text player4Text("Rijaa, press d to select", fontsub, 20);
    player4Text.setFillColor(Color::Cyan);
    player4Text.setPosition(400.f, 400.f);

    RectangleShape player1Sprite(Vector2f(100.f, 100.f));
    player1Sprite.setFillColor(Color::Red);
    player1Sprite.setPosition(120.f, 250.f);

    // declare sprite for player 1
    Texture khadija;
    khadija.loadFromFile("khadija.png");
    Sprite player1;
    player1.setTexture(khadija);
    player1.setScale(2.0f, 2.0f);
    player1.setPosition(145, 260);


    RectangleShape player2Sprite(Vector2f(100.f, 100.f));
    player2Sprite.setFillColor(Color::Green);
    player2Sprite.setPosition(420.f, 250.f);

    // declare sprite for player 2
    Texture noor;
    noor.loadFromFile("noor.png");
    Sprite player2;
    player2.setTexture(noor);
    player2.setScale(2.0f, 2.0f);
    player2.setPosition(440, 260);

    RectangleShape player3Sprite(Vector2f(100.f, 100.f));
    player3Sprite.setFillColor(Color::Blue);
    player3Sprite.setPosition(120.f, 460.f);

    // declare sprite for player 3
    Texture ammar;
    ammar.loadFromFile("ammar.png");
    Sprite player3;
    player3.setTexture(ammar);
    player3.setScale(2.0f, 2.0f);
    player3.setPosition(145, 470);

    RectangleShape player4Sprite(Vector2f(100.f, 100.f));
    player4Sprite.setFillColor(Color::Yellow);
    player4Sprite.setPosition(420.f, 450.f);

    // declare sprite for player 4
    Texture rijaa;
    rijaa.loadFromFile("rijaa.png");
    Sprite player4;
    player4.setTexture(rijaa);
    player4.setScale(2.0f, 2.0f);
    player4.setPosition(450, 460);


    bool playerSelected = false;
    string selectedPlayer;
    int playerflag = 0;
    //music for the select screen
    Music selecttheme;
    selecttheme.openFromFile("selecttheme.wav");
    selecttheme.setLoop(true);
    selecttheme.play();

    while (window2.isOpen()) {
        Event event1;
        while (window2.pollEvent(event1)) {
            if (event1.type == Event::Closed) {
                window2.close();
            }
            else if (event1.type == Event::KeyPressed) {
                if (event1.key.code == Keyboard::A) {
                    playerSelected = true;
                    selectedPlayer = "Khadija";
                    playerflag = 1;
                }
                else if (event1.key.code == Keyboard::B) {
                    playerSelected = true;
                    selectedPlayer = "Noor";
                    playerflag = 2;
                }
                else if (event1.key.code == Keyboard::C) {
                    playerSelected = true;
                    selectedPlayer = "Ammar";
                    playerflag = 3;
                }
                else if (event1.key.code == Keyboard::D) {
                    playerSelected = true;
                    selectedPlayer = "Rijaa";
                    playerflag = 4;
                }
            }
        }


        window2.clear(Color::Black);
        window2.draw(titleText);
        window2.draw(player1Text);
        window2.draw(player2Text);
        window2.draw(player3Text);
        window2.draw(player4Text);
        window2.draw(player1Sprite);
        window2.draw(player2Sprite);
        window2.draw(player3Sprite);
        window2.draw(player4Sprite);
        window2.draw(player1);
        window2.draw(player2);
        window2.draw(player3);
        window2.draw(player4);
        window2.display();

        if (playerSelected) {
            // Perform actions with the selected player
            // Add your code here
            // For example, you can store the selected player and proceed to the game
            // In this example, we simply print the selected player and close the window
            cout << "Selected Player: " << selectedPlayer << endl;
            cout << "Flag scene: " << playerflag << endl;
            selecttheme.stop(); //end select music
            window2.close();
        }



    }


    //reading score from the highscore file if it exists
    string highsc;
    int highscore;
    fstream highfile;

    highfile.open("highscore.txt", ios::in);
    if (!highfile) {
        highfile.open("highscore.txt", ios::out);
        highfile << "0";
        highfile.close();
        highfile.open("highscore.txt", ios::in);
    }
    while (highfile) {
        getline(highfile, highsc);
    }
    highfile.close();
    highscore = stoi(highsc);
    cout << highscore;

    // initialising sounds
    Music song;
    Sound over;
    Sound win;
    Sound eatSound;
    Sound life;

    SoundBuffer lifeBuffer;
    SoundBuffer winBuffer;
    SoundBuffer overBuffer;
    SoundBuffer eatBuffer;

    lifeBuffer.loadFromFile("life sound.wav");
    winBuffer.loadFromFile("win sound.wav");
    eatBuffer.loadFromFile("eat.wav");
    overBuffer.loadFromFile("over.wav");

    eatSound.setBuffer(eatBuffer);
    over.setBuffer(overBuffer);
    win.setBuffer(winBuffer);
    life.setBuffer(lifeBuffer);





    RenderWindow window(VideoMode(1000, 1300), "Pacman Maze");

    //// declare sprite and textures
    //Texture rijaa;
    //rijaa.loadFromFile("rijaa.png");
    //Texture khadija;
    //khadija.loadFromFile("khadija.png");
    //Texture ammar;
    //ammar.loadFromFile("ammar.png");
    //Texture noor;
    //noor.loadFromFile("noor.png");
    Sprite player;

    switch (playerflag) {
    case 1: {
        player.setTexture(khadija);
        song.openFromFile("khadijatheme.wav");
        break;
    }
    case 2: {
        player.setTexture(noor);
        song.openFromFile("noortheme.wav");
        break;
    }
    case 3: {
        player.setTexture(ammar);
        song.openFromFile("ammartheme.wav");
        break;
    }
    case 4: {
        player.setTexture(rijaa);
        song.openFromFile("rijaatheme.wav");
        break;
    }
    }

    song.setLoop(true);

    song.play();


    float x = 200;
    float y = 245;
    playerSpeed = 0.75f; // Adjust the player speed as needed
    /*
    player.setPosition(x, y);
    */

    // maze stuff
    const int tileSize = 40;
    const int countertile = 10;
    const int mazeWidth = 23;
    const int mazeHeight = 21;
    const int dotSize = 5;
    int score = 0;
    bool gameOver = false;



    // Adjust the starting position of the maze within the window
    float mazeStartX = 50; // Adjust the starting x-coordinate for the maze
    float mazeStartY = 200; // Adjust the starting y-coordinate for the maze

    //declaring icons for lives left as sprites
    vector<Sprite> lifeIcons;
    Sprite lifeIcon;
    Texture lifeTexture;
    lifeTexture.loadFromFile("lives.png");
    lifeIcon.setTexture(lifeTexture);
    float lifeIconSize = 2.0f; // Adjust the size of the life icon as needed
    float lifeIconSpacing = 65.0f; // Adjust the spacing between the life icons as needed
    lifeIcon.setScale(Vector2f(0.14f, 0.14f));
    int numLives = 3;


    CircleShape dot(dotSize);
    dot.setFillColor(Color::Yellow);

    RectangleShape wallTile(Vector2f(tileSize, tileSize));
    wallTile.setFillColor(Color::Blue);

    // Use the default font provided by SFML
    Font font;
    if (!font.loadFromFile("CrackMan.TTF")) {
        cout << "Error loading font." << endl;
        return -1;
    }

    Text message;
    message.setFont(font);
    message.setCharacterSize(100);
    message.setFillColor(Color::Yellow);
    // Center the message on the screen
    FloatRect textBounds = message.getLocalBounds();
    message.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    message.setPosition(window.getSize().x / 2 - 360, window.getSize().y / 2 - 100);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: 0");
    scoreText.setPosition(mazeStartX + mazeWidth * tileSize - 225, mazeStartY - 75);


    // Create a yellow box for the score counter
    RectangleShape scoreBox(Vector2f(countertile, countertile));
    scoreBox.setFillColor(Color::Yellow);
    scoreBox.setPosition(mazeStartX + mazeWidth * tileSize - 20, mazeStartY - 30);
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(Color::White);
    highScoreText.setString("High Score: " + to_string(highscore));
    highScoreText.setPosition(mazeStartX + 300, mazeStartY - 75);

    char counter[8][24] = {
        {'#','#', '#', '#', '#', '#', '#', '#', '#', '#' ,'#', '#', '#', '#','#' ,'#', '#', '#', '#','#', '#', '#', '#', '#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ' ,' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', '#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ' ,' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', '#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ' ,' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', '#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ', ' ', ' ',' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ', ' ', '#'},
        {'#',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' ,' ', ' ',' ', ' ', ' ' ,' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', '#'},
        {'#','#', '#', '#', '#', '#', '#', '#', '#', '#' ,'#', '#', '#', '#' ,'#', '#', '#', '#','#','#', '#', '#', '#', '#'},
    };



    char maze[mazeHeight][mazeWidth + 1] = {
        " ################### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.###.#.###.#### ",
        "    #.#...0...#.#    ",
        "#####.#.##=##.#.#####",
        "#.......#123#.......#",
        "#####.#.#####.#.#####",
        "    #.#.......#.#    ",
        " ####.#.#####.#.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #..#.....P.....#..# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### "
    };

    // Boolean flags to track key states
    bool upKeyPressed = false;
    bool downKeyPressed = false;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;

    // Declare ghost entities
    const int numGhosts = 4;
    int ghostCount = 0;

    vector<Texture> ghostTextures(numGhosts);  // Array of textures
    vector<Ghost> ghosts(numGhosts);

    // Load ghost textures
    ghostTextures[0].loadFromFile("redghost.png");
    ghostTextures[1].loadFromFile("blueghost.png");
    ghostTextures[2].loadFromFile("greenghost.png");
    ghostTextures[3].loadFromFile("yellowghost.png");

    // Iterate over the maze and find the starting positions for ghosts
    for (int row = 0; row < mazeHeight; ++row) {
        for (int col = 0; col < mazeWidth; ++col) {
            if (maze[row][col] >= '0' && maze[row][col] <= '3') {
                int ghostIndex = maze[row][col] - '0';
                ghosts[ghostIndex].sprite.setTexture(ghostTextures[ghostIndex]);
                ghosts[ghostIndex].sprite.setPosition(mazeStartX + col * tileSize, mazeStartY + row * tileSize);
                ghosts[ghostIndex].target = Vector2f((rand() % (mazeWidth - 2) + 1) * tileSize, (rand() % (mazeHeight - 2) + 1) * tileSize);
                ++ghostCount;
            }
        }
        // Break if all ghosts are found
        if (ghostCount == numGhosts) {
            break;
        }
    }


    // Find the starting position of the sprite ('P') in the maze
    Vector2i spriteStartPos;
    for (int i = 0; i < mazeHeight; ++i) {
        for (int j = 0; j < mazeWidth; ++j) {
            if (maze[i][j] == 'P') {
                spriteStartPos.x = j;
                spriteStartPos.y = i;
                break;
            }
        }
    }

    // Calculate the starting position of the sprite based on maze and tile size
    float spriteStartX = mazeStartX + spriteStartPos.x * tileSize + (tileSize / 2.0f) - (player.getLocalBounds().width / 2.0f);
    float spriteStartY = mazeStartY + spriteStartPos.y * tileSize + (tileSize / 2.0f) - (player.getLocalBounds().height / 2.0f);

    // Set the initial position of your sprite to the calculated starting position
    player.setPosition(spriteStartX, spriteStartY);

    // the actual window
    while (window.isOpen()) {
        Event ev;
        scoreText.setString("Score: " + to_string(score));

        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
            }
            if (ev.type == Event::KeyPressed) {
                if (ev.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }

        for (Ghost& ghost : ghosts) {
            // Get the current position of the ghost
            Vector2f ghostPosition = ghost.sprite.getPosition();

            // Calculate the direction vector towards the target position
            Vector2f direction = ghost.target - ghostPosition;
            direction = normalize(direction);

            // Calculate the new position by moving in the direction of the target
            Vector2f newPosition = ghostPosition + direction * ghost.speed;

            // Perform collision detection with walls
            FloatRect nextGhostPosition = ghost.sprite.getGlobalBounds();
            nextGhostPosition.left = newPosition.x;
            nextGhostPosition.top = newPosition.y;
            bool ghostCollision = false;

            // Check for collision with each wall tile in the maze
            for (int row = 0; row < mazeHeight; ++row) {
                for (int col = 0; col < mazeWidth; ++col) {
                    if (maze[row][col] == '#') {
                        FloatRect wallBounds(mazeStartX + col * tileSize, mazeStartY + row * tileSize, tileSize, tileSize);
                        if (nextGhostPosition.intersects(wallBounds)) {
                            ghostCollision = true;
                            break;
                        }
                    }
                }
                if (ghostCollision) {
                    break;
                }
            }

            // Update ghost position if there is no collision
            if (!ghostCollision) {
                ghost.sprite.setPosition(newPosition);
            }
            else {
                // Generate a new random target if the ghost encounters a wall
                ghost.target = Vector2f((rand() % (mazeWidth - 2) + 1) * tileSize, (rand() % (mazeHeight - 2) + 1) * tileSize);
            }



            // Handle key press events
            if (ev.type == Event::KeyPressed) {
                switch (ev.key.code) {
                case Keyboard::Up:
                    upKeyPressed = true;
                    break;
                case Keyboard::Down:
                    downKeyPressed = true;
                    break;
                case Keyboard::Right:
                    rightKeyPressed = true;
                    break;
                case Keyboard::Left:
                    leftKeyPressed = true;
                    break;
                }
            }

            // Handle key release events
            if (ev.type == Event::KeyReleased) {
                switch (ev.key.code) {
                case Keyboard::Up:
                    upKeyPressed = false;
                    break;
                case Keyboard::Down:
                    downKeyPressed = false;
                    break;
                case Keyboard::Right:
                    rightKeyPressed = false;
                    break;
                case Keyboard::Left:
                    leftKeyPressed = false;
                    break;
                }
            }

            // Update the position based on key states
            Vector2f movement(0.0f, 0.0f);
            if (upKeyPressed) {
                movement.y -= playerSpeed;
            }
            if (downKeyPressed) {
                movement.y += playerSpeed;
            }
            if (rightKeyPressed) {
                movement.x += playerSpeed;
            }
            if (leftKeyPressed) {
                movement.x -= playerSpeed;
            }

            // Perform collision detection with walls
            FloatRect nextPosition = player.getGlobalBounds();
            nextPosition.left += movement.x;
            nextPosition.top += movement.y;
            bool collision = false;

            // Check for collision with each wall tile in the maze
            for (int row = 0; row < mazeHeight; ++row) {
                for (int col = 0; col < mazeWidth; ++col) {
                    if (maze[row][col] == '#') {
                        FloatRect wallBounds(mazeStartX + col * tileSize, mazeStartY + row * tileSize, tileSize, tileSize);
                        if (nextPosition.intersects(wallBounds)) {
                            collision = true;
                            break;
                        }
                    }
                }
                if (collision) {
                    break;
                }
            }

            // Update player position if there is no collision
            if (!collision) {
                player.move(movement);
            }

            window.clear();

            // Draw the counter box
            for (int row1 = 0; row1 < 8; ++row1) {
                for (int col1 = 0; col1 < 24; ++col1) {
                    if (counter[row1][col1] == '#') {
                        scoreBox.setPosition(mazeStartX + mazeWidth * tileSize - 250 + col1 * countertile, mazeStartY - 95 + row1 * countertile);
                        window.draw(scoreBox);
                    }
                }
            }

            // Check for collision with ghost
            FloatRect playerBounds = player.getGlobalBounds();
            bool collisionDetected = false;

            for (int i = 0; i < numGhosts; ++i) {
                FloatRect ghostBounds = ghosts[i].sprite.getGlobalBounds();
                if (playerBounds.intersects(ghostBounds)) {
                    life.play();
                    collisionDetected = true;
                    if (numLives > 0) {

                        numLives--;
                        ghosts[i].sprite.setPosition(newPosition);
                    }
                    else if (numLives <= 0) {
                        message.setString("Game Over");
                        gameOver = true; // Set the game over state to true
                        over.play(); //play game over sound
                        window.draw(message);


                    }
                }
            }


            if (collisionDetected && !lifeIcons.empty()) {
                lifeIcons.pop_back(); // Remove the last life icon from the vector
            }

            // Draw the maze
            for (int row = 0; row < mazeHeight; ++row) {
                for (int col = 0; col < mazeWidth; ++col) {
                    if (maze[row][col] == '#') {
                        wallTile.setPosition(mazeStartX + col * tileSize, mazeStartY + row * tileSize);
                        window.draw(wallTile);
                    }
                    else if (maze[row][col] == '.') {
                        dot.setPosition(mazeStartX + col * tileSize + (tileSize / 2 - dotSize / 2), mazeStartY + row * tileSize + (tileSize / 2 - dotSize / 2));
                        window.draw(dot);

                        FloatRect dotBounds = dot.getGlobalBounds();
                        if (nextPosition.intersects(dotBounds)) {
                            // Collision with dot
                            maze[row][col] = ' '; // Remove the dot from the maze
                            eatSound.play();// play the eat sound
                            score++; // Increment the score
                            if (score == 183) {
                                win.play(); //play win sound
                                message.setString("Shabaash!");
                                gameOver = true; // Set the game over state to true
                            }

                        }
                    }
                }
            }

            // Draw the life icons
            for (int i = 0; i < numLives; ++i) {
                lifeIcon.setPosition(mazeStartX + i * (lifeIconSize + lifeIconSpacing), mazeStartY - 75);
                window.draw(lifeIcon);
            }

            //print end message 
            if (gameOver == true) {
                window.draw(message);
            }

            // Draw the score text
            window.draw(scoreText);
            window.draw(highScoreText);

            // Draw ghosts
            for (int i = 0; i < numGhosts; ++i) {
                window.draw(ghosts[i].sprite);
            }

            // Draw the player
            window.draw(player);
            window.display();
        }

        if (gameOver) {
            while (window.isOpen()) {
                song.stop();

                Event event2;
                while (window.pollEvent(event2)) {

                    if (event2.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event2.type == Event::KeyPressed) {
                        if (event2.key.code == Keyboard::Escape) {
                            window.close();
                        }
                    }
                }
            }
        }
    }

    //checking if the new score is a highscore 
    if (score > highscore) {
        highscore = score;
        highfile.open("highscore.txt", ios::out);
        highfile << highscore;
        highfile.close();
    }



    //saving the scores and high score
    fstream file;
    file.open("scores.txt", ios::out | ios::app);
    file << "HIGHSCORE: " << highscore << endl;
    file << "YOUR CURRENT SCORE: " << score << endl << endl << "----------" << endl << endl;
    file.close();

    return 0;
}  