#pragma once
#include "command.h"
#include <vector>

class CommandHandler {
public:
	CommandHandler() {
		_lastSavedIndex = _historyIndex = -1;
	}

	~CommandHandler() {
		for (int i = 0; i < _history.size(); i++)
			delete _history[i];
	}

	//add a command to end of queue
	void addCommand(Command* newcmd) {
		for (int i = _historyIndex + 1; i < _history.size(); i++)
			delete _history[i];
		_history.resize(_historyIndex + 1);

		_history.push_back(newcmd);
		newcmd->redo();
		_historyIndex++;
	}

	void undoCommand() {
		//printf("_hI: %d\n", _historyIndex);
		if (_historyIndex == -1)
			return;

		_history[_historyIndex]->undo();
		_historyIndex--;
	}

	void redoCommand() {
		//printf("_hI: %d\n", _historyIndex);
		if (_historyIndex == _history.size() - 1)
			return;
		_history[_historyIndex + 1]->redo();
		_historyIndex++;
	}

	bool areChanges() {
		return !(_historyIndex == _lastSavedIndex);
	}

	void callOnSave() {
		_lastSavedIndex = _historyIndex;
	}

private:
	std::vector<Command*> _history;
	int _historyIndex;
	int _lastSavedIndex;
};