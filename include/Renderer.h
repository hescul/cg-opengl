// Copyright (c) 2023. Minh Nguyen
// All rights reserved.

#pragma once

#include <array>
#include <glad/glad.h>

#include "View.h"

class Renderer {
public:
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) noexcept = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	struct ClearOptions {
		bool clear{ true };

		std::array<float, 4> clearColor{ 0.0f, 0.0f, 0.0f, 1.0f };
	};

	void setClearOptions(const ClearOptions& options);

	[[nodiscard]] ClearOptions getClearOptions() const;

	enum class PolygonMode {
		LINE = GL_LINE,
		FILL = GL_FILL
	};

	void setPolygonMode(PolygonMode mode);

	void togglePolygonMode();

	[[nodiscard]] PolygonMode getPolygonMode() const;

	void render(const View& view) const;

private:
	Renderer() = default;

	ClearOptions _clearOptions{};

	PolygonMode _polygonMode{ PolygonMode::FILL };

	friend class Engine;
};