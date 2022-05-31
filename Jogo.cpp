#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "objects.h"

//Globais
enum keys { UP, DOWN, LEFT, RIGHT,SPACE, W, A , S, D, ESCAPE,ENTER };
bool keys[11] = { false, false, false, false, false, false, false ,false ,false, false,false};
const int LARGURA = 1280;
const int ALTURA = 720;
const int NUM_BULLETS = 5;
const int NUM_ENEMYS = 10;
const int NUM_EXPLOSIONS = 5;
const int VITORIA = 50;
enum STATE{TITLE,PLAYING,LOST,WIN};

Player naruto;
Bullet bullets[NUM_BULLETS];
Enemy enemy[NUM_ENEMYS];
Explosion explosions[NUM_EXPLOSIONS];
Background FG;




//Prototipacao
void InitPlayer(Player &naruto, ALLEGRO_BITMAP *image);
void CriarPlayer(Player &naruto);
void MoverPlayerUp(Player &naruto);
void MoverPlayerDown(Player &naruto);
void MoverPlayerLeft(Player &naruto);
void MoverPlayerRight(Player &naruto);

void InitBullets(Bullet bullet[],int size,ALLEGRO_BITMAP *image);
void CriaBullet(Bullet bullet[],int size, Player &naruto);
void AtiraBullet(Bullet bullet[],int size, Player &naruto);
void AtualizarBullet(Bullet bullet[],int size);
void ColidirBullet(Bullet bullet[], int bSize, Enemy enemy[], int eSize,Player &naruto,Explosion explosions[],int rSize);

void InitEnemys(Enemy enemy[],int size,ALLEGRO_BITMAP *image);
void CriaEnemy(Enemy enemy[],int size);
void ComecaEnemy(Enemy enemy[],int size);
void AtualizarEnemy(Enemy enemy[],int size);
void ColidirEnemy(Enemy enemy[],int eSize,Player &naruto,Explosion explosions[],int rSize);

void InitExplosions(Explosion explosions[],int size, ALLEGRO_BITMAP *image);
void CriarExplosions(Explosion explosions[],int size);
void ComecaExplosions(Explosion explosions[],int size,int x,int z);
void AtualizarExplosions(Explosion explosions[],int size);

void InitBackground(Background &back, float x, float y, float velX, float vely, int width, int height, int dirX, int dirY,ALLEGRO_BITMAP *image);
void AtualizaBackground(Background &back);
void CriaBackground(Background &back);

void ChangeState(int &state, int newState);


