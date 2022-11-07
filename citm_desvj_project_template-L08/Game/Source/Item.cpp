#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"
Item::Item() : Entity(EntityType::ITEM)
{
	coin.PushBack({ 0,0,16,16 });
	coin.PushBack({ 16,0,16,16 });
	coin.PushBack({ 32,0,16,16 });
	coin.PushBack({ 48,0,16,16 });
	coin.loop = true;
	coin.speed = 0.15f;

	name.Create("item");
}

Item::~Item() {}

bool Item::Awake() {


	return true;
}

bool Item::Start() {

	//initilize textures
	texture = app->tex->Load("Assets/Textures/goldCoin.png");
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/coinPickup.ogg");
	coinbody = app->physics->CreateRectangleSensor(position.x+15, position.y+20, 10, 10, bodyType::STATIC);
	coinbody->ctype = ColliderType::ITEM;
	coinbody->listener = this;
	// L07 DONE 4: Add a physics to an item - initialize the physics body

	// L07 DONE 7: Assign collider type

	return true;
}

bool Item::Update()
{
	// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	if (isPicked == false) {
		coinframe = coin.GetCurrentFrame();
		coin.Update();
		app->render->DrawTexture(texture, position.x+7, position.y + 10, &coinframe);
	}
	

	return true;
}

bool Item::CleanUp()
{
	return true;
}

void Item::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		LOG("Collision PLAYER");
		physA->body->DestroyFixture(physA->body->GetFixtureList());
		app->audio->PlayFx(pickCoinFxId);
		isPicked = true;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;


	}

}