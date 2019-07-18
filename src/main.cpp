#include "Engine.hpp"
#include "Graphics.hpp"
#include "UI.hpp"
#include "Transform.hpp"
#include "Controller.hpp"
#include "Physics.hpp"
#include "Time.hpp"
#include "Log.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "GameState.hpp"
#include <iostream>












////// PUT PLAYER CODE IN GROUP GITHUB //////






using Aspen::Engine::Engine;
using Aspen::GameState::GameState;
using Aspen::GameState::GameStateManager;
using Aspen::Graphics::Graphics;
using Aspen::Object::Object;


void ChangeScene(Aspen::Graphics::UI::Button *button, std::string scene, GameStateManager *gsm)
{
  gsm->SetCurrentState(scene);
}


  class Player : public Aspen::Graphics::Animation
{
public:
  Player(Object *parent = nullptr, std::string name = "Player") : Aspen::Graphics::Animation(
                                                                        new Aspen::Graphics::UniformSpritesheet("./resources/lundmarkyeezy.png", 300, 300, 1, nullptr, "Loadng"),
                                                                        1.0f / 12.0f, parent, name)

  {
    GetTransform()->SetPosition(200, 200);
    //GetTransform()->SetScale(0.3, 0.3);
    //CreateChild<Aspen::Physics::AABBCollider>()->SetSize(644 * 0.3, 644 * 0.3);
    CreateChild<Aspen::Physics::Rigidbody>();
  }
};
  class Player2 : public Aspen::Graphics::Animation
{
public:
  Player2(Object *parent = nullptr, std::string name = "Player2") : Aspen::Graphics::Animation(
                                                                        new Aspen::Graphics::UniformSpritesheet("./resources/lundmarkyeezy.png", 300, 300, 1, nullptr, "Loadng"),
                                                                        1.0f / 12.0f, parent, name)

  {
    GetTransform()->SetPosition(200, 200);
    //GetTransform()->SetScale(0.3, 0.3);
    //CreateChild<Aspen::Physics::AABBCollider>()->SetSize(644 * 0.3, 644 * 0.3);
    CreateChild<Aspen::Physics::Rigidbody>();
  }
};

  void OnUpdate()
  {
    
  void OnCollision (Aspen::Physics::Collision c)
    {

    Aspen::Log::Debug("COLLISIONnnnn");
    GetRigidbody()->SetCartesianVelocity(0, -3);
    anim1->Deactivate();
    youWin->Activate();
    anim2->Deactivate();
    GetRigidbody()->SetCartesianVelocity(0, 0);
    

    }
};

class Enemy : public Aspen::Object::Object
{
Aspen::Graphics::Animation anim1;
bool GoingRight = true;

public:
Enemy(Object* parent = nullptr, std::string name = "Enemy") : Aspen::Object::Object (parent, name)
{
CreateChild<Aspen::Transform::Transform>();
CreateChild<Aspen::Physics::Rigidbody>();
CreateChild<Aspen::Physics::AABBCollider>()->SetSize(100,100);
}

void OnUpdate()
{
if (GoingRight)
{
  GetRigidbody()->SetCartesianVelocity(3,0);
}
if (!GoingRight)
{
  GetRigidbody()->SetCartesianVelocity(-3,0);
}
}
void OnCollision(Aspen::Physics::Collision c)
{
GoingRight = !GoingRight;
}
};

class Platform : public Aspen::Graphics::Rectangle
{ 
public:
  Platform(Object *parent = nullptr, std::string name = "Platform") :
  Aspen::Graphics::Rectangle(
    SDL_Rect ({0,0,32, 32}),
    Aspen::Graphics::Colors::RED, true, parent, name)
    {
      GetTransform()->SetPosition(100, 200);
      CreateChild<Aspen::Physics::AABBCollider>()->SetSize(32, 32);
      CreateChild<Aspen::Physics::Rigidbody>();

    }
      
      void OnCollision (Aspen::Physics::Collision c)
    {

    Aspen::Log::Debug("COLLISION");
    
    }

};
    
class MainMenu : public GameState
{
  Aspen::Graphics::UI::Text  *title;
  
  Player *player;
  Platform *platform;
  Enemy *enemy1;
  Player2 *Player2;
  
public:
  MainMenu(Object *parent=nullptr, std::string name="MainMenu") : GameState(parent, name)
  {
  title = new Aspen::Graphics::UI::Text("My Cool Game" , "default", 64, this, "Title");
  AddChild(title);
  title->GetTransform()->SetPosition( 271, 117);
  title->GetTransform()->SetRotation( 3.128f );
  title->GetTransform()->SetScale( 1, 1);
 

  enemy1 = new Enemy();
  AddChild(enemy1);




  player = new Player();
  AddChild(player);
  platform = new Platform(); 
  AddChild(platform); 
  player2 = new Player2();
  AddChild(player2);
  }
  
 

  void OnUpdate()
  {
   
 if (Aspen::Input::KeyHeld(SDLK_UP))
    {
      Player2->GetRigidbody()->SetCartesianVelocity(0, 5);
    }
    
    if (Aspen::Input::KeyHeld(SDLK_Right))
    {
      Player2->GetRigidbody()->SetCartesianVelocity(5, 0 );
    }
    if (Aspen::Input::KeyHeld(SDLK_LEFT))
    {
      Player2->GetRigidbody()->SetCartesianVelocity(-5, 0);
    }
      
    
       if (Aspen::Input::KeyHeld(SDLK_w))
      {
         Player->GetRigidbody()->SetCartesianVelocity(0, 5);
      }
       
      if (Aspen::Input::KeyHeld(SDLK_a))
      {
         Player->GetRigidbody()->SetCartesianVelocity(-5, 0);
        
      }
      if (Aspen::Input::KeyHeld(SDLK_d))
      {
        Player->GetRigidbody()->SetCartesianVelocity( 5, 0);
      }

      

   
    //if (title->GetTransform()-> SetScale(1, 1));


   // Aspen::Log::Debug("%d", Aspen::Graphics::DEFAULT_WINDOW_WIDTH);
  }


};


class Game : public GameState
{
  
};
 

int main(int argc, char **argv)
{
  Aspen::Log::Log::SetFile("./Aspen.log");


  //Engine engine(Aspen::Engine::START_FLAGS::ALL ^ (
    //Aspen::Engine::START_FLAGS::CREATE_GRAPHICS |
    //Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER |
    //Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE
    //));
    //Aspen::Graphics::Graphics *gfx = new Aspen::Graphics::Graphics(640, 480);
    //gfx->CreateChild<Aspen::Debug::Debug>();
    //gfx->CreateChild<Aspen::Graphics::FontCache>();
    //engine.AddChild(gfx);

  Engine engine(Aspen::Engine::START_FLAGS::ALL);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetGravityStrength(0);
  engine.FindChildOfType<Aspen::Physics::Physics>()->SetDrag(0.1);
  engine.FindChildOfType<Aspen::Time::Time>()->TargetFramerate(60);
  engine.FindChildOfType<Aspen::Graphics::Graphics>()->FindChildOfType<Aspen::Graphics::FontCache>()->LoadFont("resources/ABeeZee-Regular.ttf", "default");

  engine.FindChildOfType<GameStateManager>()->LoadState<MainMenu>(true);
  //engine.FindChildOfType<GameStateManager>()->LoadState<Game>(false);

  while (engine)
    engine();
  return 0;
}





////////////  W:640   H:480 //////////

///////////// TEST //////////////