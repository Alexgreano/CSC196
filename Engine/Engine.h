#pragma once

#include "Graphics/ParticleSystem.h"
#include "AudioSystem.h"

//math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//objects
#include "Base/Actor.h"
#include "Base/Scene.h"

#define NOMINMAX
#include "core.h"
#include "Graphics/Shape.h"
#include <vector>
#include <memory>
#include "Framework/EventSystem.h"
#include "Framework/ResourceSystem.h"
#include <algorithm>

namespace nc {
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems) {
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}