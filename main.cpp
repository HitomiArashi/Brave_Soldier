#include "CommonFunction.h"
#include "BackgroundApply.h"

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
