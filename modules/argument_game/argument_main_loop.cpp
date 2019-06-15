#include "argument_main_loop.h"
#include "game_input_handler.h"
#include "core/input_map.h"
#include "core/os/input.h"

void ArgumentMainLoop::input_event(const Ref<InputEvent> &p_event)
{
	GameInputHandler::GetSingletonInstance()->PollInputEvents(p_event);

	SceneTree::input_event(p_event);
}

void ArgumentMainLoop::input_text(const String &p_text)
{
	SceneTree::input_text(p_text);
}

void ArgumentMainLoop::init()
{
	SceneTree::init();
}

bool ArgumentMainLoop::iteration(float p_time)
{
	return SceneTree::iteration(p_time);
}

bool ArgumentMainLoop::idle(float p_time)
{
	return SceneTree::idle(p_time);
}

void ArgumentMainLoop::finish()
{
	SceneTree::finish();
}

void ArgumentMainLoop::drop_files(const Vector<String> &p_files, int p_from_screen /*= 0*/)
{
	SceneTree::drop_files(p_files, p_from_screen);
}

void ArgumentMainLoop::_bind_methods()
{
}