int main(void){

    //variaveis primitivas
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
   // bool isGameOver = false;
    int state = -1;


    //variaveis de objeto


    //variaveis do allegro
    ALLEGRO_DISPLAY*display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;
    ALLEGRO_FONT *font20 = NULL;
    ALLEGRO_BITMAP *narutoImage;
    ALLEGRO_BITMAP *enemyImage;
    ALLEGRO_BITMAP *bulletImage;
    ALLEGRO_BITMAP *expImage;
    ALLEGRO_BITMAP * fgImage = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE *rasengan = NULL;
    ALLEGRO_BITMAP *title = NULL;
    ALLEGRO_BITMAP *lost = NULL;
    ALLEGRO_BITMAP *win = NULL;



    //inicializacao de funcoes
    if(!al_init()){

        return -1;  //Iniciar allegro

    }

    display = al_create_display(LARGURA,ALTURA);    //Criar display

    if(!display){

        return -1;  //Testar display

    }

    al_init_primitives_addon();
    al_install_keyboard();  //instalar teclado
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(2);

    sample = al_load_sample("NarutoTheme-TheRaisingFightingSpirit.ogg");
    rasengan = al_load_sample("Rasengan-Sound-Effectnew.ogg");

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    narutoImage = al_load_bitmap("naruto_spritesheet_3.png");
    al_convert_mask_to_alpha(narutoImage,al_map_rgb(0,0,0));//tirar o fundo da sprite

    enemyImage = al_load_bitmap("naruto-sprites-pain-spritesheet-test.png");
    al_convert_mask_to_alpha(enemyImage,al_map_rgb(0,64,128));

    bulletImage = al_load_bitmap("vermilion_rasengan-iloveimg-resized.png");

    expImage = al_load_bitmap("explosionFull.png");

    fgImage = al_load_bitmap("konhaGatesInvertido.jpg");

    title = al_load_bitmap("titulo2.png");
    lost = al_load_bitmap("lost.png");
    win = al_load_bitmap("win.png");

    InitBackground(FG,0,0,0,0,1280,720,-1,1,fgImage);


    srand(time(NULL));

    ChangeState(state,TITLE);

    InitPlayer(naruto, narutoImage);
    InitBullets(bullets, NUM_BULLETS,bulletImage);
    InitEnemys(enemy,NUM_ENEMYS,enemyImage);
    InitExplosions(explosions,NUM_EXPLOSIONS,expImage);

    font18 = al_load_font("Arial.ttf",35,0);
    font20 = al_load_font("Arial.ttf",18,0);

    al_register_event_source(event_queue,al_get_keyboard_event_source());   //registar teclado
    al_register_event_source(event_queue,al_get_timer_event_source(timer)); //registrar timer
    al_register_event_source(event_queue, al_get_display_event_source(display));



    al_start_timer(timer);

    al_play_sample(sample,0.8,0,1,ALLEGRO_PLAYMODE_LOOP,NULL);

    while(!done){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);

        if(ev.type == ALLEGRO_EVENT_TIMER){

            redraw = true;
            if(keys[UP])
                MoverPlayerUp(naruto);
            else if(keys[DOWN])
                MoverPlayerDown(naruto);
            else if(keys[LEFT])
                MoverPlayerLeft(naruto);
            else if(keys[RIGHT])
                MoverPlayerRight(naruto);
            else if(keys[W])
                MoverPlayerUp(naruto);
            else if(keys[S])
                MoverPlayerDown(naruto);
            else if(keys[A])
                MoverPlayerLeft(naruto);
            else if(keys[D])
                MoverPlayerRight(naruto);

            if(state == TITLE){



            }else if(state == PLAYING){

                AtualizaBackground(FG);

                AtualizarExplosions(explosions,NUM_EXPLOSIONS);
                AtualizarBullet(bullets, NUM_BULLETS);
                ComecaEnemy(enemy,NUM_ENEMYS);
                AtualizarEnemy(enemy,NUM_ENEMYS);
                ColidirBullet(bullets, NUM_BULLETS, enemy, NUM_ENEMYS,naruto,explosions,NUM_EXPLOSIONS);
                ColidirEnemy(enemy, NUM_ENEMYS, naruto,explosions,NUM_EXPLOSIONS);


                if(naruto.lives <= 0)
                    ChangeState(state,LOST);

                if(naruto.score == VITORIA)
                    ChangeState(state,WIN);

            }else if(state == LOST){



            }else if(state == WIN){



            }


        }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;

            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;

            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                if(state == TITLE){
                    ChangeState(state,PLAYING);

                }else if(state == PLAYING){

                    AtiraBullet(bullets,NUM_BULLETS,naruto);
                    al_play_sample(rasengan,0.5,0,1.5,ALLEGRO_PLAYMODE_ONCE,NULL);
                    naruto.curFrame = 3;

                }else if(state == LOST ){
                    ChangeState(state,PLAYING);
                }else if(state == WIN){
                    ChangeState(state,PLAYING);
                }

                break;

            case ALLEGRO_KEY_W:
                keys[W] = true;
                break;

            case ALLEGRO_KEY_S:
                keys[S] = true;
                break;

            case ALLEGRO_KEY_A:
                keys[A] = true;
                break;

            case ALLEGRO_KEY_D:
                keys[D] = true;
                break;

            case ALLEGRO_KEY_ESCAPE:
                keys[ESCAPE] = true;
                if(state == LOST || state == WIN)
                    ChangeState(state,TITLE);

                break;

            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = true;
                if(state == TITLE)
                    done = true;
                break;

            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_UP){

            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;

            case ALLEGRO_KEY_ESCAPE:
                keys[ESCAPE] = false;
                break;

             case ALLEGRO_KEY_W:
                keys[W] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_S:
                keys[S] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_A:
                keys[A] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_D:
                keys[D] = false;
                naruto.curFrame = 1;
                break;

            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = false;
                break;


            }
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            done = true;

        }


        if(redraw && al_is_event_queue_empty(event_queue)){

            redraw = false;

            if(state == TITLE){

                al_draw_bitmap(title,0,0,0);

            }else if(state == PLAYING){


                CriaBackground(FG);

                CriarPlayer(naruto);
                CriaBullet(bullets, NUM_BULLETS,naruto);
                CriaEnemy(enemy, NUM_ENEMYS);
                CriarExplosions(explosions,NUM_EXPLOSIONS);


                al_draw_textf(font20, al_map_rgb(255,255,255), 5,5,0," Vidas restantes: %i      Score: %i ",naruto.lives,naruto.score);


            }else if(state == LOST){


                al_draw_bitmap(lost,0,0,0);
                al_draw_textf(font18, al_map_rgb(255,255,255),LARGURA/7.8,ALTURA/1.8,ALLEGRO_ALIGN_CENTER,"Score final: %i",naruto.score);

            }else if(naruto.score == VITORIA){

                al_draw_bitmap(win,0,0,0);

            }


            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));

        }
    }

    al_destroy_bitmap(win);
    al_destroy_bitmap(title);
    al_destroy_bitmap(lost);
    al_destroy_sample(sample);
    al_destroy_bitmap(fgImage);
    al_destroy_bitmap(expImage);
    al_destroy_bitmap(bulletImage);
    al_destroy_bitmap(enemyImage);
    al_destroy_bitmap(narutoImage);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font18);
    al_destroy_font(font20);
    al_destroy_display(display); //Destruir display

    return 0;
}

