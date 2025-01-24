#pragma once
#include <vector>

enum class BehaviorState
{
	FAIL = -1,
	RUNNING = 0,
	SUCCESS = 1,

	UNDEF
};

class Node
{
public:
	Node();
	virtual ~Node();

	virtual BehaviorState run() abstract;	// ����� ���� ���� �� ��� ��ȯ
	virtual void reset() = 0;	// ��� �ʱ�ȭ
	virtual void addChild(Node* node) {}
	virtual void addChildren(const std::vector<Node*>& children) {}
};

class Selector : public Node
{
public:
	BehaviorState run() override;	// �ڽ� ��� �� �ϳ��� SUCECESS�� ��ȯ�� ������ ����
	void reset() override;
	void addChild(Node* child) override;
	void addChildren(const std::vector<Node*>& nodes) override;

private:
	std::vector<Node*> children;
	BehaviorState value = BehaviorState::UNDEF;
};

class Sequence : public Node
{
public:
	BehaviorState run() override;	// �ڽ� ��� �� �ϳ��� FAIL�� ��ȯ�ϸ� ����
	void reset() override;
	void addChild(Node* child) override;
	void addChildren(const std::vector<Node*>& nodes) override;

private:
	std::vector<Node*> children;
	BehaviorState value = BehaviorState::UNDEF;
};

class Action : public Node
{
public:
	Action(const std::string& name, std::function<BehaviorState()> func) : name(name), func(func) {}
	BehaviorState run() override;
	void reset() override;

private:
	std::string name;
	std::function<BehaviorState()> func;
	BehaviorState value = BehaviorState::UNDEF;
};

class Condition : public Node
{
public:
	Condition(const std::string& name, std::function<BehaviorState()> func) : name(name), func(func) {}
	BehaviorState run() override;
	void reset() override {}

private:
	std::string name;
	std::function<BehaviorState()> func;
};