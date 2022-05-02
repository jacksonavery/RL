#pragma once

class Command {
public:
	virtual void undo() = 0;
	virtual void redo() = 0;
};