#include "version_tracker.h"
#include "editor_node.h"

VersionTracker::VersionTracker()
	: CommitHash(String("Commit ID - {0}").format(varray(GIT_COMMITHASH)))
	, CommitDate(String("Commit DateTime - {0}").format(varray(GIT_COMMITDATE)))
	, Author(String("Author - {0}").format(varray(GIT_AUTHOR)))
	, Subject(String("Subject - {0}").format(varray(GIT_SUBJECT)))
{
	
}

void VersionTracker::_bind_methods()
{
}

void VersionTracker::_notification(int p_what)
{
	switch (p_what)
	{
	case NOTIFICATION_DRAW:
	{
		RID ci = get_canvas_item();
		Size2 size = get_size();

		Ref<Font> font = get_font("font", "Tree");
		Ref<StyleBox> tree_st = get_stylebox("bg", "Tree");
		tree_st->draw(ci, Rect2(Point2(), size));
		Color color = get_color("font_color", "Tree");

		Point2 ofs = tree_st->get_offset();
		ofs.y += font->get_ascent();

		font->draw(ci, ofs, CommitHash, color);
		ofs.y += font->get_ascent();

		font->draw(ci, ofs, Author, color);
		ofs.y += font->get_ascent();

		font->draw(ci, ofs, CommitDate, color);
		ofs.y += font->get_ascent();

		font->draw(ci, ofs, Subject, color);
	}
	break;

	}
}


VersionTrackerPlugin::VersionTrackerPlugin(EditorNode *p_node)
{
	editor = p_node;
	VersionTrackerPtr = memnew(VersionTracker);
	VersionTrackerPtr->set_custom_minimum_size(Size2(0, 300));
	button = editor->add_bottom_panel_item(TTR("VersionTracker"), VersionTrackerPtr);
	button->show();
}


VersionTrackerPlugin::~VersionTrackerPlugin()
{
	memdelete(VersionTrackerPtr);
}

void VersionTrackerPlugin::edit(Object *p_object)
{
}

bool VersionTrackerPlugin::handles(Object *p_object) const
{
	return p_object->is_class("VersionTracker");
}

void VersionTrackerPlugin::make_visible(bool p_visible)
{
	if (p_visible)
	{
		button->show();
		editor->make_bottom_panel_item_visible(VersionTrackerPtr);
		VersionTrackerPtr->set_process_input(true);
	}
	else
	{

		if (VersionTrackerPtr->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();
		VersionTrackerPtr->set_process_input(false);
	}
}
