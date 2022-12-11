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
#include "Animation.h"
#include "Map.h"
Player::Player() : Entity(EntityType::PLAYER)
{

	name.Create("Player");
	playeridleright.PushBack({ 0, 0, 64, 40 });
	playeridleright.PushBack({ 64, 0, 64, 40 });
	playeridleright.PushBack({ 128, 0, 64, 40 });
	playeridleright.PushBack({ 192, 0, 64, 40 });
	playeridleright.PushBack({ 256, 0, 64, 40 });
	playeridleright.loop = true;
	playeridleright.speed = 0.11f;

	playeridleleft.PushBack({ 0, 40, 64, 40 });
	playeridleleft.PushBack({ 64, 40, 64, 40 });
	playeridleleft.PushBack({ 128, 40, 64, 40 });
	playeridleleft.PushBack({ 192, 40, 64, 40 });
	playeridleleft.PushBack({ 256, 40, 64, 40 });
	playeridleleft.loop = true;
	playeridleleft.speed = 0.11f;

	playerrunright.PushBack({ 0, 80, 64, 40 });
	playerrunright.PushBack({ 64, 80, 64, 40 });
	playerrunright.PushBack({ 128, 80, 64, 40 });
	playerrunright.PushBack({ 192, 80, 64, 40 });
	playerrunright.PushBack({ 256, 80, 64, 40 });
	playerrunright.PushBack({ 320, 80, 64, 40 });
	playerrunright.loop = true;
	playerrunright.speed = 0.17f;

	playerrunleft.PushBack({ 0, 120, 64, 40 });
	playerrunleft.PushBack({ 64, 120, 64, 40 });
	playerrunleft.PushBack({ 128, 120, 64, 40 });
	playerrunleft.PushBack({ 192, 120, 64, 40 });
	playerrunleft.PushBack({ 256, 120, 64, 40 });
	playerrunleft.PushBack({ 320, 120, 64, 40 });
	playerrunleft.loop = true;
	playerrunleft.speed = 0.17f;

	playerjumpright.PushBack({ 0, 160, 64, 40 });
	playerjumpright.PushBack({ 64, 160, 64, 40 });
	playerjumpright.PushBack({ 128, 160, 64, 40 });
	playerjumpright.loop = false;
	playerjumpright.speed = 0.20f;

	playerjumpleft.PushBack({ 0, 200, 64, 40 });
	playerjumpleft.PushBack({ 64, 200, 64, 40 });
	playerjumpleft.PushBack({ 128, 200, 64, 40 });
	playerjumpleft.loop = false;
	playerjumpleft.speed = 0.20f;

	playerdeathright.PushBack({ 0, 400, 64, 40 });
	playerdeathright.PushBack({ 64, 400, 64, 40 });
	playerdeathright.PushBack({ 128, 400, 64, 40 });
	playerdeathright.PushBack({ 192, 400, 64, 40 });
	playerdeathright.loop = false;
	playerdeathright.speed = 0.20f;

	playerdeathleft.PushBack({ 0, 440, 64, 40 });
	playerdeathleft.PushBack({ 64, 440, 64, 40 });
	playerdeathleft.PushBack({ 128, 440, 64, 40 });
	playerdeathleft.PushBack({ 192, 440, 64, 40 });
	playerdeathleft.loop = false;
	playerdeathleft.speed = 0.20f;

	bluegem.PushBack({ 0,0,24,24 });
	bluegem.PushBack({ 24,0,24,24 });
	bluegem.PushBack({ 48,0,24,24 });
	bluegem.PushBack({ 72,0,24,24 });
	bluegem.loop = true;
	bluegem.speed = 0.13f;

	atacD.PushBack({ 0,480,64,40 });
	atacD.PushBack({ 64,480,64,40 });
	atacD.PushBack({ 128,480,64,40 });
	atacD.PushBack({ 0,480,64,40 });
	atacD.loop = false;
	atacD.speed = 0.15f;

	atacE.PushBack({ 192,480,64,40 });
	atacE.PushBack({ 256,480,64,40 });
	atacE.PushBack({ 320,480,64,40 });
	atacE.PushBack({ 192,480,64,40 });
	atacE.loop = false;
	atacE.speed = 0.15f;

	vides.PushBack({ 0,0,24,28 });
	vides.PushBack({ 24,0,24,28 });
	vides.PushBack({ 48,0,24,28 });
	vides.PushBack({ 72,0,24,28 });
	vides.PushBack({ 96,0,24,28 });
	vides.PushBack({ 120,0,24,28 });
	vides.PushBack({ 144,0,24,28 });
	vides.PushBack({ 168,0,24,28 });
	vides.loop = true;
	vides.speed = 0.1f;

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
	menutexture = app->tex->Load("Assets/Textures/Screens/Start.png");
	menutexture2 = app->tex->Load("Assets/Textures/Screens/Start2.png");
	deathtexture = app->tex->Load("Assets/Textures/Screens/DeathCam.png");
	texture = app->tex->Load(texturePath);
	textureleft= app->tex->Load("Assets/Textures/Player2.png");
	playerdeadtext= app->tex->Load("Assets/Textures/Dea.png");
	closechest = app->tex->Load("Assets/Textures/chest1.png");
	openchest = app->tex->Load("Assets/Textures/chest2.png");
	doublejumptext = app->tex->Load("Assets/Textures/Screens/doublejumptext.png");
	bluegemroll = app->tex->Load("Assets/Textures/Spritesheets/bluegemspritesheet.png");
	lifesprite = app->tex->Load("Assets/Textures/Spritesheets/Calavera.png");

	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x+16, position.y+16, 14, bodyType::DYNAMIC);
	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	deathsound= app->audio->LoadFx("Assets/Audio/Fx/DeathsoundinMinecraft.ogg");
	checkpointsound= app->audio->LoadFx("Assets/Audio/Fx/CheckpointSoundEffect.ogg");
	startsound = app->audio->LoadFx("Assets/Audio/Fx/BindingofIsaacGameStartSound.ogg");
	chestopen= app->audio->LoadFx("Assets/Audio/Fx/chestopen.ogg");
	jumpfx= app->audio->LoadFx("Assets/Audio/Fx/JumpFX.ogg");
	winsongfx=app->audio->LoadFx("Assets/Audio/Fx/winsongfx.ogg");
	espasasoroll = app->audio->LoadFx("Assets/Audio/Fx/Espasa.ogg");
	hitsfx = app->audio->LoadFx("Assets/Audio/Fx/MinecraftHitSoundEffect.ogg");
	bandera = false;
	deathbool = false;
	deathtimer = 0;
	doublejumptimer = 0;
	atactimer = 0;
	chest = false;
	start = false;
	dreta = true;
	gempos.x = 0;
	gempos.y = 0;
	lifes = 3;
	menutimer = 60;
	app->LoadGameRequest();

	espasa = app->physics->CreateRectangleSensor(0, 0, 21, 8, STATIC);
	espasa->ctype = ColliderType::ESPASA;

	hitimer = 0;
	atacD.currentFrame = 4;
	atacE.currentFrame = 4;

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
		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
			pbody->body->SetTransform({ 4,7 },0);
		}
		if (chest == false) {
			app->render->DrawTexture(closechest, 2144, 352);

		}
		if (chest == true) {
			app->render->DrawTexture(openchest, 2144, 352);
			gemrect = bluegem.GetCurrentFrame();
			bluegem.Update();
			app->render->DrawTexture(bluegemroll, position.x+8, position.y-20,&gemrect);
			
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
					rect = playerrunleft.GetCurrentFrame();
					playerrunleft.Update();
				}
				if (salt > 0) {
					vel = b2Vec2(-speed, saltvel);
					rect = playerjumpleft.GetCurrentFrame();
					playerjumpleft.Update();
				}

				dreta = false;
				idle = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				if (salt <= 0) {
					vel = b2Vec2(speed, -GRAVITY_Y);
					rect = playerrunright.GetCurrentFrame();
					playerrunright.Update();
				}
				if (salt > 0) {
					vel = b2Vec2(speed, saltvel);
					rect = playerjumpright.GetCurrentFrame();
					playerjumpright.Update();

				}

				dreta = true;
				idle = false;

			}
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && salt <= 0 && doublejump >= 1 && doublejumptimer <= 0) {
				app->audio->PlayFx(jumpfx);
				salt = 17;
				vel = b2Vec2(0, saltvel);
				doublejump--;
				doublejumptimer = 20;
				idle = false;

			}

		}
		//Set the velocity of the pbody of the player
		pbody->body->SetLinearVelocity(vel);

		//Update player position in pixels

		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
			if (dreta == true && deathtimer < 90) {
				rect = playeridleright.GetCurrentFrame();
				playeridleright.Update();
			}
			if (dreta == false && deathtimer < 90) {
				rect = playeridleleft.GetCurrentFrame();
				playeridleleft.Update();
			}
			if (dreta == true && salt > 0) {
				rect = playerjumpright.GetCurrentFrame();
				playerjumpright.Update();
			}
			if (dreta == false && salt > 0) {
				rect = playerjumpleft.GetCurrentFrame();
				playerjumpleft.Update();
			}

		}
		if (deathtimer > 90) {
			if (dreta == true) {
				rect = playerdeathright.GetCurrentFrame();
				playerdeathright.Update();
			}
			if (dreta == false) {
				rect = playerdeathleft.GetCurrentFrame();
				playerdeathleft.Update();
			}
		}
		

		b2Vec2 xdd = pbody->body->GetPosition();
		xdd.x = ((-xdd.x) * 50 * app->win->GetScale()) + 600;
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
			playerdeathleft.Reset();
			playerdeathright.Reset();
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
		
		

		if (deathtimer > 0 && deathtimer < 90) {
			app->render->camera.x = -10000 * 3;
			app->render->DrawTexture(deathtexture, 10000, 118);
			dreta = true;
		}
		if (bandera == true) {

			app->render->DrawTexture(doublejumptext, 1120, 220);

		}
		if (app->scene->godmode == true) {
			doublejump = 2;
			doublejumptimer = 0;
		}
		if (dreta == true && deathbool==false)
		{

			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN && atacD.currentFrame > 2)
			{
				app->audio->PlayFx(espasasoroll);
				atacD.Reset();
			}
			if (atacD.currentFrame < 3) {
				espasa->body->SetTransform({ pbody->body->GetPosition().x + 0.51f,pbody->body->GetPosition().y + 0.15f }, 0);
				rect = atacD.GetCurrentFrame();
				atacD.Update();
			}
			else {
				espasa->body->SetTransform({ 0,0 }, 0);

			}
		}
		if (dreta == false && deathbool == false)
		{
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN && atacE.currentFrame > 2)
			{
				app->audio->PlayFx(espasasoroll);
				atacE.Reset();
			}
			if (atacE.currentFrame < 3) {
				espasa->body->SetTransform({ pbody->body->GetPosition().x - 0.3f,pbody->body->GetPosition().y + 0.15f }, 0);
				rect = atacE.GetCurrentFrame();
				atacE.Update();
				
			}
			else {
				espasa->body->SetTransform({ 0,0 }, 0);

			}
		}
		if (hitimer < 0 || deathbool == true) {
			app->render->DrawTexture(texture, position.x - 12, position.y + 0, &rect);
		}
		if (hitimer > 0 && hitimer%2!=0 && deathbool == false) {
			app->render->DrawTexture(texture, position.x - 12, position.y + 0, &rect);
		}
		hitimer--;
	}

	if (lifes > 2)
	{
		app->render->DrawTexture(lifesprite, pbody->body->GetPosition().x - 0.3f, pbody->body->GetPosition().y, &lifesrect);
		app->render->DrawTexture(lifesprite, -app->render->camera.x + 30, -app->render->camera.y, &lifesrect);
		app->render->DrawTexture(lifesprite, -app->render->camera.x + 60, -app->render->camera.y, &lifesrect);
		lifesrect = vides.GetCurrentFrame();
		vides.Update();

	}

	
	return true;
}

