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
	texture = app->tex->Load(texturePath);

	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x+16, position.y+16, 16, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/coinPickup.ogg");
	bandera = false;
	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	int speed = 4; 
	
	
	if (salt <= 0) {
		vel = b2Vec2(0, -GRAVITY_Y);
	}

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
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		if (salt <= 0) {
			vel = b2Vec2(speed, -GRAVITY_Y);
		}
		if (salt > 0) {
			vel = b2Vec2(speed, saltvel);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && salt<=0 && doublejump>=1) {
		salt = 16;
		vel = b2Vec2(0, saltvel);
		doublejump--;
	}
	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;
	app->render->DrawTexture(texture, position.x+3 , position.y+5);
	
	b2Vec2 xdd = pbody->body->GetPosition();
	xdd.x = ((-xdd.x) * 50 * 3) + 600;
	if (xdd.x < -96) {
		app->render->camera.x = xdd.x;
	}
	if (xdd.x < -2950) {
		bandera = true;

	}
	
	
	
	salt--;
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
			app->entityManager->DestroyEntity(this);
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
			break;

	}
	


}
