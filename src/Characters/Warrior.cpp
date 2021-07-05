#include "Warrior.h"
#include "TextureManager.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Collider.h"
#include "Camera.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <windows.h>

Warrior::Warrior(Properties* props): Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, 80);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{

    m_Animation->SetProps("player", 0, 8, 100);
    m_RigidBody->UnSetForce();

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) )
    {
        m_RigidBody->ApplyForceX(BACKWARD * 5);
        m_Animation->SetProps("player_run", 0, 8, 100, SDL_FLIP_HORIZONTAL);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )
    {
        m_RigidBody->ApplyForceX(FORWARD * 5);
        m_Animation->SetProps("player_run", 0, 8, 100);
    }
    
    if ( Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_LEFT) )
    {
        m_Animation->SetProps("player_attack1", 0, 4, 100);
    }
    
    if ( Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_RIGHT) )
    {
        m_Animation->SetProps("player_attack2", 0, 4, 100);
    }

    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded )
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0 )
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    int height = 111;

    // mover no eixo X
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, height, height);

    if( CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) )
    {
        m_Transform->X = m_LastSafePosition.X;
    }
  
    // mover no eixo Y
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, height, height);

    if( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else {
        m_IsGrounded = false;
    }


    if (m_IsJumping || !m_IsGrounded)
    {
        m_Animation->SetProps("player_jump", 0, 2, 150);
    } 

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}  
