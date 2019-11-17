#pragma once
#include "scene/gui/control.h"
#include "editor/editor_plugin.h"

class EditorNode;

class VersionTracker : public Control
{
	GDCLASS(VersionTracker, Control);

public:
	VersionTracker();

	static void _bind_methods();
	void _notification(int p_what);

	bool unreference() const { return true; }

private:
	String CommitHash;
	String CommitDate;
	String Author;
	String Subject;
};

class VersionTrackerPlugin : public EditorPlugin
{
	GDCLASS(VersionTrackerPlugin, EditorPlugin);

public:
	VersionTrackerPlugin(EditorNode* p_node);
	~VersionTrackerPlugin();

	virtual String get_name() const { return "VersionTracker"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);


private:
	VersionTracker* VersionTrackerPtr = nullptr;
	EditorNode *editor = nullptr;
	Button *button = nullptr;
};