void InitPlayer(Player &naruto, ALLEGRO_BITMAP *image = NULL){

    naruto.x = 50;
    naruto.y = ALTURA/2;
    naruto.ID = PLAYER;
    naruto.lives = 3;
    naruto.speed = 9;
    naruto.boundx = 6;
    naruto.boundy = 7;
    naruto.score = 0;

    naruto.maxFrame = 6;
    naruto.curFrame = 0;
    naruto.frameCount = 50;
    naruto.frameDelay = 5;
    naruto.frameWidth = 68;
    naruto.frameHeight = 80;
    naruto.animationColumns = 6;
    naruto.animationDirection = 1;

    naruto.animationRow = 0;

    if(image != NULL)
        naruto.image = image;

}


void CriarPlayer(Player &naruto){

    int fx = (naruto.curFrame % naruto.animationColumns) * naruto.frameWidth;
    int fy = naruto.animationRow * naruto.frameHeight;

    al_draw_bitmap_region(naruto.image,fx,fy,naruto.frameWidth,
                          naruto.frameHeight,naruto.x - naruto.frameWidth/2,naruto.y - naruto.frameHeight/4,0);

}

void MoverPlayerUp(Player &naruto){

     naruto.curFrame = 2;

    naruto.y -= naruto.speed;
    if(naruto.y < 10){

        naruto.y = 10;

    }

}

void MoverPlayerDown(Player &naruto){

     naruto.curFrame = 3;

    naruto.y += naruto.speed;
    if(naruto.y > ALTURA-10){

        naruto.y = ALTURA-10;

    }

}

void MoverPlayerLeft(Player &naruto){

    naruto.curFrame = 4;
    naruto.x -= naruto.speed;
    if(naruto.x <0){

        naruto.x = 0;

    }

}

void MoverPlayerRight(Player &naruto){

    naruto.curFrame = 5;

    naruto.x += naruto.speed;
    if(naruto.x > LARGURA-10){

        naruto.x = LARGURA-10;

    }

}

void InitBullets(Bullet bullet[],int size,ALLEGRO_BITMAP *image = NULL){

    for(int i = 0;i < size; i++){

        bullet[i].ID = BULLET;
        bullet[i].speed = 10;
        bullet[i].live = false;

        bullet[i].maxFrame = 1;
        bullet[i].curFrame = 0;
        bullet[i].frameCount = 0;
        bullet[i].frameDelay = 1;
        bullet[i].frameWidth = 40;
        bullet[i].frameHeight = 40;
        bullet[i].animationColumns = 1;
        bullet[i].animationDirection = 1;

        if(image != NULL)
            bullet[i].image = image;

    }

}

