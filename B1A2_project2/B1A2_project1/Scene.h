#pragma once

class Panel;
class Actor;
class Player;
class Inventory;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

public:
	Actor* GetActor(int32 id);

protected:
	void AddActor(Actor* actor);
	void AddPanel(Panel* panel);
	void RemovePanel(Panel* panel);

public:
	void RemoveActor(Actor* actor);

protected:
	std::vector<Actor*> _actors[LAYER_MAXCOUNT];
	std::vector<Panel*> _panels;

	SceneState _sceneState = SceneState::Play;
};