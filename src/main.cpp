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

class Player : public Aspen::Object::Object
{ 
 Aspen::Graphics::Animation *anim1;
 Aspen::Graphics::Animation *anim2;
 Aspen::Graphics::UI::Text  *youWin;

public:
   Player(Object *parent = nullptr, std::string name = "Player") :
     Object(parent, name)
  {
    youWin = new Aspen::Graphics::UI::Text("YOU WIN!!!" , "default", 64, this, "Title");
    AddChild(youWin);
    youWin->GetTransform()->SetPosition( 320, 240);
    youWin->GetTransform()->SetRotation( 3.128f );
    youWin->GetTransform()->SetScale( 1, 1);
    youWin->Deactivate();




    anim1 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/New Piskel.png",32, 32, 94, nullptr, "CubeSpritesheet"), 1.0f/12.0f, parent, "Cube animation");
    AddChild(anim1);
    anim2 = new Aspen::Graphics::Animation(new Aspen::Graphics::UniformSpritesheet("./resources/Flight.png",32, 32, 9, nullptr, "FlightSpritesheet"), 1.0f/12.0f, parent, "Flight animation");
    anim2->Deactivate();
    AddChild(anim2);
    CreateChild<Aspen::Physics::AABBCollider>()->SetSize(32,32);
    CreateChild<Aspen::Physics::Rigidbody>();
    CreateChild<Aspen::Transform::Transform>();
    GetTransform()->SetPosition(100, 100);
  }

  void OnUpdate()
  {
    if (Aspen::Input::KeyHeld(SDLK_w))
    {
      GetRigidbody()->SetCartesianVelocity(0, -5);
      anim1->Deactivate();
      anim2->Activate();
    }
    
    if (Aspen::Input::KeyHeld(SDLK_s))
    {
      GetRigidbody()->SetCartesianVelocity(0, 5);
      anim1->Deactivate();
      anim2->Activate();
      
      
      
    }
      
    if (Aspen::Input::KeyHeld(SDLK_a))
    {
      GetRigidbody()->SetCartesianVelocity(-5, 0);
      anim1->Deactivate();
      anim2->Activate();
    }
     
      if (Aspen::Input::KeyHeld(SDLK_d))
    {
      GetRigidbody()->SetCartesianVelocity(5, 0);
      anim1->Deactivate();
      anim2->Activate();
    }
           
      if (!Aspen::Input::KeyHeld(SDLK_d) && !Aspen::Input::KeyHeld(SDLK_s) && !Aspen::Input::KeyHeld(SDLK_a) && !Aspen::Input::KeyHeld(SDLK_w))
    {
      anim2->Deactivate();
      anim1->Activate();
    }
    
  }
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
  
public:
  MainMenu(Object *parent=nullptr, std::string name="MainMenu") : GameState(parent, name)
  {
  title = new Aspen::Graphics::UI::Text("My Cool Game" , "default", 64, this, "Title");
  AddChild(title);
  title->GetTransform()->SetPosition( 271, 117);
  title->GetTransform()->SetRotation( 3.128f );
  title->GetTransform()->SetScale( 1, 1);
 

  





  player = new Player();
  AddChild(player);
  platform = new Platform(); 
  AddChild(platform); 
  }
  
 

  void OnUpdate()
  {
    if (Aspen::Input::KeyHeld(SDLK_SPACE))
      {

  
       Aspen::Log::Info("Space held");
       
      }
      else
      {
      
       //title->GetTransform()-> SetPosition(271, 117);

      }



       if (Aspen::Input::KeyHeld(SDLK_s))
      {

  
       Aspen::Log::Info("s held");
       //title->GetTransform()-> SetScale(2, 2);
       
      }
      else
      {
      
     

      }
       
      if (Aspen::Input::KeyHeld(SDLK_UP))
      {
        Aspen::Log::Info("Up held");
        ///title->GetTransform()->SetRotation( 40.138f );//

        
       // title->GetRigidbody()-> SetCartesianVelocity(0, 5);
         
      }
      if (Aspen::Input::KeyHeld(SDLK_DOWN))
      {
        Aspen::Log::Info("Down held");
        


        
        
      }











      if (Aspen::Input::KeyHeld(SDLK_LEFT))
      {
        Aspen::Log::Info("Left held");
        ///title->GetTransform()->SetRotation( 40.138f );//


        
      }
        
        else if (Aspen::Input::KeyHeld(SDLK_RIGHT))
        {
          Aspen::Log::Info("Right held");
         

        }
          else
          {
            
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