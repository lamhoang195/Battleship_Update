#include <bits/stdc++.h>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PowerObject.h"
#include "TextObject.h"
#include "BossObject.h"
#include "MenuObject.h"
#include <vector>
#include <ctime>

TTF_Font* font_time;
TTF_Font* font_menu;
Uint8 a = 255;
long long CurrentTime;
long long LastTime;

BaseObject g_background;
BaseObject gameover;
BaseObject g_menu;
BaseObject g_gameover;
BaseObject g_win;
BaseObject gamewin;

PlayerObject g_playerobject;

ThreatsObject g_threats_1;
ThreatsObject g_threats_2;
ThreatsObject g_threats_3;
ThreatsObject g_threats_4;
ThreatsObject g_threats_5;
ThreatsObject g_threats_6;

BossObject g_boss;

MenuObject PlayButton;
MenuObject QuitButton;

//khởi động thông số cửa sổ
bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    //thiết lập tỉ lệ chất lượng
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //tạo cửa sổ window
    g_window = SDL_CreateWindow("Game Battleship",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN
                                );
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);//màu sắc render ra màn hinh

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
        if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 )
        {
            success = true;
        }
        //Doc file wav audio
        g_sound_laser_l = Mix_LoadWAV("Mixer/sfx_laser1.wav");
        g_sound_exp_player = Mix_LoadWAV("Mixer/shipExplosion.wav");
        g_sound_exp_threats = Mix_LoadWAV("Mixer/shipExplosion.wav");
        g_sound_play = Mix_LoadWAV("Mixer/play.mp3");
        g_sound_gameover = Mix_LoadWAV("Mixer/gameover.mp3");
        g_sound_menu = Mix_LoadWAV("Mixer/GameOverBGM.wav");
        g_sound_gamewin = Mix_LoadWAV("Mixer/GameWin.mp3");

        if(g_sound_bullet == NULL || g_sound_exp_player == NULL || g_sound_exp_threats == NULL || g_sound_laser_l == NULL || g_sound_laser_r == NULL)
        {
            success = true;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("Font/kenvector_future.ttf", 20);
        font_menu = TTF_OpenFont("Font/kenvector_future.ttf", 30);
        if(font_time == NULL)
        {
            success = false;
        }
        if(font_menu == NULL)
        {
            success = false;
        }
    }
    return success;
}

