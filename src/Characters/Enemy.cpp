#include "Enemy.h"
#include "Character.h"
#include "Camera.h"
#include "CollisionHandler.h"

#include <SDL2/SDL.h>

Enemy::Enemy(Properties* props) : Character(props)
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5);

    m_Collider = new Collider();

    m_Animation = new SequenceAnimation(false);
    m_Animation->Parse("assets/animation.xml");
    m_Animation->SetCurrentSequence("slime_idle");
} 

void Enemy::Draw()
{
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 2.0f, 2.0f, m_Flip);
}

void Enemy::Update(float dt)
{
    // x-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 32 * 2, 25 * 2);

    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    // y-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 32 * 2, 25 * 2);

    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    m_Animation->Update(dt);

    if( m_Animation->IsEnded() )
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSequence("slime_move");
    }
}

void Enemy::Clean()
{

}