///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/Core.hpp>
#include <SplayLibrary/Private/PrivateNotIncluded.hpp>

namespace spl
{
	Texture::Texture() :
		_texture(0),
		_params(),

		_borderColor(),
		_compareMode(),
		_compareFunc(),
		_minLod(),
		_maxLod(),
		_lodBias(),
		_minFilter(),
		_magFilter(),
		_maxAnisotropy(),
		_sWrap(),
		_tWrap(),
		_rWrap()
	{
	}

	Texture::Texture(const TextureCreationParams& params) : Texture()
	{
		createNew(params);
	}

	void Texture::createNew(const TextureCreationParams& params)
	{
		const uint32_t internalFormatGL = _spl::textureInternalFormatToGLenum(params.internalFormat);
		const ImplementationDependentValues& impl = Context::getCurrentContext()->getImplementationDependentValues();

		destroy();

		_params.target = params.target;
		_params.internalFormat = params.internalFormat;
		glCreateTextures(_spl::textureTargetToGLenum(_params.target), 1, &_texture);

		switch (_params.target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(params.width)) + 1.0);

				_params.width = params.width;
				_params.levels = params.levels;

				glTextureStorage1D(_texture, _params.levels, internalFormatGL, _params.width);

				break;
			}
			case TextureTarget::Texture2D:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxTextureSize);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(std::max(params.width, params.height))) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.levels = params.levels;

				glTextureStorage2D(_texture, _params.levels, internalFormatGL, _params.width, _params.height);

				break;
			}
			case TextureTarget::Texture3D:
			{
				assert(params.width > 0 && params.width <= impl.general.max3dTextureSize);
				assert(params.height > 0 && params.height <= impl.general.max3dTextureSize);
				assert(params.depth > 0 && params.depth <= impl.general.max3dTextureSize);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(std::max({ params.width, params.height, params.depth }))) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.depth = params.depth;
				_params.levels = params.levels;

				glTextureStorage3D(_texture, _params.levels, internalFormatGL, _params.width, _params.height, _params.depth);

				break;
			}
			case TextureTarget::Array1D:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxArrayTextureLayers);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(params.width)) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.levels = params.levels;

				glTextureStorage2D(_texture, _params.levels, internalFormatGL, _params.width, _params.height);

				break;
			}
			case TextureTarget::Array2D:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxTextureSize);
				assert(params.depth > 0 && params.depth <= impl.general.maxArrayTextureLayers);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(std::max(params.width, params.height))) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.depth = params.depth;
				_params.levels = params.levels;

				glTextureStorage3D(_texture, _params.levels, internalFormatGL, _params.width, _params.height, _params.depth);

				break;
			}
			case TextureTarget::Rectangle:
			{
				assert(params.width > 0 && params.width <= impl.general.maxRectangleTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxRectangleTextureSize);

				_params.width = params.width;
				_params.height = params.height;

				glTextureStorage2D(_texture, 1, internalFormatGL, _params.width, _params.height);

				break;
			}
			case TextureTarget::Buffer:
			{
				assert(params.buffer != nullptr);
				assert(params.bufferSize > 0 && params.bufferSize <= impl.general.maxTextureBufferSize);
				assert(params.bufferOffset + params.bufferSize <= params.buffer->getSize());

				_params.buffer = params.buffer;
				_params.bufferSize = params.bufferSize;
				_params.bufferOffset = params.bufferOffset;

				glTextureBufferRange(_texture, internalFormatGL, _params.buffer->getHandle(), _params.bufferOffset, _params.bufferSize);

				break;
			}
			case TextureTarget::CubeMap:
			{
				assert(params.width == params.height);
				assert(params.width > 0 && params.width <= impl.general.maxCubeMapTextureSize);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(params.width)) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.depth = 6;
				_params.levels = params.levels;

				glTextureStorage2D(_texture, _params.levels, internalFormatGL, _params.width, _params.height);

				break;
			}
			case TextureTarget::CubeMapArray:
			{
				assert(params.width == params.height);
				assert(params.width > 0 && params.width <= impl.general.maxCubeMapTextureSize);
				assert(params.depth % 6 == 0);
				assert(params.depth > 0 && params.depth <= impl.general.maxArrayTextureLayers);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(params.width)) + 1.0);

				_params.width = params.width;
				_params.height = params.height;
				_params.depth = params.depth;
				_params.levels = params.levels;

				glTextureStorage3D(_texture, _params.levels, internalFormatGL, _params.width, _params.height, _params.depth);

				break;
			}
			case TextureTarget::Multisample2D:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxTextureSize);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(std::max(params.width, params.height))) + 1.0);
				assert(params.samples > 0 && params.samples <= impl.general.maxSamples);

				_params.width = params.width;
				_params.height = params.height;
				_params.levels = params.levels;
				_params.samples = params.samples;
				_params.fixedSampleLocations = params.fixedSampleLocations;

				glTextureStorage2DMultisample(_texture, _params.samples, internalFormatGL, _params.width, _params.height, _params.fixedSampleLocations);

				break;
			}
			case TextureTarget::Multisample2DArray:
			{
				assert(params.width > 0 && params.width <= impl.general.maxTextureSize);
				assert(params.height > 0 && params.height <= impl.general.maxTextureSize);
				assert(params.depth > 0 && params.depth <= impl.general.maxArrayTextureLayers);
				assert(params.levels > 0 && params.levels <= std::floor(std::log2(std::max(params.width, params.height))) + 1.0);
				assert(params.samples > 0 && params.samples <= impl.general.maxSamples);

				_params.width = params.width;
				_params.height = params.height;
				_params.depth = params.depth;
				_params.levels = params.levels;
				_params.samples = params.samples;
				_params.fixedSampleLocations = params.fixedSampleLocations;

				glTextureStorage3DMultisample(_texture, _params.samples, internalFormatGL, _params.width, _params.height, _params.depth, _params.fixedSampleLocations);

				break;
			}
			default:
			{
				assert(false);
				break;
			}
		}

		_newTextureParameters();
	}

	void Texture::update(const TextureUpdateParams& params)
	{
		assert(isValid());
		assert((params.data == nullptr) != (params.bufferData == nullptr));

		const uint32_t formatGL = _spl::textureFormatToGLenum(params.dataFormat);
		const uint32_t dataTypeGL = _spl::textureDataTypeToGLenum(params.dataType);

		const void* data = params.data;
		if (params.bufferData)
		{
			Buffer::bind(*params.bufferData, BufferTarget::PixelUnpack);
			data = reinterpret_cast<void*>(params.bufferOffset);
		}
		else
		{
			Buffer::unbind(BufferTarget::PixelUnpack);
		}

		switch (_params.target)
		{
			case TextureTarget::Texture1D:
			{
				assert(params.level < _params.levels);
				assert(params.width > 0 && params.xOffset + params.width <= _params.width);

				glTextureSubImage1D(_texture, params.level, params.xOffset, params.width, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture2D:
			case TextureTarget::Array1D:
			case TextureTarget::Rectangle:
			{
				assert(params.level < _params.levels);
				assert(params.width > 0 && params.xOffset + params.width <= _params.width);
				assert(params.height > 0 && params.yOffset + params.height <= _params.height);

				glTextureSubImage2D(_texture, params.level, params.xOffset, params.yOffset, params.width, params.height, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Texture3D:
			case TextureTarget::Array2D:
			case TextureTarget::CubeMap:
			case TextureTarget::CubeMapArray:
			{
				assert(params.level < _params.levels);
				assert(params.width > 0 && params.xOffset + params.width <= _params.width);
				assert(params.height > 0 && params.yOffset + params.height <= _params.height);
				assert(params.depth > 0 && params.zOffset + params.depth <= _params.depth);

				glTextureSubImage3D(_texture, params.level, params.xOffset, params.yOffset, params.zOffset, params.width, params.height, params.depth, formatGL, dataTypeGL, data);

				break;
			}
			case TextureTarget::Buffer:
			case TextureTarget::Multisample2D:
			case TextureTarget::Multisample2DArray:
			{
				assert(false);	// These textures cannot be updated this way.
				break;
			}
			default:
			{
				assert(false);
				break;
			}
		}

		// TODO: Instead of this, restore the buffer that was here before
		if (params.bufferData)
		{
			Buffer::unbind(BufferTarget::PixelUnpack);
		}
	}

	void Texture::destroy()
	{
		if (_texture != 0)
		{
			Context::getCurrentContext()->_unbindTexture(this);

			glDeleteTextures(1, &_texture);

			_texture = 0;
			_params = {};
		}
	}

	void Texture::setBorderColor(float r, float g, float b, float a)
	{

	}

	void Texture::setCompareMode(TextureCompareMode compareMode)
	{

	}

	void Texture::setCompareFunc(CompareFunc compareFunc)
	{

	}

	void Texture::setMinLod(float lod)
	{

	}

	void Texture::setMaxLod(float lod)
	{

	}

	void Texture::setLodBias(float bias)
	{

	}

	void Texture::setMinFiltering(TextureFiltering filtering)
	{

	}

	void Texture::setMagFiltering(TextureFiltering filtering)
	{

	}

	void Texture::setMaxAnisotropy(float maxAnisotropy)
	{

	}

	void Texture::setWrappingS(TextureWrapping wrap)
	{

	}

	void Texture::setWrappingT(TextureWrapping wrap)
	{

	}

	void Texture::setWrappingR(TextureWrapping wrap)
	{

	}

	bool Texture::isValid() const
	{
		return _texture != 0;
	}

	uint32_t Texture::getHandle() const
	{
		return _texture;
	}

	const TextureCreationParams& Texture::getCreationParams() const
	{
		return _params;
	}

	const scp::f32vec4& Texture::getBorderColor() const
	{
		return _borderColor;
	}

	TextureCompareMode Texture::getCompareMode() const
	{
		return _compareMode;
	}

	CompareFunc Texture::getCompareFunc() const
	{
		return _compareFunc;
	}

	float Texture::getMinLod() const
	{
		return _minLod;
	}

	float Texture::getMaxLod() const
	{
		return _maxLod;
	}

	float Texture::getLodBias() const
	{
		return _lodBias;
	}

	TextureFiltering Texture::getMinFiltering() const
	{
		return _minFilter;
	}

	TextureFiltering Texture::getMagFiltering() const
	{
		return _magFilter;
	}

	float Texture::getMaxAnisotropy() const
	{
		return _maxAnisotropy;
	}

	TextureWrapping Texture::getWrappingS() const
	{
		return _sWrap;
	}

	TextureWrapping Texture::getWrappingT() const
	{
		return _tWrap;
	}

	TextureWrapping Texture::getWrappingR() const
	{
		return _rWrap;
	}

	Texture::~Texture()
	{
		destroy();
	}

	void Texture::bind(const Texture& texture, uint32_t textureUnit)
	{
		std::vector<const Texture*>& contextTextures = Context::getCurrentContext()->_state.textureBindings;

		assert(texture.isValid());
		assert(textureUnit < contextTextures.size());

		contextTextures[textureUnit] = &texture;

		glBindTextureUnit(textureUnit, texture._texture);
	}

	void Texture::bind(const Texture* const* textures, uint32_t firstUnit, uint32_t count)
	{
		std::vector<const Texture*>& contextTextures = Context::getCurrentContext()->_state.textureBindings;

		assert(firstUnit + count <= contextTextures.size());

		std::copy_n(textures, count, contextTextures.begin() + firstUnit);

		uint32_t* names = reinterpret_cast<uint32_t*>(alloca(sizeof(uint32_t) * count));
		for (uint32_t i = 0; i < count; ++i)
		{
			if (textures[i] == nullptr)
			{
				names[i] = 0;
			}
			else
			{
				assert(textures[i]->isValid());
				names[i] = textures[i]->_texture;
			}
		}

		glBindTextures(firstUnit, count, names);
	}

	void Texture::unbind(uint32_t textureUnit, uint32_t count)
	{
		std::vector<const Texture*>& contextTextures = Context::getCurrentContext()->_state.textureBindings;

		assert(textureUnit + count <= contextTextures.size());

		std::fill_n(contextTextures.begin() + textureUnit, count, nullptr);

		glBindTextures(textureUnit, count, nullptr);
	}

	void Texture::_newTextureParameters()
	{
		_borderColor = { 0.f, 0.f, 0.f, 0.f };
		_compareMode = TextureCompareMode::None;
		_compareFunc = CompareFunc::LessEqual;
		_minLod = -1000.f;
		_maxLod = 1000.f;
		_lodBias = 0.f;
		_magFilter = TextureFiltering::Linear;
		_maxAnisotropy = 1.f;
		// TODO: base level, max level, depth stencil texture mode, swizzle ?

		if (_params.target == TextureTarget::Rectangle)
		{
			_minFilter = TextureFiltering::Linear;
			_sWrap = TextureWrapping::ClampToEdge;
			_tWrap = TextureWrapping::ClampToEdge;
			_rWrap = TextureWrapping::ClampToEdge;
		}
		else
		{
			_minFilter = TextureFiltering::NearestMipmapLinear;
			_sWrap = TextureWrapping::Repeat;
			_tWrap = TextureWrapping::Repeat;
			_rWrap = TextureWrapping::Repeat;
		}
	}

	void Texture::_loadImageFromFile(const std::filesystem::path& path, TextureInternalFormat internalFormat, ImageLoadInfos& infos)
	{
		switch (internalFormat)
		{
			case TextureInternalFormat::R_u8:					return _loadImageFromFile<TextureInternalFormat::R_u8>(path, infos);
			case TextureInternalFormat::R_i8:					return _loadImageFromFile<TextureInternalFormat::R_i8>(path, infos);
			case TextureInternalFormat::R_nu8:					return _loadImageFromFile<TextureInternalFormat::R_nu8>(path, infos);
			case TextureInternalFormat::R_ni8:					return _loadImageFromFile<TextureInternalFormat::R_ni8>(path, infos);
			case TextureInternalFormat::R_u16:					return _loadImageFromFile<TextureInternalFormat::R_u16>(path, infos);
			case TextureInternalFormat::R_i16:					return _loadImageFromFile<TextureInternalFormat::R_i16>(path, infos);
			case TextureInternalFormat::R_f16:					return _loadImageFromFile<TextureInternalFormat::R_f16>(path, infos);
			case TextureInternalFormat::R_nu16:					return _loadImageFromFile<TextureInternalFormat::R_nu16>(path, infos);
			case TextureInternalFormat::R_ni16:					return _loadImageFromFile<TextureInternalFormat::R_ni16>(path, infos);
			case TextureInternalFormat::R_u32:					return _loadImageFromFile<TextureInternalFormat::R_u32>(path, infos);
			case TextureInternalFormat::R_i32:					return _loadImageFromFile<TextureInternalFormat::R_i32>(path, infos);
			case TextureInternalFormat::R_f32:					return _loadImageFromFile<TextureInternalFormat::R_f32>(path, infos);
			case TextureInternalFormat::RG_u8:					return _loadImageFromFile<TextureInternalFormat::RG_u8>(path, infos);
			case TextureInternalFormat::RG_i8:					return _loadImageFromFile<TextureInternalFormat::RG_i8>(path, infos);
			case TextureInternalFormat::RG_nu8:					return _loadImageFromFile<TextureInternalFormat::RG_nu8>(path, infos);
			case TextureInternalFormat::RG_ni8:					return _loadImageFromFile<TextureInternalFormat::RG_ni8>(path, infos);
			case TextureInternalFormat::RG_u16:					return _loadImageFromFile<TextureInternalFormat::RG_u16>(path, infos);
			case TextureInternalFormat::RG_i16:					return _loadImageFromFile<TextureInternalFormat::RG_i16>(path, infos);
			case TextureInternalFormat::RG_f16:					return _loadImageFromFile<TextureInternalFormat::RG_f16>(path, infos);
			case TextureInternalFormat::RG_nu16:				return _loadImageFromFile<TextureInternalFormat::RG_nu16>(path, infos);
			case TextureInternalFormat::RG_ni16:				return _loadImageFromFile<TextureInternalFormat::RG_ni16>(path, infos);
			case TextureInternalFormat::RG_u32:					return _loadImageFromFile<TextureInternalFormat::RG_u32>(path, infos);
			case TextureInternalFormat::RG_i32:					return _loadImageFromFile<TextureInternalFormat::RG_i32>(path, infos);
			case TextureInternalFormat::RG_f32:					return _loadImageFromFile<TextureInternalFormat::RG_f32>(path, infos);
			case TextureInternalFormat::RGB_u8:					return _loadImageFromFile<TextureInternalFormat::RGB_u8>(path, infos);
			case TextureInternalFormat::RGB_i8:					return _loadImageFromFile<TextureInternalFormat::RGB_i8>(path, infos);
			case TextureInternalFormat::RGB_nu8:				return _loadImageFromFile<TextureInternalFormat::RGB_nu8>(path, infos);
			case TextureInternalFormat::RGB_ni8:				return _loadImageFromFile<TextureInternalFormat::RGB_ni8>(path, infos);
			case TextureInternalFormat::RGB_u16:				return _loadImageFromFile<TextureInternalFormat::RGB_u16>(path, infos);
			case TextureInternalFormat::RGB_i16:				return _loadImageFromFile<TextureInternalFormat::RGB_i16>(path, infos);
			case TextureInternalFormat::RGB_f16:				return _loadImageFromFile<TextureInternalFormat::RGB_f16>(path, infos);
			case TextureInternalFormat::RGB_nu16:				return _loadImageFromFile<TextureInternalFormat::RGB_nu16>(path, infos);
			case TextureInternalFormat::RGB_ni16:				return _loadImageFromFile<TextureInternalFormat::RGB_ni16>(path, infos);
			case TextureInternalFormat::RGB_u32:				return _loadImageFromFile<TextureInternalFormat::RGB_u32>(path, infos);
			case TextureInternalFormat::RGB_i32:				return _loadImageFromFile<TextureInternalFormat::RGB_i32>(path, infos);
			case TextureInternalFormat::RGB_f32:				return _loadImageFromFile<TextureInternalFormat::RGB_f32>(path, infos);
			case TextureInternalFormat::RGBA_u8:				return _loadImageFromFile<TextureInternalFormat::RGBA_u8>(path, infos);
			case TextureInternalFormat::RGBA_i8:				return _loadImageFromFile<TextureInternalFormat::RGBA_i8>(path, infos);
			case TextureInternalFormat::RGBA_nu8:				return _loadImageFromFile<TextureInternalFormat::RGBA_nu8>(path, infos);
			case TextureInternalFormat::RGBA_ni8:				return _loadImageFromFile<TextureInternalFormat::RGBA_ni8>(path, infos);
			case TextureInternalFormat::RGBA_u16:				return _loadImageFromFile<TextureInternalFormat::RGBA_u16>(path, infos);
			case TextureInternalFormat::RGBA_i16:				return _loadImageFromFile<TextureInternalFormat::RGBA_i16>(path, infos);
			case TextureInternalFormat::RGBA_f16:				return _loadImageFromFile<TextureInternalFormat::RGBA_f16>(path, infos);
			case TextureInternalFormat::RGBA_nu16:				return _loadImageFromFile<TextureInternalFormat::RGBA_nu16>(path, infos);
			case TextureInternalFormat::RGBA_ni16:				return _loadImageFromFile<TextureInternalFormat::RGBA_ni16>(path, infos);
			case TextureInternalFormat::RGBA_u32:				return _loadImageFromFile<TextureInternalFormat::RGBA_u32>(path, infos);
			case TextureInternalFormat::RGBA_i32:				return _loadImageFromFile<TextureInternalFormat::RGBA_i32>(path, infos);
			case TextureInternalFormat::RGBA_f32:				return _loadImageFromFile<TextureInternalFormat::RGBA_f32>(path, infos);
			case TextureInternalFormat::Depth_nu16:				return _loadImageFromFile<TextureInternalFormat::Depth_nu16>(path, infos);
			case TextureInternalFormat::Depth_nu24:				return _loadImageFromFile<TextureInternalFormat::Depth_nu24>(path, infos);
			case TextureInternalFormat::Depth_nu32:				return _loadImageFromFile<TextureInternalFormat::Depth_nu32>(path, infos);
			case TextureInternalFormat::Depth_f32:				return _loadImageFromFile<TextureInternalFormat::Depth_f32>(path, infos);
			case TextureInternalFormat::Stencil_u1:				return _loadImageFromFile<TextureInternalFormat::Stencil_u1>(path, infos);
			case TextureInternalFormat::Stencil_u4:				return _loadImageFromFile<TextureInternalFormat::Stencil_u4>(path, infos);
			case TextureInternalFormat::Stencil_u8:				return _loadImageFromFile<TextureInternalFormat::Stencil_u8>(path, infos);
			case TextureInternalFormat::Stencil_u16:			return _loadImageFromFile<TextureInternalFormat::Stencil_u16>(path, infos);
			case TextureInternalFormat::Depth_nu24_Stencil_u8:	return _loadImageFromFile<TextureInternalFormat::Depth_nu24_Stencil_u8>(path, infos);
			case TextureInternalFormat::Depth_f32_Stencil_u8:	return _loadImageFromFile<TextureInternalFormat::Depth_f32_Stencil_u8>(path, infos);
			case TextureInternalFormat::RGB_nu4:				return _loadImageFromFile<TextureInternalFormat::RGB_nu4>(path, infos);
			case TextureInternalFormat::RGB_nu5:				return _loadImageFromFile<TextureInternalFormat::RGB_nu5>(path, infos);
			case TextureInternalFormat::RGB_nu10:				return _loadImageFromFile<TextureInternalFormat::RGB_nu10>(path, infos);
			case TextureInternalFormat::RGB_nu12:				return _loadImageFromFile<TextureInternalFormat::RGB_nu12>(path, infos);
			case TextureInternalFormat::R_nu3_G_nu3_B_nu2:		return _loadImageFromFile<TextureInternalFormat::R_nu3_G_nu3_B_nu2>(path, infos);
			case TextureInternalFormat::R_nu5_G_nu6_B_nu5:		return _loadImageFromFile<TextureInternalFormat::R_nu5_G_nu6_B_nu5>(path, infos);
			case TextureInternalFormat::R_f11_G_f11_B_f10:		return _loadImageFromFile<TextureInternalFormat::R_f11_G_f11_B_f10>(path, infos);
			case TextureInternalFormat::RGBA_nu2:				return _loadImageFromFile<TextureInternalFormat::RGBA_nu2>(path, infos);
			case TextureInternalFormat::RGBA_nu4:				return _loadImageFromFile<TextureInternalFormat::RGBA_nu4>(path, infos);
			case TextureInternalFormat::RGBA_nu12:				return _loadImageFromFile<TextureInternalFormat::RGBA_nu12>(path, infos);
			case TextureInternalFormat::RGB_nu5_A_nu1:			return _loadImageFromFile<TextureInternalFormat::RGB_nu5_A_nu1>(path, infos);
			case TextureInternalFormat::RGB_u10_A_u2:			return _loadImageFromFile<TextureInternalFormat::RGB_u10_A_u2>(path, infos);
			case TextureInternalFormat::RGB_nu10_A_nu2:			return _loadImageFromFile<TextureInternalFormat::RGB_nu10_A_nu2>(path, infos);
			default: assert(false);
		}
	}
}