void Clean()
{
    g_background.Free();
    g_playerobject.Free();
    gameover.Free();

    SDL_DestroyRenderer(g_screen);//giải phóng g_screen
    g_screen = NULL;

    SDL_DestroyWindow(g_window);//giải phóng cửa sổ g_window
    g_window = NULL;

    Mix_FreeChunk(g_sound_bullet);
    g_sound_bullet = NULL;
    Mix_FreeChunk(g_sound_laser_l);
    g_sound_laser_l = NULL;
    Mix_FreeChunk(g_sound_laser_r);
    g_sound_laser_r = NULL;
    Mix_FreeChunk(g_sound_exp_player);
    g_sound_exp_player = NULL;
    Mix_FreeChunk(g_sound_menu);
    g_sound_menu = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    ImpTimer fps_timer;
    int bg_y = 0;
    if(init() == false)
        return -1;

    g_background.LoadImg("Image/Background/background.jpg", g_screen);
    gamewin.LoadImg("Image/Background/background.jpg", g_screen);
    gameover.LoadImg("Image/Background/background.jpg", g_screen);
    g_gameover.LoadImg("Image/Background/Gameover.png", g_screen);
    g_playerobject.LoadImg("Image/Player/shipLoser1.png", g_screen);
    g_menu.LoadImg("Image/Player/Menu.png", g_screen);
    g_win.LoadImg("Image/Background/GameWin.png", g_screen);

    g_threats_1.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
    g_threats_2.LoadImg("Image/Player/Enemies/enemyBlue4.png", g_screen);
    g_threats_3.LoadImg("Image/Player/Enemies/enemyRed4.png", g_screen);
    g_threats_4.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
    g_threats_5.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
    g_threats_6.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);

    g_boss.LoadImg("Image/Player/boss.png", g_screen);

    //máu threat 2 và 3
    int threats_2_die = 1;
    int threats_3_die = 2;

    //khởi tạo threats
    g_threats_1.set_y_val(2);
    g_threats_1.GenerateBullet(g_screen, g_sound_bullet);
    Mix_PlayChannel(-1, g_sound_bullet, 0);

    g_threats_2.set_y_val(2);
    g_threats_2.GenerateBullet(g_screen, g_sound_bullet);

    g_threats_3.set_y_val(2);
    g_threats_3.GenerateBullet(g_screen, g_sound_bullet);

    g_threats_4.set_y_val(2);
    g_threats_4.GenerateBullet(g_screen, g_sound_bullet);

    g_threats_5.set_y_val(2);
    g_threats_5.GenerateBullet(g_screen, g_sound_bullet);

    g_threats_6.set_y_val(2);
    g_threats_6.GenerateBullet(g_screen, g_sound_bullet);

    //Khởi tạo boss
    g_boss.set_stats();
    g_boss.set_x_pos(SCREEN_WIDTH/2 - 370/2);
    g_boss.set_y_limit(25);
    g_boss.set_y_pos(-200);
    g_boss.set_health(500);

    ExplosionObject exp_player;
    bool tRet = exp_player.LoadImg("Image/Player/explosion.png", g_screen);
    if(!tRet) return -1;
    exp_player.set_clip();

    //Power
    PowerObject power_player;
    power_player.InitP(g_screen);

    //Time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    UINT score_value = 0;

    //Giảm âm lượng âm thanh
    Mix_VolumeChunk(g_sound_play, MIX_MAX_VOLUME/5);
    Mix_VolumeChunk(g_sound_exp_player, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(g_sound_menu, MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(g_sound_gameover, MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(g_sound_gamewin, MIX_MAX_VOLUME);
    Mix_VolumeChunk(g_sound_laser_l, MIX_MAX_VOLUME/2);

    SDL_Event g_event;
    bool InMenu = false;
    bool play = true;
    bool GameOver = false;
    bool GameWin = false;

    //Hiện Menu
    while(!InMenu)
    {
        if(!Mix_Playing(1))
        {
            Mix_PlayChannel(1, g_sound_menu,-1);
        }
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                InMenu = false;
            }
            PlayButton.HandlePlayButton(g_event, g_screen, InMenu);
            QuitButton.HandleExitButton(g_event, g_screen, play, InMenu);
        }
        PlayButton.SetRect(60, 450);
        QuitButton.SetRect(60, 550);
        g_menu.Render(g_screen);
        PlayButton.Render(g_screen);
        QuitButton.Render(g_screen);
        SDL_RenderPresent(g_screen);
    }

    //Chơi, GameOver, GameWin
    while(play)
    {
        Mix_HaltChannel(1);
        if(!Mix_Playing(2))
        {
            Mix_PlayChannel(2, g_sound_play,-1);
        }
        fps_timer.start();
        if (!GameOver && !GameWin)
        {
             g_threats_1.LoadImg("Image/Player/Enemies/enemyBlack4.png", g_screen);
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    play = false;
                }
                g_playerobject.HanderInputAction(g_event, g_screen, g_sound_laser_l);
            }
            //trước load ảnh sét lại màu cho màn hình
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

            SDL_RenderClear(g_screen);//xóa màn hình đi

            SDL_ShowCursor(SDL_DISABLE);//ẩn chuột

            g_background.MoveBackGround(g_screen, NULL);

            power_player.ShowP(g_screen);

            g_playerobject.HandleMove();
            g_playerobject.Render(g_screen, NULL);
            g_playerobject.HandleLaser(g_screen);

            g_threats_1.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            g_threats_1.Render(g_screen, NULL);
            g_threats_1.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT/2);

            //check flick
            CurrentTime = SDL_GetTicks();
            if (g_playerobject.get_flick() == true)
            {
                if (CurrentTime >= LastTime + 3000)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                }
                else
                {
                    g_playerobject.flicking(a);
                    g_playerobject.setAlpha(a);
                }
            }
            if (g_playerobject.get_flick() == false)
            {
                g_playerobject.setAlpha(255);
            }


            int frame_exp_width = exp_player.get_frame_width();
            int frame_exp_height = exp_player.get_frame_height();

            //va cham voi may bay dich 1
            bool is_col_1 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_1.GetRect());
            if(is_col_1 && CurrentTime >= LastTime + 3000)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_1.GetRect().x + g_threats_1.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_1.GetRect().y + g_threats_1.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                }
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                g_threats_1.ResetThreats(SCREEN_WIDTH);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 1
            std::vector <EnemyBullet*> enemybullet_list_1 = g_threats_1.get_bullet_list();
            for(int i = 0; i < enemybullet_list_1.size(); i++)
            {
                EnemyBullet* p_enemybullet_1 = enemybullet_list_1.at(i);
                if(p_enemybullet_1 != NULL)
                {
                    bool ret_col= SDL_Common::check_overlap(p_enemybullet_1->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000)
                    {
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_1.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            g_playerobject.set_flick(false);
                            a = 255;
                            GameOver = true;
                        }
                        LastTime=CurrentTime;
                    }
                }
            }

            //may bay dich 1 va cham voi laser
            std::vector <LaserObject*> laser_list_1 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_1.size(); i++)
            {
                LaserObject* p_laser_1 = laser_list_1.at(i);
                if(p_laser_1 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_1->GetRect(), g_threats_1.GetRect());
                    if(ret_col)
                    {
                        score_value++;
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_1->GetRect().x + p_laser_1->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_1->GetRect().y + p_laser_1->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                        }
                        g_threats_1.ResetThreats(SCREEN_WIDTH);
                        g_playerobject.RemoveLaser(i);
                    }
                }
            }

            //va cham voi may bay 2
            bool is_col_2 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_2.GetRect());
            if(is_col_2 && CurrentTime >= LastTime + 3000 && score_value >= 5)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_2.GetRect().x + g_threats_2.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_2.GetRect().y + g_threats_2.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                }
                //g_threats1.ResetThreats(SCREEN_WIDTH);
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                power_player.Decrease();
                g_threats_2.ResetThreats(SCREEN_WIDTH);
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 2
            std::vector <EnemyBullet*> enemybullet_list_2 = g_threats_2.get_bullet_list();
            for(int i = 0; i < enemybullet_list_2.size(); i++)
            {
                EnemyBullet* p_enemybullet_2 = enemybullet_list_2.at(i);
                if(p_enemybullet_2 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_enemybullet_2->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 5)
                    {
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_2.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            GameOver = true;
                            g_playerobject.set_flick(false);
                            a = 255;
                        }
                        LastTime = CurrentTime;
                    }
                }
            }

            //may bay 2 va cham voi laser
            std::vector <LaserObject*> laser_list_2 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_2.size(); i++)
            {
                LaserObject* p_laser_2 = laser_list_2.at(i);
                if(p_laser_2 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_2->GetRect(), g_threats_2.GetRect());
                    if(ret_col && score_value >= 5)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_2->GetRect().x + p_laser_2->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_2->GetRect().y + p_laser_2->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                        }
                        if(threats_2_die == 1)
                        {
                            threats_2_die--;
                            g_playerobject.RemoveLaser(i);
                        }
                        else if(threats_2_die == 0)
                        {
                            score_value++;
                            g_threats_2.ResetThreats(SCREEN_WIDTH);
                            threats_2_die = 1;
                            g_playerobject.RemoveLaser(i);
                        }
                    }
                }
            }

            //va cham voi may bay 3
            bool is_col_3 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_3.GetRect());
            if(is_col_3 && CurrentTime >= LastTime + 3000 && score_value >= 10)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_3.GetRect().x + g_threats_3.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_3.GetRect().y + g_threats_3.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                power_player.Decrease();
                g_threats_3.ResetThreats(SCREEN_WIDTH);
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    GameOver = true;
                    g_playerobject.set_flick(false);
                    a = 255;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 3
            std::vector <EnemyBullet*> enemybullet_list_3 = g_threats_3.get_bullet_list();
            for(int i = 0; i < enemybullet_list_3.size(); i++)
            {
                EnemyBullet* p_enemybullet_3 = enemybullet_list_3.at(i);
                if(p_enemybullet_3 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_enemybullet_3->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 10)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = g_playerobject.GetRect().x + g_playerobject.GetRect().w*0.5 - 118*0.5;
                            int y_pos = g_playerobject.GetRect().y + g_playerobject.GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            SDL_RenderPresent(g_screen);
                        }
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_3.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            a = 255;
                            GameOver = true;
                            g_playerobject.set_flick(false);
                        }
                        LastTime = CurrentTime;
                    }
                }
            }

            //may bay 3 va cham voi laser
            std::vector <LaserObject*> laser_list_3 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_3.size(); i++)
            {
                LaserObject* p_laser_3 = laser_list_3.at(i);
                if(p_laser_3 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_3->GetRect(), g_threats_3.GetRect());
                    if(ret_col && score_value >= 10)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_3->GetRect().x + p_laser_3->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_3->GetRect().y + p_laser_3->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                        }
                        if(threats_3_die == 1 || threats_3_die == 2)
                        {
                            threats_3_die--;
                            g_playerobject.RemoveLaser(i);
                        }
                        else if(threats_3_die == 0)
                        {
                            score_value++;
                            g_threats_3.ResetThreats(SCREEN_WIDTH);
                            threats_3_die = 2;
                            g_playerobject.RemoveLaser(i);
                        }
                    }
                }
            }

            //va cham voi may bay dich 4
            bool is_col_4 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_4.GetRect());
            if(is_col_4 && CurrentTime >= LastTime + 3000 && score_value >= 2)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_4.GetRect().x + g_threats_4.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_4.GetRect().y + g_threats_4.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                }
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                g_threats_4.ResetThreats(SCREEN_WIDTH);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 4
            std::vector <EnemyBullet*> enemybullet_list_4 = g_threats_4.get_bullet_list();
            for(int i = 0; i < enemybullet_list_4.size(); i++)
            {
                EnemyBullet* p_enemybullet_4 = enemybullet_list_4.at(i);
                if(p_enemybullet_4 != NULL)
                {
                    bool ret_col= SDL_Common::check_overlap(p_enemybullet_4->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 2)
                    {
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_4.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            g_playerobject.set_flick(false);
                            a = 255;
                            GameOver = true;
                        }
                        LastTime=CurrentTime;
                    }
                }
            }

            //may bay dich 4 va cham voi laser
            std::vector <LaserObject*> laser_list_7 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_7.size(); i++)
            {
                LaserObject* p_laser_4 = laser_list_7.at(i);
                if(p_laser_4 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_4->GetRect(), g_threats_4.GetRect());
                    if(ret_col && score_value >= 2)
                    {
                        score_value++;
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_4->GetRect().x + p_laser_4->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_4->GetRect().y + p_laser_4->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        g_threats_4.ResetThreats(SCREEN_WIDTH);
                        g_playerobject.RemoveLaser(i);
                    }
                }
            }

            //va cham voi may bay dich 5
            bool is_col_5 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_5.GetRect());
            if(is_col_5 && CurrentTime >= LastTime + 3000 && score_value >= 6)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_5.GetRect().x + g_threats_5.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_5.GetRect().y + g_threats_5.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                }
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                g_threats_5.ResetThreats(SCREEN_WIDTH);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 5
            std::vector <EnemyBullet*> enemybullet_list_5 = g_threats_5.get_bullet_list();
            for(int i = 0; i < enemybullet_list_5.size(); i++)
            {
                EnemyBullet* p_enemybullet_5 = enemybullet_list_5.at(i);
                if(p_enemybullet_5 != NULL)
                {
                    bool ret_col= SDL_Common::check_overlap(p_enemybullet_5->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 4)
                    {
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_5.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            g_playerobject.set_flick(false);
                            a = 255;
                            GameOver = true;
                        }
                        LastTime=CurrentTime;
                    }
                }
            }

            //may bay dich 5 va cham voi laser
            std::vector <LaserObject*> laser_list_5 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_5.size(); i++)
            {
                LaserObject* p_laser_5 = laser_list_1.at(i);
                if(p_laser_5 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_5->GetRect(), g_threats_5.GetRect());
                    if(ret_col && score_value >= 4)
                    {
                        score_value++;
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_5->GetRect().x + p_laser_5->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_5->GetRect().y + p_laser_5->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                        }
                        g_threats_5.ResetThreats(SCREEN_WIDTH);
                        g_playerobject.RemoveLaser(i);
                    }
                }
            }

            //va cham voi may bay dich 6
            bool is_col_6 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_threats_6.GetRect());
            if(is_col_6 && CurrentTime >= LastTime + 3000 && score_value >= 6)
            {
                score_value++;
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_threats_6.GetRect().x + g_threats_6.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_threats_6.GetRect().y + g_threats_6.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                }
                g_playerobject.got_hit();
                g_playerobject.set_flick(true);
                g_threats_6.ResetThreats(SCREEN_WIDTH);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua may bay 6
            std::vector <EnemyBullet*> enemybullet_list_6 = g_threats_6.get_bullet_list();
            for(int i = 0; i < enemybullet_list_6.size(); i++)
            {
                EnemyBullet* p_enemybullet_6 = enemybullet_list_6.at(i);
                if(p_enemybullet_6 != NULL)
                {
                    bool ret_col= SDL_Common::check_overlap(p_enemybullet_6->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 6)
                    {
                        power_player.Decrease();
                        g_playerobject.set_flick(true);
                        g_playerobject.got_hit();
                        g_threats_6.RemoveBullet(i);
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            g_playerobject.set_flick(false);
                            a = 255;
                            GameOver = true;
                        }
                        LastTime=CurrentTime;
                    }

                }
            }

            //may bay dich 6 va cham voi laser
            std::vector <LaserObject*> laser_list_6 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_6.size(); i++)
            {
                LaserObject* p_laser_6 = laser_list_6.at(i);
                if(p_laser_6 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_6->GetRect(), g_threats_6.GetRect());
                    if(ret_col && score_value >= 6)
                    {
                        score_value++;
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_6->GetRect().x + p_laser_6->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_6->GetRect().y + p_laser_6->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                        }
                        g_threats_6.ResetThreats(SCREEN_WIDTH);
                        g_playerobject.RemoveLaser(i);
                    }
                }
            }

            //va chạm với boss được miễn thương 3 giây
            bool is_col_7 = SDL_Common::check_overlap(g_playerobject.GetRect(), g_boss.GetRect());
            if(is_col_7 && CurrentTime >= LastTime + 3000 && score_value >= 50)
            {
                for(int ex = 0; ex < 5; ex++)
                {
                    int x_pos = g_boss.GetRect().x + g_boss.GetRect().w*0.5 - 118*0.5;
                    int y_pos = g_boss.GetRect().y + g_boss.GetRect().h*0.5 - 118*0.5;
                    exp_player.set_frame(ex);
                    exp_player.SetRect(x_pos, y_pos);
                    exp_player.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                Mix_PlayChannel(-1, g_sound_exp_player, 0);
                g_playerobject.set_flick(true);
                g_playerobject.got_hit();
                g_boss.got_hit(10);
                power_player.Decrease();
                SDL_RenderPresent(g_screen);
                if(g_playerobject.get_life() == 0)
                {
                    g_playerobject.set_flick(false);
                    a = 255;
                    GameOver = true;
                }
                LastTime=CurrentTime;
            }

            //va cham voi dan cua boss
            std::vector <BossBullet*> bossbullet_list = g_boss.get_boss_bullet_list();
            for(int i = 0; i < bossbullet_list.size(); i++)
            {
                BossBullet* p_bossbullet = bossbullet_list.at(i);
                if(p_bossbullet != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_bossbullet->GetRect(), g_playerobject.GetRect());
                    if(ret_col && CurrentTime >= LastTime + 3000 && score_value >= 50)
                    {
                        g_playerobject.set_flick(true);
                        power_player.Decrease();
                        g_playerobject.got_hit();
                        SDL_RenderPresent(g_screen);
                        if(g_playerobject.get_life() == 0)
                        {
                            a = 255;
                            GameOver = true;
                            g_playerobject.set_flick(false);
                        }
                        LastTime=CurrentTime;
                    }
                }
            }

            //dan play va cham voi boss
            std::vector <LaserObject*> laser_list_4 = g_playerobject.get_laser_list();
            for(int i = 0; i < laser_list_4.size(); i++)
            {
                LaserObject* p_laser_4 = laser_list_4.at(i);
                if(p_laser_4 != NULL)
                {
                    bool ret_col = SDL_Common::check_overlap(p_laser_4->GetRect(), g_boss.GetRect());
                    if(ret_col&& score_value >= 50)
                    {
                        for(int ex = 0; ex < 5; ex++)
                        {
                            int x_pos = p_laser_4->GetRect().x + p_laser_4->GetRect().w*0.5 - 118*0.5;
                            int y_pos = p_laser_4->GetRect().y + p_laser_4->GetRect().h*0.5 - 118*0.5;
                            exp_player.set_frame(ex);
                            exp_player.SetRect(x_pos, y_pos);
                            exp_player.Show(g_screen);
                            //SDL_RenderPresent(g_screen);
                        }
                        g_boss.got_hit(3);
                        g_playerobject.RemoveLaser(i);
                        if(g_boss.get_health() <= 0)
                        {
                            GameWin = true;
                        }
                    }
                }
            }

            if(score_value >= 5)
            {
                g_threats_2.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_threats_2.Render(g_screen, NULL);
                g_threats_2.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 10)
            {
                g_threats_3.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_threats_3.Render(g_screen, NULL);
                g_threats_3.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 2)
            {
                g_threats_4.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_threats_4.Render(g_screen, NULL);
                g_threats_4.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 4)
            {
                g_threats_5.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_threats_5.Render(g_screen, NULL);
                g_threats_5.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 6)
            {
                g_threats_6.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                g_threats_6.Render(g_screen, NULL);
                g_threats_6.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            if(score_value >= 50)
            {
                g_boss.MoveThreat();
                g_boss.Show(g_screen, NULL);
                if(g_boss.canspawnbullet() == true)
                {
                    g_boss.GenerateBullet(g_screen);
                }
                g_boss.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            //Show score
            std::string val_str_score = std::to_string(score_value);
            std::string strScore("Score: ");
            strScore += val_str_score;
            score_game.SetText(strScore);
            score_game.LoadFromRenderText(font_time, g_screen);
            score_game.RenderText(g_screen, SCREEN_WIDTH*0.5 -50, 5);

            //Show game time
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            std::string str_val = std::to_string(time_val);
            str_time += str_val;
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 140, 5);
            SDL_RenderPresent(g_screen);//đưa ảnh vào màn hình

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 2500/FRAME_PER_SECOND;

            if(real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >= 0)
                {
                    SDL_Delay(delay_time);
                }
            }
        }
        else if(GameOver && !GameWin)
        {
            //Cho nhac tat di o day
            Mix_HaltChannel(2);
            if(!Mix_Playing(3))
            {
                Mix_PlayChannel(3, g_sound_gameover, -1);
            }
            while(SDL_PollEvent(&g_event) !=0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    play = true;
                }
                QuitButton.HandleExitButton(g_event, g_screen, play, GameOver);
            }
            gameover.MoveBackGround(g_screen, NULL);
            g_gameover.SetRect(SCREEN_WIDTH/2 - 600/2, 0);
            g_gameover.Render(g_screen, NULL);
            QuitButton.SetRect(SCREEN_WIDTH/2 - 279/2, 520);
            QuitButton.Render(g_screen);
            SDL_ShowCursor(SDL_ENABLE);  //Hien con tro chuot
            SDL_RenderPresent(g_screen);
        }
        else
        {
            Mix_HaltChannel(3);
            if(!Mix_Playing(4))
            {
                Mix_PlayChannel(4, g_sound_gamewin, -1);
            }

            while(SDL_PollEvent(&g_event) !=0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    play = true;
                }
                QuitButton.HandleExitButton(g_event, g_screen, play, GameOver);
            }
            gamewin.Render(g_screen, NULL);
            g_win.SetRect(SCREEN_WIDTH/2 - 600/2, 0);
            g_win.Render(g_screen, NULL);
            QuitButton.SetRect(SCREEN_WIDTH/2 - 279/2, 520);
            QuitButton.Render(g_screen);
            SDL_ShowCursor(SDL_ENABLE);  //Hien con tro chuot
            SDL_RenderPresent(g_screen);
        }
    }
    Clean();
    return 0;
}
