#pragma once
#include <vector>

template<typename ObjectType>
class Object {
public:
	Object(){}

	ObjectType* getParent() const {
		return parent;
	}

	void setParent(Object* parent) {
		this->parent = dynamic_cast<ObjectType*>(parent);
	}

	virtual void addChild(ObjectType* child) {
		dynamic_cast<Object*>(child)->setParent(this);
		children.push_back(child);
	}

	void deleteChild(ObjectType* child) {
		for (auto it = children.begin(); it != children.end(); ++it) {
			if (*it == child) {
				children.erase(it);
				return;
			}
		}
	}
	std::vector<ObjectType*>getChildren() {
		return children;
	}

protected:
	ObjectType* parent = nullptr;
	std::vector<ObjectType*>children;
};

