#pragma once
#include "core/os/input_event.h"
#include <functional>
#include "core/object.h"
#include "enum_flag_operations.h"

enum class EInputActionStatus
{
	None			= 0,
	Pressed			= 1 << 0,
	Released		= 1 << 1,
	ThisFrame		= 1 << 2,
	JustPressed		= Pressed | ThisFrame,
	JustReleased	= Released | ThisFrame
};

ENUM_FLAG_OPERATIONS(EInputActionStatus);

struct InputDetails
{
	Ref<InputEvent> Event;
	EInputActionStatus ActionState;

public:
	InputDetails() : ActionState(EInputActionStatus::None) { }
};

class GameInputHandler : public Object
{
	GDCLASS(GameInputHandler, Object);

public:
	typedef std::function<bool(const InputDetails&)> InputCallback;

public:
	void BindInputEvent(String eventName, InputCallback callback);
	void PollInputEvents(const Ref<InputEvent>& Event) const;
	bool EventIsAction(const Ref<InputEvent>& event, String actionName);

	static GameInputHandler* GetSingletonInstance();

protected:
	static void _bind_methods();

protected:
	Map<String, Vector<InputCallback>> InputBindings;
	static GameInputHandler* SingletonInstance;
};

#define BIND_INPUT_CALLBACK(ActionBinding, OwningPtr, FunctionPtr)\
{\
	using std::placeholders::_1;\
	GameInputHandler::InputCallback callback = std::bind(FunctionPtr, OwningPtr, _1);\
	GameInputHandler::GetSingletonInstance()->BindInputEvent(ActionBinding, callback);\
}
