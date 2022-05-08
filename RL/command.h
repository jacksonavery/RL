#pragma once

class Command {
public:
	// undo/redo return true if grouped with prev/next func
	virtual void undo() = 0;
	virtual void redo() = 0;
	bool groupWithNext = 0;
};