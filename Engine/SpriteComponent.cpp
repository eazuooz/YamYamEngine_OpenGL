// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "LevelLoader.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
	,mVisible(true)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		// Scale the quad by the width/height of texture
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);
		
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		
		// Since all sprites use the same shader/vertices,
		// the game first sets them active before any sprite draws
		
		// Set world transform
		shader->SetMatrixUniform("uWorldTransform", world);
		// Set current texture
		mTexture->SetActive();
		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	// Set width/height
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}

void SpriteComponent::LoadProperties(const rapidjson::Value& inObj)
{
	Component::LoadProperties(inObj);

	std::string texFile;
	if (JsonHelper::GetString(inObj, "textureFile", texFile))
	{
		SetTexture(mOwner->GetGame()->GetRenderer()->GetTexture(texFile));
	}

	JsonHelper::GetInt(inObj, "drawOrder", mDrawOrder);
	JsonHelper::GetBool(inObj, "visible", mVisible);
}

void SpriteComponent::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	Component::SaveProperties(alloc, inObj);

	if (mTexture)
	{
		JsonHelper::AddString(alloc, inObj, "textureFile", mTexture->GetFileName());
	}

	JsonHelper::AddInt(alloc, inObj, "drawOrder", mDrawOrder);
	JsonHelper::AddBool(alloc, inObj, "visible", mVisible);
}
