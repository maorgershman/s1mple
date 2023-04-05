module;

export module Main;

import Console;
import Keepalive;

export void run() noexcept
{
	Console console;

	Keepalive keepalive;
	keepalive.run();
}