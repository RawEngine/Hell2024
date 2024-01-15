#pragma once

// TODO: Move to PCH.h (Precompiled header)
#include <filesystem>
#include <memory>

class Log;

class Engine
{
public:
	Engine();
	~Engine();

	void Run();
	bool Init();
	void LazyKeyPresses();
	void LazyKeyPressesEditor();

private:

	void InitLogSystem();

private:

	const std::filesystem::path _pathApplication;

	std::unique_ptr<Log> _Log;
};
