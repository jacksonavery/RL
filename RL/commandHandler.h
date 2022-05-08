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

		//adjust the new command's grouping
		newcmd->groupWithNext = _groupOpen;

		// add and do the new command.
		// intentionally don't call redoCommand because incomplete grouping
		// will break things.
		_history.push_back(newcmd);
		_historyIndex++;
		_history[_historyIndex]->redo();

	}

	void undoCommand() {
		//printf("_hI: %d\n", _historyIndex);
		if (_historyIndex == -1)
			return;

		//do {
		//	_historyIndex--;
		//} while (_history[_historyIndex + 1]->undo());
		do {
			_history[_historyIndex]->undo();
			_historyIndex--;
		} while (_historyIndex > -1 && _history[_historyIndex]->groupWithNext);
	}

	void redoCommand() {
		//printf("_hI: %d\n", _historyIndex);
		if (_historyIndex == _history.size() - 1)
			return;

		do {
			_historyIndex++;
			_history[_historyIndex]->redo();
		} while (_historyIndex < _history.size() - 1 && _history[_historyIndex]->groupWithNext);
	}

	bool areChanges() {
		return !(_historyIndex == _lastSavedIndex);
	}

	void callOnSave() {
		_lastSavedIndex = _historyIndex;
	}

	// start and end group can be called to group operations so that a single
	// undo press undoes the whole group.
	void startGroup() {
		_groupOpen = true;
	}

	void stopGroup() {
		_groupOpen = false;
		_history[_history.size() - 1]->groupWithNext = false;
	}

private:
	std::vector<Command*> _history;
	int _historyIndex;
	int _lastSavedIndex;
	bool _groupOpen = false;
};