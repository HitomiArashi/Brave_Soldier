#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"

BaseObject g_background; //Save the infomation about the background

/**
Initialize the data
*/
bool InitData()
{
    bool success = true; //Check if initialization is successful
    int ret = SDL_Init(SDL_INIT_VIDEO); //Initialize the background
    if (ret < 0) //Error
    {
        success = false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //Set the ratio of the quality

        /**
        Create a window of the app
        */
        g_window = SDL_CreateWindow(NAME_OF_THE_APP,                                    //Title or name of the window
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,   //Pos of the window
                                    SCREEN_WIDTH, SCREEN_HEIGHT,                        //Size of the window
                                    SDL_WINDOW_SHOWN);                                  //Show the window

        if (g_window == NULL) //Create failed
        {
            success = false;
        }
        else
        {
            /**
            Creat the background of the app
            */
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
            if (g_screen == NULL) //Create failed
            {
                success = false;
            }
            else
            {
                /**
                Set background color when first upload
                */
                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                int imgFlags = IMG_INIT_PNG; //Initialize the format of the image will be uploaded
                if (!(IMG_Init(imgFlags)) && imgFlags) //Load failed
                {
                    success = false;
                }
            }
        }
    }
    return success; //Initialization successful
}

/**
Upload the background on window
*/
bool LoadBackground()
{
    bool ret = g_background.LoadImg("Resorces//Image//background.png", g_screen);
    if (ret == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Close()
{
    //Destroy the background and screen
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    //Destroy the window
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    //Quit program
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    //Check if init data successful
    if (InitData() == false)
    {
        return -1;
    }

    //Check if background is loaded successful
    if (LoadBackground() == false)
    {
        return -1;
    }

    //Load the tile map
    GameMap game_map;
    game_map.LoadMap("Resorces/map/map_diagram.dat");
    game_map.LoadTiles(g_screen);

    bool is_quit = false; //Check if the app is still allowed to run
    while (!is_quit)
    {
        //Check if press the "Exit" button
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
        }

        //Reset the screen before load the background
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        //Upload the background on the screen
        g_background.Render(g_screen, NULL);

        //Show the tile map
        game_map.DrawMap(g_screen);

        //Reset the screen to show the background
        SDL_RenderPresent(g_screen);
    }

    //Clear all memory and close all program
    Close();
    return 0;
}
