#include "Game.hpp"
#include "Texture.hpp"
#include "MainScreen.hpp"
#include "GameOverScreen.hpp"
#include "PauseScreen.hpp"
#include "StartScreen.hpp"
#include "GameObject.hpp"
#include "Life.hpp"
#include "Tree.hpp"
#include "Smoke.hpp"
#include "Fire.hpp"
#include "Earth.hpp"
#include "Enemies.hpp"
#include "Deforestation.hpp"
#include "IntensiveFarming.hpp"
#include "FosilFuels.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "RandomObj.hpp"

SDL_Renderer *Game::renderer = nullptr;

bool Game::running()
{
    return isRunning;
}

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialised" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
}

void Game::init()
{
    //create objects
    startscreen = new StartScreen(starttex, buttontex);
    gameoverscreen = new GameOverScreen(gameovertex, buttontex);
    pausescreen = new PauseScreen(pausetex, buttontex);
    mainscreen = new MainScreen(maintex);
    life = new Life *[2];
    life[0] = new Life(objectstex, 10, 10, 550, 10, 0.5, 490, 100); //0.5
    life[1] = new Life(objectstex, 16, 117, 564, 24, 0.5, 437, 46); //change width according to life (changing 437 changed the width)
    //rec = {564, 24, 437, 46};
    earth = new Earth(objectstex, 580, 20, 800, 0, 0.5, 170, 170);
    pollutedObj = new GameObject *[3];
    pollutedObj[0] = new Tree(deadTree, 0, 0, 250, 350, 0.5, 91, 174); //0.5
    pollutedObj[1] = new Tree(deadTree, 90, 30, 600, 365, 0.5, 80, 145);
    //pollutedObj[3] = new Trash(objectstex, );
    //pollutedObj[3] = new Fire(fire, 0, 0, 350, 380, 0.2, 940, 280);    //0.2
    cleanObj = new GameObject *[6];
    cleanObj[0] = new Tree(cleantree, 0, 83, 250, 390, 1, 110, 61);
    cleanObj[1] = new Tree(cleantree, 157, 127, 450, 390, 1, 35, 50);
    cleanObj[2] = new Tree(cleantree, 130, 280, 560, 380, 1, 60, 70);
    cleanObj[3] = new Tree(cleantree, 317, 426, 100, 408, 1, 20, 38);
    cleanObj[4] = new Tree(cleantree, 317, 426, 125, 408, 1, 20, 38);
    cleanObj[5] = new Tree(cleantree, 317, 426, 780, 410, 1, 20, 38);
    enemy_list = new Enemies *[3];
    enemy_list[0] = new Deforestation(deforesttex, NULL);
    //enemy_list[1] = new IntensiveFarming(intensivefarmingtex, NULL);
    //enemy_list[2] = new FossilFuel(fossilfueltex, NULL);
    player = new Player(playertex);
    ecoFriendly = new GameObject *[8];
    nonecoFriendly = new GameObject *[8];
    ecoFriendly[0] = new RandomObj(objectstex, 29, 250, 250, 395, 0.3, 200, 150);
    ecoFriendly[1] = new RandomObj(objectstex, 260, 220, 350, 395, 0.3, 170, 174);
    ecoFriendly[2] = new RandomObj(objectstex, 480, 240, 400, 395, 0.3, 140, 140);
    ecoFriendly[3] = new RandomObj(objectstex, 690, 230, 500, 395, 0.3, 140, 176);
    ecoFriendly[4] = new RandomObj(objectstex, 860, 230, 430, 395, 0.3, 130, 100);
    // ecoFriendly[5] = new RandomObj(objectstex, 553, 630, );
    // ecoFriendly[6] = new RandomObj(objectstex, );
    // ecoFriendly[7] = new RandomObj(objectstex, );
    // nonecoFriendly[0] = new RandomObj(objectstex, );
    // nonecoFriendly[1] = new RandomObj(objectstex, );
    // nonecoFriendly[2] = new RandomObj(objectstex, );
    // nonecoFriendly[3] = new RandomObj(objectstex, );
    // nonecoFriendly[4] = new RandomObj(objectstex, );
    // nonecoFriendly[5] = new RandomObj(objectstex, );
    // nonecoFriendly[6] = new RandomObj(objectstex, );
    // nonecoFriendly[7] = new RandomObj(objectstex, );
}

