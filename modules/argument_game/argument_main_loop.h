#pragma once
#include "scene/main/scene_tree.h"

class InputEventMouseMotion;

class ArgumentMainLoop : public SceneTree
{
	GDCLASS(ArgumentMainLoop, SceneTree);

public:

	virtual void input_event(const Ref<InputEvent> &p_event) override;
	virtual void input_text(const String &p_text) override;
	virtual void init() override;
	virtual bool iteration(float p_time) override;
	virtual bool idle(float p_time) override;
	virtual void finish() override;

	virtual void drop_files(const Vector<String> &p_files, int p_from_screen = 0) override;

protected:
	static void _bind_methods();

	Ref<InputEventMouseMotion> MouseMoveEvent;
	static const String MouseMoveEventName;
};