void CriaBullet(Bullet bullet[],int size, Player &naruto){

    for (int i = 0;i < size; i++){

        if(bullet[i].live){

                int fx = (bullet[i].curFrame % bullet[i].animationColumns) * bullet[i].frameWidth;
                int fy = (bullet[i].curFrame / bullet[i].animationColumns) * bullet[i].frameHeight;

                al_draw_bitmap_region(bullet[i].image,fx,fy,bullet[i].frameWidth,
                                      bullet[i].frameHeight,bullet[i].x - bullet[i].frameWidth/2,bullet[i].y - bullet[i].frameHeight/4,0);
            //al_draw_filled_circle(bullet[i].x,bullet[i].y,5,al_map_rgb(255,0,255));

        }


    }

}

void AtiraBullet(Bullet bullet[],int size, Player &naruto){

    for(int i = 0; i < size ; i++){

        if(!bullet[i].live){

            bullet[i].x = naruto.x+17;
            bullet[i].y = naruto.y;
            bullet[i].live = true;
            naruto.curFrame = 3;
            break;

        }

    }

}

void AtualizarBullet(Bullet bullet[],int size){

    for(int i= 0;i < size; i++){

        if(bullet[i].live){

            bullet[i].x += bullet[i].speed;
            if(bullet[i].x > LARGURA)
                bullet[i].live = false;

        }

    }

}

void ColidirBullet(Bullet bullet[], int bSize, Enemy enemy[], int eSize,Player &naruto,Explosion explosions[],int rSize){

    for( int i = 0; i < bSize; i++){

        if(bullet[i].live){

            for( int j = 0; j < eSize; j++){

                if(enemy[j].live){

                    if(bullet[i].x > (enemy[j].x - enemy[j].boundx) &&
                        bullet[i].x < (enemy[j].x + enemy[j].boundx) &&
                        bullet[i].y > (enemy[j].y - enemy[j].boundy) &&
                        bullet[i].y < (enemy[j].y + enemy[j].boundy)){

                            bullet[i].live = false;
                            enemy[j].live = false;

                            naruto.score++;

                            ComecaExplosions(explosions,eSize,bullet[i].x,bullet[i].y);

                        }

                }

            }

        }

    }

}

void InitEnemys(Enemy enemy[],int size,ALLEGRO_BITMAP *image = NULL){

    for(int i = 0; i < size; i++){

        enemy[i].ID = ENEMY;
        enemy[i].live = false;
        enemy[i].speed = 3;
        enemy[i].boundx = 29;
        enemy[i].boundy = 39;

        enemy[i].maxFrame = 5;
        enemy[i].curFrame = 0;
        enemy[i].frameCount = 0;
        enemy[i].frameDelay = 40;
        enemy[i].frameWidth = 70;
        enemy[i].frameHeight = 80;
        enemy[i].animationColumns = 6;
        enemy[i].animationDirection = 1;

        if(image != NULL)
            enemy[i].image = image;



    }

}

void CriaEnemy(Enemy enemy[],int size){

    for (int i=0; i < size; i++){

        if(enemy[i].live){

           int fx = (enemy[i].curFrame % enemy[i].animationColumns) * enemy[i].frameWidth;
           int fy = (enemy[i].curFrame / enemy[i].animationColumns) * enemy[i].frameHeight;

            al_draw_bitmap_region(enemy[i].image,fx,fy,enemy[i].frameWidth,
                                  enemy[i].frameHeight,enemy[i].x - enemy[i].frameWidth/2,enemy[i].y - enemy[i].frameHeight/2,0);

            /*al_draw_filled_rectangle(enemy[i].x - enemy[i].boundx, enemy[i].y - enemy[i].boundy,enemy[i].x + enemy[i].boundx,
                                     enemy[i].y + enemy[i].boundy,al_map_rgba(255,0,255,100));*/

        }

    }

}

void ComecaEnemy(Enemy enemy[],int size){

    for (int i = 0; i< size; i++){

        if(!enemy[i].live){

            if(rand() % 500 == 0){

                enemy[i].live = true;
                enemy[i].x = LARGURA;
                enemy[i].y = 30 + rand()% (ALTURA - 60);
                break;

            }

        }

    }

}

void AtualizarEnemy(Enemy enemy[],int size){

    for( int i = 0; i< size; i++){

        if(enemy[i].live){

            if(++enemy[i].frameCount >= enemy[i].frameDelay){

                enemy[i].curFrame += enemy[i].animationDirection;

                if(enemy[i].curFrame >= enemy[i].maxFrame)
                    enemy[i].curFrame =0;
                else if(enemy[i].curFrame <= 0)
                    enemy[i].curFrame = enemy[i].maxFrame -1;

                enemy[i].frameCount = 0;
            }

            enemy[i].x -= enemy[i].speed;

        }

    }

}

