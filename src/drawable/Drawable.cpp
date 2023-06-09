// Copyright (c) 2023. Minh Nguyen
// All rights reserved.

#include "drawable/Drawable.h"

Entity Drawable::getEntity() const {
	return _entity;
}

Shader* Drawable::getShader() const {
	return _shader;
}

Shader *Drawable::Builder::defaultShader(Engine& engine) const {
    const auto shader = Shader::Builder(_shaderModel).build(engine);
    if (_shaderModel == Shader::Model::UNLIT) {
        if (_textureUnlit != nullptr) {
            shader->use();
            shader->setUniform(Shader::Uniform::UNLIT_TEXTURE, *_textureUnlit);
        }
    } else if (_shaderModel == Shader::Model::PHONG) {
        shader->use();
        shader->setUniform(Shader::Uniform::MATERIAL_AMBIENT, _phongAmbient.r, _phongAmbient.g, _phongAmbient.b);
        shader->setUniform(Shader::Uniform::MATERIAL_DIFFUSE, _phongDiffuse.r, _phongDiffuse.g, _phongDiffuse.b);
        shader->setUniform(Shader::Uniform::MATERIAL_SPECULAR, _phongSpecular.r, _phongSpecular.g, _phongSpecular.b);
        shader->setUniform(Shader::Uniform::MATERIAL_SHININESS, _phongShininess);

        if (_textureDiffuse != nullptr) {
            shader->setUniform(Shader::Uniform::TEXTURED_MATERIAL_DIFFUSE, *_textureDiffuse);
        }
        if (_textureSpecular != nullptr) {
            shader->setUniform(Shader::Uniform::TEXTURED_MATERIAL_SPECULAR, *_textureSpecular);
        }
        shader->setUniform(Shader::Uniform::TEXTURED_MATERIAL_SHININESS, _textureShininess);
    }
    return shader;
}

Drawable::Builder& Drawable::Builder::shaderModel(const Shader::Model model) {
	_shaderModel = model;
	return *this;
}

Drawable::Builder &Drawable::Builder::phongAmbient(const float r, const float g, const float b) {
    _phongAmbient.r = r; _phongAmbient.g = g; _phongAmbient.b = b;
    return *this;
}

Drawable::Builder &Drawable::Builder::phongAmbient(const glm::vec3 &ambient) {
    return phongAmbient(ambient.r, ambient.g, ambient.b);
}

Drawable::Builder &Drawable::Builder::phongDiffuse(const float r, const float g, const float b) {
    _phongDiffuse.r = r; _phongDiffuse.g = g; _phongDiffuse.b = b;
    return *this;
}

Drawable::Builder &Drawable::Builder::phongDiffuse(const glm::vec3 &diffuse) {
    return phongDiffuse(diffuse.r, diffuse.g, diffuse.b);
}

Drawable::Builder &Drawable::Builder::phongSpecular(const float r, const float g, const float b) {
    _phongSpecular.r = r; _phongSpecular.g = g; _phongSpecular.b = b;
    return *this;
}

Drawable::Builder &Drawable::Builder::phongSpecular(const glm::vec3 &specular) {
    return phongSpecular(specular.r, specular.g, specular.b);
}

Drawable::Builder &Drawable::Builder::phongShininess(const float shininess) {
    _phongShininess = shininess;
    return *this;
}

Drawable::Builder &Drawable::Builder::phongMaterial(const phong::Material &material) {
    phongAmbient(material.ambient);
    phongDiffuse(material.diffuse);
    phongSpecular(material.specular);
    phongShininess(material.shininess);
    return *this;
}

Drawable::Builder &Drawable::Builder::textureUnlit(Texture* const texture) {
    _textureUnlit = texture;
    return *this;
}

Drawable::Builder &Drawable::Builder::textureDiffuse(Texture* const texture) {
    _textureDiffuse = texture;
    return *this;
}

Drawable::Builder &Drawable::Builder::textureSpecular(Texture* const texture) {
    _textureSpecular = texture;
    return *this;
}

Drawable::Builder &Drawable::Builder::textureShininess(const float shininess) {
    _textureShininess = shininess;
    return *this;
}
