#include "UserInput.h"

void UserInput::userInputManagement(EntityManager* manager, TextureManager& text, shared_ptr<Player> player)
{
    Clock deltaTime;
    float xForce = 0;

    shared_ptr<Entity> ePet = manager->getAllPets()[0];
    shared_ptr<Pet> pet = dynamic_pointer_cast<Pet>(ePet);

    while (true)
    {
        if (isMenu) {
            deltaTime.restart();
            continue;
        }

        while (isEditing) {
            timeSinceLastFrame = deltaTime.restart().asSeconds();

            Vector2f directionV = Vector2f(0, 0);
            if (Keyboard::isKeyPressed(Keyboard::Scancode::A) || Joystick::getAxisPosition(0, Joystick::X) < -50.f)
            {
                directionV.x += -1;
            }

            if (Keyboard::isKeyPressed(Keyboard::Scancode::D) || Joystick::getAxisPosition(0, Joystick::X) > 50.f)
            {
                directionV.x += 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Scancode::W) || Joystick::getAxisPosition(0, Joystick::Y) < -50.f)
            {
                directionV.y += -1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Scancode::S) || Joystick::getAxisPosition(0, Joystick::Y) > 50.f)
            {
                directionV.y += 1;
            }

            player->getCamera()->move(directionV * 500.f * timeSinceLastFrame);
        }

        while (isPause) {
            deltaTime.restart();
            continue;
        }
        timeSinceLastFrame = deltaTime.restart().asSeconds();
        direction.x = 0;
        collide = 0;
        collideClimb = 0;

        if (Joystick::isConnected(0) && !isConnected)
        {
			isConnected = true;
        }


        if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::getAxisPosition(0, Joystick::Z) < -0.5f) && bulletclock.getElapsedTime().asSeconds() >= bulletdeltaTime && timeSinceLastPressOfDorQ.getElapsedTime().asMilliseconds() >= 100 && (player->entitySprite.getTexture() == &text.idlePlayerRightText || player->entitySprite.getTexture() == &text.idlePlayerLeftText) && !player->isClimbing)
        {
            managerMutex.lock();
            player->isShooting = true;
            bulletclock.restart();
            if (!player->playerLastDirection)
            {
                manager->createPlayerProjectiles(Vector2f(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y - player->getHitBox().height / 2), text.projectileText, "LEFT");
            }
            else
            {
                manager->createPlayerProjectiles(Vector2f(player->entitySprite.getPosition().x, player->entitySprite.getPosition().y - player->getHitBox().height / 2), text.projectileText, "RIGHT");
            }
			managerMutex.unlock();
        }
        else
		{
			player->isShooting = false;
		}

        if (Keyboard::isKeyPressed(Keyboard::E) || Joystick::isButtonPressed(0, 1)) {
            pet->petisaplatform = true;
			pet->becomeplatforme(player->entitySprite, player->playerLastDirection);
        }
        else
        {
            pet->petisaplatform = false;
            pet->newplatform = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::LShift) /*|| Joystick::isButtonPressed(N/A, N/A)*/ && dashSpamClock.getElapsedTime().asSeconds() >= playerDashSpamDeltatime && !player->isCrouching) {
            dashSpamClock.restart();
            player->isDashing = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::LControl) /*|| Joystick::isButtonPressed(N/A, N/A)*/ && !player->isDashing && !player->isClimbing) {
            player->isCrouching = true;
        }
        else {
            player->isCrouching = false;
        }

        if (canClimb || player->isClimbing)
        {
            if (Keyboard::isKeyPressed(Keyboard::Z) /*|| Joystick::isButtonPressed(N/A, N/A)*/)
            {
                player->isClimbing = true;
                direction.y = -0.35f;
            }

            else if (Keyboard::isKeyPressed(Keyboard::S) /*|| Joystick::isButtonPressed(N/A, N/A)*/)
            {
                player->isClimbing = true;
                direction.y = 0.35f;
            }
            else if (player->isClimbing)
            {
                direction.y = 0;
            }
        }

        int xOffset = player->getHitBox().getSize().x / 4;
        int yOffset = player->getHitBox().getSize().y / 8;

        FloatRect leftBox(player->getHitBox().getPosition() + Vector2f(0, yOffset / 2), Vector2f(1, yOffset*7));
        FloatRect rightBox(player->getHitBox().getPosition() + Vector2f(player->getHitBox().getSize().x - 1, 0) + Vector2f(0, yOffset / 2), Vector2f(1, yOffset*7));

        FloatRect upBox(player->getHitBox().getPosition() + Vector2f(xOffset / 2, 0), Vector2f(xOffset*3, 1));
        FloatRect downBox(player->getHitBox().getPosition() + Vector2f(0, player->getHitBox().getSize().y - 1) + Vector2f(xOffset / 2, 0), Vector2f(xOffset*3, 1));

        if (!isHanging)
        {
            if (Keyboard::isKeyPressed(Keyboard::Scancode::A) || Joystick::getAxisPosition(0, Joystick::X) < -50.f)
            {
                timeSinceLastPressOfDorQ.restart();

                if (player->isCrouching)
                {
                    direction.x += -0.5;
                }
                else
                {
                    direction.x += -1;
                }
                player->playerLastDirection = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Scancode::D) || Joystick::getAxisPosition(0, Joystick::X) > 50.f)
            {
                timeSinceLastPressOfDorQ.restart();

                if (player->isCrouching)
                {
                    direction.x += 0.5;
                }
                else
                {
                    direction.x += 1;
                }
                player->playerLastDirection = true;
            }
        }

        for (int i = 0; i < tileMap.size(); i++)
        {
            shared_ptr<Tile> tile = tileMap[i];

            if (tile->getSprite()->getGlobalBounds().intersects(player->getHitBox()))
            {
                if ((tile->getType() == "StickyWallR")
                    and tile->getSprite()->getGlobalBounds().contains(Vector2f(player->getHitBox().left, player->entitySprite.getPosition().y)))
                {
                    if (!isHanging) {
                        direction.y = 0.f;
                    }
                }
                else if ((tile->getType() == "StickyWallL")
                    and tile->getSprite()->getGlobalBounds().contains(Vector2f(player->getHitBox().left + player->getHitBox().width, player->entitySprite.getPosition().y)))
                {
                    if (!isHanging) {
                        direction.y = 0.f;
                    }
                }
                if (isGrounded and player->getFeetPos().y > tile->getSprite()->getPosition().y and tile->getSprite()->getGlobalBounds().intersects(downBox)) {
                    if (tile->getType() == "Wall") {
                        player->entitySprite.move(0, -1);
                    }
                }
                if (tile->getType() == "Door") {
                    
                    if (mapReference.getCurrentMap() + 1 < mapReference.getLevels().size())
                    {
                        mapReference.setCurrentMap(mapReference.getCurrentMap() + 1);
                        mapReference.loadLab(tileMap, *player, mapReference.getLevels()[mapReference.getCurrentMap()]);
                    }
                    /*ofstream save("Assets/Save/save.txt");
                    save.clear();
                    char posX = char(player->entitySprite.getPosition().x);
                    char posY = char(player->entitySprite.getPosition().y);
                    char pos = posX + ';' + posY;
                    save.put(pos);
                    save.put('\n');
                    save.write(&char(mapReference.getCurrentMap()), 1);
                    save.put('\n');
                    save.put(player->getHealth());*/
                }
            }
        }

        isHanging = false;

        for (int i = 0; i < tileMap.size(); i++)
        {
            shared_ptr<Tile> tile = tileMap[i];

            if (tile->getSprite()->getGlobalBounds().intersects(player->getHitBox()))
            {
                if ((tile->getType() == "Floor" or tile->getType() == "Wall")
                    /* and player->getFeetPos().y <= tile->getSprite()->getPosition().y */
                    and tile->getSprite()->getGlobalBounds().intersects(downBox))
                {
                    if (tile->getType() == "Floor") {
                        if (player->getFeetPos().y <= tile->getSprite()->getPosition().y) {
                            collide++;
                            isGrounded = true;
                        }
                    }
                    else {
                        collide++;
                        isGrounded = true;
                    }
                    player->isClimbing = false;
                }
                else if ((tile->getType() == "StickyWallR")
                    and tile->getSprite()->getGlobalBounds().contains(Vector2f( player->getHitBox().left, player->entitySprite.getPosition().y)))
                {
                    isHanging = true;
                    if (player->entitySprite.getTexture() != &text.hangingPlayerTextL) {
                        player->entitySprite.setTexture(text.hangingPlayerTextL);
                        player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
                        xForce = 0;
                        direction.x = 0;
                        player->isClimbing = false;
                    }
                }
                else if ((tile->getType() == "StickyWallL")
                    and tile->getSprite()->getGlobalBounds().contains(Vector2f(player->getHitBox().left + player->getHitBox().width, player->entitySprite.getPosition().y)))
                {
                    isHanging = true;
                    if (player->entitySprite.getTexture() != &text.hangingPlayerTextR) {
                        player->entitySprite.setTexture(text.hangingPlayerTextR);
                        player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
                        xForce = 0;
                        direction.x = 0;
                        player->isClimbing = false;
                    }
                }
                else if (tile->getType() == "Climb") {
                    collideClimb++;
                    if (player->isClimbing)
                    {
                        //if (player->entitySprite.getTexture() != &text.climbingPlayerText) {
                        //    //player->entitySprite.setTexture(text.climbingPlayerText);
                        //    player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
                        //    player->entitySprite.setPosition(tile->getSprite()->getPosition().x + tile->getSprite()->getGlobalBounds().width / 2, player->entitySprite.getPosition().y);
                        //}
                    }
                    else
                    {
                        canClimb = true;
                    }
                }

                if ((tile->getType() == "Floor" or tile->getType() == "Wall" or tile->getType() == "StickyWallR" or tile->getType() == "StickyWallL")
                    && direction.y > 0.f && tile->getSprite()->getGlobalBounds().intersects(downBox)
                    /* and player->getFeetPos().y <= tile->getSprite()->getPosition().y*/)
                {
                    if (tile->getType() == "Floor") {
                        if (player->getFeetPos().y <= tile->getSprite()->getPosition().y) {
                            direction.y = 0;
                            isGrounded = true;
                        }
                    }
                    else {
                        direction.y = 0;
                        isGrounded = true;
                    }
                }
            }
        }
        if ((player->entitySprite.getTexture() == &text.hangingPlayerTextL or player->entitySprite.getTexture() == &text.hangingPlayerTextR) and !isHanging) {
            if (player->entitySprite.getTexture() == &text.hangingPlayerTextR) {
                player->entitySprite.setTexture(text.jumpingPlayerLeftText);
            }
            else {
                player->entitySprite.setTexture(text.jumpingPlayerRightText);
            }
            player->entitySprite.setTextureRect(IntRect(0, 0, player->entitySprite.getTextureRect().height, player->entitySprite.getTextureRect().height));
        }

        if (collideClimb == 0)
        {
            canClimb = false;
            player->isClimbing = false;
        }


        if (pet->petisaplatform == true && pet->getHitBox().contains(player->getFeetPos() + Vector2f(0, 1)) && player->getFeetPos().y <= pet->getHitBox().getPosition().y) {
            isGrounded = true;
            collide++;
            if (direction.y > 0.f)
            {
                direction.y = 0;
            }
        }

        if (isGrounded) {
            xForce = 0;
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Space) or Joystick::isButtonPressed(0, 0)) && (collide != 0 or isHanging) and canJump && !player->isClimbing)
        {
            player->isJumping = true;
            collide = 0;
            if (player->isCrouching) {
                direction.y = -jumpForce / 1.5f;
            }
            else
            {
                direction.y = -jumpForce;
            }
            if (isHanging) {
                if (player->entitySprite.getTexture() == &text.hangingPlayerTextL) {
                    if (Keyboard::isKeyPressed(Keyboard::Scancode::D) or Keyboard::isKeyPressed(Keyboard::Scancode::A)
                        or Joystick::getAxisPosition(0, Joystick::X) < -50.f or Joystick::getAxisPosition(0, Joystick::X) > 50.f) {
                        xForce = 0.6f;
                    }
                    else {
                        xForce = 0.2f;
                    }
                }
                else if (player->entitySprite.getTexture() == &text.hangingPlayerTextR) {
                    if (Keyboard::isKeyPressed(Keyboard::Scancode::A) or Keyboard::isKeyPressed(Keyboard::Scancode::D)
                        or Joystick::getAxisPosition(0, Joystick::X) < -50.f or Joystick::getAxisPosition(0, Joystick::X) > 50.f) {
                        xForce = -0.6f;
                    }
                    else {
                        xForce = -0.2f;
                    }
                }
                direction.x = xForce;
            }
            canJump = false;
        }
        else if ((!Keyboard::isKeyPressed(Keyboard::Space) and !Joystick::isButtonPressed(0, 0)) and (isGrounded or isHanging) and !canJump) {
            canJump = true;
        }

        if (collide == 0 && !player->isClimbing)
        {
            if (isHanging and direction.y > 0.f) {
                direction.y += (gravity * timeSinceLastFrame) / 15.f;
            }
            else {
                direction.y += gravity * timeSinceLastFrame;
            }
            isGrounded = false;
        }
        else { 
            isGrounded = true;
            player->isJumping = false;
        }

        if (xForce != 0) {
            float add = direction.x * timeSinceLastFrame * 1.5f;
            xForce += add;
        }

        if (xForce > 1) {
            xForce = 1;
        }
        else if (xForce < -1) {
            xForce = -1;
        }

        if (xForce != 0) {
            direction.x = xForce;
        }

        for (int i = 0; i < tileMap.size(); i++)
        {
            shared_ptr<Tile> tile = tileMap[i];

            if ((tile->getType() == "Wall" or tile->getType() == "StickyWallR" or tile->getType() == "StickyWallL") and tile->getSprite()->getGlobalBounds().intersects(player->getHitBox()))
            {
                if ((player->isDashing && player->playerLastDirection == true) || direction.x > 0 && tile->getSprite()->getGlobalBounds().intersects(rightBox))
                {
                    direction.x = 0;
                    player->isDashing = false;
                    dashCout = 0;
                }
                else if ((player->isDashing && player->playerLastDirection == false) || direction.x < 0 && tile->getSprite()->getGlobalBounds().intersects(leftBox))
                {
                    direction.x = 0;
                    player->isDashing = false;
                    dashCout = 0;
                }
                if (direction.y < 0 && tile->getSprite()->getGlobalBounds().intersects(upBox))
                {
                    direction.y = 0;
                }
                else if (direction.y > 0 && tile->getSprite()->getGlobalBounds().intersects(downBox))
                {
                    direction.y = 0;
                }
            }
        }
        bool playerAlreadyPushed = false;
        for (int i = 0; i < tileMap.size(); i++)
        {
            shared_ptr<Tile> tile = tileMap[i];

            if (tile->isMoving) {
                float distanceToTile = abs(tile->getSprite()->getPosition().x - tile->waypoints[abs(tile->currentWaypoint - 1)].x);
                float distanceToNext = abs(tile->waypoints[tile->currentWaypoint].x - tile->waypoints[abs(tile->currentWaypoint - 1)].x);

                if (i - 1 >= 0 and tileMap[i - 1]->isMoving) {
                    tile->currentWaypoint = tileMap[i - 1]->currentWaypoint;
                }
                else if (distanceToTile >= distanceToNext) {
                    tile->currentWaypoint = abs(tile->currentWaypoint - 1);
                }

                Vector2f movement;
                if (tile->getSprite()->getPosition().x <= tile->waypoints[tile->currentWaypoint].x) {
                    movement = Vector2f(1, 0) * 160.f * timeSinceLastFrame;
                    tile->getSprite()->move(movement);
                }
                else {
                    movement = Vector2f(-1, 0) * 160.f * timeSinceLastFrame;
                    tile->getSprite()->move(movement);
                }

                if (tile->getSprite()->getGlobalBounds().intersects(player->getHitBox()) and !playerAlreadyPushed)
                {
                    if ((tile->getType() == "Floor" or tile->getType() == "Wall")
                        and player->getFeetPos().y <= tile->getSprite()->getPosition().y
                        and tile->getSprite()->getGlobalBounds().intersects(downBox))
                    {
                        player->entitySprite.move(movement);
                        playerAlreadyPushed = true;

                    }
                }
            }
        }

        if (player->isDashing) {
            if (dashClock.getElapsedTime().asMilliseconds() >= playerDashSpeed)
            {
                dashClock.restart();
                if (dashCout >= playerDashLenght) {
                    player->isDashing = false;
                    dashCout = 0;
                }
                else
                {
                    dashCout++;
                    if (player->playerLastDirection == true)
                    {
                        player->entitySprite.move(1, 0);
                    }
                    else
                    {
                        player->entitySprite.move(-1, 0);
                    }
                }
            }
        }
        else
        {
            player->entitySprite.move(direction* player->getSpeed()* timeSinceLastFrame);
        }

        if (direction.x != 0) {
            isStill = false;
            if (direction.x > 0) {
                isLookingLeft = false;
            }
            else if (direction.x < 0) {
                isLookingLeft = true;
            }
        }
        else {
            isStill = true;
        }
    }
}