void Game::LoadMedia()
{
    playertex = Texture::loadTexture("sprites/player.png");
    if (playertex == NULL)
    {
        std::cout << "Player texture not loaded" << std::endl;
    }
    buttontex = Texture::loadTexture("buttons.png");
    if (buttontex == NULL)
    {
        std::cout << "Button texture not loaded" << std::endl;
    }
    starttex = Texture::loadTexture("screens/Start Screen.png");
    if (starttex == NULL)
    {
        std::cout << "Start screen texture not loaded" << std::endl;
    }
    gameovertex = Texture::loadTexture("screens/Game Over.png");
    if (gameovertex == NULL)
    {
        std::cout << "Game over screen texture not loaded" << std::endl;
    }
    pausetex = Texture::loadTexture("screens/Pause Screen.png");
    if (pausetex == NULL)
    {
        std::cout << "Pause screen texture not loaded" << std::endl;
    }
    maintex = Texture::loadTexture("screens/Main Screen.png");
    if (maintex == NULL)
    {
        std::cout << "Main screen texture not loaded" << std::endl;
    }
    objectstex = Texture::loadTexture("sprites/objects.png");
    if (objectstex == NULL)
    {
        std::cout << "Objects Texture not loaded" << std::endl;
    }
    deadTree = Texture::loadTexture("sprites/dead tree.png");
    if (deadTree == NULL)
    {
        std::cout << "Dead tree texture not loaded" << std::endl;
    }
    smoke = Texture::loadTexture("sprites/smoke.png");
    if (smoke == NULL)
    {
        std::cout << "Smoke texture not loaded" << std::endl;
    }
    fire = Texture::loadTexture("sprites/fire.png");
    if (fire == NULL)
    {
        std::cout << "Fire texture not loaded" << std::endl;
    }
    cleantree = Texture::loadTexture("sprites/trees.png");
    if (cleantree == NULL)
    {
        std::cout << "Trees texture not loaded" << std::endl;
    }
    deforesttex = Texture::loadTexture("sprites/enemy1.png");
    if (deforesttex == NULL)
    {
        std::cout << "Deforestation texture not loaded" << std::endl;
    }
    intensivefarmingtex = Texture::loadTexture("sprites/enemy2.png");
    if (intensivefarmingtex == NULL)
    {
        std::cout << "Intensive Farming texture not loaded" << std::endl;
    }
    fossilfueltex = Texture::loadTexture("sprites/enemy3.png");
    if (fossilfueltex == NULL)
    {
        std::cout << "Fossil fuels texture not loaded" << std::endl;
    }
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:

            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                player->set_direction("UP");
                break;
            case SDLK_LEFT:
                player->set_direction("left");
                break;
            case SDLK_RIGHT:
                player->set_direction("right");
                break;
            default:
                player->set_direction("static");
                break;
            }

            break;
        case SDL_KEYUP:
            player->set_direction("static");
            break;
        default:
            break;
        }
        if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
        {
            // Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);
            for (int i = 0; i < currentScreen->totalButtons; i++)
            {
                if (currentScreen->btns[i]->isOverMouse(x, y))
                {
                    if (currentScreen == startscreen)
                    {
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (i == 0) //startgame
                            {
                                currentScreen = mainscreen;
                            }
                            else if (i == 1)
                            {
                                currentScreen = startscreen;
                            }
                            else if (i == 2) //quit
                            {
                                isRunning = false;
                            }
                        }
                    }
                    else if (currentScreen == pausescreen)
                    {
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (i == 0) //options
                            {
                            }
                            else if (i == 1) //resume
                            {
                                //currentScreen = mainscreen;
                            }
                            else if (i == 2) //quit
                            {
                                isRunning = false;
                            }
                            else if (i == 3) //sound
                            {
                            }
                        }
                    }
                    else if (currentScreen == gameoverscreen)
                    {
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (i == 0) //quit
                            {
                                isRunning = false;
                            }
                            else if (i == 1) //playagain
                            {
                                currentScreen = mainscreen;
                            }
                        }
                    }
                }
            }
        }
    }
}
void Game::Update()
{
    life[1]->Update();
    player->Update();
}

void Game::Render()
{
    //clear screen
    SDL_RenderClear(renderer);
    //Render background
    if (currentScreen == mainscreen)
    {
        mainscreen->Update();

        
        if (isPolluted)
        {
            for (int i = 0; i < 2; i++)
            {
                //pollutedObj[i]->Update();
                pollutedObj[i]->Render();
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                cleanObj[i]->Render();
            }
        }
        for (int i = 0; i < 2; i++)
        {
            life[i]->Render();
        }
        earth->Render();
        // for (int i = 0; i < 2; i++)
        // {
        //     ecoFriendly[i]->Render();
        // }
        if (frameStart == 5000)
        {
            //std::cout << rand() % 8 << std::endl;
            ecoFriendly[rand() % 8]->Render();
        }

        player->Render();

        if(abs(player->player_dest.x - enemy_list[0]->destRect.x) < 10)
        {
            enemy_list[0]->srcRect.y = enemy_list[0]->srcRect.h;
            std::cout << "anand" << abs(player->player_dest.x - enemy_list[0]->destRect.x) << "     " << enemy_list[0]->srcRect.h << std::endl;
        }

        std::cout << player->destRect.x << "   player x   " << enemy_list[0]->destRect.x << "   enemy x     " << std::endl;
        if(!check_collision(player->destRect, enemy_list[0]->destRect))
        {
            enemy_list[0]->Render(0);
        }
        else
        {
            enemy_list[0]->Render(285);
        }
        
        
        std::cout << check_collision(player->destRect, enemy_list[0]->destRect) << std::endl;
        
    }
    else
    {
        currentScreen->Render();
    }
    //update screen
    SDL_RenderPresent(renderer);
}

void Game::gameLoop()
{
    const int FPS = 60;
    const int framedelay = 1000 / FPS;
    const SDL_Rect* a = &(player->player_dest);
    const SDL_Rect* b = &(enemy_list[0]->destRect);

    

    int frameTime;
    currentScreen = startscreen;
    isPolluted = true;
    while (isRunning)
    {
        handleEvents();
        Update();
        Render();
        //break;
        frameStart = SDL_GetTicks();
        frameTime = SDL_GetTicks() - frameStart;

        if (framedelay > frameTime)
        {
            // std::cout << frameStart << std::endl;
            // std::cout << frameTime << std::endl;
            SDL_Delay(framedelay - frameTime);
        }
    }
}

void Game::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

Game::~Game()
{
    delete mainscreen;
    delete startscreen;
    delete gameoverscreen;
    delete pausescreen;
    delete earth;

    for (int i = 0; i < 2; i++)
    {
        delete[] life[i];
    }
    for (int i = 0; i < 3; i++)
    {
        delete[] pollutedObj[3];
    }
    for (int i = 0; i < 6; i++)
    {
        delete[] cleanObj[i];
    }
    delete[] life;
    delete[] pollutedObj;
    delete[] cleanObj;
}


bool Game::check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
