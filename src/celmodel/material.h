// material.h
//
// Copyright (C) 2004-2010, Celestia Development Team
// Original version by Chris Laurel <claurel@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#ifndef _CELMODEL_MATERIAL_H_
#define _CELMODEL_MATERIAL_H_

#include <Eigen/Core>
#include <string>
#include <array>
#include <celutil/color.h>
#include <celcompat/filesystem.h>


namespace cmod
{

class Material
{
public:
    Material();
    ~Material();

    class Color
    {
    public:
        constexpr Color() :
            m_red(0.0f),
            m_green(0.0f),
            m_blue(0.0f)
        {
        }

        constexpr Color(float r, float g, float b) :
            m_red(r),
            m_green(g),
            m_blue(b)
        {
        }

        Color(const ::Color& color) :
            m_red(color.red()),
            m_green(color.green()),
            m_blue(color.blue())
        {
        }

        constexpr float red() const
        {
            return m_red;
        }

        constexpr float green() const
        {
            return m_green;
        }

        constexpr float blue() const
        {
            return m_blue;
        }

        Eigen::Vector3f toVector3() const
        {
            return Eigen::Vector3f(m_red, m_green, m_blue);
        }

        constexpr bool operator==(const Color& other) const
        {
            return m_red == other.m_red && m_green == other.m_green && m_blue == other.m_blue;
        }

        constexpr bool operator!=(const Color& other) const
        {
            return !(*this == other);
        }

    private:
        float m_red;
        float m_green;
        float m_blue;
    };

    class TextureResource
    {
    public:
        virtual ~TextureResource() = default;
        virtual fs::path source() const = 0;
    };

    class DefaultTextureResource : public TextureResource
    {
    public:
        DefaultTextureResource(const fs::path& source) : m_source(source) {};
        fs::path source() const override { return m_source; }

    private:
        fs::path m_source;
    };

    enum BlendMode
    {
        NormalBlend             = 0,
        AdditiveBlend           = 1,
        PremultipliedAlphaBlend = 2,
        BlendMax                = 3,
        InvalidBlend            = -1,
    };

    enum TextureSemantic
    {
        DiffuseMap             =  0,
        NormalMap              =  1,
        SpecularMap            =  2,
        EmissiveMap            =  3,
        TextureSemanticMax     =  4,
        InvalidTextureSemantic = -1,
    };

    Color diffuse{ 0.0f, 0.0f, 0.0f };
    Color emissive{ 0.0f, 0.0f, 0.0f };
    Color specular{ 0.0f, 0.0f, 0.0f };
    float specularPower{ 1.0f };
    float opacity{ 1.0f };
    BlendMode blend{ NormalBlend };
    std::array<TextureResource*, TextureSemanticMax> maps;
};

} // namespace cmod

#endif // _CELMODEL_MATERIAL_H_

