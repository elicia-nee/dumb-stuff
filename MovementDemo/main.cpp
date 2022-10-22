#include <iostream>

#include "raylib.h"

struct Player{
    Vector2 position;
    Texture2D up,down,left,right;
    Rectangle hitbox;
};
const int screenWidth = 720;
const int screenHeight = 480;
const int frameRate = 30;
const Vector2 center = {0,0};
int main(void){
    InitWindow(screenWidth,screenHeight,"Movement Demo");
    SetTargetFPS(frameRate);
    bool closeWindow = false;
    Player player;
    player.position = center;
    player.up = LoadTexture("resources/up_sprite.png");
    player.down = LoadTexture("resources/down_sprite.png");
    player.left = LoadTexture("resources/left_sprite.png");
    player.right = LoadTexture("resources/right_sprite.png");
    player.hitbox = {player.position.x-player.up.width/2,
                    player.position.x-player.up.width/2,
                    (float) player.up.width,(float) player.up.height};
    Rectangle room = {300,240,600,480};
    Rectangle door = {320,20,40,100};
    Rectangle doorVisualPos = {320,20,40,100};
    std::string directions[4] = {"Up","Down","Left","Right"};
    std::string facing = directions[0];
    Vector2 mousePos = {0,0};
    bool closeToDoor = false,winScreen = false;
    while (!closeWindow)
    {
        if(WindowShouldClose()) closeWindow = true;
        if(IsKeyDown(KEY_UP)) {facing = directions[0]; 
            if((player.position.y - player.hitbox.y)<room.y) player.position.y +=5;}
        if(IsKeyDown(KEY_DOWN)) {facing = directions[1]; 
            if((player.position.y+player.hitbox.y)>(room.y-room.height)) player.position.y -=5;}
        if(IsKeyDown(KEY_LEFT)) {facing = directions[2]; 
            if((player.position.x-player.hitbox.x)<room.x) player.position.x +=5;}
        if(IsKeyDown(KEY_RIGHT)) {facing = directions[3]; 
            if((player.position.x+player.hitbox.y)>(room.x-room.width)) player.position.x -=5;}
        mousePos = GetMousePosition();
        closeToDoor = abs(player.position.x-(door.x-door.width/2))<50 && 
            (player.position.y<(door.y+30)&&
                player.position.y>(door.y-door.height-30));
        doorVisualPos = {screenWidth/2-(door.x-player.position.x),screenHeight/2-(door.y-player.position.y),40,100};
        if(CheckCollisionPointRec(mousePos,doorVisualPos)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&closeToDoor){
                winScreen = true;
            }
        BeginDrawing();
            ClearBackground(winScreen?YELLOW:BLACK);
            DrawText("You Win!",screenWidth/2,screenHeight/2,40,BLACK);
            if(!winScreen){
                DrawRectangle(screenWidth/2-
                        (room.x-player.position.x),
                        screenHeight/2-(room.y-player.position.y),
                        room.width,room.height,DARKBLUE);
                DrawRectangle(screenWidth/2-
                        (door.x-player.position.x),
                        screenHeight/2-(door.y-player.position.y),
                        door.width,door.height,closeToDoor?
                            (CheckCollisionPointRec(mousePos,doorVisualPos)?DARKGREEN:GREEN):SKYBLUE);
                if(facing == "Up") DrawTexture(player.up,screenWidth/2-player.up.width/2,screenHeight/2-player.up.height/2,WHITE);
                if(facing == "Down") DrawTexture(player.down,screenWidth/2-player.up.width/2,screenHeight/2-player.up.height/2,WHITE);
                if(facing == "Left") DrawTexture(player.left,screenWidth/2-player.up.width/2,screenHeight/2-player.up.height/2,WHITE);
                if(facing == "Right") DrawTexture(player.right,screenWidth/2-player.up.width/2,screenHeight/2-player.up.height/2,WHITE);
                //Prints the coordinates of the player
                DrawText(TextFormat("Player X = %s\nPlayer Y = %s",
                    std::to_string(player.position.x).c_str(),
                    std::to_string(player.position.y).c_str()
                    ),0,0,20,WHITE);
            }
        EndDrawing();
    }
    UnloadTexture(player.up);UnloadTexture(player.down);UnloadTexture(player.left);UnloadTexture(player.right);
    CloseWindow();
    
    return 0;
}
