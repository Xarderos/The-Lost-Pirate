#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Window.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Item.h"
Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	//texturePath = "Assets/Textures/player/idle1.png";
	int scale = app->win->GetScale();
	//L02: DONE 5: Get Player parameters from XML

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {
	int salt;
	//initilize textures
	menutexture = app->tex->Load("Assets/Textures/Start.png");
	menutexture2 = app->tex->Load("Assets/Textures/Start2.png");
	deathtexture = app->tex->Load("Assets/Textures/DeathCam.png");
	texture = app->tex->Load(texturePath);
	textureleft= app->tex->Load("Assets/Textures/Player2.png");
	playerdeadtext= app->tex->Load("Assets/Textures/Dea.png");
	closechest = app->tex->Load("Assets/Textures/chest1.png");
	openchest = app->tex->Load("Assets/Textures/chest2.png");
	congrats = app->tex->Load("Assets/Textures/congrats.png");
	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x+16, position.y+16, 14, bodyType::DYNAMIC);
	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/coinPickup.ogg");
	deathsound= app->audio->LoadFx("Assets/Audio/Fx/DeathsoundinMinecraft.ogg");
	checkpointsound= app->audio->LoadFx("Assets/Audio/Fx/CheckpointSoundEffect.ogg");
	startsound = app->audio->LoadFx("Assets/Audio/Fx/BindingofIsaacGameStartSound.ogg");
	chestopen= app->audio->LoadFx("Assets/Audio/Fx/chestopen.ogg");
	bandera = false;
	deathbool = false;
	deathtimer = 0;
	doublejumptimer = 0;
	chest = false;
	start = false;
	dreta = true;
	menutimer = 60;
	app->LoadGameRequest();
	
	return true;
}

bool Player::Update()
{

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && start == false) {
		app->audio->PlayFx(startsound);
		start = true;
	}
	if (start == false) {
		app->render->camera.x = -10000 * 3;
		
		app->render->DrawTexture(menutexture, 10000, 118);
		
		if (menutimer > 0 && menutimer<=23) {
			app->render->DrawTexture(menutexture2, 10000, 118);
		}
		if (menutimer == 0) {
			menutimer = 45;
		}
		menutimer--;
	}
	if (start == true) {

		if (chest == false) {
			app->render->DrawTexture(closechest, 2144, 352);

		}
		if (chest == true) {
			app->render->DrawTexture(openchest, 2144, 352);
			app->render->DrawTexture(congrats, 2100, 200);

		}
		if (deathtimer > 0 && deathtimer < 90) {
			app->render->camera.x = -10000 * 3;
			app->render->DrawTexture(deathtexture, 10000, 118);
		}
		// L07 DONE 5: Add physics to the player - updated player position using physics
		int speed = 4;
		if (salt <= 0) {
			vel = b2Vec2(0, -GRAVITY_Y);
		}
		if (deathtimer < 0 && chest == false) {

			
			//L02: DONE 4: modify the position of the player using arrow keys and render the texture
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
				//
			}
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				//
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				if (salt <= 0) {
					vel = b2Vec2(-speed, -GRAVITY_Y);
				}
				if (salt > 0) {
					vel = b2Vec2(-speed, saltvel);
				}
				dreta = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				if (salt <= 0) {
					vel = b2Vec2(speed, -GRAVITY_Y);
				}
				if (salt > 0) {
					vel = b2Vec2(speed, saltvel);
				}
				dreta = true;

			}
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && salt <= 0 && doublejump >= 1 && doublejumptimer <= 0) {
				salt = 16;
				vel = b2Vec2(0, saltvel);
				doublejump--;
				doublejumptimer = 20;
			}
		}
		//Set the velocity of the pbody of the player
		pbody->body->SetLinearVelocity(vel);

		//Update player position in pixels

		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
		if (dreta == true && deathtimer < 90) {
			app->render->DrawTexture(texture, position.x + 6, position.y + 4);
		}
		if (dreta == false && deathtimer < 90) {
			app->render->DrawTexture(textureleft, position.x + 6, position.y + 4);
		}
		if (deathtimer > 90) {
			app->render->DrawTexture(playerdeadtext, position.x + 6, position.y + 4);
		}

		b2Vec2 xdd = pbody->body->GetPosition();
		xdd.x = ((-xdd.x) * 50 * 3) + 600;
		if (xdd.x < -96 && xdd.x >-4896) {
			app->render->camera.x = xdd.x;
		}
		if (xdd.x > -96) {
			app->render->camera.x = -96;
		}
		if (xdd.x < -4896) {
			app->render->camera.x = -4896;
		}

		if (xdd.x < -2950 && bandera == false) {
			app->audio->PlayFx(checkpointsound);
			death = b2Vec2(24, 1);
			bandera = true;
		}

		if (deathbool == true && deathtimer < 90) {
			pbody->body->SetTransform(death, deathangle);
			doublejump = 0;
			deathbool = false;
		}
		if (deathtimer == 0) {
			if (bandera == false) {
				app->render->camera.x = -96;
			}
			if (bandera == true) {
				app->render->camera.x = -2950;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
			app->render->playerposx = pbody->body->GetTransform().p.x;
			app->render->playerposy = pbody->body->GetTransform().p.y;
			app->SaveGameRequest();

		}
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
			app->LoadGameRequest();
			pbody->body->SetTransform({ (float)app->render->playerposx,(float)app->render->playerposy }, 0);
			chest = false;
		}
		deathtimer--;

		doublejumptimer--;
		salt--;
	}
	
	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		case ColliderType::ITEM:
			LOG("Collision ITEM");
			app->audio->PlayFx(pickCoinFxId);
			break;
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			if (bandera == false) {
				doublejump = 1;
			}
			if (bandera == true) {
				doublejump = 2;
			}
			break;
		case ColliderType::DEATH:
			LOG("Collision DEATH");
			deathbool = true;
			deathtimer = 120;
			app->audio->PlayFx(deathsound);
			dreta = true;
			break;
		case ColliderType::CHEST:
			LOG("Collision UNKNOWN");
			app->audio->PlayFx(chestopen);
			chest = true;
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
		
			break;
		

	}
	


}