void ColidirEnemy(Enemy enemy[],int eSize,Player &naruto,Explosion explosions[],int rSize){

    for( int i = 0; i< eSize; i++){

        if(enemy[i].live){

            if(enemy[i].x - enemy[i].boundx < naruto.x + naruto.boundx &&
                enemy[i].x + enemy[i].boundx > naruto.x - naruto.boundx &&
                enemy[i].y - enemy[i].boundy < naruto.y + naruto.boundy &&
                enemy[i].y + enemy[i].boundy > naruto.y - naruto.boundy){

                    naruto.lives--;
                    enemy[i].live = false;
                    ComecaExplosions(explosions,eSize,naruto.x,naruto.y);

                }else if(enemy[i].x < 0){

                    enemy[i].live = false;
                    naruto.lives--;

                }

        }

    }

}

void InitExplosions(Explosion explosions[],int size, ALLEGRO_BITMAP *image = NULL){

    for(int i=0;i<size;i++){

        explosions[i].live = false;

        explosions[i].maxFrame = 32;
        explosions[i].curFrame = 0;
        explosions[i].frameCount = 0;
        explosions[i].frameDelay = 1;
        explosions[i].frameWidth = 250;
        explosions[i].frameHeight = 250;
        explosions[i].animationColumns = 8;
        explosions[i].animationDirection = 1;

        if(image != NULL)
            explosions[i].image = image;

    }

}

void CriarExplosions(Explosion explosions[],int size){

    for(int i=0;i<size;i++){

        if(explosions[i].live){

            int fx = (explosions[i].curFrame % explosions[i].animationColumns)* explosions[i].frameWidth;
            int fy = (explosions[i].curFrame / explosions[i].animationColumns)* explosions[i].frameHeight;

            al_draw_bitmap_region(explosions[i].image,fx,fy,explosions[i].frameWidth,
                                  explosions[i].frameHeight,explosions[i].x - explosions[i].frameWidth/2,explosions[i].y - explosions[i].frameHeight/2,0 );

        }

    }

}

void ComecaExplosions(Explosion explosions[],int size,int x,int y){

    for(int i=0;i<size;i++){

        if(!explosions[i].live){

            explosions[i].live = true;
            explosions[i].x = x;
            explosions[i].y = y;
            break;

        }
    }



}

void AtualizarExplosions(Explosion explosions[],int size){

    for(int i=0;i < size; i++){

        if(explosions[i].live){

            if(++explosions[i].frameCount >= explosions[i].frameDelay){

                explosions[i].curFrame += explosions[i].animationDirection;

                if(explosions[i].curFrame >= explosions[i].maxFrame){

                    explosions[i].curFrame=0;
                    explosions[i].live = false;

                }
                explosions[i].frameCount = 0;
            }

        }

    }

}

void InitBackground(Background &back, float x, float y, float velX, float vely, int width, int height, int dirX, int dirY,ALLEGRO_BITMAP *image){

    back.x = x;
    back.y = y;
    back.velX = velX;
    back.velY = vely;
    back.width = width;
    back.height = height;
    back.dirX = dirX;
    back.dirY = dirY;
    back.image = image;

}

void AtualizaBackground(Background &back){

    back.x += back.velX * back.dirX;
    if(back.x + back.width <=0)
        back.x = 0;

}

void CriaBackground(Background &back){

    al_draw_bitmap(back.image,back.x,back.y,0);

    if(back.x + back.width < LARGURA)
        al_draw_bitmap(back.image,back.x+back.width,back.y,0);



}

void ChangeState(int &state, int newState){

    if(state == TITLE){



    }else if(state == PLAYING){



    }else if(state == LOST){



    }

    state = newState;

    if(state == TITLE){



    }else if(state == PLAYING){

        InitPlayer(naruto);
        InitBullets(bullets, NUM_BULLETS);
        InitEnemys(enemy,NUM_ENEMYS);
        InitExplosions(explosions,NUM_EXPLOSIONS);


    }else if(state == LOST){



    }

}
