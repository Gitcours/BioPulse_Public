#pragma once
#include <iostream>
#include <filesystem>
#include <mutex>
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using std::system;
namespace fs = std::filesystem;
using namespace std;
using namespace sf;
using namespace fs;

extern RenderWindow window;

extern bool isGameRunning;
extern bool isMenu;
extern bool isPlaying, isOption, isCredits, isPause,
isAlive, isLost, isConnected,
onVolume, isFirstStart, isControls, isSounds,isStats;
extern bool isEditing;
extern bool isEditMenu;
extern bool isUpdateHP;

extern float playerFrame;
extern float playerbulletFrame;
extern float playerDashSpamDeltatime;
extern float playerDashLenght;
extern float playerDashSpeed;
extern float playerDamageDetlaTime;
extern float gravity;
extern float jumpForce;

extern float bulletspeed;
extern float bulletdeltaTime;
extern float bulletdistancetocentercameratodie;
extern float playerBulletDamage;

extern float playerEffectFrame;

extern float petFrame;
extern float petdistancetofollowplayer;
extern float petidleoffset;
extern float petspeed;
extern float petidlespeed;
extern float petplatformdistancetoplayer;

extern bool isGrounded;
extern bool jumpAnimCanBeLaunch;
extern bool isLookingLeft;
extern bool isStill;

extern float timeSinceLastFrame;
extern float timePassed;
extern float timePassedIG;

extern mutex playerbulletsmutex;

extern Vector2f direction;

extern mutex managerMutex;

extern int tileRes;
extern bool canJump;
extern bool isHanging;

extern float crabeFrame;
extern float hippoFrame;
extern float poissonGFrame;
