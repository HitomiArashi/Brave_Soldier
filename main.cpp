#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"

BaseObject g_background; //Save the infomation about the background
bool check_upload;

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
        g_window = SDL_CreateWindow(NAME_OF_THE_APP,            //Title or name of the window
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

std::vector <ThreatObject*> MakeThreatList()
{
    std::vector<ThreatObject*> list;

    ThreatObject* dynamic_threat = new ThreatObject[20];
    for (int i = 0; i < THREAT_AMOUNT; i++)
    {
        ThreatObject* p_threat = (dynamic_threat + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Resources//img//threat_left.png", g_screen);
            p_threat->SetClip();
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);
            p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_input_left(1);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_y_pos() + 60;
            p_threat->set_animationPos(pos1, pos2);

            list.push_back(p_threat);
        }
    }

    ThreatObject* threat_objs = new ThreatObject[THREAT_AMOUNT];
    for (int i = 0; i < THREAT_AMOUNT; i++)
    {
        ThreatObject* p_threat = (threat_objs + 1);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("Resources//img//threat_level.png", g_screen);
            p_threat->SetClip();
            p_threat->set_x_pos(THREAT_ORIGINAL + i * THREAT_DISTANCE);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            list.push_back(p_threat);
        }
    }
    return list;
}

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

    //Make threat object
    std::vector<ThreatObject*> threat = MakeThreatList();

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

        for (int i = 0; i < threat.size(); i++)
        {
            ThreatObject* p_threat = threat.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->HandleMove(map_data);
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
