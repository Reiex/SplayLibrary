#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
	struct Event
	{
		template<typename T> T as() const { return *((T*) (this)); }

		enum class EventType
		{
			Unknown,
			ResizeEvent
		};

		EventType type = EventType::Unknown;
	};

	struct ResizeEvent : public Event
	{
		uvec2 size;
	};
}
