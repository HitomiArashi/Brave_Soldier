#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"

BaseObject g_background; //Save the infomation about the background
bool check_upload; //Check the image upload process

/**
 * @brief Initialize the data
 *
 * @return true
 * @return false
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
         * @brief Create the window of the app
         *
         */
        g_window = SDL_CreateWindow(NAME_OF_THE_APP.c_str(),    //Title or name of the window
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
             * @brief Creat the background of the app
             *
             */
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
            if (g_screen == NULL) //Create failed
            {
                success = false;
            }
            else
            {
                /**
                 * @brief Construct a new sdl setrenderdrawcolor object
                 *
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
 * @brief Upload the background on window
 *
 * @return true
 * @return false
 */
bool LoadBackground()
{
    bool ret = g_background.LoadImg("Resources/img/background.png", g_screen);
    if (ret == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief Remove the memory
 *
 */
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

/**
 * @brief Make new group of threat objects
 *
 * @return std::vector<ThreatsObject*>
 */
std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* threats_obj = new ThreatsObject[20];
    for (int i = 0; i < 20; i ++)
    {
        ThreatsObject* p_threat = (threats_obj + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Resouces//img//threat_lvl.png", g_screen);
            p_threat->SetClip();
            p_threat->set_x_pos(700 + i * 1200);
            p_threat->set_y_pos(250);

            list_threats.push_back(p_threat);
        }
    }

    return list_threats;
}

/**
 * @brief Main code running
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

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
    check_upload = game_map.LoadMap("Resources/map good/map_diagram.dat");
    if (check_upload == false)
        return -1;
    game_map.LoadTiles(g_screen);
    Map map_data = game_map.getMap();

    //Make main object
    MainObject p_player;
    check_upload = p_player.LoadImg("Resources/img/player_right.png", g_screen);
    if (check_upload == false)
    {
        return -1;
    }
    p_player.SetClips();

    //Make threat objects
    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    bool is_quit = false; //Check if the app is still allowed to run
    while (!is_quit)
    {
        fps_timer.Start();

        //Check if press the "Exit" button
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen);
        }

        //Reset the screen before load the background
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        //Upload the background on the screen
        g_background.Render(g_screen, NULL);

        //Show the main object
        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        //Show the tile map
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //Show the threat objects
        for (int i = 0; i < threats_list.size(); i ++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->DoPlayer(map_data);
                p_threat->Show(g_screen);
            }
        }

        //Reset the screen to show the background
        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks(); //Time runned
        int time_per_frame = 1000 / FRAME_PER_SECOND; //Count on Milisecond

        if (real_imp_time < time_per_frame) //FPS Ratio
        {
            int delay_time = time_per_frame - real_imp_time; //Add delay time
            SDL_Delay(abs(delay_time));
        }
    }

    //Clear all memory and close all program
    Close();
    return 0;
}
