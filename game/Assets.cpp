#include <string>

#include "Assets.h"

std::map<std::string, Surface*> Assets::Graphics;
std::map<std::string, Animation*> Assets::Animations;
std::map<std::string, Mix_Chunk*> Assets::Sounds;
std::map<std::string, Level*> Assets::Levels;

void Assets::Load() {            
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	
	//Menu
	Animations["logo"] = new Animation("logo");
	Animations["logo"]->FrameTime = 0.08f;

	for(int i = 0; i < 4; i++) {
		std::string file = "assets/menu/intro_" + std::to_string(i) + ".gif";
		Animations["logo"]->AddSprite(new Surface(&file[0]));
	}

	//Player
	Animations["player_normal_left"] = new Animation("player_normal_left");
	Animations["player_normal_left"]->FrameTime = 0.08f;
	Animations["player_normal_left"]->AddSprite(new Surface("assets/player/normal_left_0.png"));
	Animations["player_normal_left"]->AddSprite(new Surface("assets/player/normal_left_1.png"));

	Animations["player_normal_right"] = new Animation("player_normal_right");
	Animations["player_normal_right"]->FrameTime = 0.08f;
	Animations["player_normal_right"]->AddSprite(new Surface("assets/player/normal_right_0.png"));
	Animations["player_normal_right"]->AddSprite(new Surface("assets/player/normal_right_1.png"));

	Animations["player_normal_up"] = new Animation("player_normal_up");
	Animations["player_normal_up"]->FrameTime = 0.08f;
	Animations["player_normal_up"]->AddSprite(new Surface("assets/player/normal_up_0.png"));
	Animations["player_normal_up"]->AddSprite(new Surface("assets/player/normal_up_1.png"));

	Animations["player_normal_down"] = new Animation("player_normal_down");
	Animations["player_normal_down"]->FrameTime = 0.08f;
	Animations["player_normal_down"]->AddSprite(new Surface("assets/player/normal_down_0.png"));
	Animations["player_normal_down"]->AddSprite(new Surface("assets/player/normal_down_1.png"));

	Animations["player_sword_left"] = new Animation("player_sword_left");
	Animations["player_sword_left"]->LoopAnimation = false;
	Animations["player_sword_left"]->FrameTime = 0.08f;
	Animations["player_sword_left"]->AddSprite(new Surface("assets/player/attack_sword_left_0.png"));
	Animations["player_sword_left"]->AddSprite(new Surface("assets/player/attack_sword_left_1.png"));
	Animations["player_sword_left"]->AddSprite(new Surface("assets/player/attack_sword_left_0.png"));

	Animations["player_sword_right"] = new Animation("player_sword_right");
	Animations["player_sword_right"]->LoopAnimation = false;
	Animations["player_sword_right"]->FrameTime = 0.08f;
	Animations["player_sword_right"]->AddSprite(new Surface("assets/player/normal_right_0.png"));
	Animations["player_sword_right"]->AddSprite(new Surface("assets/player/attack_sword_right.png"));
	Animations["player_sword_right"]->AddSprite(new Surface("assets/player/normal_right_0.png"));

	Animations["player_sword_up"] = new Animation("player_sword_up");
	Animations["player_sword_up"]->LoopAnimation = false;
	Animations["player_sword_up"]->FrameTime = 0.08f;
	Animations["player_sword_up"]->AddSprite(new Surface("assets/player/attack_sword_up_0.png"));
	Animations["player_sword_up"]->AddSprite(new Surface("assets/player/attack_sword_up_1.png"));
	Animations["player_sword_up"]->AddSprite(new Surface("assets/player/attack_sword_up_0.png"));

	Animations["player_sword_down"] = new Animation("player_sword_down");
	Animations["player_sword_down"]->LoopAnimation = false;
	Animations["player_sword_down"]->FrameTime = 0.08f;
	Animations["player_sword_down"]->AddSprite(new Surface("assets/player/normal_down_0.png"));
	Animations["player_sword_down"]->AddSprite(new Surface("assets/player/attack_sword_down.png"));
	Animations["player_sword_down"]->AddSprite(new Surface("assets/player/normal_down_0.png"));
	
    Animations["rupee"] = new Animation("rupee");
	Animations["rupee"]->FrameTime = 0.1f;
	Animations["rupee"]->AddSprite(new Surface("assets/player/rupee_0.png"));
    Animations["rupee"]->AddSprite(new Surface("assets/player/rupee_1.png"));
	    
	Graphics["pickup_bow"] = new Surface("assets/player/pickup_bow.png");
	Graphics["pickup_sword"] = new Surface("assets/player/pickup_sword.png");

	Sounds["arrow_shoot"] = Mix_LoadWAV("assets/sounds/arrow_shoot.wav");
	Sounds["bomb_drop"] = Mix_LoadWAV("assets/sounds/bomb_drop.wav");
	Sounds["bomb_explode"] = Mix_LoadWAV("assets/sounds/bomb_explode.wav");
	Sounds["die"] = Mix_LoadWAV("assets/sounds/die.wav");
	Sounds["enemy_hit"] = Mix_LoadWAV("assets/sounds/enemy_hit.wav");
	Sounds["enemy_kill"] = Mix_LoadWAV("assets/sounds/enemy_kill.wav");
	Sounds["get_heart"] = Mix_LoadWAV("assets/sounds/get_heart.wav");
	Sounds["get_item"] = Mix_LoadWAV("assets/sounds/get_item.wav");
	Sounds["get_rupee"] = Mix_LoadWAV("assets/sounds/get_rupee.wav");
	Sounds["hurt"] = Mix_LoadWAV("assets/sounds/hurt.wav");
	Sounds["item_fanfare"] = Mix_LoadWAV("assets/sounds/item_fanfare.wav");
	Sounds["low_health"] = Mix_LoadWAV("assets/sounds/low_health.wav");
	Sounds["stairs"] = Mix_LoadWAV("assets/sounds/stairs.wav");
	Sounds["sword_slash"] = Mix_LoadWAV("assets/sounds/sword_slash.wav");

	Graphics["life_label"] = new Surface("assets/player/gui/life_label.png");
	Graphics["rupees"] = new Surface("assets/player/gui/rupees.png");
	Graphics["ui_arrow"] = new Surface("assets/player/gui/arrow.png");

	Graphics["arrow_slot"] = new Surface("assets/player/gui/arrow_slot.png");
	Graphics["bomb_slot"] = new Surface("assets/player/gui/bomb_slot.png");
	Graphics["sword_slot"] = new Surface("assets/player/gui/sword_slot.png");

	Graphics["inslot_bow"] = new Surface("assets/player/gui/bow.png");
	Graphics["inslot_sword"] = new Surface("assets/player/gui/sword.png");

	Graphics["heart"] = new Surface("assets/player/gui/life_full.png");
	Graphics["heart_half"] = new Surface("assets/player/gui/life_half.png");

	//Weapons
	Graphics["bomb"] = new Surface("assets/player/bomb.png");

	Graphics["arrow_up"] = new Surface("assets/player/arrow_up.png");
	Graphics["arrow_down"] = new Surface("assets/player/arrow_down.png");
	Graphics["arrow_left"] = new Surface("assets/player/arrow_left.png");
	Graphics["arrow_right"] = new Surface("assets/player/arrow_right.png");

	Animations["bomb_explode"] = new Animation("bomb_explode");
	Animations["bomb_explode"]->FrameTime = 0.05f;
	Animations["bomb_explode"]->LoopAnimation = false;
	for(int i = 1; i < 13; i++) {
		std::string file = "assets/player/bomb_expl_" + std::to_string(i) + ".png";
		Animations["bomb_explode"]->AddSprite(new Surface(&file[0]));
	}

	Animations["fire"] = new Animation("fire");
	Animations["fire"]->FrameTime = 0.08f;
	for(int i = 0; i < 4; i++) {
		Animations["fire"]->AddSprite(Animations["bomb_explode"]->Sprites[i]);
	}


	//Oktorok
	Animations["oktorok_left"] = new Animation("oktorok_left");
	Animations["oktorok_left"]->FrameTime = 0.08f;
	Animations["oktorok_left"]->AddSprite(new Surface("assets/Enemies/oktorok_left_0.png"));
	Animations["oktorok_left"]->AddSprite(new Surface("assets/Enemies/oktorok_left_1.png"));

	Animations["oktorok_right"] = new Animation("oktorok_right");
	Animations["oktorok_right"]->FrameTime = 0.08f;
	Animations["oktorok_right"]->AddSprite(new Surface("assets/Enemies/oktorok_right_0.png"));
	Animations["oktorok_right"]->AddSprite(new Surface("assets/Enemies/oktorok_right_1.png"));

	Animations["oktorok_up"] = new Animation("oktorok_up");
	Animations["oktorok_up"]->FrameTime = 0.08f;
	Animations["oktorok_up"]->AddSprite(new Surface("assets/Enemies/oktorok_up_0.png"));
	Animations["oktorok_up"]->AddSprite(new Surface("assets/Enemies/oktorok_up_1.png"));

	Animations["oktorok_down"] = new Animation("oktorok_down");
	Animations["oktorok_down"]->FrameTime = 0.08f;
	Animations["oktorok_down"]->AddSprite(new Surface("assets/Enemies/oktorok_down_0.png"));
	Animations["oktorok_down"]->AddSprite(new Surface("assets/Enemies/oktorok_down_1.png"));

    Animations["rock_projectile"] = new Animation("rock_projectile");
    Animations["rock_projectile"]->FrameTime = 0.1f;
    Animations["rock_projectile"]->AddSprite(new Surface("assets/Enemies/rock_projectile_0.png"));
    Animations["rock_projectile"]->AddSprite(new Surface("assets/Enemies/rock_projectile_1.png"));

	//Tektite
	Animations["tektite"] = new Animation("tektite");
	Animations["tektite"]->FrameTime = 0.15f;

	Animations["tektite"]->AddSprite(new Surface("assets/Enemies/tektite_normal.png"));
	Animations["tektite"]->AddSprite(new Surface("assets/Enemies/tektite_jump.png"));

	Animations["tektite_jump"] = new Animation("tektite_jump");
	Animations["tektite_jump"]->FrameTime = 0.08f;    
	Animations["tektite_jump"]->AddSprite(new Surface("assets/Enemies/tektite_jump.png"));

    //Moblin
	Animations["moblin_left"] = new Animation("moblin_left");
	Animations["moblin_left"]->FrameTime = 0.08f;
	Animations["moblin_left"]->AddSprite(new Surface("assets/Enemies/moblin_left_0.png"));
	Animations["moblin_left"]->AddSprite(new Surface("assets/Enemies/moblin_left_1.png"));

	Animations["moblin_right"] = new Animation("moblin_right");
	Animations["moblin_right"]->FrameTime = 0.08f;
	Animations["moblin_right"]->AddSprite(new Surface("assets/Enemies/moblin_right_0.png"));
	Animations["moblin_right"]->AddSprite(new Surface("assets/Enemies/moblin_right_1.png"));

	Animations["moblin_up"] = new Animation("moblin_up");
	Animations["moblin_up"]->FrameTime = 0.08f;
	Animations["moblin_up"]->AddSprite(new Surface("assets/Enemies/moblin_up_0.png"));
	Animations["moblin_up"]->AddSprite(new Surface("assets/Enemies/moblin_up_1.png"));

	Animations["moblin_down"] = new Animation("moblin_down");
	Animations["moblin_down"]->FrameTime = 0.08f;
	Animations["moblin_down"]->AddSprite(new Surface("assets/Enemies/moblin_down_0.png"));
	Animations["moblin_down"]->AddSprite(new Surface("assets/Enemies/moblin_down_1.png"));

    //Zola
	Animations["zola"] = new Animation("zola");
	Animations["zola"]->FrameTime = 0.25f;
    Animations["zola"]->LoopAnimation = false;
    Surface* zola0 = new Surface("assets/Enemies/zola_0.png");
    Surface* zola1 = new Surface("assets/Enemies/zola_1.png");
    Surface* zola2 = new Surface("assets/Enemies/zola_2.png");

	Animations["zola"]->AddSprite(zola0);
    Animations["zola"]->AddSprite(zola1);
	Animations["zola"]->AddSprite(zola0);
    Animations["zola"]->AddSprite(zola1);
	Animations["zola"]->AddSprite(zola0);
    Animations["zola"]->AddSprite(zola1);
	Animations["zola"]->AddSprite(zola0);
    Animations["zola"]->AddSprite(zola1);


	Animations["zola"]->AddSprite(zola2);
    Animations["zola"]->AddSprite(zola2);    
    Animations["zola"]->AddSprite(zola2);    
    Animations["zola"]->AddSprite(zola2);    
    Animations["zola"]->AddSprite(zola2);    
    Animations["zola"]->AddSprite(zola2);    
    Animations["zola"]->AddSprite(zola2);
    Animations["zola"]->AddSprite(zola1);
    Animations["zola"]->AddSprite(zola0);

	//Boss
	Animations["boss"] = new Animation("boss");
	Animations["boss"]->FrameTime = 0.08f;
	for(int i = 0; i < 5; i++) {
		std::string file = "assets/enemies/boss_" + std::to_string(i) + ".png";
		Animations["boss"]->AddSprite(new Surface(&file[0]));
	}	


	//Editor
	Graphics["editor_2"] = new Surface("assets/editor/player_start.png");
	Graphics["editor_3"] = new Surface("assets/editor/octorok_red.gif");
	Graphics["editor_4"] = new Surface("assets/editor/tektite.png");
    Graphics["editor_5"] = new Surface("assets/editor/moblin.png");
    Graphics["editor_6"] = new Surface("assets/editor/zola.png");
	Graphics["editor_7"] = new Surface("assets/editor/level.png");
	Graphics["editor_8"] = new Surface("assets/editor/position.png");
	Graphics["editor_9"] = new Surface("assets/editor/random.png");

	//Levels
	Levels["overworld"] = new Level("overworld");
	Levels["overworld"]->Init();

	Levels["room 1"] = new Level("room 1");
	Levels["room 1"]->Init();

	Levels["boss"] = new Level("boss");
	Levels["boss"]->Init();

	Levels["shopkeeper"] = new Level("shopkeeper");
	Levels["shopkeeper"]->Init();

	Levels["random"] = new Level("random");
	Levels["random"]->Init();

}

void Assets::DestroyLevels() {	
	Levels["overworld"]->Destroy();
	
	Levels["room 1"]->Destroy();

	Levels["boss"]->Destroy();

	Levels["shopkeeper"]->Destroy();

	Levels["random"]->Destroy();
}