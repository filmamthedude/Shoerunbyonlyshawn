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

// This is my special comment

///Goals for Elle://///
//-Make background sprite the background of the game
//

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

class FO : public Aspen::Object::Object
{
  bool GoingRight = true;

public:
  FO(Object *parent = nullptr, std::string name = "Enemy") : Aspen::Object::Object(parent, name)
  {
    CreateChild<Aspen::Transform::Transform>();
    CreateChild<Aspen::Physics::Rigidbody>();
    CreateChild<Aspen::Physics::AABBCollider>()->SetSize(300, 100);
  }
  void OnUpdate()
  {
    if (GoingRight)
    {
      GetRigidbody()->SetCartesianVelocity(3, 0);
    }
    if (!GoingRight)
    {
      GetRigidbody()->SetCartesianVelocity(-3, 0);
    }
  }
};

class Enemy : public Aspen::Object::Object
{
  Aspen::Graphics::Animation anim1;
  bool GoingRight = true;

public:
  Enemy(Object *parent = nullptr, std::string name = "Enemy") : Aspen::Object::Object(parent, name)
  {
    CreateChild<Aspen::Transform::Transform>();
    CreateChild<Aspen::Physics::Rigidbody>();
    CreateChild<Aspen::Physics::AABBCollider>()->SetSize(100, 100);
  }

  void OnUpdate()
  {
    if (GoingRight)
    {
      GetRigidbody()->SetCartesianVelocity(3, 0);
    }
    if (!GoingRight)
    {
      GetRigidbody()->SetCartesianVelocity(-3, 0);
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
  Platform(Object *parent = nullptr, std::string name = "Platform") : Aspen::Graphics::Rectangle(
                                                                          SDL_Rect({0, 0, 2600, 60}),
                                                                          Aspen::Graphics::Colors::RED, true, parent, name)
  {
    GetTransform()->SetPosition(640, 60);
    CreateChild<Aspen::Physics::AABBCollider>()->SetSize(2600, 60);
  }
};

class Background : public Aspen::Object::Object

{
  Aspen::Graphics::Sprite *BG;

public:
  Background(Object *parent = nullptr, std::string name = "Background") :

                                                                          Object(parent, name)
  {
    CreateChild<Aspen::Transform::Transform>();
    BG = new Aspen::Graphics::Sprite("./resources/Background_Final.png", parent, "background");
    AddChild(BG);
  }
};

class MainMenu : public GameState
{

  Aspen::Graphics::UI::Text *title;

  Player *player;

  Enemy *enemy1;
  Player2 *player2;
  Platform *platform;
  Platform *platform2;
  Platform *platform3;

public:
  MainMenu(Object *parent = nullptr, std::string name = "MainMenu") : GameState(parent, name)

  {

    Background *BG = new Background(nullptr, "Background");
    //Aspen::Log::Debug("Background is in the program!")
    BG->GetTransform()->SetPosition(200, 200);
    AddChild(BG);
    title = new Aspen::Graphics::UI::Text("My Cool Game", "default", 64, this, "Title");
    AddChild(title);
    title->GetTransform()->SetPosition(271, 117);
    title->GetTransform()->SetRotation(3.128f);
    title->GetTransform()->SetScale(1, 1);

    enemy1 = new Enemy();
    AddChild(enemy1);

    player = new Player();
    AddChild(player);
    player2 = new Player2();
    AddChild(player2);
    platform = new Platform();
    AddChild(platform);
    platform->GetTransform()->SetPosition(640, 670);
    platform2 = new Platform();
    AddChild(platform2);
    platform2->GetTransform()->SetPosition(640, 400);
    platform3 = new Platform();
    AddChild(platform3);
    platform3->GetTransform()->SetPosition(640, 400);
  }

  void OnUpdate()
  {

    if (Aspen::Input::KeyHeld(SDLK_UP))
    {
      Player2->GetRigidbody()->SetCartesianVelocity(0, 5);
    }

    if (Aspen::Input::KeyHeld(SDLK_RIGHT))
    {
      player2->GetRigidbody()->SetCartesianVelocity(5, 0);
    }
    if (Aspen::Input::KeyHeld(SDLK_LEFT))
    {
      Player2->GetRigidbody()->SetCartesianVelocity(-5, 0);
    }

    if (Aspen::Input::KeyHeld(SDLK_w))
    {
      player->GetRigidbody()->SetCartesianVelocity(0, 5);
    }

    if (Aspen::Input::KeyHeld(SDLK_a))
    {
      player->GetRigidbody()->SetCartesianVelocity(-5, 0);
    }
    if (Aspen::Input::KeyHeld(SDLK_d))
    {
      player->GetRigidbody()->SetCartesianVelocity(5, 0);
    }

    if (Aspen::Input::KeyHeld(SDLK_w))
    {
      player->GetRigidbody()->SetCartesianVelocity(0, 5);
    }

    if (Aspen::Input::KeyHeld(SDLK_a))
    {
      player->GetRigidbody()->SetCartesianVelocity(-5, 0);
    }
    if (Aspen::Input::KeyHeld(SDLK_d))
    {
      player->GetRigidbody()->SetCartesianVelocity(5, 0);
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

  Engine engine(Aspen::Engine::START_FLAGS::ALL ^ (Aspen::Engine::START_FLAGS::CREATE_GRAPHICS |
                                                   Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_DEBUGGER |
                                                   Aspen::Engine::START_FLAGS::CREATE_GRAPHICS_FONTCACHE));
  Aspen::Graphics::Graphics *gfx = new Aspen::Graphics::Graphics(1280, 720, &engine, "Graphics 720p");
  engine.AddChild(gfx);
  gfx->CreateChild<Aspen::Debug::Debug>();
  gfx->CreateChild<Aspen::Graphics::FontCache>();

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