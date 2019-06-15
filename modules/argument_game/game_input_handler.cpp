#include "game_input_handler.h"
#include "core/input_map.h"
#include "core/map.h"
#include "common/debug.h"
#include <utility>
#include "core/os/input.h"

GameInputHandler* GameInputHandler::SingletonInstance = NULL;

void GameInputHandler::BindInputEvent(String eventName, InputCallback callback)
{
	assert(InputMap::get_singleton()->get_action_map().has(eventName)); // Add event to Input Map in Project settings
	if (InputBindings.has(eventName))
	{
		InputBindings[eventName].push_back(callback);
	}
	else
	{
		Vector<InputCallback> callbackArray;
		callbackArray.push_back(callback);
		InputBindings.insert(eventName, callbackArray);
	}
}

void GameInputHandler::PollInputEvents(const Ref<InputEvent>& Event) const
{
	for (auto itr = InputMap::get_singleton()->get_action_map().front(); itr; itr = itr->next())
	{
		if (InputBindings.has(itr->key()) && InputMap::get_singleton()->action_has_event(itr->key(), Event))
		{
			InputDetails input;
			input.Event = Event;

			input.ActionState |= Event->is_action_pressed(itr->key()) ? EInputActionStatus::Pressed : EInputActionStatus::None;
			input.ActionState |= Event->is_action_released(itr->key()) ? EInputActionStatus::Released : EInputActionStatus::None;
			input.ActionState |= Input::get_singleton()->is_action_this_frame(itr->key()) ? EInputActionStatus::ThisFrame : EInputActionStatus::None;

			if (input.ActionState == EInputActionStatus::None)
				input.ActionState = EInputActionStatus::Pressed;

			const Vector<InputCallback>& callbackArray = InputBindings[itr->key()];
			for (int i = 0; i < callbackArray.size(); ++i)
			{
				callbackArray[i](input);
			}
		}
	}
}

bool GameInputHandler::EventIsAction(const Ref<InputEvent> &event, String actionName)
{
	for (auto itr = InputMap::get_singleton()->get_action_map().front(); itr; itr = itr->next())
	{
		if (itr->key() == actionName && InputMap::get_singleton()->action_has_event(itr->key(), event))
		{
			return true;
		}
	}

	return false;
}

GameInputHandler* GameInputHandler::GetSingletonInstance()
{
	if (!SingletonInstance)
	{
		SingletonInstance = memnew(GameInputHandler);
	}

	return SingletonInstance;
}



void GameInputHandler::_bind_methods()
{
}
