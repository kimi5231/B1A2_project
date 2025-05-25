#include "pch.h"
#include "BehaviorTree.h"

// Selector
BehaviorState Selector::run()
{
    for (auto& child : children) {
        value = child->run();
        if (value == BehaviorState::RUNNING || value == BehaviorState::SUCCESS) {
            return value;
        }
    }
    value = BehaviorState::FAIL;    
    return value;   // 모든 자식 노드가 FAIL이면, 최종적으로 FAIL 반환
}

void Selector::reset()
{
    value = BehaviorState::UNDEF;
    for (auto& child : children) {
        child->reset();
    }
}

void Selector::addChild(Node* child)
{
    if (!child)
        return;

	children.push_back(child);
}

void Selector::addChildren(const std::vector<Node*>& nodes)
{
	for (const auto& child : nodes)
		children.push_back(child);
}

// Sequence
BehaviorState Sequence::run()
{
    for (Node* child : children)
    {
        BehaviorState result = child->run();

        if (result == BehaviorState::FAIL)
        {
            value = BehaviorState::FAIL;
            return value;
        }
        if (result == BehaviorState::RUNNING)
        {
            value = BehaviorState::RUNNING;
            return value;
        }
    }

    value = BehaviorState::SUCCESS; 
    return value;   // 모든 자식 노드가 SUCCESS를 반환하면 최종적으로 SUCCESS 반환
}

void Sequence::reset()
{
    value = BehaviorState::UNDEF;
    for (Node* child : children)
    {
        child->reset();
    }
}

void Sequence::addChild(Node* child)
{
    if (!child)
        return;

    children.push_back(child);
}

void Sequence::addChildren(const std::vector<Node*>& nodes)
{
    for (Node* node : nodes)
    {
        if (node)
        {
            children.push_back(node);
        }
    }
}

// Action
BehaviorState Action::run()
{
    value = func();
    return value;
}

void Action::reset()
{
    value = BehaviorState::UNDEF;
}

BehaviorState Condition::run()
{
    return func();
}

Node::Node()
{
}

Node::~Node()
{
}
