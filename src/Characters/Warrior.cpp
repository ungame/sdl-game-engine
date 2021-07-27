#include "Warrior.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
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
    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking1 = false;
    m_IsAttacking2 = false;
    m_IsCrouching = false;

    m_Flip = SDL_FLIP_NONE;
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-65, -53, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 0, 8, 80);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);

    // Vector2D cam = Camera::GetInstance()->GetPosition();
    // SDL_Rect box = m_Collider->Get();
    // box.x -= cam.X;
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{

    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    bool isAttacking = m_IsAttacking1 || m_IsAttacking2;

    // correr para direita
    if ( Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !isAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    // correr para a esquerda
    if ( Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !isAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // agachar
    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) )
    {
        m_RigidBody->UnSetForce();
        m_IsCrouching = true;
    }

    // atacar 1
    if ( Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_LEFT) )
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking1 = true;
        m_IsAttacking2 = !m_IsAttacking1;
    }
    
    // atacar 2
    if ( Input::GetInstance()->GetMouseButtonDown(SDL_BUTTON_RIGHT) )
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking2 = true;
        m_IsAttacking1 = !m_IsAttacking2;
    }

    // pular
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded )
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    } 
    else 
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // cair
    if( m_RigidBody->Velocity().Y > 0 && !m_IsGrounded )
    {
        m_IsFalling = true;
    }
    else 
    {
        m_IsFalling = false;
    }

    // tempo de ataque
    if( (m_IsAttacking1 || m_IsAttacking2) && m_AttackTime > 0 )
    {
        m_AttackTime -= dt;
    }
    else 
    {
        m_IsAttacking1 = false;
        m_IsAttacking2 = false;
        m_AttackTime = ATTACK_TIME;
    }

    int boxWidth = 30;
    int boxHeight = 51;

    // mover no eixo X
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, boxWidth, boxHeight);

    if( CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()) )
    {
        m_Transform->X = m_LastSafePosition.X;
    }
  
    // mover no eixo Y
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, boxWidth, boxHeight);

    if( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else {
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    AnimationState();
    
    m_Animation->Update(dt);
}

void Warrior::AnimationState()
{
    m_Animation->SetProps("player_idle", 0, 8, 100);

    if(m_IsRunning)
    {
        m_Animation->SetProps("player_run", 0, 8, 100);
    }

    if(m_IsCrouching)
    {
        m_Animation->SetProps("player_crouch", 0, 6, 200);
    }

    if(m_IsJumping)
    {
        m_Animation->SetProps("player_jump", 0, 2, 200);
    }

    if(m_IsFalling)
    {
        m_Animation->SetProps("player_fall", 0, 2, 200);
    }

    if(m_IsAttacking1)
    {
        m_Animation->SetProps("player_attack1", 0, 4, 200);
    }

    if(m_IsAttacking2)
    {
        m_Animation->SetProps("player_attack2", 0, 4, 200);
    }
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}  
