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
	Sampler::Sampler() :
		_sampler(0),
		_borderColor(0.f, 0.f, 0.f, 0.f),
		_compareMode(TextureCompareMode::None),
		_compareFunc(CompareFunc::LessEqual),
		_minLod(-1000.f),
		_maxLod(1000.f),
		_lodBias(0.f),
		_minFilter(TextureFiltering::NearestMipmapLinear),
		_magFilter(TextureFiltering::Linear),
		_maxAnisotropy(1.f),
		_sWrap(TextureWrapping::Repeat),
		_tWrap(TextureWrapping::Repeat),
		_rWrap(TextureWrapping::Repeat)
	{
		glCreateSamplers(1, &_sampler);
	}

	Sampler::Sampler(const Sampler& sampler) : Sampler()
	{
		_copyFrom(sampler);
	}

	Sampler::Sampler(Sampler&& sampler) :
		_sampler(0)
	{
		_moveFrom(std::move(sampler));
	}

	Sampler& Sampler::operator=(const Sampler& sampler)
	{
		assert(isValid());

		_copyFrom(sampler);
		return *this;
	}

	Sampler& Sampler::operator=(Sampler&& sampler)
	{
		_moveFrom(std::move(sampler));
		return *this;
	}

	void Sampler::setBorderColor(float r, float g, float b, float a)
	{
		assert(isValid());

		_borderColor.x = r;
		_borderColor.y = g;
		_borderColor.z = b;
		_borderColor.w = a;
		glSamplerParameterfv(_sampler, GL_TEXTURE_BORDER_COLOR, reinterpret_cast<const float*>(&_borderColor));
	}

	void Sampler::setCompareMode(TextureCompareMode compareMode)
	{
		assert(isValid());

		_compareMode = compareMode;
		glSamplerParameteri(_sampler, GL_TEXTURE_COMPARE_MODE, _spl::textureCompareModeToGLenum(_compareMode));
	}

	void Sampler::setCompareFunc(CompareFunc compareFunc)
	{
		assert(isValid());

		_compareFunc = compareFunc;
		glSamplerParameteri(_sampler, GL_TEXTURE_COMPARE_FUNC, _spl::compareFuncToGLenum(_compareFunc));
	}

	void Sampler::setMinLod(float lod)
	{
		assert(isValid());

		_minLod = lod;
		glSamplerParameterf(_sampler, GL_TEXTURE_MIN_LOD, _minLod);
	}

	void Sampler::setMaxLod(float lod)
	{
		assert(isValid());

		_maxLod = lod;
		glSamplerParameterf(_sampler, GL_TEXTURE_MAX_LOD, _maxLod);
	}

	void Sampler::setLodBias(float bias)
	{
		assert(isValid());

		_lodBias = bias;
		glSamplerParameterf(_sampler, GL_TEXTURE_LOD_BIAS, _lodBias);
	}

	void Sampler::setMinFiltering(TextureFiltering filtering)
	{
		assert(isValid());

		_minFilter = filtering;
		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, _spl::textureFilteringToGLenum(_minFilter));
	}

	void Sampler::setMagFiltering(TextureFiltering filtering)
	{
		assert(isValid());

		_magFilter = filtering;
		glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, _spl::textureFilteringToGLenum(_magFilter));
	}

	void Sampler::setMaxAnisotropy(float maxAnisostropy)
	{
		assert(isValid());
		assert(maxAnisostropy >= 1.f);

		_maxAnisotropy = maxAnisostropy;
		glSamplerParameterf(_sampler, GL_TEXTURE_MAX_ANISOTROPY, _maxAnisotropy);
	}

	void Sampler::setWrappingS(TextureWrapping wrap)
	{
		assert(isValid());

		_sWrap = wrap;
		glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_S, _spl::textureWrappingToGLenum(_sWrap));
	}

	void Sampler::setWrappingT(TextureWrapping wrap)
	{
		assert(isValid());

		_tWrap = wrap;
		glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_T, _spl::textureWrappingToGLenum(_tWrap));
	}

	void Sampler::setWrappingR(TextureWrapping wrap)
	{
		assert(isValid());

		_rWrap = wrap;
		glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_R, _spl::textureWrappingToGLenum(_rWrap));
	}

	bool Sampler::isValid() const
	{
		return _sampler != 0;
	}

	const scp::f32vec4& Sampler::getBorderColor() const
	{
		return _borderColor;
	}

	TextureCompareMode Sampler::getCompareMode() const
	{
		return _compareMode;
	}

	CompareFunc Sampler::getCompareFunc() const
	{
		return _compareFunc;
	}

	float Sampler::getMinLod() const
	{
		return _minLod;
	}

	float Sampler::getMaxLod() const
	{
		return _maxLod;
	}

	float Sampler::getLodBias() const
	{
		return _lodBias;
	}

	TextureFiltering Sampler::getMinFiltering() const
	{
		return _minFilter;
	}

	TextureFiltering Sampler::getMagFiltering() const
	{
		return _magFilter;
	}

	float Sampler::getMaxAnisotropy() const
	{
		return _maxAnisotropy;
	}

	TextureWrapping Sampler::getWrappingS() const
	{
		return _sWrap;
	}

	TextureWrapping Sampler::getWrappingT() const
	{
		return _tWrap;
	}

	TextureWrapping Sampler::getWrappingR() const
	{
		return _rWrap;
	}

	Sampler::~Sampler()
	{
		_destroy();
	}

	void Sampler::bind(const Sampler* sampler, uint32_t textureUnit)
	{
		std::vector<const Sampler*>& contextSamplers = Context::getCurrentContext()->_state.samplerBindings;

		assert(sampler == nullptr || sampler->isValid());
		assert(textureUnit < contextSamplers.size());

		contextSamplers[textureUnit] = sampler;

		if (sampler)
		{
			glBindSampler(textureUnit, sampler->_sampler);
		}
		else
		{
			glBindSampler(textureUnit, 0);
		}
	}

	void Sampler::bind(const Sampler* const* samplers, uint32_t firstUnit, uint32_t count)
	{
		std::vector<const Sampler*>& contextSamplers = Context::getCurrentContext()->_state.samplerBindings;

		assert(firstUnit + count <= contextSamplers.size());

		if (samplers == nullptr)
		{
			std::fill_n(contextSamplers.begin() + firstUnit, count, nullptr);

			glBindSamplers(firstUnit, count, nullptr);
		}
		else
		{
			std::copy_n(samplers, count, contextSamplers.begin() + firstUnit);

			uint32_t* names = reinterpret_cast<uint32_t*>(alloca(sizeof(uint32_t) * count));
			for (uint32_t i = 0; i < count; ++i)
			{
				if (samplers[i] == nullptr)
				{
					names[i] = 0;
				}
				else
				{
					assert(samplers[i]->isValid());
					names[i] = samplers[i]->_sampler;
				}
			}

			glBindSamplers(firstUnit, count, names);
		}
	}

	void Sampler::_copyFrom(const Sampler& sampler)
	{
		setBorderColor(sampler._borderColor.x, sampler._borderColor.y, sampler._borderColor.z, sampler._borderColor.w);
		setCompareMode(sampler._compareMode);
		setCompareFunc(sampler._compareFunc);
		setMinLod(sampler._minLod);
		setMaxLod(sampler._maxLod);
		setLodBias(sampler._lodBias);
		setMinFiltering(sampler._minFilter);
		setMagFiltering(sampler._magFilter);
		setMaxAnisotropy(sampler._maxAnisotropy);
		setWrappingS(sampler._sWrap);
		setWrappingT(sampler._tWrap);
		setWrappingR(sampler._rWrap);
	}

	void Sampler::_moveFrom(Sampler&& sampler)
	{
		_destroy();

		_sampler = sampler._sampler;
		_borderColor = sampler._borderColor;
		_compareMode = sampler._compareMode;
		_compareFunc = sampler._compareFunc;
		_minLod = sampler._minLod;
		_maxLod = sampler._maxLod;
		_lodBias = sampler._lodBias;
		_minFilter = sampler._minFilter;
		_magFilter = sampler._magFilter;
		_maxAnisotropy = sampler._maxAnisotropy;
		_sWrap = sampler._sWrap;
		_tWrap = sampler._tWrap;
		_rWrap = sampler._rWrap;

		sampler._sampler = 0;

		Context* context = Context::getCurrentContext();
		for (uint8_t i = 0; i < context->_state.samplerBindings.size(); ++i)
		{
			if (context->_state.samplerBindings[i] == &sampler)
			{
				context->_state.samplerBindings[i] = this;
			}
		}
	}

	void Sampler::_destroy()
	{
		if (_sampler != 0)
		{
			Context::getCurrentContext()->_unbindSampler(this);
			glDeleteSamplers(1, &_sampler);
			_sampler = 0;
		}
	}
}
