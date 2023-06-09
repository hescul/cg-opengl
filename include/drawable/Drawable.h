// Copyright (c) 2023. Minh Nguyen
// All rights reserved.

#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <stdexcept>

#include "EntityManager.h"
#include "Shader.h"
#include "Texture.h"

#include "drawable/Material.h"

class Drawable {
public:
	~Drawable() = default;
	Drawable(const Drawable& other) = delete;
	Drawable& operator=(const Drawable& other) = delete;
	Drawable(Drawable&& other) noexcept = delete;
	Drawable& operator=(Drawable&& other) noexcept = delete;

	class Builder {
	public:
		virtual ~Builder() = default;
		Builder(const Builder&) = default;
		Builder(Builder&&) noexcept = default;
		Builder& operator=(const Builder&) = default;
		Builder& operator=(Builder&&) noexcept = default;

		Builder& shaderModel(Shader::Model model);

        Builder& phongAmbient(float r, float g, float b);
        Builder& phongAmbient(const glm::vec3& ambient);
        Builder& phongDiffuse(float r, float g, float b);
        Builder& phongDiffuse(const glm::vec3& diffuse);
        Builder& phongSpecular(float r, float g, float b);
        Builder& phongSpecular(const glm::vec3& specular);
        Builder& phongShininess(float shininess);
        Builder& phongMaterial(const phong::Material& material);

        Builder& textureUnlit(Texture* texture);

        Builder& textureDiffuse(Texture* texture);
        Builder& textureSpecular(Texture* texture);
        Builder& textureShininess(float shininess);

		virtual std::unique_ptr<Drawable> build(Engine& engine) = 0;

	protected:
        // This is required for user-defined constructors in the derived builders.
        Builder() = default;

        /**
         * Builds an instance of the default shader using the default values set for this Drawable's Builder. The derived
         * builders can choose to use this default shader which handles most of the shading initializations, or create a
         * new one and initialize it on theirs own.
         * @param engine - the Engine used for this Drawable::Builder's construction.
         * @return The default Shader.
         */
        [[nodiscard]] Shader* defaultShader(Engine& engine) const;

    private:
		Shader::Model _shaderModel{ Shader::Model::UNLIT };

        glm::vec3 _phongAmbient{1.0f, 0.5f, 0.31f };
        glm::vec3 _phongDiffuse{1.0f, 0.5f, 0.31f };
        glm::vec3 _phongSpecular{0.5f, 0.5f, 0.5f };
        float _phongShininess{ 32.0f };

        Texture* _textureUnlit{ nullptr };

        Texture* _textureDiffuse{ nullptr };
        Texture* _textureSpecular{ nullptr };
        float _textureShininess{ 10.0f };
	};

    [[nodiscard]] Entity getEntity() const;

    [[nodiscard]] Shader* getShader() const;

protected:
	Drawable(const Entity entity, Shader* const shader) : _entity{ entity }, _shader{ shader } {
    }

private:
	const Entity _entity;

	Shader* const _shader;
};