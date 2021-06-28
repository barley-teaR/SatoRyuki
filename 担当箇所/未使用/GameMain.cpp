// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	HP_green = GraphicsDevice.CreateSpriteFromFile(_T("緑.png"));
	HP_red = GraphicsDevice.CreateSpriteFromFile(_T("ゲージベース2.png"));
	HP_black = GraphicsDevice.CreateSpriteFromFile(_T("ゲージベース.png"));

	hit_points = 300;
	hp_x = 320.0f;
	hp_y = 22;
	red_x = 320.0f;
	red_down = false;
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here
	/*320\22*/
	KeyboardState key = Keyboard->GetState();
	KeyboardBuffer keybuf = Keyboard->GetBuffer();


	if (keybuf.IsPressed(Keys_Space)) {
		hit_points -= 100;
	}
	/*for (int i; i > hp_x;i++) {
		red_x = -1.0f;
	}*/
	if (hp_x * hit_points / 300.0f < red_x) {
		red_x -= 2;
	}
//	hp_bar = RectWH(hp_x-320.0f, hp_y-22.0f, hp_x, hp_y);
	hp_bar  = RectWH(0.0f, 0.0f, hp_x * hit_points / 300.0f, 22);
	red_bar = RectWH(0.0f, 0.0f, red_x , 22);
//	hp_x = hp_x * hit_points / hit_points;
//	red_bar;
	return 0;
}

void GameMain::HpAnimation()
{
	if (hp_x * hit_points / 300.0f < red_x) {
		red_x -= 2;
	}
	
	hp_bar = RectWH(0.0f, 0.0f, hp_x * hit_points / 300.0f, 22);
	red_bar = RectWH(0.0f, 0.0f, red_x, 22);
}
/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();
	SpriteBatch.Draw(*HP_green, Vector3(0, 0, 1),RectWH(hp_bar));
	SpriteBatch.Draw(*HP_red,   Vector3(0, 0, 2), RectWH(red_bar));
	SpriteBatch.Draw(*HP_black, Vector3(0, 0, 3));
	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
