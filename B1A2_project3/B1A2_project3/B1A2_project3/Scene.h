#pragma once

enum
{
	MAX_LAYER = 32
};

class GameObject;


class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	void SetLayerName(uint8 index, const std::wstring& name);
	const std::wstring& IndexToLayerName(uint8 index) { return _layerNames[index]; }
	uint8 LayerNameToIndex(const std::wstring& name);

	std::shared_ptr<class Camera> GetMainCamera();

	virtual void Render();

	void ClearRTV();

	void RenderShadow();
	void RenderDeferred();
	void RenderLights();
	void RenderFinal();

	void RenderForward();

protected:
	void PushLightData();

public:
	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

	const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

protected:
	std::vector<std::shared_ptr<GameObject>>		_gameObjects;
	std::vector<std::shared_ptr<class Camera>>	_cameras;
	std::vector<std::shared_ptr<class Light>>		_lights;

	std::array<std::wstring, MAX_LAYER> _layerNames;
	std::map<std::wstring, uint8> _layerIndex;
};