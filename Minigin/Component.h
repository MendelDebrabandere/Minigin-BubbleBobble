#pragma once

namespace dae
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() {};

		virtual void Update() {};
		//virtual void LateUpdate() {};
		virtual void FixedUpdate() {};


		//void Destroy();

	};
}

