#include "GameSprite.h"

GameSprite::GameSprite()
{
	// Default the sprite to position (0, 0, 0)
	position.x = 0;
	position.y = 0;
	position.z = 0;

	//When color is set to white, what you see is exactly what the image looks like.
	color = D3DCOLOR_ARGB(255, 255, 255, 255);


	//We are not initialized yet
	initialized = false;
}

GameSprite::GameSprite(float x, float y)
{
	//Set the position to the programmer's requested X and Y coordinates.  
	//Default Z to 0
	position.x = x;
	position.y = y;
	position.z = 0;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	//When color is set to white, what you see is exactly what the image looks like.
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	//We are not initialized yet
	initialized = false;
}

bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), 
		width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL); 
		return false;
	}

	//Attempt to create the sprite
	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
		return false;
	}

	initialized = true;

	return true;
}

bool GameSprite::IsInitialized()
{
	//Are we initialized (have a texture and sprite)
	return initialized;
}


void GameSprite::Draw(float gameTime)
{
	if(sprite && tex)
	{
		//D3DXSPRITE_OBJECTSPACE is needed for the camera to work
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

		sprite->Draw(tex, NULL, NULL, &position, color);

		sprite->End();
	}
}

GameSprite::~GameSprite()
{
	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	if(tex)
	{
		tex->Release();
		tex = 0;
	}
}