iPoint Player::GetPos()
{
	pos.x = pbody->body->GetPosition().x;
	pos.y = pbody->body->GetPosition().y;

	return pos;
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
		
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			if (bandera == false) {
				doublejump = 1;
			}
			if (bandera == true) {
				doublejump = 2;
			}
			playerjumpright.Reset();
			playerjumpleft.Reset();

			break;
		case ColliderType::DEATH:
			LOG("Collision DEATH");
			if (app->scene->godmode == false) {
				deathbool = true;
				deathtimer = 120;
				app->audio->PlayFx(deathsound);
			}
			lifes = 3;
			break;
		case ColliderType::ENEMY:
			LOG("Collision ENEMY");
			if (app->scene->godmode == false) {
				if (hitimer < 0) {
					app->audio->PlayFx(hitsfx);
					lifes--;
					hitimer = 60;
				}
				if (lifes == 0) {
					deathbool = true;
					deathtimer = 120;
					app->audio->PlayFx(deathsound);
					lifes = 3;
				}

			}
			break;
		case ColliderType::CHEST:
			LOG("Collision CHESTO");
			app->audio->PlayFx(chestopen);
			app->audio->PlayFx(winsongfx);
			chest = true;
			physB->GetPosition(gempos.x, gempos.y);
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
		
			break;

		default:

			break;
		

	}
	
}

