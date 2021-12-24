#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Functions and classes for OpenGL buffer manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Buffer.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates Buffer
	/// \enum BufferTarget
	/// \brief Encapsulation of OpenGL buffer targets. Specifies the purpose of a Buffer.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum class BufferTarget
	{
		Array,				///< TODO
		AtomicCounter,		///< TODO
		CopyRead,			///< TODO
		CopyWrite,			///< TODO
		DispatchIndirect,	///< TODO
		DrawIndirect,		///< TODO
		ElementArray,		///< TODO
		Parameter,			///< TODO
		PixelPack,			///< TODO
		PixelUnpack,		///< TODO
		Query,				///< TODO
		ShaderStorage,		///< TODO
		Texture,			///< TODO
		TransformFeedback,	///< TODO
		Uniform
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \relates Buffer
	/// \enum BufferUsage
	/// \brief Encapsulation of OpenGL buffer usages.
	/// 
	/// There are two ways of specifying the properties of an OpenGL buffer: with usage or with storage flags.
	/// For storage flags, see enum BufferStorageFlags::Flags.
	/// 
	/// A usage is an implicit declaration of the properties of an OpenGL buffer. To be clear: you don't know how it is
	/// optimized, but the driver will optimize based on your intents declared with the usage. However, when using
	/// BufferUsage, any operation on buffer remains possible, there are no restrictions on read/write operations like
	/// there could be with buffer storage flags.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum class BufferUsage
	{
		Undefined,		///< Invalid buffer usage. Used for error detection purpose, and to know if a buffer is created using BufferUsage or BufferStorageFlags.
		StreamDraw,		///< The buffer is filled by the application and read on GPU. The data is used once between every update.
		StreamRead,		///< The buffer is filled on GPU and read by the application. The data is used once between every update.
		StreamCopy,		///< The buffer is filled and read on GPU. The data is used once between every update.
		StaticDraw,		///< The buffer is filled by the application and read on GPU. The data is updated once and used many times.
		StaticRead,		///< The buffer is filled on GPU and read by the application. The data is updated once and used many times.
		StaticCopy,		///< The buffer is filled and read on GPU. The data is updated once and used many times.
		DynamicDraw,	///< The buffer is filled by the application and read on GPU. The data is used many times between every update.
		DynamicRead,	///< The buffer is filled on GPU and read by the application. The data is used many times between every update.
		DynamicCopy		///< The buffer is filled and read on GPU. The data is used many times between every update.
	};

	namespace BufferStorageFlags
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \relates Buffer
		/// \enum Flags
		/// \brief Encapsulation of OpenGL buffer storage flags.
		/// 
		/// There are two ways of specifying the properties of an OpenGL buffer: with usage or with storage flags.
		/// For usage, see enum class BufferUsage.
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		enum Flags
		{
			None = 0,					///< TODO
			DynamicStorage = 1 << 0,	///< TODO
			MapRead = 1 << 1,			///< TODO
			MapWrite = 1 << 2,			///< TODO
			MapPersistent = 1 << 3,		///< TODO
			MapCoherent = 1 << 4,		///< TODO
			ClientStorage = 1 << 5		///< TODO
		};
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \ingroup Core
	/// \class Buffer
	/// \brief Class for manipulating OpenGL buffer almost directly.
	/// 
	/// A buffer is an encapsulation of an OpenGL buffer object. It only implements usual OpenGL operations on buffers
	/// (creation, destruction, copy, update and mapping) nothing more or less.
	/// For instance this class does not modify storage flags/usage or resize buffers if not explicitely told to.
	/// 
	/// However, the goal is to make all the operations available for any type of buffer (except for mapping if bad
	/// storage flags are specified) and to check for buffer types and size during operations in debug mode, while
	/// being very performant in release mode.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Buffer
	{
		public:

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Default constructor. No OpenGL buffer is created.
			///
			/// This constructor is thus equivalent to create an invalid buffer, which can later be created with
			/// createNew, copyFrom or moveFrom.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			Buffer();
			Buffer(uint32_t size, BufferUsage usage, const void* data = nullptr);				///< Constructs a buffer from usage. See method `createNew`.
			Buffer(uint32_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);	///< Constructs a buffer from storage flags. See method `createNew`.
			Buffer(const Buffer& buffer);														///< Copies constructor. Equivalent to calling `copyFrom` on and invalid buffer.
			Buffer(Buffer&& buffer);															///< Moves constructor. Equivalent to calling `moveFrom` on and invalid buffer.

			Buffer& operator=(const Buffer& buffer);	///< Copy assign operator. See method `copyFrom`.
			Buffer& operator=(Buffer&& buffer);			///< Move assign operator. See method `moveFrom`.

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Creates a new buffer that replaces the current one.
			///
			/// If the buffer was valid, it is destroyed and its data is lost.
			/// 
			/// \param size		Size of the new buffer.
			/// \param usage	See enum class BufferUsage.
			/// \param data		If not `nullptr`, fill the buffer with `data`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void createNew(uint32_t size, BufferUsage usage, const void* data = nullptr);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Creates a new buffer that replaces the current one.
			///
			/// If the buffer was valid, it is destroyed and its data is lost.
			/// 
			/// \param size		Size of the new buffer.
			/// \param flags	See enum BufferStorageFlags::Flags.
			/// \param data		If not `nullptr`, fill the buffer with `data`.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void createNew(uint32_t size, BufferStorageFlags::Flags flags, const void* data = nullptr);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Copies a buffer into another.
			///
			/// If the current buffer is invalid, this method creates a new buffer with the same size and flags as
			/// `buffer` and copy `buffer` into it.
			/// 
			/// If the current buffer is valid, only the content of `buffer` is copied, and only on the first
			/// `buffer.getSize()` bytes.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void copyFrom(const Buffer& buffer);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Moves a buffer into another.
			///
			/// Destroyes the current OpenGL buffer it is valid and replace it with `buffer`'s OpenGL buffer.
			/// 
			/// Warning: This function changes the size and flags of the current buffer.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void moveFrom(Buffer&& buffer);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Updates the current buffer content from application's memory.
			///
			/// Warning: Depending on the type of buffer, this function might have huge performances disparities.
			/// 
			/// \param data			Pointer to application's memory data.
			/// \param size			Number of bytes to update in the buffer.
			/// \param dstOffset	Offset for data to be copied in.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void update(const void* data, uint32_t size, uint32_t dstOffset = 0);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Updates the current buffer content from another buffer.
			/// 
			/// \param data			Buffer to copy content from.
			/// \param size			Number of bytes to update in the buffer.
			/// \param dstOffset	Offset for data to be copied in.
			/// \param srcOffset	Offset for data to be copied from.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void update(const Buffer& data, uint32_t size, uint32_t dstOffset = 0, uint32_t srcOffset = 0);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \brief Destroy underlying OpenGL buffer and makes the buffer invalid.
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			void destroy();

			// TODO: mapping

			uint32_t getHandle() const;							///< Returns underlying OpenGL buffer name.
			uint32_t getSize() const;							///< Returns buffer size.
			BufferUsage getUsage() const;						///< Returns usage associated to the buffer or BufferUsage::Undefined if it was created with storage flags.
			BufferStorageFlags::Flags getStorageFlags() const;	///< Returns storage flags associated to the buffer or 0 if it was created with usage.
			bool isValid() const;								///< Returns true if an OpenGL buffer is associated with the instance and is in valid state.

			static void bind(const Buffer& buffer, BufferTarget target);	///< Binds the buffer to a target in the OpenGL state machine.
			static void unbind(BufferTarget target);						///< Unbinds the target in the OpenGL state machine.

			~Buffer();

		private:

			uint32_t _buffer;					///< OpenGL buffer name.
			uint32_t _size;						///< Buffer size.
			BufferUsage _usage;					///< Usage associated to the buffer, or BufferUsage::Undefined if created with storage flags.
			BufferStorageFlags::Flags _flags;	///< Storage flags associated to the buffer, or 0 if created with usage.

	};
}
