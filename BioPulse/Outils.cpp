#include "Outils.h"

RenderWindow window(VideoMode(1920, 1080), "Test", Style::None);


bool isGameRunning = true;
bool isMenu = true;
bool isEditing = false;
bool isEditMenu = false;
bool isUpdateHP = false;

bool isPlaying = false, isOption = false, isCredits = false, isPause = false, isConnected=false,
isAlive = true, isLost = false, isFirstStart=true, isControls = false, isSounds = false,isStats=false;
float playerFrame;
float playerbulletFrame = 0.15f;
float playerBulletDamage = 3.f;
float playerDamageDetlaTime = 2.f;

float playerDashSpamDeltatime = 0.5f;
float playerDashLenght = 250.f;
float playerDashSpeed = 0.01f;

Vector2f direction = Vector2f(0.f, 0.f);
float gravity = 4.f;
float jumpForce = 1.43f;
float bulletspeed = 0.8f;
float bulletdeltaTime = 0.5f;
float bulletdistancetocentercameratodie = 1000.f;

float playerEffectFrame = 0.05f;

float petFrame = 0.1f;
float petspeed = 0.3f;
float petidlespeed = 0.01f;
float petdistancetofollowplayer = 100.f;
float petidleoffset = 5.f;
float petplatformdistancetoplayer = 60.f;

float timeSinceLastFrame;
float timePassed;
float timePassedIG;

bool isGrounded;
bool isLookingLeft = false;
bool isStill = true;

mutex managerMutex;

int tileRes = 32;
bool canJump = true;
bool isHanging = false;

float crabeFrame = 0.15f;
float hippoFrame = 0.3f;
float poissonGFrame = 0.3f;
